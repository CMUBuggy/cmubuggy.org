<?php

if (empty($_GET["urlkey"])) {
  // We should have been redirected into orglist.inc, not here.  What happened?
  die("Ooops, no org specified!");
}

$orgUrlKey = $_GET["urlkey"];

// We use pchart on this page, so make sure to include it.
// (path relative to index.php)
include_once("lib/pChart_includes.inc");

#(/org) metadata (existance, names, founding, url, notes)
$metaDataQuery = "SELECT case when isgreek = 1 then greekname else longname end AS longname,
                         case when isgreek = 1 OR longname != shortname then shortname else null end as shortname,
                         isracingorg,
                         orgurl,
                         yearfounded,
                         note,
                         orglogos.image_url AS image_url
                    FROM hist_orgs o
                    LEFT JOIN orglogos ON o.orgid = orglogos.orgid
                    WHERE o.orgid=?;";
$metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $orgUrlKey);

if ($metaData->num_rows == 1) {
  $org = $metaData->fetch_assoc();
} else if ($metaData->num_rows == 0) {
  echo("I'm sorry, I don't know about org: " . $orgUrlKey);
  exit(0);
} else {
  echo("I'm sorry, I seem to be confused and think there are more than one org called: " . $orgUrlKey);
  exit(0);
}

// Arrays we use for tracking to later summarize.
$trophyCount = 0;
$trophyArr = array();
$recordArr = array();
$classesWithRecords = array();  // Map of classes that actually have a record.

// Keys for team data abbreviations ("Mens A", "Womens C", etc).
// No more than a D team please!
//
// This maps the english class name to the valid entry keys for that class.
$classkeys = array("Men's" => array("ma", "mb", "mc", "md"),
                   "Women's" => array("wa", "wb", "wc", "wd"),
                   "All Gender" => array("na", "nb", "nc", "nd"),
                   "Robotic" => array("ra", "rb", "rc", "rd"));

// (/org trophies, not design) Awards, specified org
// Applies to all orgs (e.g. including Support)
//
// We concat the 99 here for sorting purposes with the other results later.
$otherTrophyQuery = "SELECT year, concat('99', award) as award FROM hist_orgawards
                     WHERE orgid = ?
                     ORDER BY year DESC;";
$otherTrophies = dbBoundQuery($HISTORY_DATABASE, $otherTrophyQuery, "s", $orgUrlKey);

while ($o = $otherTrophies->fetch_assoc()) {
  addtrophy($o["year"], $o["award"]);
}

// (/org trophies, design) Design Awards, specified org
//
// Seems probable this only applies to racing orgs, but we do it anyway for all.
// Some awards just have org data and no buggy even though it clearly is for a specific buggy.
//
// We concat the 98 here for sorting purposes with the other results later.
//
// Note that while design awards imply that there is a buggy being awarded, we do not always
// have that association -- so there are a number of rows that have the org id in the designawards
// table, but no buggyid.  We need to get both sets, and then merge them.
$designTrophiesQuery = "SELECT year, concat('98Design - ', award) AS award, buggyname, buggyid FROM (
                               SELECT b.orgid, year, award, b.name AS buggyname, b.buggyid
                                 FROM hist_designawards d
                                 INNER JOIN hist_buggies b ON d.buggyid = b.buggyid
                               UNION SELECT orgid, year, award, NULL AS buggyname, NULL AS buggyid FROM hist_designawards) x
                          WHERE orgid = ?
                          ORDER BY year DESC;";
$designTrophies = dbBoundQuery($HISTORY_DATABASE, $designTrophiesQuery, "s", $orgUrlKey);

while ($d = $designTrophies->fetch_assoc()) {
  $extra = "";
  if (!empty($d["buggyid"])) {
    $extra = " (<a href=\"/history/buggy/".$d["buggyid"]."\">".$d["buggyname"]."</a>)";
  }
  addtrophy($d["year"], $d["award"], $extra);
}

$buggyListQuery = "SELECT b.name, b.birthyear, b.note, b.buggyid AS urlKey,
                          b.formerly AS formerid, fb.name AS fname,
                          fo.orgid AS forgid, fo.shortname AS forg
                   FROM hist_buggies b
                   LEFT JOIN hist_buggies fb ON b.formerly = fb.buggyid
                   LEFT JOIN hist_orgs fo ON fo.orgid = fb.orgid
                   WHERE b.orgid = ?
                   ORDER BY b.birthyear DESC;";
$buggyList = dbBoundQuery($HISTORY_DATABASE, $buggyListQuery, "s", $orgUrlKey);


