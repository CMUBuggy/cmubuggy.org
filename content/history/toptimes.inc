<?php

$TOP_N = 50;

// Course records, top 50, by class. Set class (M or W) in 4 spots
// Could do this in one query and then split them locally, but doesn't seem worth it to save just one query.
// We do get the classanchor (for tabs) per row though, for conveinence.
$query = "SELECT
           T.year, T.entryid,
           case when T.class = 'M' then 'mens'
                when T.class = 'W' then 'womens'
                when T.class = 'N' then 'allgender'
                when T.class = 'R' then 'robotic'
                else 'unknown' end AS classanchor,
	         CONCAT(shortname, ' ', T.team) AS teamname,
           T.note as note,
           b.name AS buggy, b.buggyid AS buggyid,
	         T.time
    FROM (
		      SELECT year, entryid, class, orgid, team, buggyid, note, nullif(prelim,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, class, orgid, team, buggyid, note, nullif(reroll,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, class, orgid, team, buggyid, note, nullif(final,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, class, orgid, team, buggyid, note, nullif(finalreroll,0) as time from hist_raceentries where class = ?) as T
    LEFT JOIN hist_orgs o on T.orgid = o.orgid
    LEFT JOIN hist_buggies b on T.buggyid = b.buggyid
    WHERE T.time IS NOT NULL
    ORDER BY T.time ASC
    LIMIT ".$TOP_N.";";

$top50men = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","M","M","M","M");
$top50women = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","W","W","W","W");
$top50allgender = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","N","N","N","N");
$top50robotic = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","R","R","R","R");

function displayTable($teamList, $displayNotes=false){
  global $RACEDAY_URL_PART;
  echo("<table class=\"table\">");
  $count = 1;
  while ($team = $teamList->fetch_assoc()) {
    $year = $team["year"];

    echo("<tr><td>".$count.".</td>");
    echo("<td><a href=\"/history/".$RACEDAY_URL_PART."/".$year."#".$team["classanchor"]."\">".$year."</a></td>");
    echo("<td><a href=\"/history/team/".$team["entryid"]."\">".$team["teamname"]."</a></td>");
    echo("<td><a href=\"/history/buggy/".$team["buggyid"]."\">".$team["buggy"]."</a></td>");
    echo("<td>".displayTime($team["time"])."</td>");
    if ($displayNotes) {
      echo("<td>".$team["note"]."</td>");
    }
    echo("</tr>");

    $count++;
  }
  echo("</table>");
}
?>

<p><i>Note: This table does not account for DQs.</i></p>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's</a></li>
  <li class="nav-item">
    <a id="womens-tab" href="#tab-womens" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's</a></li>
  <li class="nav-item">
    <a id="allgender-tab" href="#tab-allgender" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-allgender" aria-selected="false">All Gender</a></li>
  <li class="nav-item">
    <a id="robotic-tab" href="#tab-robotic" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-robotic" aria-selected="false">Robotic</a></li>
  </ul>


<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayTable($top50men); ?>
  </div>
  <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
    <?php displayTable($top50women); ?>
  </div>
  <div class="tab-pane fade" id="tab-allgender" role="tabpanel" aria-labelledby="allgender-tab">
    <?php displayTable($top50allgender); ?>
  </div>
  <div class="tab-pane fade" id="tab-robotic" role="tabpanel" aria-labelledby="robotic-tab">
    <?php
          // Robotic class gets their notes displayed, since RC vs Autonomous is a
          // critical detail about the roll and is currently only in notes.
          displayTable($top50robotic, true);
    ?>
  </div>
</div>











