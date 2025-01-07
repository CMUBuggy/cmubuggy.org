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
                      b.buggyid AS buggyid,
                      orglogos.image_url AS org_image_url
                 FROM hist_raceentries e
                 LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                 LEFT JOIN orglogos ON e.orgid = orglogos.orgid
                 LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                 WHERE year = ? AND class IN ('M','W','N','R')
                 ORDER BY o.shortname, class, team";

  $rosters = dbBoundQuery($HISTORY_DATABASE, $resQuery, "d", $year);

  if ($rosters->num_rows == 0) {
    if ($year == $CURRENT_YEAR) {
     echo("<p>Stay tuned – rosters will be posted the week of Carnival. We'll see you then!</p>");
     exit();
    } else {
      die("Sorry, we don't have data for ".$year.".");
    }
  }

  // We first run through the results to identify all the participating orgs and teams, and
  // link the teams to the orgs.

  // Entries By Org is keyed by orgname, 3 keys: "Mens", "Womens", "All Gender"
  // (Recover the orgid by using participatingOrgs, above)
  // mens is an numeric array of all mens teams in team order, values are the table strings for the entry and buggy columns.
  // womens is a numeric array of all womens teams in team order, values are the table strings for the entry and buggy columns.
  $participatingOrgs = array();
  $participatingOrgImages = array();
  $entriesByOrg = array();
  $haveRobotic = false;

  while($row = $rosters->fetch_assoc()) {
    $orgname = $row["orgname"];
    $class = $row["class"];

    $participatingOrgs[$orgname] = $row["orgid"];
    if(isset($row["org_image_url"])) {
      $participatingOrgImages[$orgname] = $row["org_image_url"];
    }

    if (!isset($entriesByOrg[$orgname])) {
      // Init this org.
      $entriesByOrg[$orgname] = array();
      $entriesByOrg[$orgname]["Mens"] = array();
      $entriesByOrg[$orgname]["Womens"] = array();
      $entriesByOrg[$orgname]["All Gender"] = array();
      $entriesByOrg[$orgname]["Robotic"] = array();
    }

    $entryString = "<a href=\"/history/team/".$row["entryid"]."\">".$class." ".$row["team"]."</a>";
    if (strlen($row["buggyname"]) > 0) {
      $entryString .= "<span class=\"d-none d-sm-inline\"><br></span>\n";
      $entryString .= "<span class=\"d-sm-none\">(</span>";
      $entryString .= "<span class=\"font-italic\"><a href=\"/history/buggy/".$row["buggyid"]."\">".$row["buggyname"]."</a></span>";
      $entryString .= "<span class=\"d-sm-none\">)</span>";
    }

    array_push($entriesByOrg[$orgname][$class], $entryString);
    if ($class == 'Robotic') {
      $haveRobotic = true;
    }
  }

  // Second Table, Entries:
  if ($haveRobotic) {
    // We have robot entries, need a title for the humans
    echo("<hr><h3>Organizations</h3>");
  }
  echo("<div class=\"table-responsive\"><table class=\"table\">");
  printEntriesForClasses(["Mens", "Womens", "All Gender"]);
  echo("</table></div>");

  if ($haveRobotic) {
    // We have robot entries.
    echo("<hr><h3>Robotic Organizations</h3>");
    echo("<div class=\"table-responsive\"><table class=\"table\">");
    printEntriesForClasses(["Robotic"]);
    echo("</table></div>");
  }

  function printEntriesForClasses($classList) {
    global $year, $entriesByOrg, $participatingOrgs, $participatingOrgImages;

    // How gross is this?  In order to put the logos into a reasonable spot and make them dissapear as the
    // screen gets small, we need to make the "Organization" column responsive and change its colspan as we
    // do so.  Thus, it looks like we actually have 2 Org columns, but we never show more than one.
    echo("<tr>");
    echo("<th class=\"d-none d-md-table-cell\" colspan=2 style=\"text-align: center\">Organization</th>");
    echo("<th class=\"d-md-none\" style=\"text-align: center\">Organization</th>");
    echo("<th class=\"d-sm-none\">Teams</th>");
    foreach ($classList as $c) {
      echo("<th class=\"d-none d-sm-table-cell\">".$c."</th>");
    }
    echo("</tr>\n");

    foreach ($entriesByOrg as $orgname => $e) {
      $orgid = $participatingOrgs[$orgname];

      $rows = 0;
      foreach ($classList as $c) {
        $rows = max($rows, count($e[$c]));
      }
      if ($rows == 0) {
        // No relevant classes (e.g. robotic org when printing humans)
        continue;
      }

      echo("<tr>");

      echo("<td class=\"d-none d-md-table-cell align-middle\" rowspan=".$rows.">");
      if (isset($participatingOrgImages[$orgname])) {
        echo("<img class=\"img-fluid\" style=\"max-width: 100px;\" src=\"".$participatingOrgImages[$orgname]."\">");
      }
      echo("</td>");

      echo("<td rowspan=".$rows.">");
      echo("<h4><a href=\"/history/org/".$orgid."\">".$orgname."</a></h4>");

      echo("<a class=\"btn btn-primary\" href=\"/raceday/rosters/".$year."/".$orgid."\">View Rosters</a>");
      echo("</td>");

      for ($i = 0; $i < $rows; $i++) {
        if ($i > 0) {
          echo("<tr>");
        }
        echo("<td class=\"text-nowrap d-sm-none\">\n");
        foreach ($classList as $c) {
          displayIfSet($e[$c], $i);
        }
        echo("</td>");

        foreach ($classList as $c) {
          displayColIfSet($e[$c], $i);
        }
        echo("</tr>\n");
      }
    }
  }

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