// I apologize for how convoluted this query is.
//
// I don't want to make it worse, but note that this includes times when the prelim was faster than the reroll even
// if the reroll was granted and used.
$recordQuery = "SELECT A.class, A.team, A.record,
                       B.year, B.entryid
                  FROM (
                    SELECT class, team, min(time) AS record FROM (
                      SELECT class, team, nullif(prelim,0) AS time FROM hist_raceentries WHERE orgid = ?
                      UNION SELECT class, team, nullif(reroll,0) AS time FROM hist_raceentries WHERE orgid = ?
                      UNION SELECT class, team, nullif(final,0) AS time FROM hist_raceentries WHERE orgid = ?
                      UNION SELECT class, team, nullif(finalreroll,0) AS time FROM hist_raceentries WHERE orgid = ?) X
                    GROUP BY class, team) A
                  CROSS JOIN hist_raceentries B
                    ON B.orgid = ? AND B.class=A.class AND B.team=A.team
                       AND A.record IN (B.prelim, B.reroll, B.final, B.finalreroll);";
$recordData = dbBoundQuery($HISTORY_DATABASE, $recordQuery, "sssss", $orgUrlKey, $orgUrlKey, $orgUrlKey, $orgUrlKey, $orgUrlKey);
$hasRecords = $recordData->num_rows > 0;  // true if team has any records at all

while($r = $recordData->fetch_assoc()) {
  $classesWithRecords[$r["class"]] = "x";

  $key = $r["class"].$r["team"];

  // If a team/class ties themselves, keep the earlier one for the table.
  if (isset($recordArr[$key]) &&
      $r["year"] > $recordArr[$key]["year"]) {
    continue;
  }

  $recordArr[$key] = $r;
}

