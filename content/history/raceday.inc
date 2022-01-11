<?php
  if (empty($_GET["year"])) {
    // We should have been redirected into racedaylist.inc, not here.  What happened?
    die("Ooops, no year specified!");
  }

  $year = $_GET['year'] * 1;

  // orders by place, then by prelim time, then whether DQed
  $resQuery = "SELECT nullif(place, 0) place,
                      concat(shortname, ' ', team) AS team,
                      e.entryid AS entryid,
                      b.name AS buggy,
                      case when prelim > 0 then concat(floor(prelim / 60), ':', right(concat('0',format(prelim % 60, 2)),5)) else NULL end prelim,
                      case when reroll > 0 then concat(floor(reroll / 60), ':', right(concat('0',format(reroll % 60, 2)),5)) else NULL end reroll,
                      case when final > 0 then concat(floor(final / 60), ':', right(concat('0',format(final % 60, 2)),5)) else NULL end final,
                      case when finalreroll > 0 then concat(floor(finalreroll / 60), ':', right(concat('0',format(finalreroll % 60, 2)),5)) else NULL end finalreroll,
                      nullif(dq,'0') dq,
                      e.note
                 FROM hist_raceentries e
                 LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                 LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                 WHERE year = ? AND class = ?
                 ORDER BY place=0, place, prelim=0, prelim, DQ;";

  $mensResults = dbBoundQuery("history", $resQuery, "ds", $year, 'M');
  $womensResults = dbBoundQuery("history", $resQuery, "ds", $year, 'W');

  // Getting heats is a mess, rather than issue a ton of queries, we fetch all the relevant heats
  // and then split them by prelim/final/reroll/etc locally.
  //
  // We do not fetch exhibitions -- (class == E).  This is only useful if we can link them to videos,
  // so if we start to do videos, remember to fetch exhibitions as well and deal with them!
  //
  // For sanity sake on this query, we only return the time seconds value, and we'll convert it using
  // the displayTime() utility function later.
  //
  // Heats data is SUPER GROSS, especially because the way rerolls can run off the rails and need to be
  // done "just in time" in many cases.  This leads to "isfinals" in the heats table meaning "happened on finals
  // day", which doesn't match how we keep times in the raceentries table where finalreroll is
  // "reroll earned for final roll".  Thus, many but not all of the "isfinals" "isreroll" times are _actually_
  // (prelim) reroll times.
  //
  // So, in the case of a final reroll, we are going to use finalreroll if we have it, otherwise use
  // reroll.  This is not perfect, but works in almost 99% of the cases.
  //
  // Note that we only fetch exhibitions if there is a video to go with them, since we have nothing to display otherwise.
  $heatQuery = "SELECT number, isfinals, isreroll, h.class,
      concat(o1.shortname, ' ', e1.team) AS team1, e1.entryid AS teamid1, e1.DQ AS dq1,
      case when isfinals = 0 and isreroll = 0 then e1.prelim
           when isfinals = 0 and isreroll = 1 then e1.reroll
           when isfinals = 1 and isreroll = 0 then e1.final
           when isfinals = 1 and isreroll = 1 and e1.finalreroll > 0 then e1.finalreroll
           when isfinals = 1 and isreroll = 1 and e1.finalreroll <= 0 then e1.reroll end AS timesec1,
      concat(o2.shortname, ' ', e2.team) AS team2, e2.entryid AS teamid2, e2.DQ AS dq2,
      case when isfinals = 0 and isreroll = 0 then e2.prelim
           when isfinals = 0 and isreroll = 1 then e2.reroll
           when isfinals = 1 and isreroll = 0 then e2.final
           when isfinals = 1 and isreroll = 1 and e2.finalreroll > 0 then e2.finalreroll
           when isfinals = 1 and isreroll = 1 and e2.finalreroll <= 0 then e2.reroll end AS timesec2,
      concat(o3.shortname, ' ', e3.team) AS team3, e3.entryid AS teamid3, e3.DQ AS dq3,
      case when isfinals = 0 and isreroll = 0 then e3.prelim
           when isfinals = 0 and isreroll = 1 then e3.reroll
           when isfinals = 1 and isreroll = 0 then e3.final
           when isfinals = 1 and isreroll = 1 and e3.finalreroll > 0 then e3.finalreroll
           when isfinals = 1 and isreroll = 1 and e3.finalreroll <= 0 then e3.reroll end AS timesec3,
      h.note, v.youtubeid AS video_youtubeid, v.title AS video_title, v.urlkey AS video_urlkey
    FROM hist_heats h
    LEFT JOIN hist_raceentries e1 on concat(h.year, '.', Lane1) = e1.entryid LEFT JOIN hist_orgs o1 on e1.orgid = o1.orgid
    LEFT JOIN hist_raceentries e2 on concat(h.year, '.', Lane2) = e2.entryid LEFT JOIN hist_orgs o2 on e2.orgid = o2.orgid
    LEFT JOIN hist_raceentries e3 on concat(h.year, '.', Lane3) = e3.entryid LEFT JOIN hist_orgs o3 on e3.orgid = o3.orgid
    LEFT JOIN video v on h.heatid = CAST(v.heatid as CHAR)
    WHERE h.year = ? AND (h.class != 'E' OR v.youtubeid IS NOT NULL)
    ORDER BY h.class,isfinals,isreroll,number ASC;";

  $heatData = dbBoundQuery("history", $heatQuery, "d", $year);

  $pheatsArr = array();
  $fheatsArr = array();

  // Split up the heat data into class/reroll/prelim/final buckets.
  // We are assuming the sort order is maintained here.
  while ($h = $heatData->fetch_assoc()) {
    $heattype = $h["class"] . $h["isreroll"];
    if ($h["isfinals"] == 1) {
      $fheatsArr[$heattype][$h["number"]] = $h;
    } else {
      $pheatsArr[$heattype][$h["number"]] = $h;
    }
  }

  function displayResults($resultList) {
    global $racedayList;

    echo("<div class=\"table-responsive\"><table class=\"table\">");
    echo("<thead><tr><th>Place</th><th>Team</th><th>Prelims Time</th><th>Prelim Reroll</th><th>Finals Time</th><th>Finals Reroll</th><th>Notes</th></tr></thead>");
    echo("<tbody>");

    while ($r = $resultList->fetch_assoc()) {
      echo("<tr>");
      if ($resultList->num_rows == 1 &&
          empty($r["prelim"]) && empty($r["reroll"]) && empty($r["final"]) && empty($r["finalreroll"])) {
        // One entry, no times.  This was a year that didn't happen.  Post the reason.
        echo("<td colspan=\"7\" class=\"text-center\">".$r["note"]."</td>");
      } else {
        echo("<td>".$r["place"]."</td>");
        echo("<td><a href=\"/history/team/".$r["entryid"]."\">".$r["team"]."</a></td>");
        echo("<td>".$r["prelim"]."</td>");
        echo("<td>".$r["reroll"]."</td>");
        echo("<td>".$r["final"]."</td>");
        echo("<td>".$r["finalreroll"]."</td>");
        $notes = $r["note"];
        if (!empty($r["dq"])) {
          if (!empty($notes)) {
            $notes .= "<br>";
          }
          $notes .= "DQ: ".$r["dq"];
        }
        echo("<td>".$notes."</td>");
        echo("</tr>");
      }
    }
    echo("</tbody></table></div>");
  }

  function displayHeats($heatArr){
    // We put womens first on the heats display because historically heats
    // for womens run earlier in the morning.  This is also why Exhibitions
    // are on top.
    $heattypes = array("E0","W0","W1","M0","M1");
    $heattypelabels = array("M0"=>"Men's",
                            "M1"=>"Men's Rerolls",
                            "W0"=>"Women's",
                            "W1"=>"Women's Rerolls",
                            "E0"=>"Exhibitions");
    foreach($heattypes as $type){
      if(isset($heatArr[$type])){
        echo("<h4>".$heattypelabels[$type]."</h4>");
        echo("<div class\"table-responsive\"><table class=\"table\"><thead>");

        if ($type != "E0") {
          // Not Exhibition, Add useful headers.
          echo("<tr><th></th><th></th><th>Lane 1</th><th>Lane 2</th><th>Lane 3</th><th>Notes</th></tr>");
        }

        echo("</thead><tbody>");
        foreach($heatArr[$type] as $heat){
          echo("<tr><td>".$heat["number"]."</td>");

          // TODO: Video Links!
          if (!empty($heat["video_youtubeid"])) {
            $video = array(
              "youtubeid" => $heat["video_youtubeid"],
              "title" => $heat["video_title"],
              "urlkey" => $heat["video_urlkey"]
            );
            echo("<td>");
            include("content/youtubevid.inc");
            echo("</td>");
          } else {
            // No video
            echo("<td></td>");
          }

          if ($type != "E0") {
            // Not Exhibition, Show Lanes
            for($lane = 1; $lane <= 3; $lane++) {
              if (!empty($heat["team".$lane])) {
                echo("<td><a href=\"/history/team/".$heat["teamid".$lane]."\">".$heat["team".$lane]."</a>");
                $time = displayTime($heat["timesec".$lane]);
                if (!empty($time)) {
                  echo("<br />".$time);
                }
                if (!empty($heat["dq".$lane])) {
                  echo("<br /> DQ:".$heat["dq".$lane]);
                }
                echo("</td>");
              } else {
                echo("<td></td>");
              }
            }
            echo("<td>".$heat["note"]."</td>");
          } else {
            // Exhibition that has a video, the only thing really to show is the video title here.
            echo("<td>".$heat["video_title"]."</td>");
          }
          echo("</tr>");
        }
        echo("</tbody></table></div>");
      }
    }
  }

  $prevlink = "";
  $nextlink = "";

  if($year > 1920) {
    $prevlink = "<a href=\"/history/raceday/".($year - 1)."\">&laquo ".($year - 1)."</a>";
  }
  if($year < date("Y")){
    $nextlink = " | <a href=\"/history/raceday/".($year + 1)."\">".($year + 1)." &raquo</a>";
  }
