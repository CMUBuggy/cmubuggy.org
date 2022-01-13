<?php

if (empty($_GET["urlkey"])) {
  // We should have been redirected into buggylist.inc, not here.  What happened?
  die("Ooops, no buggy specified!");
}

$buggyUrlKey = $_GET["urlkey"];

#(/buggy) metadata (existance, build year, org, notes)
$metaDataQuery = "SELECT name, birthyear, o.shortname AS org, b.orgid, b.note FROM hist_buggies b
                    LEFT JOIN hist_orgs o ON b.orgid=o.orgid
                    WHERE b.buggyid=?;";

$metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $buggyUrlKey);

if ($metaData->num_rows == 1) {
  $buggy = $metaData->fetch_assoc();
} else if ($metaData->num_rows == 0) {
  echo("I'm sorry, I don't know about buggy: " . $buggyUrlKey);
  exit(0);
} else {
  echo("I'm sorry, I seem to be confused and think there are more than one buggy called: " . $buggyUrlKey);
  exit(0);
}

//
// Fetching the link to the videos is a bit gross, since we need to join against every lane of the heats table
// for each of the 4 heats, and fetch up to 4 different blocks of youtube data.  Apologies for the shorthand naming.
//
$raceQuery = "SELECT e.year,
                     CONCAT(case when e.class = 'W' then 'Women\'s' else 'Men\'s' end, ' ', team) AS Team,
                     entryid AS TeamID,
                     nullif(place,0) AS Place,
                     Prelim, Reroll, Final, FinalReroll,
                     case when DQ <> '0' then DQ else null end AS DQ,
                     vp.youtubeid AS pyoutubeid, vp.title AS ptitle,
                     vr.youtubeid AS ryoutubeid, vr.title AS rtitle,
                     vf.youtubeid AS fyoutubeid, vf.title AS ftitle,
                     vfr.youtubeid AS fryoutubeid, vfr.title AS frtitle,
                     e.note
                FROM hist_raceentries e
                LEFT JOIN hist_heats hp ON hp.isfinals = 0 AND hp.isreroll = 0
                                           AND (CONCAT(hp.year,'.',hp.lane1)=e.entryid
                                                OR CONCAT(hp.year,'.',hp.lane2)=e.entryid
                                                OR CONCAT(hp.year,'.',hp.lane3)=e.entryid)
                LEFT JOIN video vp ON CAST(vp.heatid AS CHAR) = hp.heatid
                LEFT JOIN hist_heats hr ON hr.isfinals = 0 AND hr.isreroll = 1
                                           AND (CONCAT(hr.year,'.',hr.lane1)=e.entryid
                                                OR CONCAT(hr.year,'.',hr.lane2)=e.entryid
                                                OR CONCAT(hr.year,'.',hr.lane3)=e.entryid)
                LEFT JOIN video vr ON CAST(vr.heatid AS CHAR) = hr.heatid
                LEFT JOIN hist_heats hf ON hf.isfinals = 1 AND hf.isreroll = 0
                                           AND (CONCAT(hf.year,'.',hf.lane1)=e.entryid
                                                OR CONCAT(hf.year,'.',hf.lane2)=e.entryid
                                                OR CONCAT(hf.year,'.',hf.lane3)=e.entryid)
                LEFT JOIN video vf ON CAST(vf.heatid AS CHAR) = hf.heatid
                LEFT JOIN hist_heats hfr ON hfr.isfinals = 1 AND hfr.isreroll = 1
                                           AND (CONCAT(hfr.year,'.',hfr.lane1)=e.entryid
                                                OR CONCAT(hfr.year,'.',hfr.lane2)=e.entryid
                                                OR CONCAT(hfr.year,'.',hfr.lane3)=e.entryid)
                LEFT JOIN video vfr ON CAST(vfr.heatid AS CHAR) = hfr.heatid
                WHERE buggyid = ?
                ORDER BY year DESC, Team ASC;";

$raceData = dbBoundQuery($HISTORY_DATABASE, $raceQuery, "s", $buggyUrlKey);

// Combine all buggy awards (design)
$awardQuery = "SELECT year,
                      case when award = 1 then '1st Place Design'
                           when award = 2 then '2nd Place Design'
                           when award = 3 then '3rd Place Design'
                           else concat('Design ', award) end as award,
                      note
                      FROM hist_designawards
                      WHERE buggyid = ?
               UNION SELECT year,
                      concat(case when place = 1 then '1st Place'
                                  when place = 2 then '2nd Place'
                                  when place = 3 then '3rd Place'
                                  else concat(place, 'th Place') end,
                             case when class = 'W' then ' Women\'s'
                                  else ' Men\'s' end)
                      AS award, note
                      FROM hist_raceentries
                      WHERE buggyid = ?
                            AND place >= 1 AND place <= 6
                            AND dq = '0'
               ORDER BY year DESC, award ASC;";

