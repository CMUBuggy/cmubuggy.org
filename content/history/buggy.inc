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

$metaData = dbBoundQuery("history", $metaDataQuery, "s", $buggyUrlKey);

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
// TODO: If we have the data, we need to link the videos.
//
$raceQuery = "SELECT year, 
	CONCAT(case when class = 'W' then 'Women\'s' else 'Men\'s' end, ' ', team) AS Team,
  entryid AS TeamID,
  nullif(place,0) AS Place, 
	case when prelim <> 0 then concat(floor(prelim / 60), ':', right(concat('0',format(prelim % 60, 2)),5)) else null end AS Prelim, 
	case when reroll <> 0 then concat(floor(reroll / 60), ':', right(concat('0',format(reroll % 60, 2)),5)) else null end AS Reroll,
	case when final <> 0 then concat(floor(final / 60), ':', right(concat('0',format(final % 60, 2)),5)) else null end AS Final,
	case when finalreroll <> 0 then concat(floor(finalreroll / 60), ':', right(concat('0',format(finalreroll % 60, 2)),5)) else null end AS FinalReroll,
	case when DQ <> '0' then DQ else null end AS DQ,
  note
FROM hist_raceentries
WHERE buggyid = ?
ORDER BY year DESC, Team ASC;";

$raceData = dbBoundQuery("history", $raceQuery, "s", $buggyUrlKey);

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

$awardData = dbBoundQuery("history", $awardQuery, "ss", $buggyUrlKey, $buggyUrlKey);
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
            $year = $r["year"];
            echo("<tr><td><a href=\"/history/raceday/".$year."\">".$year."</a></td>");
            echo("<td><a href=\"/history/team/".$r["TeamID"]."\">".$r["Team"]."</a></td>");
            echo("<td>".$r["Place"]."</td>");
            echo("<td>".$r["Prelim"]."</td>");
            echo("<td>".$r["Reroll"]."</td>");
            echo("<td>".$r["Final"]."</td>");
            echo("<td>".$r["FinalReroll"]."</td>");
            echo("<td>".$r["DQ"]." ".$r["note"]."</td></tr>");

            /*
            TODO: This is how videos used to work, look into this once we have video data.
                  Note this is tricky because the prior method relied on per-heat rows which we don't have now.

            $videolist = null;
            $videolist = $team->GetHeat()->GetVideoList();
            $video = null;
            if($videolist){ $video = reset($videolist); }
            echo("<td>");
            include("content/youtubevid.inc");
            echo("</td>");
            */
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
