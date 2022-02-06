<?php
  // Display an overview of the participants of a given raceday year.
  //
  // More useful for a raceday that hasn't happened yet, rather than one that has already happened.

  // After March, default to current year (otherwise prior year).
  // Not 100% perfect, but should be pretty rare to use this anyway.
  $year = date("Y");
  if (date("m") < 4) {
    // Not yet april, use prior year.
    $year = $year - 1;
  }

  // Hopefully, though, we have a parameter.
  if (!empty($_GET["year"])) {
    $year = $_GET['year'] * 1;
  }


  $resQuery = "SELECT e.entryid AS entryid,
                      shortname AS orgname,
                      e.orgid AS orgid,
                      case when class = 'M' then 'Mens'
                           when class = 'W' then 'Womens'
                           else 'Unknown' end AS class,
                      team,
                      b.name AS buggyname,
                      b.buggyid AS buggyid
                 FROM hist_raceentries e
                 LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                 LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                 WHERE year = ?
                 ORDER BY o.shortname, class, team";

  $rosters = dbBoundQuery($HISTORY_DATABASE, $resQuery, "d", $year);

  if ($rosters->num_rows == 0) {
    die("Sorry, unknown year.");
  }

  // We first run through the results to identify all the participating orgs and teams, and
  // link the teams to the orgs.

  // Entries By Org is keyed by orgname, 2 keys: "Mens", "Womens".
  // (Recover the orgid by using participatingOrgs, above)
  // mens is an numeric array of all mens teams in team order, values are the table strings for the entry and buggy columns.
  // womens is a numeric array of all womens teams in team order, values are the table strings for the entry and buggy columns.
  $participatingOrgs = array();
  $entriesByOrg = array();

  while($row = $rosters->fetch_assoc()) {
    $orgname = $row["orgname"];
    $class = $row["class"];

    // If class isn't understood to be mens or womens, skip this entry.
    if ($class != "Mens" && $class != "Womens") {
      continue;
    }

    $participatingOrgs[$orgname] = $row["orgid"];

    if (!isset($entriesByOrg[$orgname])) {
      // Init this org.
      $entriesByOrg[$orgname] = array();
      $entriesByOrg[$orgname]["Mens"] = array();
      $entriesByOrg[$orgname]["Womens"] = array();
    }

    $entryString = "<td><a href=\"/history/team/".$row["entryid"]."\">".$class." ".$row["team"]."</a></td>";
    $entryString .= "<td><a href=\"/history/buggy/".$row["buggyid"]."\">".$row["buggyname"]."</a></td>";

    array_push($entriesByOrg[$orgname][$class], $entryString);
  }

  echo("<h1>".$year." Entered Orgs</h1>");

  // First Table, Orgs:
  echo ("<div class=\"table-responsive\"><table class=\"table\">");
  // If I understand this correctly, php maintains key order when inserting,
  // so since we sorted by org name above, this should maintain that sort.
  $ORG_COLS = 4;
  $rowMod = 0;

  foreach ($participatingOrgs as $org => $orgid) {
      if ($rowMod == 0) {
        echo("<tr>");
      }
      echo("<td><a href=\"/history/org/".$orgid."\">".$org."</a></td>");
      $rowMod = ($rowMod + 1) % $ORG_COLS;
      if ($rowMod == 0) {
        echo("</tr>");
      }
  }

  // Clean up the last row.
  if ($rowMod > 0) {
    echo("<td colspan=".($ORG_COLS - $rowMod)."></td></tr>");
  }

  echo("</table></div>");

  // Second Table, Entries:
  echo("<h1>".$year." Entered Teams</h1>");
  echo("<div class=\"table-responsive\"><table class=\"table\">");
  echo("<tr><th rowspan=2>Orginization</th><th colspan=2>Mens</th><th colspan=2>Womens</th></tr>");
  echo("<tr><th>Team</th><th>Buggy</th><th>Team</th><th>Buggy</th></tr>");
  foreach ($entriesByOrg as $orgname => $e) {
      $orgid = $participatingOrgs[$orgname];

      $rows = max(count($e["Mens"]), count($e["Womens"]));
      echo("<tr>");
      echo("<td rowspan=".$rows.">");
      echo("<h4><a href=\"/history/org/".$orgid."\">".$orgname."</a></h4>");
      echo("(<a href=\"/history/rosters/".$year."/".$orgid."\">View All Rosters</a>)");
      echo("</td>");

      for ($i = 0; $i < $rows; $i++) {
        if ($i > 0) {
          echo("<tr>");
        }
        displayEntryCols($e["Mens"], $i);
        displayEntryCols($e["Womens"], $i);
        echo("</tr>");
      }
  }
  echo("</table></div>");

  // Helper for printing out each entry (or not) for the entry table.
  function displayEntryCols($e, $index) {
    if (isset($e[$index])) {
      echo($e[$index]);
    } else {
      echo("<td colspan=2></td>");
    }
  }
?>
