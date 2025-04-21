<script>
  function dopopup(heatid) {
    // Does not open into same window since we may want to preload several rosters.
    window.open("/content/tv/tvheat-view.php?t="+heatid, "_blank", "popup=true,width=960,height=540");
  }
</script>

<?php
  // Display an overview of the heats in a given raceday year.
  //
  // Starting in March, default to the current year to allow Raceday mode to be turned on a month out.
  // Otherwise use the prior year. Not 100% perfect, but should be pretty rare to use this anyway.
  $CURRENT_YEAR = date("Y");
  $year = getDefaultRacedayYear();

  // Hopefully, though, we have a parameter.
  if (!empty($_GET["year"])) {
    $year = $_GET['year'] * 1;
  }

  $classMap = array(
    "M" => "Mens",
    "N" => "All Gender",
    "W" => "Womens",
    "R" => "Robotic",
    "Z" => "Mixed"
  );

  // Much simpler than the race query, since we only need lane, shortname, entry class, and team.
  $heatQuery = "SELECT h.heatid AS heatid, number, isfinals, isreroll, h.class AS heatclass,
      o1.shortname AS sn1, e1.team AS t1, e1.entryid AS teamid1, e1.class AS oclass1,
      o2.shortname AS sn2, e2.team AS t2, e2.entryid AS teamid2, e2.class AS oclass2,
      o3.shortname AS sn3, e3.team AS t3, e3.entryid AS teamid3, e3.class AS oclass3
    FROM hist_heats h
    LEFT JOIN hist_raceentries e1 ON concat(h.year, '.', Lane1) = e1.entryid LEFT JOIN hist_orgs o1 ON e1.orgid = o1.orgid
    LEFT JOIN hist_raceentries e2 ON concat(h.year, '.', Lane2) = e2.entryid LEFT JOIN hist_orgs o2 ON e2.orgid = o2.orgid
    LEFT JOIN hist_raceentries e3 ON concat(h.year, '.', Lane3) = e3.entryid LEFT JOIN hist_orgs o3 ON e3.orgid = o3.orgid
    WHERE h.year = ? AND h.class != 'E'
    ORDER BY h.class,isfinals,isreroll,number ASC;";

  $heatData = dbBoundQuery($HISTORY_DATABASE, $heatQuery, "d", $year);

  if ($heatData->num_rows == 0) {
    if ($year == $CURRENT_YEAR) {
     echo("<h1>".$year." Heats</h1>");
     echo("<p>Stay tuned – heats will be posted the week of Carnival. We'll see you then!</p>");
     exit();
    } else {
      die("Sorry, we don't have data for ".$year.".");
    }
  }

  // We first run through the results to identify all the participating orgs and teams, and
  // link the teams to the orgs.

  echo("<ul>");
  while($row = $heatData->fetch_assoc()) {
    echo("<li>");
    echo("<a href=\"#\" onclick=\"dopopup(&quot;".$row["heatid"]."&quot;)\">");
    echo($classMap[$row["heatclass"]]." ".$row["number"]);
    if ($row["isfinals"] || $row["isreroll"]) {
      $heatspecial = "";
      $heatspecial .= $row["isfinals"] ? "Finals" : "";
      $heatspecial .= $row["isfinals"] && $row["isreroll"] ? ", " : "";
      $heatspecial .= $row["isreroll"] ? "Reroll" : "";
      echo(" (".$heatspecial.")");
    }
    echo("</a></li>");
  }
  echo("</ul>")
?>