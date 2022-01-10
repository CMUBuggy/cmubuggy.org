<?php

if (empty($_GET['id'])) {
  // this should have redirected to personlist.  Shouldn't be here.
  die("Oops, no person specified!");
}

$urlkey = $_GET['id'];

// Check existance & get name.
$metaDataQuery = "SELECT concat(firstname, ' ', lastname) AS name FROM hist_people WHERE personid=?;";
$metaData = dbBoundQuery("history",$metaDataQuery,"s",$urlkey);

$personName = "";
if ($metaData->num_rows == 1) {
  $personName = $metaData->fetch_assoc()["name"];
} else if ($metaData->num_rows == 0) {
  echo("I'm sorry, I don't know anything about: " . $urlkey);
  exit(0);
} else {
  echo("I'm sorry, I seem to be confused and think there are more than one person referenced by: " . $urlkey);
  exit(0);
}

$sweepstakesQuery = "SELECT concat(year, ' ', role) AS roledesc FROM hist_sweepstakes WHERE personid=? ORDER BY year DESC;";
$sweepstakesData = dbBoundQuery("history", $sweepstakesQuery,"s",$urlkey);

$teamQuery = "SELECT e.entryid,e.year,heattype,e.orgid,o.shortname AS orgname,
                     case when e.class = 'M' then 'Men\'s'
                          when e.class = 'W' then 'Women\'s'
                          else 'Unknown' end AS class,
                     case when e.class = 'M' then 'mens'
                          when e.class = 'W' then 'womens'
                          else 'Unknown' end AS classanchor,
                     e.team, position AS role,
                     case when heattype = 'Prelim' then e.prelim
                          when heattype = 'Prelim Reroll' then e.reroll
                          when heattype = 'Final' then e.final
                          when heattype = 'Final Reroll' then e.finalreroll
                          else NULL end AS timeSecs,
                     nullif(e.place,0) AS place, e.note, e.dq
                FROM hist_entrypeoplemap epm
                LEFT JOIN hist_raceentries e ON epm.entryid=e.entryid
                LEFT JOIN hist_orgs o ON e.orgid=o.orgid
                WHERE personid=?
                ORDER BY e.year,heattype,e.class,o.shortname,e.team;";
$teamData = dbBoundQuery("history", $teamQuery, "s", $urlkey);

?>

<?php
  echo("<h1>".$personName."</h1>");
  if($sweepstakesData->num_rows > 0) {
    echo("<h2>Sweepstakes Positions</h2>");
    echo("<ul class=\"list-unstyled\">");
    while ($s = $sweepstakesData->fetch_assoc()) {
      echo("<li>".$s["roledesc"]."</li>");
    }
    echo("</ul>");
  }
  if($teamData->num_rows > 0) {
    echo("<h2>Teams</h2>");
    echo("<div class=\"table-responsive\"><table class=\"table\"><thead><tr><th>Year</th><th>Day</th><th>Team</th><th>Role</th><th>Time</th><th>Place</th><th>DQ/Note</th></tr></thead><tbody>");
    while ($t = $teamData->fetch_assoc()) {
      echo("<tr>");
      echo("<td><a href=\"/history/raceday/".$t["year"]."#".$t["classanchor"]."\">".$t["year"]."</a></td>");
      echo("<td>".$t["heattype"]."</td>");
      echo("<td><a href=\"/history/team/".$t["entryid"]."\">".$t["orgname"]." ".$t["class"]." ".$t["team"]."</a></td>");
      echo("<td>".$t["role"]."</td>");
      echo("<td>".displayTime($t["timeSecs"])."</td>");
      echo("<td>".$t["place"]."</td>");

      $notes = $t["note"];
      if (!empty($t["dq"])) {
        if (!empty($notes)) {
          $notes .= "<br>";
        }
        $notes .= "DQ: ".$t["dq"];
      }
      echo("<td>".$notes."</td>");
      echo("</tr>");
    }
    echo("</tbody></table></div>");
  }
?>