?>

<h1>Raceday <?php echo($year);?></h1>

<div class="my-2">
  <?php echo($prevlink.$nextlink); ?>
</div>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's Results</a>
  </li>
  <?php if ($year >= 1979) { ?>
    <li class="nav-item">
      <a id="womens-tab" href="#tab-womens" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's Results</a>
    </li>
  <?php } ?>
  <?php if(count($pheatsArr)>0) { ?>
    <li class="nav-item">
      <a id="prelimheats-tab" href="#tab-prelimheats" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-prelimheats" aria-selected="false">Prelim Heats</a>
    </li>
  <?php } ?>
  <?php if($year >= 1979 && count($fheatsArr)>0) { ?>
    <li class="nav-item">
      <a id="finalsheats-tab" href="#tab-finalsheats" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-finalsheats" aria-selected="false">Finals Heats</a>
    </li>
  <?php } ?>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayResults($mensResults); ?>
  </div>
  <?php // Don't display womens tab before 1979 (mostly so we render war years properly)
        if ($year >= 1979) { ?>
    <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
      <?php displayResults($womensResults); ?>
    </div>
  <?php } ?>
  <?php if(count($pheatsArr)>0) { ?>
    <div class="tab-pane fade" id="tab-prelimheats" role="tabpanel" aria-labelledby="prelimheats-tab">
      <?php displayHeats($pheatsArr); ?>
    </div>
  <?php } ?>
  <?php if($year >= 1979 && count($fheatsArr)>0) { ?>
    <div class="tab-pane fade" id="tab-finalsheats" role="tabpanel" aria-labelledby="finalsheats-tab">
      <?php displayHeats($fheatsArr); ?>
    </div>
  <?php } ?>
</div>
<?php