// And after that convoluted query, we have an absolutely enormous query to get all the historical team times.
//
// As of 2023 (plus, in order to handle robotic buggies) we can't assume that any org must have a Mens team,
// so we need to do a UNION SELECT by class to pull up each class separately.  Then, it is reassembled
// into by-year data below.
$entryQuery = "SELECT ma.year AS year, ma.class AS class,
               # Mens
                      case when ma.finalreroll > 0 then ma.finalreroll
                           when ma.final > 0 then ma.final
                           when ma.reroll > 0 then ma.reroll
                           when ma.prelim > 0 then ma.prelim
                           else NULL end AS 'a.timesecs',
                      case when ma.DQ <> '0' then 'DQ' else nullif(ma.Place, 0) end AS 'a.place',
                      ma.entryid AS 'a.entryid',
                      case when mb.finalreroll > 0 then mb.finalreroll
                           when mb.final > 0 then mb.final
                           when mb.reroll > 0 then mb.reroll
                           when mb.prelim > 0 then mb.prelim
                           else NULL end AS 'b.timesecs',
                      case when mb.DQ <> '0' then 'DQ' else nullif(mb.Place, 0) end AS 'b.place',
                      mb.entryid AS 'b.entryid',
                      case when mc.finalreroll > 0 then mc.finalreroll
                           when mc.final > 0 then mc.final
                           when mc.reroll > 0 then mc.reroll
                           when mc.prelim > 0 then mc.prelim
                           else NULL end AS 'c.timesecs',
                      case when mc.DQ <> '0' then 'DQ' else nullif(mc.Place, 0) end AS 'c.place',
                      mc.entryid AS 'c.entryid',
                      case when md.finalreroll > 0 then md.finalreroll
                           when md.final > 0 then md.final
                           when md.reroll > 0 then md.reroll
                           when md.prelim > 0 then md.prelim
                           else NULL end AS 'd.timesecs',
                      case when md.DQ <> '0' then 'DQ' else nullif(md.Place, 0) end AS 'd.place',
                      md.entryid AS 'd.entryid'
                  FROM hist_raceentries ma
                  LEFT JOIN hist_raceentries mb ON ma.year=mb.year AND mb.class = 'M' AND ma.orgid = mb.orgid AND mb.team = 'B'
                  LEFT JOIN hist_raceentries mc ON ma.year=mc.year AND mc.class = 'M' AND ma.orgid = mc.orgid AND mc.team = 'C'
                  LEFT JOIN hist_raceentries md ON ma.year=md.year AND md.class = 'M' AND ma.orgid = md.orgid AND md.team = 'D'
                  WHERE ma.team = 'A' AND ma.class = 'M' AND ma.orgid = ?

               # Womens
               UNION SELECT wa.year AS year, wa.class AS class,
                      case when wa.finalreroll > 0 then wa.finalreroll
                           when wa.final > 0 then wa.final
                           when wa.reroll > 0 then wa.reroll
                           when wa.prelim > 0 then wa.prelim
                           else NULL end AS 'a.timesecs',
                      case when wa.DQ <> '0' then 'DQ' else nullif(wa.Place, 0) end AS 'a.place',
                      wa.entryid AS 'a.entryid',
                      case when wb.finalreroll > 0 then wb.finalreroll
                           when wb.final > 0 then wb.final
                           when wb.reroll > 0 then wb.reroll
                           when wb.prelim > 0 then wb.prelim
                           else NULL end AS 'b.timesecs',
                      case when wb.DQ <> '0' then 'DQ' else nullif(wb.Place, 0) end AS 'b.place',
                      wb.entryid AS 'b.entryid',
                      case when wc.finalreroll > 0 then wc.finalreroll
                           when wc.final > 0 then wc.final
                           when wc.reroll > 0 then wc.reroll
                           when wc.prelim > 0 then wc.prelim
                           else NULL end AS 'c.timesecs',
                      case when wc.DQ <> '0' then 'DQ' else nullif(wc.Place, 0) end AS 'c.place',
                      wc.entryid AS 'c.entryid',
                      case when wd.finalreroll > 0 then wd.finalreroll
                           when wd.final > 0 then wd.final
                           when wd.reroll > 0 then wd.reroll
                           when wd.prelim > 0 then wd.prelim
                           else NULL end AS 'd.timesecs',
                      case when wd.DQ <> '0' then 'DQ' else nullif(wd.Place, 0) end AS 'd.place',
                      wd.entryid AS 'd.entryid'
                  FROM hist_raceentries wa
                  LEFT JOIN hist_raceentries wb ON wa.year=wb.year AND wb.class = 'W' AND wa.orgid = wb.orgid AND wb.team = 'B'
                  LEFT JOIN hist_raceentries wc ON wa.year=wc.year AND wc.class = 'W' AND wa.orgid = wc.orgid AND wc.team = 'C'
                  LEFT JOIN hist_raceentries wd ON wa.year=wd.year AND wd.class = 'W' AND wa.orgid = wd.orgid AND wd.team = 'D'
                  WHERE wa.team = 'A' AND wa.class = 'W' AND wa.orgid = ?

               # All Gender
               UNION SELECT na.year AS year, na.class AS class,
               case when na.finalreroll > 0 then na.finalreroll
                           when na.final > 0 then na.final
                           when na.reroll > 0 then na.reroll
                           when na.prelim > 0 then na.prelim
                           else NULL end AS 'a.timesecs',
                      case when na.DQ <> '0' then 'DQ' else nullif(na.Place, 0) end AS 'a.place',
                      na.entryid AS 'a.entryid',
                      case when nb.finalreroll > 0 then nb.finalreroll
                           when nb.final > 0 then nb.final
                           when nb.reroll > 0 then nb.reroll
                           when nb.prelim > 0 then nb.prelim
                           else NULL end AS 'b.timesecs',
                      case when nb.DQ <> '0' then 'DQ' else nullif(nb.Place, 0) end AS 'b.place',
                      nb.entryid AS 'b.entryid',
                      case when nc.finalreroll > 0 then nc.finalreroll
                           when nc.final > 0 then nc.final
                           when nc.reroll > 0 then nc.reroll
                           when nc.prelim > 0 then nc.prelim
                           else NULL end AS 'c.timesecs',
                      case when nc.DQ <> '0' then 'DQ' else nullif(nc.Place, 0) end AS 'c.place',
                      nc.entryid AS 'c.entryid',
                      case when nd.finalreroll > 0 then nd.finalreroll
                           when nd.final > 0 then nd.final
                           when nd.reroll > 0 then nd.reroll
                           when nd.prelim > 0 then nd.prelim
                           else NULL end AS 'd.timesecs',
                      case when nd.DQ <> '0' then 'DQ' else nullif(nd.Place, 0) end AS 'd.place',
                      nd.entryid AS 'd.entryid'
                  FROM hist_raceentries na
                  LEFT JOIN hist_raceentries nb ON na.year=nb.year AND nb.class = 'N' AND na.orgid = nb.orgid AND nb.team = 'B'
                  LEFT JOIN hist_raceentries nc ON na.year=nc.year AND nc.class = 'N' AND na.orgid = nc.orgid AND nc.team = 'C'
                  LEFT JOIN hist_raceentries nd ON na.year=nd.year AND nd.class = 'N' AND na.orgid = nd.orgid AND nd.team = 'D'
                  WHERE na.team = 'A' AND na.class = 'N' AND na.orgid = ?

               # Robotic
               UNION SELECT ra.year AS year, ra.class AS class,
               case when ra.finalreroll > 0 then ra.finalreroll
                           when ra.final > 0 then ra.final
                           when ra.reroll > 0 then ra.reroll
                           when ra.prelim > 0 then ra.prelim
                           else NULL end AS 'a.timesecs',
                      case when ra.DQ <> '0' then 'DQ' else nullif(ra.Place, 0) end AS 'a.place',
                      ra.entryid AS 'a.entryid',
                      case when rb.finalreroll > 0 then rb.finalreroll
                           when rb.final > 0 then rb.final
                           when rb.reroll > 0 then rb.reroll
                           when rb.prelim > 0 then rb.prelim
                           else NULL end AS 'b.timesecs',
                      case when rb.DQ <> '0' then 'DQ' else nullif(rb.Place, 0) end AS 'b.place',
                      rb.entryid AS 'b.entryid',
                      case when rc.finalreroll > 0 then rc.finalreroll
                           when rc.final > 0 then rc.final
                           when rc.reroll > 0 then rc.reroll
                           when rc.prelim > 0 then rc.prelim
                           else NULL end AS 'c.timesecs',
                      case when rc.DQ <> '0' then 'DQ' else nullif(rc.Place, 0) end AS 'c.place',
                      rc.entryid AS 'c.entryid',
                      case when rd.finalreroll > 0 then rd.finalreroll
                           when rd.final > 0 then rd.final
                           when rd.reroll > 0 then rd.reroll
                           when rd.prelim > 0 then rd.prelim
                           else NULL end AS 'd.timesecs',
                      case when rd.DQ <> '0' then 'DQ' else nullif(rd.Place, 0) end AS 'd.place',
                      rd.entryid AS 'd.entryid'
                  FROM hist_raceentries ra
                  LEFT JOIN hist_raceentries rb ON ra.year=rb.year AND rb.class = 'R' AND ra.orgid = rb.orgid AND rb.team = 'B'
                  LEFT JOIN hist_raceentries rc ON ra.year=rc.year AND rc.class = 'R' AND ra.orgid = rc.orgid AND rc.team = 'C'
                  LEFT JOIN hist_raceentries rd ON ra.year=rd.year AND rd.class = 'R' AND ra.orgid = rd.orgid AND rd.team = 'D'
                  WHERE ra.team = 'A' AND ra.class = 'R' AND ra.orgid = ?
                  ORDER BY year,class DESC;";

