<?php
  // Display an overview of the participants of a given raceday year. More useful for a raceday that
  // hasn't happened yet, rather than one that has already happened.
  //
  // Starting in March, default to the current year to allow Raceday mode to be turned on a month out.
  // Otherwise use the prior year. Not 100% perfect, but should be pretty rare to use this anyway.
  $CURRENT_YEAR = date("Y");
  $year = getDefaultRacedayYear();

  // Hopefully, though, we have a parameter.
  if (!empty($_GET["year"])) {
    $year = $_GET['year'] * 1;
  }

  $resQuery = "SELECT e.entryid AS entryid,
                      shortname AS orgname,
                      e.orgid AS orgid,
                      case when class = 'M' then 'Mens'
                           when class = 'W' then 'Womens'
                           when class = 'N' then 'All Gender'
                           when class = 'R' then 'Robotic'
                           else 'Error' end AS class,
                      team,
                      b.name AS buggyname,
                      b.buggyid AS buggyid
                 FROM hist_raceentries e
                 LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                 LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                 WHERE year = ? AND class IN ('M','W','N','R')
                 ORDER BY o.shortname, class, team";

  $rosters = dbBoundQuery($HISTORY_DATABASE, $resQuery, "d", $year);

  if ($rosters->num_rows == 0) {
    if ($year == $CURRENT_YEAR) {
     echo("<h1>".$year." Rosters</h1>");
     echo("<p>Stay tuned – rosters will be posted the week of Carnival. We'll see you then!</p>");
     exit();
    } else {
      die("Sorry, we don't have data for ".$year.".");
    }
  }

  // We first run through the results to identify all the participating orgs and teams, and
  // link the teams to the orgs.

  // Entries By Org is keyed by orgname, 3 keys: "Mens", "Womens", "All Gender", "Robotic"
  // (Recover the orgid by using participatingOrgs)
  $participatingOrgs = array();
  $entriesByOrg = array();

  while($row = $rosters->fetch_assoc()) {
    $orgname = $row["orgname"];
    $class = $row["class"];

    $participatingOrgs[$orgname] = $row["orgid"];

    if (!isset($entriesByOrg[$orgname])) {
      // Init this org.
      $entriesByOrg[$orgname] = array();
      $entriesByOrg[$orgname]["Mens"] = array();
      $entriesByOrg[$orgname]["Womens"] = array();
      $entriesByOrg[$orgname]["All Gender"] = array();
      $entriesByOrg[$orgname]["Robotic"] = array();
    }

    $entryString = "<a href=\"/content/tv/tvroster-view.php?t=".$row["entryid"]."\">".$class." ".$row["team"]."</a>";
    if (!empty($row["buggyname"])) {
      $entryString .= "<span class=\"d-none d-sm-inline\"><br></span>\n";
      $entryString .= "<span class=\"d-sm-none\">(</span>";
      $entryString .= "<small class=\"font-italic\"><a href=\"/history/buggy/".$row["buggyid"]."\">".$row["buggyname"]."</a></small>";
      $entryString .= "<span class=\"d-sm-none\">)</span>";
    }

    array_push($entriesByOrg[$orgname][$class], $entryString);
  }

  // Second Table, Entries:
  echo("<h1>".$year." Team Rosters (TV Portal)</h1>");
  echo("<h4>Warning: Displays single roster.  Tries prelim first, then final.</h4>");
  echo("<div class=\"table-responsive\"><table class=\"table\">");

  echo("<tr>");
  echo("<th>Organization</th>");
  echo("<th>Mens</th>");
  echo("<th>Womens</th>");
  echo("<th>All Gender</th>");
  echo("<th>Robotic</th>");
  echo("</tr>\n");

  foreach ($entriesByOrg as $orgname => $e) {
      $orgid = $participatingOrgs[$orgname];

      $rows = max(count($e["Mens"]), count($e["Womens"]), count($e["All Gender"]), count($e["Robotic"]));
      echo("<tr>");

      echo("<td rowspan=".$rows.">");
      echo("<h4><a href=\"/history/org/".$orgid."\">".$orgname."</a></h4>");
      echo("</td>");

      for ($i = 0; $i < $rows; $i++) {
        if ($i > 0) {
          echo("<tr>");
        }
        echo("<td class=\"text-nowrap d-sm-none\">\n");
        displayIfSet($e["Mens"],$i);
        displayIfSet($e["Womens"], $i);
        displayIfSet($e["All Gender"], $i);
        displayIfSet($e["Robotic"], $i);
        echo("</td>");

        displayColIfSet($e["Mens"], $i);
        displayColIfSet($e["Womens"], $i);
        displayColIfSet($e["All Gender"], $i);
        displayColIfSet($e["Robotic"], $i);
        echo("</tr>\n");
      }
  }
  echo("</table></div>");

  function displayIfSet($e, $index) {
    if (isset($e[$index])) {
      echo($e[$index]);
      echo("<br>");
    }
  }

  // Helper for printing out each entry (or not) for the entry table.
  function displayColIfSet($e, $index) {
    echo("<td class=\"text-nowrap d-none d-sm-table-cell\">\n");
    if (isset($e[$index])) {
      echo($e[$index]);
    }
    echo("</td>\n");
  }
?>