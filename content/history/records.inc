<?php

// Course records, top 50, by class. Set class (M or W) in 4 spots
$recordQuery = "SELECT
           T.year, T.entryid,
	         concat(shortname, case when T.team = 'A' then '' else concat(' ', T.team) end) AS teamname,
           b.name AS buggy, b.buggyid AS buggyid,
	         concat(floor(T.time / 60), ':', right(concat('0',format(T.time % 60, 2)),5)) AS time
    FROM (
		      SELECT year, entryid, orgid, team, buggyid, nullif(prelim,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, orgid, team, buggyid, nullif(reroll,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, orgid, team, buggyid, nullif(final,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, orgid, team, buggyid, nullif(finalreroll,0) as time from hist_raceentries where class = ?) as T
    LEFT JOIN hist_orgs o on T.orgid = o.orgid
    LEFT JOIN hist_buggies b on T.buggyid = b.buggyid
    WHERE T.time IS NOT NULL
    ORDER BY T.time ASC
    LIMIT 50;";

$top50men = dbBoundQuery("history",$recordQuery,"ssss","M","M","M","M");
$top50women = dbBoundQuery("history",$recordQuery,"ssss","W","W","W","W");

function displayRecordTable($teamList){
  echo("<table class=\"table\">");
  $count = 1;
  while ($team = $teamList->fetch_assoc()) {
    $year = $team["year"];

    echo("<tr><td>".$count.".</td>");
    echo("<td><a href=\"/history/raceday/".$year."\">".$year."</a></td>");
    echo("<td><a href=\"/history/team/".$team["entryid"]."\">".$team["teamname"]."</a></td>");
    echo("<td><a href=\"/history/buggy/".$team["buggyid"]."\">".$team["buggy"]."</a></td>");
    echo("<td>".$team["time"]."</td></tr>");

    $count++;
  }
  echo("</table>");
}
?>

<h1>Course Records</h1>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's</a></li>
  <li class="nav-item">
    <a id="womens-tab" href="#tab-womens" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's</a></li>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayRecordTable($top50men); ?>
  </div>
  <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
    <?php displayRecordTable($top50women); ?>
  </div>
</div>