$entryResultSet = dbBoundQuery($HISTORY_DATABASE, $entryQuery, "ssss", $orgUrlKey, $orgUrlKey, $orgUrlKey, $orgUrlKey);
$entryMap = array();  // Map we use to combine a year into one row with classteam indications.
$entryTimes = array();   // Associative array of time-seconds by [year][ma/mb/wa/wb/etc]

while ($e = $entryResultSet->fetch_assoc()) {
  $year = $e["year"];
  foreach (["a","b","c","d"] as $team) {
    $class = strtolower($e["class"]);
    $classteam = $class . $team;
    if (array_key_exists($team.".timesecs", $e)) {
      $e[$team.".time"] = displayTime($e[$team.".timesecs"]);
      $entryTimes[$e["year"]][$classteam] = $e[$team.".timesecs"];
    }

    // Check if we need to add trophies
    if (!empty($e[$team.".place"])) {
      $place = $e[$team.".place"];
      // checkTrophyYear will ensure we only display trophies that existed
      // in that year.
      if ($place != "DQ" && checkTrophyYear($class, $year, $place)) {
        // The keying here ensures we sort race medals above other medals
        // and better places are sorted above lower places, regardless of class.
        //
        // TODO: We standardized on the sort order of Mens, Womens, All Gender in the
        // initial implementation of 3 class support, but 'N' sorts between 'M' and 'W',
        // so we change the prefix for All Gender to be 1 instead of 0.
        //
        // Likewise, we put robots below all gender (so add a "2" prefix), but as of 2023
        // there aren't robot awards anyway.
        $raceAwardSortPrefix = "0";
        if ($classteam[0] == 'n') {
          $raceAwardSortPrefix = "1";
        } else if ($classteam[0] == 'r') {
          $raceAwardSortPrefix = "2";
        }
        addtrophy($year, $raceAwardSortPrefix.$e[$team.".place"].$classteam[0]);
      }
    }

    // Copy data over to the main entry map for the year.
    if (!isset($entryMap[$year])) {
      $entryMap[$year] = array();
      $entryMap[$year]["year"] = $year;
    }
    // no need to copy timesecs, since it isn't displayed.
    $entryMap[$year][$classteam.".time"] = $e[$team.".time"];
    $entryMap[$year][$classteam.".place"] = $e[$team.".place"];
    $entryMap[$year][$classteam.".entryid"] = $e[$team.".entryid"];
  }
}

$entryData = array();  // Just a flat list of years in descending order with all the classes and teams.
$years = array_keys($entryMap);
krsort($years);
foreach($years as $year) {
  array_push($entryData,$entryMap[$year]);
}
unset($entryMap); // not needed any more