$awardData = dbBoundQuery($HISTORY_DATABASE, $awardQuery, "ss", $buggyUrlKey, $buggyUrlKey);
?>

<h1><?php echo($buggy["name"]);?></h1>

<?php
  // Path is relative to our cwd from the file that called us (e.g. /index.php due to redirects) not relative to this .inc file!
  if (file_exists("img/buggy/".$buggyUrlKey)) {
    // No useful alt text to go here sicne it'd really only be the name.
    echo("<img class=\"mb-3\" src=\"/img/buggy/".$buggyUrlKey."\" />");
  }
?>

<dl class="row">
  <dt class="col-sm-5">Built</dt>
  <dd class="col-sm-7"><?php echo($buggy["birthyear"]); ?></dd>

  <dt class="col-sm-5">Organization</dt>
  <dd class="col-sm-7"><?php echo("<a href=\"/history/org/".$buggy["orgid"]."\">".$buggy["org"]. "</a>"); ?></dd>

  <?php if (!empty($buggy["note"])) { ?>
    <dt class="col-sm-5">Notes</dt>
    <dd class="col-sm-7"><?php echo($buggy["note"]); ?></dd>
  <?php } ?>
</dl>

<ul class="nav nav-tabs" role="tablist">
  <li class="nav-item">
    <a id="races-tab" href="#tab-races" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-races" aria-selected="true">Races <span class="badge badge-primary"><?php echo($raceData->num_rows); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="awards-tab" href="#tab-awards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-awards" aria-selected="false">Awards <span class="badge badge-primary"><?php echo($awardData->num_rows); ?></span></a>
  </li>
</ul>
<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-races" role="tabpanel" aria-labelledby="races-tab">
    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr class="text-nowrap">
            <th>Year</th>
            <th>Team</th>
            <th>Place</th>
            <th>Prelim</th>
            <th>Prelim Reroll</th>
            <th>Final</th>
            <th>FinalReroll</th>
            <th>DQ / Notes</th>
          </tr>
        </thead>
        <tbody>
          <?php
          while ($r = $raceData->fetch_assoc()) {
            $heatorder = array('Prelim', 'Reroll', 'Final', 'FinalReroll');
            $heattypes = array('Prelim' => 'p','Reroll' => 'r','Final' => 'f', 'FinalReroll' => 'fr');

            $videomap = array();
            foreach ($heattypes as $type => $vp) {
              if (!empty($r[$vp."youtubeid"])) {
                $videomap[$type] = array(
                  "youtubeid" => $r[$vp."youtubeid"],
                  "title" => $r[$vp."title"],
                  "nothumbnail" => "See Video" // there just isn't enough room for thumbnails on this page.
                );
              }
            }

            // Because the heats table treats "finals reroll" as "reroll on finals day", we need to
            // fudge videos that are labeled as "finals reroll" but are likely to be prelims rerolls.
            //
            // So, if we have a final reroll video, and no prelim reroll video, and there is
            // no final reroll time, relabel that video.
            //
            // Example buggy that has a lot of these cases: shakazulu
            //
            // This is a hack that might break if the final reroll _acutally_ had no time (e.g. crash)
            // and there is no prelim reroll.
            if (isset($videomap["FinalReroll"])
                && !isset($videomap["Reroll"])
                && empty($r["FinalReroll"])) {
              $videomap["Reroll"] = $videomap["FinalReroll"];
              unset($videomap["FinalReroll"]);
            }

            $year = $r["year"];
            echo("<tr><td><a href=\"/history/raceday/".$year."\">".$year."</a></td>");
            echo("<td><a href=\"/history/team/".$r["TeamID"]."\">".$r["Team"]."</a></td>");
            echo("<td>".$r["Place"]."</td>");
            foreach ($heatorder as $type) {
              echo("<td>");
              echo(displayTime($r[$type]));
              if (isset($videomap[$type])) {
                echo ("<br>");
                $video = $videomap[$type];
                include("content/youtubevid.inc");
              }
              echo("</td>");
            }
            echo("<td>".$r["DQ"]." ".$r["note"]."</td></tr>");
          }
          ?>
        </tbody>
      </table>
    </div>
  </div>
  <div class="tab-pane fade" id="tab-awards" role="tabpanel" aria-labelledby="awards-tab">
    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr class="text-nowrap">
            <th>Year</th>
            <th>Awards</th>
          </tr>
        </thead>
        <tbody>
          <?php
            while($a = $awardData->fetch_assoc()) {
              echo("<tr><td>".$a["year"]."</td>");
              echo("<td>".$a["award"]."</td>");
              echo("<td>".$a["note"]."</td></tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>
</div>
