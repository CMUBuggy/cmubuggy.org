<?php
  // Show all the people on the teams for a given year for a given org.

  if (empty($_GET["year"])) {
    // Definately shouldn't be on this page due to htaccess -- even the roster-by-year page is better.
    die("Ooops, no year specified!");
  }

  if (empty($_GET["org"])) {
    die("No org specified.");
  }

  $year = $_GET['year'] * 1;
  $orgurlkey = $_GET['org'];
  $orgshortname = $orgurlkey;  // Temp until we can replace it.

  // Note that this is a rare query where we don't do alphabetical class sort, since Womens
  // typically race before mens, and we envision this as a live-use raceday page.
  $resQuery = "SELECT e.entryid AS entryid,
                      shortname AS orgname,
                      case when class = 'M' then 'Mens'
                           when class = 'W' then 'Womens'
                           else 'Unknown' end AS class,
                      team,
                      b.name AS buggyname,
                      b.buggyid AS buggyid,
                      b.birthyear AS buggyyear,
                      b.smugmug_slug AS buggy_smugmug_slug,
                      m.heattype AS heattype,
                      m.position AS position,
                      m.personid AS personid,
                      concat(p.firstname, ' ', p.lastname) as personname
                 FROM hist_raceentries e
                 LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                 LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                 LEFT JOIN hist_entrypeoplemap m ON m.entryid = e.entryid
                 LEFT JOIN hist_people p ON p.personid = m.personid
                 WHERE e.year = ? AND e.orgid = ?
                 ORDER BY o.shortname, class DESC, team, heattype, position";

  $rosters = dbBoundQuery($HISTORY_DATABASE, $resQuery, "ds", $year, $orgurlkey);

  if ($rosters->num_rows == 0) {
    die("Sorry, couldn't find that.");
  }

  // Split the results table into each team.
  // Keyed by "Mens A", "Mens B", "Womens A", etc.
  // Values are themselves assoc arrays.
  //  "entry" -> link string to the entry itself
  //  "buggy" -> link string for the buggy name
  //  "people" -> assoc array "Prelim Driver", "Finals Hill 1", etc to link string for each person.
  $teams = array();

  while($row = $rosters->fetch_assoc()) {
    $orgshortname = $row["orgname"]; // As long as we get one row, we have a better name.

    $class = $row["class"];

    // If class isn't understood to be mens or womens, skip this entry.
    if ($class != "Mens" && $class != "Womens") {
      continue;
    }

    $teamkey = $class." ".$row["team"];

    if (!isset($teams[$teamkey])) {
      // Init this team
      $teams[$teamkey] = array();
      // Stuff keyed off the specific entry never changes, so we just set it up once.
      $teams[$teamkey]["entry"] = "<a href=\"/history/team/".$row["entryid"]."\">".$teamkey."</a>";
      if (!empty($row["buggyid"])) {
        $teams[$teamkey]["buggy"] = "<a href=\"/history/buggy/".$row["buggyid"]."\">".$row["buggyname"]."</a>";
      }
      if (!empty($row["buggyyear"])) {
        $buggyyear = $row["buggyyear"];
        $age = "";
        if ($year == $buggyyear) {
          $age = " <i>(New Buggy)</i>";
        } else if ($year > $buggyyear) {
          $age = " <i>(" . ($year - $buggyyear) . " years old)</i>";
        }
        $teams[$teamkey]["buggyage"] = $buggyyear.$age;
      }
      if (!empty($row["buggy_smugmug_slug"])) {
        $buggy_image_url = makeSmugmugUrl($row["buggy_smugmug_slug"], "S");
        $teams[$teamkey]["buggyimage"] = "<img class=\"img-fluid img-thumbnail\" src=\"".$buggy_image_url."\">";
      }
      $teams[$teamkey]["people"] = array();
    }

    if (isset($row["personid"])) {
      // Don't show heat type if its prelims, this lets us get a cleaner view for
      // current year roster display.
      $personKey = ($row["heattype"] == "Prelim" ? "" : $row["heattype"]." ").$row["position"];
      $teams[$teamkey]["people"][$personKey] = "<a href=\"/history/person/".$row["personid"]."\">".$row["personname"]."</a>";
    }
  }

  echo("<h1>".$year." ".$orgshortname." Rosters</h1>");
  echo("<p><a href=\"/raceday/rosters/".$year."\">See ".$year." rosters summary</a></p>");
  echo ("<div class=\"table-responsive\"><table class=\"table\">");

  echo("<tr><th width=40% scope=\"col\">Team</th><th scope=\"col\">Role</th><th scope=\"col\">Person</th></tr>");
  foreach ($teams as $teamKey => $team) {
    echo("<tr>");

    $rows = count($team["people"]);
    echo("<td width=40% rowspan=".max(1,$rows)."><h4>".$team["entry"]."</h4><dl>");
    if(isset($team["buggy"])) {
      echo("<dt>Buggy</dt><dd>".$team["buggy"]."</dd>");
    }
    if(isset($team["buggyage"])) {
      echo("<dt>Buggy Built</dt><dd>".$team["buggyage"]."</dd>");
    }
    echo("</dl>");
    if(isset($team["buggyimage"])) {
      echo($team["buggyimage"]);
    }
    echo("</td>");

    if ($rows == 0) {
      echo("<td colspan=2></td></tr>");
    }

    $firstRow = true;
    foreach($team["people"] as $role => $person) {
      if (!$firstRow) {
        echo ("<tr>");
        $firstRow = false;
      }
      echo("<td>".$role."</td>");
      echo("<td>".$person."</td>");
      echo("</tr>");
    }
  }

  echo("</table></div>");
?>