// Add a trophy to trophyarray.
// awardType is the text that describes the actual award
// extra is for any extra details that will be placed verbatim after the award in the list.
//       For example: a link to the buggy page for design comp awards.
function addtrophy($year, $awardType, $extra = "") {
  global $trophyArr, $trophyCount;

  $awardData = array("award" => $awardType,
                     "extra" => $extra);

  if(array_key_exists($year, $trophyArr)){
    array_push($trophyArr[$year],$awardData);
  } else {
    $trophyArr[$year]= array($awardData);
  }

  $trophyCount++;
}

// $yearParity is used to stripe the table with alternating background colors.
function displayraceyear($year, $entry, $yearParity=false) {
  global $RACEDAY_URL_PART;
  global $classkeys;

  $thisYearClasses = array();

  // How many rows does this year need?  [1 per class]
  foreach(array_keys($classkeys) as $class) {
    foreach($classkeys[$class] as $k) {
      if (isset($entry[$k.".entryid"])) {
        array_push($thisYearClasses, $class);
        break;
      }
    }
  }

  $rowspanText = "";
  $rows = count($thisYearClasses);
  if ($rows <= 0) {
    die ("oops, year with no rows: ".$year);
  }

  foreach ($thisYearClasses as $class) {
    $cssClass="";
    $classAnchor="";
    switch($class) {
      case "Men's":
        $cssClass = "mensRow";
        $classAnchor = "#mens";
        break;
      case "Women's":
        $cssClass = "womensRow";
        $classAnchor = "#womens";
        break;
      case "All Gender":
        $cssClass = "allgenderRow";
        $classAnchor = "#allgender";
        break;
      case "Robotic":
        $cssClass = "roboticRow";
        $classAnchor = "#robotic";
        break;
      default:
        die("oops, unknown class in ".$year.": ".$class);
    };

    if ($yearParity) {
      $cssClass = $cssClass . " table-parity-color year-parity";
    }

    echo("<tr class=\"classRow ".$cssClass."\"><td><a href=\"/history/".$RACEDAY_URL_PART."/".$year.$classAnchor."\">".$year."</a></td>");
    echo("<td class=\"classCol\">".$class."</td>");
    foreach ($classkeys[$class] as $entrytype) {
      if (isset($entry[$entrytype.".entryid"])) {
        $time = $entry[$entrytype.".time"];
        $outcome = $entry[$entrytype.".place"];
        $id = $entry[$entrytype.".entryid"];

        if (empty($time)) {
          $time = "--&nbsp;--&nbsp;--";
        }

        echo("<td><a href=\"/history/team/".$id."\">".$time."</a></td><td>".$outcome."</td>");
      } else {
        echo ("<td></td><td></td>");
      }
    }
    echo("</tr>\n");
  }
}

// Allows sorting on the trophy name stored in the "award" key.
function trophyCmp($a, $b) {
  $aval = $a["award"];
  $bval = $b["award"];

  if ($aval == $bval) {
    return 0;
  }
  return ($aval < $bval) ? -1 : 1;
}

function displaytrophyyear($trophies, $year){
  uasort($trophies, 'trophyCmp');
  echo("<tr><td>".$year."</td><td><ul class=\"list-unstyled mb-0\">");
  foreach($trophies as $t){
    $trophy = $t["award"];
    $extra = $t["extra"];

    echo("<li>");
    switch($trophy) {
      case "01m":
        echo("Men's 1st Place");
        break;
      case "02m":
        echo("Men's 2nd Place");
        break;
      case "03m":
        echo("Men's 3rd Place");
        break;
      case "04m":
        echo("Men's 4th Place");
        break;
      case "05m":
        echo("Men's 5th Place");
        break;
      case "06m":
        echo("Men's 6th Place");
        break;
      case "01w":
        echo("Women's 1st Place");
        break;
      case "02w":
        echo("Women's 2nd Place");
        break;
      case "03w":
        echo("Women's 3rd Place");
        break;
      case "04w":
        echo("Women's 4th Place");
        break;
      case "05w":
        echo("Women's 5th Place");
        break;
      case "06w":
        echo("Women's 6th Place");
        break;
      // See note where the tropihes are added for why we use "1" for raceAwardSortPrefix.
      case "11n":
        echo("All Gender 1st Place");
        break;
      case "12n":
        echo("All Gender 2nd Place");
        break;
      case "13n":
        echo("All Gender 3rd Place");
        break;
      case "14n":
        echo("All Gender 4th Place");
        break;
      case "15n":
        echo("All Gender 5th Place");
        break;
      case "16n":
        echo("All Gender 6th Place");
        break;
      case "98Design - 1":
        echo("Design Comp - 1st Place");
        break;
      case "98Design - 2":
        echo("Design Comp - 2nd Place");
        break;
      case "98Design - 3":
        echo("Design Comp - 3rd Place");
        break;
      case "98Design - Showcase Spark":
        echo("Design Comp - Showcase Spark");
        break;
      case "98Design - Honorable Mention":
        echo("Design Comp - Honorable Mention");
        break; 
      case "98Design - People's Choice":
        echo("Design Comp - People's Choice");
        break;
      case "99T-Shirt Award":
        echo("Best T-Shirt Award");
        break;
      case "99Chairman's Choice":
        // Named after Anne
        echo("Anne Witchner Chairman's Choice");
        break;
      case "99Spirit of Buggy":
        // Named after Tom
        echo("Tom Wood Spirit of Buggy");
        break;
      default:
        // Unknown Award ("Most Improved"?)
        // If we have a leading 2 digit sort key, remove it before displaying.
        if(preg_match("/^[0-9]{2}/", $trophy)) {
          $trophy = substr($trophy, 2);
        }
        echo($trophy);
    }
    echo($extra."</li>");
  }
  echo("</ul></td></tr>");
}

