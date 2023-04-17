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
                else 'unknown' end AS classanchor,
	         concat(shortname, case when T.team = 'A' then '' else concat(' ', T.team) end) AS teamname,
           b.name AS buggy, b.buggyid AS buggyid,
	         T.time
    FROM (
		      SELECT year, entryid, class, orgid, team, buggyid, nullif(prelim,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, class, orgid, team, buggyid, nullif(reroll,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, class, orgid, team, buggyid, nullif(final,0) as time from hist_raceentries where class = ?
	        UNION ALL SELECT year, entryid, class, orgid, team, buggyid, nullif(finalreroll,0) as time from hist_raceentries where class = ?) as T
    LEFT JOIN hist_orgs o on T.orgid = o.orgid
    LEFT JOIN hist_buggies b on T.buggyid = b.buggyid
    WHERE T.time IS NOT NULL
    ORDER BY T.time ASC
    LIMIT ".$TOP_N.";";

$top50men = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","M","M","M","M");
$top50women = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","W","W","W","W");
$top50allgender = dbBoundQuery($HISTORY_DATABASE,$query,"ssss","N","N","N","N");

function displayTable($teamList){
  echo("<table class=\"table\">");
  $count = 1;
  while ($team = $teamList->fetch_assoc()) {
    $year = $team["year"];

    echo("<tr><td>".$count.".</td>");
    echo("<td><a href=\"/history/raceday/".$year."#".$team["classanchor"]."\">".$year."</a></td>");
    echo("<td><a href=\"/history/team/".$team["entryid"]."\">".$team["teamname"]."</a></td>");
    echo("<td><a href=\"/history/buggy/".$team["buggyid"]."\">".$team["buggy"]."</a></td>");
    echo("<td>".displayTime($team["time"])."</td></tr>");

    $count++;
  }
  echo("</table>");
}
?>

<h1>Top <?php echo($TOP_N); ?> Times</h1>

<p><i>Note: This table does not account for DQs.</i></p>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's</a></li>
  <li class="nav-item">
    <a id="womens-tab" href="#tab-womens" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's</a></li>
<?php if($top50allgender->num_rows > 0) { ?>
  <li class="nav-item">
    <a id="allgender-tab" href="#tab-allgender" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-allgender" aria-selected="false">All Gender</a></li>
<?php } ?>
  </ul>


<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayTable($top50men); ?>
  </div>
  <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
    <?php displayTable($top50women); ?>
  </div>
  <?php if($top50allgender->num_rows > 0) { ?>
    <div class="tab-pane fade" id="tab-allgender" role="tabpanel" aria-labelledby="allgender-tab">
    <?php displayTable($top50allgender); ?>
  </div>
  <?php } ?>
</div>











