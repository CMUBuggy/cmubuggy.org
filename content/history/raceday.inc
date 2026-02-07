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
                      b.name AS buggyname,
                      b.buggyid AS buggyid,
                      prelim, reroll, final, finalreroll,
                      nullif(dq,'0') dq,
                      e.note
                 FROM hist_raceentries e
                 LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                 LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                 WHERE year = ? AND class = ?
                 ORDER BY place=0, place, prelim=0, prelim, DQ, team;";

  // We could get these all at once instead of 3 different queries and split them locally while maintaining the sort order,
  // but this is slightly simpler to write/understand.
  //
  // Also, if we decide to use a single connection on this page, we can reuse the prepared statement here.
  $mensResults = dbBoundQuery($HISTORY_DATABASE, $resQuery, "ds", $year, 'M');
  $womensResults = dbBoundQuery($HISTORY_DATABASE, $resQuery, "ds", $year, 'W');
  $allgenderResults = dbBoundQuery($HISTORY_DATABASE, $resQuery, "ds", $year, 'N');
  $roboticResults = dbBoundQuery($HISTORY_DATABASE, $resQuery, "ds", $year, 'R');

  // Getting heats is a mess, rather than issue a ton of queries, we fetch all the relevant heats
  // and then split them by prelim/final/reroll/etc locally.
  //
  // We do not fetch exhibitions -- (class == E) unless they also have a video to link to, since
  // exhibitions otherwise have no useful data to share.  So, if you want an exhibition to show,
  // it needs to have a linked video (and, ideally a title in the video table entry)
  //
  // Heats data is SUPER GROSS, especially because the way rerolls can run off the rails and need to be
  // done "just in time" in many cases.  This leads to "isfinals" in the heats table meaning "happened on finals
  // day", which doesn't match how we keep times in the raceentries table where finalreroll is
  // "reroll earned for final roll".  Thus, many but not all of the "isfinals" "isreroll" times are _actually_
  // (prelim) reroll times.
  //
  // So, in the case of a final reroll, we are going to use finalreroll if we have it, otherwise use
  // reroll.  This is not perfect, but works in almost 99% of the cases.  Example case where it does
  // not work: 2010 PiKA Mens A.
  //
  // Note that we only fetch exhibitions if there is a video to go with them, since we have nothing to display otherwise.
  $heatQuery = "SELECT number, isfinals, isreroll, h.class,
      o1.shortname AS sn1, e1.team AS t1, e1.entryid AS teamid1, e1.DQ AS dq1, e1.class AS oclass1,
      case when isfinals = 0 and isreroll = 0 then e1.prelim
           when isfinals = 0 and isreroll = 1 then e1.reroll
           when isfinals = 1 and isreroll = 0 then e1.final
           when isfinals = 1 and isreroll = 1 and e1.finalreroll > 0 then e1.finalreroll
           when isfinals = 1 and isreroll = 1 and e1.finalreroll <= 0 then e1.reroll end AS timesec1,
      o2.shortname AS sn2, e2.team AS t2, e2.entryid AS teamid2, e2.DQ AS dq2, e2.class AS oclass2,
      case when isfinals = 0 and isreroll = 0 then e2.prelim
           when isfinals = 0 and isreroll = 1 then e2.reroll
           when isfinals = 1 and isreroll = 0 then e2.final
           when isfinals = 1 and isreroll = 1 and e2.finalreroll > 0 then e2.finalreroll
           when isfinals = 1 and isreroll = 1 and e2.finalreroll <= 0 then e2.reroll end AS timesec2,
      o3.shortname AS sn3, e3.team AS t3, e3.entryid AS teamid3, e3.DQ AS dq3, e3.class AS oclass3,
      case when isfinals = 0 and isreroll = 0 then e3.prelim
           when isfinals = 0 and isreroll = 1 then e3.reroll
           when isfinals = 1 and isreroll = 0 then e3.final
           when isfinals = 1 and isreroll = 1 and e3.finalreroll > 0 then e3.finalreroll
           when isfinals = 1 and isreroll = 1 and e3.finalreroll <= 0 then e3.reroll end AS timesec3,
      h.note, v.youtubeid AS video_youtubeid, v.title AS video_title
    FROM hist_heats h
    LEFT JOIN hist_raceentries e1 ON concat(h.year, '.', Lane1) = e1.entryid LEFT JOIN hist_orgs o1 ON e1.orgid = o1.orgid
    LEFT JOIN hist_raceentries e2 ON concat(h.year, '.', Lane2) = e2.entryid LEFT JOIN hist_orgs o2 ON e2.orgid = o2.orgid
    LEFT JOIN hist_raceentries e3 ON concat(h.year, '.', Lane3) = e3.entryid LEFT JOIN hist_orgs o3 ON e3.orgid = o3.orgid
    LEFT JOIN video v ON h.heatid = v.heatid
    WHERE h.year = ? AND (h.class != 'E' OR v.youtubeid IS NOT NULL)
    ORDER BY h.class,isfinals,isreroll,number ASC;";

  $heatData = dbBoundQuery($HISTORY_DATABASE, $heatQuery, "d", $year);

  $historyLinkQuery = "SELECT link FROM hist_yearhistorylink WHERE year = ?;";
  $historyLinkData = dbBoundQuery($HISTORY_DATABASE, $historyLinkQuery, "d", $year);

  $historyLink = "";
  if ($historyLinkData->num_rows == 1) {
    // year is a primary key for this table, so it should be 1 or 0.
    $historyLink = $historyLinkData->fetch_assoc()["link"];
  }

  $pheatsArr = array();
  $fheatsArr = array();
  // Split up the heat data into class/reroll/prelim/final buckets.
  // We are assuming the sort order is maintained here.
  while ($h = $heatData->fetch_assoc()) {
    $heattype = $h["class"] . $h["isreroll"];
    if ($h["class"] == 'Z') {
      // Mixed Class heats need to include the origin class of the entry.
      $classMap = array("M" => "Men's",
                        "W" => "Women's",
                        "R" => "Robotic",
                        "N" => "All Gender");

      $h["team1"] = empty($h["sn1"]) ? "" : $h["sn1"]." ".$classMap[$h["oclass1"]]." ".$h["t1"];
      $h["team2"] = empty($h["sn2"]) ? "" : $h["sn2"]." ".$classMap[$h["oclass2"]]." ".$h["t2"];
      $h["team3"] = empty($h["sn3"]) ? "" : $h["sn3"]." ".$classMap[$h["oclass3"]]." ".$h["t3"];
    } else {
      $h["team1"] = empty($h["sn1"]) ? "" : $h["sn1"]." ".$h["t1"];
      $h["team2"] = empty($h["sn2"]) ? "" : $h["sn2"]." ".$h["t2"];
      $h["team3"] = empty($h["sn3"]) ? "" : $h["sn3"]." ".$h["t3"];
    }
    if ($h["isfinals"] == 1) {
      $fheatsArr[$heattype][$h["number"]] = $h;
    } else {
      $pheatsArr[$heattype][$h["number"]] = $h;
    }
  }

  function displayResults($resultList) {
    echo("<div class=\"table-responsive\"><table class=\"table\">");
    echo("<thead><tr><th>Place</th><th>Team</th><th>Buggy</th><th>Prelims</th><th>Prelim Reroll</th><th>Finals</th><th>Finals Reroll</th><th>Notes</th></tr></thead>");
    echo("<tbody>");

    while ($r = $resultList->fetch_assoc()) {
      echo("<tr>");
      if ($resultList->num_rows == 1 &&
          empty($r["prelim"]) && empty($r["reroll"]) &&
          empty($r["final"]) && empty($r["finalreroll"]) &&
          empty($r["dq"])) {
        // One entry, no times _or_ DQ/DNF.  This was a year that didn't happen.
        // Post the reason instead.
        echo("<td colspan=\"7\" class=\"text-center\">".$r["note"]."</td>");
      } else {
        echo("<td>".$r["place"]."</td>");
        echo("<td style=\"white-space: nowrap\"><a href=\"/history/team/".$r["entryid"]."\">".$r["team"]."</a></td>");

        if (strlen($r["buggyname"]) > 0) {
          echo("<td><a href=\"/history/buggy/".$r["buggyid"]."\">".$r["buggyname"]."</a></td>");
        } else {
          echo("<td></td>");
        }

        echo("<td>".displayTime($r["prelim"])."</td>");
        echo("<td>".displayTime($r["reroll"])."</td>");
        echo("<td>".displayTime($r["final"])."</td>");
        echo("<td>".displayTime($r["finalreroll"])."</td>");
        $notes = $r["note"];
        if (strlen($r["dq"]) > 0) {
          if (strlen($notes) > 0) {
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
    // are on top.  Of course, this doesn't always happen and shouldn't be
    // considered to have been the actual order rolls happened on the day.
    $heattypes = array("E0","N0","N1","W0","W1","M0","M1","Z0","Z1");
    $heattypelabels = array("M0"=>"Men's",
                            "M1"=>"Men's Rerolls",
                            "W0"=>"Women's",
                            "W1"=>"Women's Rerolls",
                            "N0"=>"All Gender",
                            "N1"=>"All Gender Rerolls",
                            "Z0"=>"Mixed Class",
                            "Z1"=>"Mixed Class Rerolls",
                            "E0"=>"Exhibitions");
    foreach($heattypes as $type){
      if(isset($heatArr[$type])){
        echo("<h4>".$heattypelabels[$type]."</h4>");
        echo("<table class=\"table\"><thead>");

        if ($type != "E0") {
          // Not Exhibition, Add useful headers.
          echo("<tr><th></th><th></th><th>Lane 1</th><th>Lane 2</th><th>Lane 3</th><th>Notes</th></tr>");
        }

        echo("</thead><tbody>");
        foreach($heatArr[$type] as $heat){
          echo("<tr><td>".$heat["number"]."</td>");

          if (!empty($heat["video_youtubeid"])) {
            $video = array(
              "youtubeid" => $heat["video_youtubeid"],
              "title" => $heat["video_title"],
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
        echo("</tbody></table>");
      }
    }
  }

  $prevlink = "";
  $nextlink = "";

  $FIRST_YEAR = 1920;
  if($year > $FIRST_YEAR) {
    $prevlink = "<a href=\"/history/".$RACEDAY_URL_PART."/".($year - 1)."\">&laquo ".($year - 1)."</a>";
  }

  // Partial logic to determine if we show the next year _without_ an extra DB query.
  // If we're looking before last year, show the next link.
  // If we're looking _at_ last year, only show the next link if it is april or later.
  $lastyear = date("Y") - 1;
  if($year < $lastyear || ($year == $lastyear && date("n") >= 4)) {
    $nextlink = "<a href=\"/history/".$RACEDAY_URL_PART."/".($year + 1)."\">".($year + 1)." &raquo</a>";

    // We only need the vertical bar if we're putting in next year _and_ we're past 1920.
    if ($year > $FIRST_YEAR) {
      $nextlink = " | ".$nextlink;
    }
  }
?>

<?php if (!empty($historyLink)) { ?>
  Read a history of <a href="<?php echo($historyLink); ?>">this year</a>.
<?php } ?>

<div class="my-2">
  <?php echo($prevlink.$nextlink); ?>
</div>

<ul class="nav nav-tabs mb-2" role="tablist">
  <?php if ($mensResults->num_rows > 0) { // should effecitvely always be true, but you never know... ?>
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-bs-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's</a>
  </li>
  <?php } ?>
  <?php if ($womensResults->num_rows > 0) { // safer alternative to "year >= 1979" ?>
    <li class="nav-item">
      <a id="womens-tab" href="#tab-womens" class="nav-link" data-bs-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's</a>
    </li>
  <?php } ?>
  <?php if ($allgenderResults->num_rows > 0) { ?>
    <li class="nav-item">
      <a id="allgender-tab" href="#tab-allgender" class="nav-link" data-bs-toggle="tab" role="tab" aria-controls="tab-allgender" aria-selected="false">All Gender</a>
    </li>
  <?php } ?>
  <?php if ($roboticResults->num_rows > 0) { ?>
    <li class="nav-item">
      <a id="robotic-tab" href="#tab-robotic" class="nav-link" data-bs-toggle="tab" role="tab" aria-controls="tab-robotic" aria-selected="false">Robotic</a>
    </li>
  <?php } ?>
  <?php if (count($pheatsArr) > 0) { ?>
    <li class="nav-item">
      <a id="prelimheats-tab" href="#tab-prelimheats" class="nav-link" data-bs-toggle="tab" role="tab" aria-controls="tab-prelimheats" aria-selected="false">Prelim Heats</a>
    </li>
  <?php } ?>
  <?php if (count($fheatsArr) > 0) { ?>
    <li class="nav-item">
      <a id="finalsheats-tab" href="#tab-finalsheats" class="nav-link" data-bs-toggle="tab" role="tab" aria-controls="tab-finalsheats" aria-selected="false">Finals Heats</a>
    </li>
  <?php } ?>
</ul>

<div class="tab-content">
  <?php if ($mensResults->num_rows > 0) { ?>
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayResults($mensResults); ?>
  </div>
  <?php } ?>
  <?php if ($womensResults->num_rows > 0) { ?>
    <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
      <?php displayResults($womensResults); ?>
    </div>
  <?php } ?>
  <?php if ($allgenderResults->num_rows > 0) { ?>
    <div class="tab-pane fade" id="tab-allgender" role="tabpanel" aria-labelledby="allgender-tab">
      <?php displayResults($allgenderResults); ?>
    </div>
  <?php } ?>
  <?php if ($roboticResults->num_rows > 0) { ?>
    <div class="tab-pane fade" id="tab-robotic" role="tabpanel" aria-labelledby="robotic-tab">
      <?php displayResults($roboticResults); ?>
    </div>
  <?php } ?>
  <?php if (count($pheatsArr) > 0) { ?>
    <div class="tab-pane fade" id="tab-prelimheats" role="tabpanel" aria-labelledby="prelimheats-tab">
      <?php displayHeats($pheatsArr); ?>
    </div>
  <?php } ?>
  <?php if (count($fheatsArr) > 0) { ?>
    <div class="tab-pane fade" id="tab-finalsheats" role="tabpanel" aria-labelledby="finalsheats-tab">
      <?php displayHeats($fheatsArr); ?>
    </div>
  <?php } ?>
</div>