function displayrecord($entrytype) {
  // It might be nice to display directly some additional data (e.g. prelim vs final?)
  global $recordArr;
  if(isset($recordArr[$entrytype])){
    $r = $recordArr[$entrytype];
    echo("<a href=\"/history/team/".$r["entryid"]."\">".displayTime($r["record"])."<br />".$r["year"]."</a>");
  }
}

// Returns true if this org has at least 2 entries in the provided
// range for any of the given entry types.  That is, is there anything
// at all worth trying to graph?
function isTrendableOrg($entrytypes, $firstyear, $lastyear) {
  global $entryTimes;
  $entryCount = array();
  foreach ($entrytypes as $et) {
    $entryCount[$et] = 0;
  }
  for($year=$firstyear;$year<=$lastyear;$year++) {
    if (isset($entryTimes[$year])) {
      $times = $entryTimes[$year];
      foreach ($entrytypes as $et) {
        if (isset($times[$et])) {
          $entryCount[$et]++;
          if ($entryCount[$et] >= 2) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

function graphtrends($entrytypes, $firstyear, $lastyear) {
  global $entryTimes, $orgUrlKey, $org;
  $graphArr = array();
  $chartData = new pData();
  $filename = "trend".$orgUrlKey.$firstyear.$lastyear;
  foreach($entrytypes as $et) {
    $filename.=$et;
  }

  if(file_exists("/content/cache/graph/".$filename)){
    echo("<img src=\"/content/cache/graph/".$filename.".png\" alt=\"\" class=\"img-fluid my-2\">");
  } else {
    for($year=$firstyear;$year<=$lastyear;$year++){
      $chartData->addPoints($year,"Year");
      if(isset($entryTimes[$year])) {
        $times = $entryTimes[$year];
        foreach ($entrytypes as $entrytype) {
          if (isset($times[$entrytype])) {
            $graphArr[$entrytype][$year] = $times[$entrytype];
          } else {
            $graphArr[$entrytype][$year] = VOID;
          }
        }
      } else {
        foreach($entrytypes as $entrytype) {
          $graphArr[$entrytype][$year] = VOID;
        }
      }
    }

    foreach($entrytypes as $type){
      //remove series for which there are no records in the time range.  the "VOID" points end up being counted as 1.something, so > 100 filters out non-real entries
      if(array_sum($graphArr[$type]) > 100){
        $label = "";
        switch($type) {
          case "ma": $label = "Men's A"; break;
          case "mb": $label = "Men's B"; break;
          case "mc": $label = "Men's C"; break;
          case "mc": $label = "Men's D"; break;
          case "wa": $label = "Women's A"; break;
          case "wb": $label = "Women's B"; break;
          case "wc": $label = "Women's C"; break;
          case "wd": $label = "Women's D"; break;
          case "na": $label = "All Gender A"; break;
          case "nb": $label = "All Gender B"; break;
          case "nc": $label = "All Gender C"; break;
          case "nd": $label = "All Gender D"; break;
        }
        $chartData->addPoints($graphArr[$type],$label);
        $chartData->setSerieWeight($label,1);
      }
    }
    $chartTitle = $org["shortname"]." ".$firstyear."-".$lastyear;
    $chartFilename = $orgUrlKey."Mtrends";

    include("content/history/trendchart.inc");
  }
}
?>
<div class="row mb-2 align-items-center">
  <div class="col">
  <dl class="row">
  <dt class="col-sm-3">Founded</dt><dd class="col-sm-9"><?php echo($org["yearfounded"]); ?></dd>
  <?php
    if($org["orgurl"]) {
      // We don't store these with a leading "http://" so....
      // Hopefully everyone redirects to https if they use it.
      echo ("<dt class=\"col-sm-3\">Website</dt><dd class=\"col-sm-9\"><a href=\"http://".$org["orgurl"]."\">".$org["orgurl"]."</a></dd>");
    }
    if($org["note"]) {
      echo ("<dt class=\"col-sm-3\">Notes</dt><dd class=\"col-sm-9\">".$org["note"]."</dd>");
    }
  ?>
  </dl>
  </div>
  <?php if(isset($org["image_url"])) { ?>
  <div class="d-none d-sm-flex col align-items-center justify-content-end">
    <img class="img-fluid" style="max-height: 200px" src="<?php echo($org["image_url"]); ?>" />
  </div>
  <?php } ?>
</div>

<?php
  // Only graph trends in the last 20 years for A->C teams
  $thisYear = date("Y");
  $trendStartYear = $thisYear - 20;
  $trendMens = array("ma", "mb", "mc");
  $trendWomens = array("wa", "wb", "wc");
  $trendAllGender = array("na", "nb", "nc");
  $trendRobotic = array("ra", "rb", "rc");


  // Is there any data at all that is worth trying to trend for this org? (e.g. do we have a trends tab?)
  //
  // Also keep track of this per-class so we know what graphs to render.
  $trendableMens = isTrendableOrg($trendMens, $trendStartYear, $thisYear);
  $trendableWomens = isTrendableOrg($trendWomens, $trendStartYear, $thisYear);
  $trendableAllGender = isTrendableOrg($trendAllGender, $trendStartYear, $thisYear);
  $trendableRobotic = isTrendableOrg($trendRobotic, $trendStartYear, $thisYear);
  $trendableOrg = $trendableMens || $trendableWomens || $trendableAllGender || $trendableRobotic;
?>

<?php if ($org["isracingorg"] == 1) { ?>
  <ul class="nav nav-tabs mb-2" role="tablist">
    <li class="nav-item">
      <a id="raceresults-tab" href="#tab-raceresults" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-raceresults" aria-selected="true">Race Results</a>
    </li>
    <?php if ($hasRecords) { ?>
    <li class="nav-item">
      <a id="records-tab" href="#tab-records" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-records" aria-selected="false">Records</a>
    </li>
    <?php } ?>
    <li class="nav-item">
      <a id="buggies-tab" href="#tab-buggies" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-buggies" aria-selected="false">Buggies <span class="badge badge-primary"><?php echo($buggyList->num_rows); ?></span></a>
    </li>
    <li class="nav-item">
      <a id="trophies-tab" href="#tab-trophies" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-trophies" aria-selected="false">Trophies <span class="badge badge-primary"><?php echo($trophyCount); ?></span></a>
    </li>
    <?php if ($trendableOrg) { ?>
      <li class="nav-item">
        <a id="trends-tab" href="#tab-trends" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-trends" aria-selected="false">Trends</a>
      </li>
    <?php } ?>
  </ul>

  <script defer type="text/javascript" src="/js/cmubuggy-classfilter.js?ver=2023032100"></script>

  <div class="tab-content">
    <div class="tab-pane fade show active" id="tab-raceresults" role="tabpanel" aria-labelledby="raceresults-tab">
      <h2>Race Results</h2>

      <p>
      <b>Filter By Race Class:</b>
      <select name="classFilter" aria-controls="raceListTable">
        <option value="ALL" selected>Show All Classes</option>
        <option value="mensRow">Only Show Men's</option>
        <option value="womensRow">Only Show Women's</option>
        <option value="allgenderRow">Only Show All Gender</option>
        <option value="roboticRow">Only Show Robotic</option>
      </select>
      </p>

      <div class="table-responsive">
        <table class="table" id="raceListTable">
          <thead>
            <tr class="text-nowrap">
              <th>Year</th>
              <th class="classCol">Class</th>
              <th colspan="2">Team A</th>
              <th colspan="2">Team B</th>
              <th colspan="2">Team C</th>
              <th colspan="2">Team D</th>
            </tr>
          </thead>
          <tbody>
            <?php
              $yearParity = false;
              foreach ($entryData as $e) {
                displayraceyear($e["year"], $e, $yearParity);
                $yearParity = !$yearParity;
              }
            ?>
          </tbody>
        </table>
      </div>
    </div>
    <?php
    // We only display the records tab if the org actually _has_ records.  Even then
    // we only display the classes for which a record exists.
    if ($hasRecords) { ?>
    <div class="tab-pane fade" id="tab-records" role="tabpanel" aria-labelledby="records-tab">
      <h2>Organization Records</h2>
      <p><i>Note: This table does not account for DQs.</i></p>
      <div class="table-responsive">
        <table class="table">
          <thead>
            <tr>
              <th></th>
              <th>A team</th>
              <th>B team</th>
              <th>C team</th>
              <th>D team</th>
            </tr>
          </thead>
          <tbody>
            <?php if (isset($classesWithRecords["M"])) { ?>
            <tr>
              <th>Men's</th>
              <td><?php displayrecord("MA"); ?></td>
              <td><?php displayrecord("MB"); ?></td>
              <td><?php displayrecord("MC"); ?></td>
              <td><?php displayrecord("MD"); ?></td>
            </tr>
            <?php }
                  if (isset($classesWithRecords["W"])) { ?>
            <tr>
              <th>Women's</th>
              <td><?php displayrecord("WA"); ?></td>
              <td><?php displayrecord("WB"); ?></td>
              <td><?php displayrecord("WC"); ?></td>
              <td><?php displayrecord("WD"); ?></td>
            </tr>
            <?php }
                  if (isset($classesWithRecords["N"])) { ?>
            <tr>
              <th>All Gender</th>
              <td><?php displayrecord("NA"); ?></td>
              <td><?php displayrecord("NB"); ?></td>
              <td><?php displayrecord("NC"); ?></td>
              <td><?php displayrecord("ND"); ?></td>
            </tr>
            <?php }
                  if (isset($classesWithRecords["R"])) { ?>
            <tr>
              <th>Robotic</th>
              <td><?php displayrecord("RA"); ?></td>
              <td><?php displayrecord("RB"); ?></td>
              <td><?php displayrecord("RC"); ?></td>
              <td><?php displayrecord("RD"); ?></td>
            </tr>
            <?php } ?>
          </tbody>
        </table>
      </div>
    </div>
    <?php } ?>
    <div class="tab-pane fade" id="tab-buggies" role="tabpanel" aria-labelledby="buggies-tab">
      <h2>Buggies</h2>
      <div class="table-responsive">
        <table class="table">
          <thead>
            <tr>
              <th>Build Year</th>
              <th>Buggy</th>
              <th>Note</th>
            </tr>
          </thead>
          <tbody>
            <?php
              while ($b = $buggyList->fetch_assoc()) {
                echo("<tr><td>".$b["birthyear"]."</td>");
                echo("<td><a href=\"/history/buggy/".$b["urlKey"]."\">" . $b["name"] . "</a></td>");

                // Notes field also gets a bonus note if there is a "formerly" known as buggy.
                //
                // We add a period if there is no obvious ending punctuation on the note already
                // and there is a "former" buggy.
                //
                // Similar logic is in buggylist.inc.
                echo("<td>");
                $punctuation = "";

                if (!empty($b["note"])) {
                  echo($b["note"]);

                  $lastchar = substr($b["note"], -1);
                  if (!in_array($lastchar, [".","?","!",";",","])) {
                    $punctuation = ".  ";
                  }
                }
                if (!empty($b["fname"] && !empty($b["forg"]))) {
                  echo($punctuation."Formerly ".$b["forg"]."'s ".$b["fname"]);
                }
                echo("</td></tr>\n");
              }
            ?>
          </tbody>
        </table>
        </div>
    </div>
    <div class="tab-pane fade" id="tab-trophies" role="tabpanel" aria-labelledby="trophies-tab">
      <h2>Awards</h2>
      <div class="table-responsive">
        <table class="table">
          <thead>
            <tr>
              <th>Year</th>
              <th>Awards</th>
            </tr>
          </thead>
          <tbody>
            <?php
              krsort($trophyArr);
              array_walk($trophyArr,"displaytrophyyear");
            ?>
          </tbody>
        </table>
      </div>
    </div>
    <?php if ($trendableOrg) { ?>
      <div class="tab-pane fade" id="tab-trends" role="tabpanel" aria-labelledby="trends-tab">
        <h2>Trends</h2>
        <?php
            if ($trendableMens) {
              graphtrends($trendMens, $trendStartYear, $thisYear);
            }
            if ($trendableWomens) {
              graphtrends($trendWomens, $trendStartYear, $thisYear);
            }
            if ($trendableAllGender) {
              graphtrends($trendAllGender, $trendStartYear, $thisYear);
            }
            if ($trendableRobotic) {
              graphtrends($trendRobotic, $trendStartYear, $thisYear);
            }
        ?>
      </div>
    <?php } ?>
  </div>
<?php
  } else { // NOT A RACING ORG - Simpler handling since we only worry about trophies.
?>
  <h5>Trophies <span class="badge badge-primary"><?php echo($trophyCount); ?></span></h2>

  <div class="table-responsive">
    <table class="table">
      <thead>
        <tr>
          <th>Year</th>
          <th>Awards</th>
        </tr>
      </thead>
      <tbody>
        <?php
          krsort($trophyArr);
          array_walk($trophyArr,"displaytrophyyear");
        ?>
      </tbody>
    </table>
  </div>
<?php } ?>
