<?php

if (empty($_GET["urlkey"])) {
  // We should have been redirected into orglist.inc, not here.  What happened?
  die("Ooops, no org specified!");
}

$orgUrlKey = $_GET["urlkey"];


#(/org) metadata (existance, names, founding, url, notes)
$metaDataQuery = "SELECT case when isgreek = 1 then greekname else longname end AS longname,
                         case when isgreek = 1 OR longname != shortname then shortname else null end as shortname,
                         isracingorg,
                         orgurl,
                         yearfounded,
                         note
                    FROM hist_orgs
                    WHERE orgid=?;";
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

// Keys for various things ("Mens A", "Womens C", etc).
// No more than a D team please!
$entrytypes = array("ma", "mb", "mc", "md", "wa", "wb", "wc", "wd");

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
//
// TODO: this could return the buggy (when we know it) and notes, but we don't actually use these things in the display.
//       it would certainly be a nice touch to do so (at least to link to the buggy page, for example)
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

$buggyListQuery = "SELECT name, birthyear, note, buggyid AS urlKey FROM hist_buggies
                   WHERE orgid = ?
                   ORDER BY birthyear DESC;";
$buggyList = dbBoundQuery($HISTORY_DATABASE, $buggyListQuery, "s", $orgUrlKey);


// I apologize for how convoluted this query is.
//
// I don't want to make it worse, but note that this includes times when the prelim was faster than the reroll even
// if the reroll was granted and used.
$recordQuery = "SELECT A.class, A.team, A.record,
                       B.year, B.entryid
                  FROM (
                    SELECT class, team, min(time) AS record FROM (
                      SELECT year, class, team, nullif(prelim,0) AS time FROM hist_raceentries WHERE orgid = ?
                      UNION SELECT year, class, team, nullif(reroll,0) AS time FROM hist_raceentries WHERE orgid = ?
                      UNION SELECT year, class, team, nullif(final,0) AS time FROM hist_raceentries WHERE orgid = ?
                      UNION SELECT year, class, team, nullif(finalreroll,0) AS time FROM hist_raceentries WHERE orgid = ?) X
                    GROUP BY class, team) A
                  CROSS JOIN hist_raceentries B
                    ON B.class=A.class AND B.team=A.team AND A.record IN (B.prelim, B.reroll, B.final, B.finalreroll);";
$recordData = dbBoundQuery($HISTORY_DATABASE, $recordQuery, "ssss", $orgUrlKey, $orgUrlKey, $orgUrlKey, $orgUrlKey);

while($r = $recordData->fetch_assoc()) {
  $key = $r["class"].$r["team"];
  $recordArr[$key] = $r;
}

// And after that convoluted query, we have an absolutely enormous query to get all the historical team times.
//
// In an unusual step, we don't calculate the pretty version of time in the SQL query, because we need to hand the
// graphing tool raw seconds, so we just use our displayTime() utility function.
$entryQuery = "SELECT ma.year,
               # Mens
                      case when ma.finalreroll > 0 then ma.finalreroll
                           when ma.final > 0 then ma.final
                           when ma.reroll > 0 then ma.reroll
                           when ma.prelim > 0 then ma.prelim
                           else NULL end AS 'ma.timesecs',
                      case when ma.DQ <> '0' then 'DQ' else nullif(ma.Place, 0) end AS 'ma.place',
                      ma.entryid AS 'ma.entryid',
                      case when mb.finalreroll > 0 then mb.finalreroll
                           when mb.final > 0 then mb.final
                           when mb.reroll > 0 then mb.reroll
                           when mb.prelim > 0 then mb.prelim
                           else NULL end AS 'mb.timesecs',
                      case when mb.DQ <> '0' then 'DQ' else nullif(mb.Place, 0) end AS 'mb.place',
                      mb.entryid AS 'mb.entryid',
                      case when mc.finalreroll > 0 then mc.finalreroll
                           when mc.final > 0 then mc.final
                           when mc.reroll > 0 then mc.reroll
                           when mc.prelim > 0 then mc.prelim
                           else NULL end AS 'mc.timesecs',
                      case when mc.DQ <> '0' then 'DQ' else nullif(mc.Place, 0) end AS 'mc.place',
                      mc.entryid AS 'mc.entryid',
                      case when md.finalreroll > 0 then md.finalreroll
                           when md.final > 0 then md.final
                           when md.reroll > 0 then md.reroll
                           when md.prelim > 0 then md.prelim
                           else NULL end AS 'md.timesecs',
                      case when md.DQ <> '0' then 'DQ' else nullif(md.Place, 0) end AS 'md.place',
                      md.entryid AS 'md.entryid',

               # Womens
                      case when wa.finalreroll > 0 then wa.finalreroll
                           when wa.final > 0 then wa.final
                           when wa.reroll > 0 then wa.reroll
                           when wa.prelim > 0 then wa.prelim
                           else NULL end AS 'wa.timesecs',
                      case when wa.DQ <> '0' then 'DQ' else nullif(wa.Place, 0) end AS 'wa.place',
                      wa.entryid AS 'wa.entryid',
                      case when wb.finalreroll > 0 then wb.finalreroll
                           when wb.final > 0 then wb.final
                           when wb.reroll > 0 then wb.reroll
                           when wb.prelim > 0 then wb.prelim
                           else NULL end AS 'wb.timesecs',
                      case when wb.DQ <> '0' then 'DQ' else nullif(wb.Place, 0) end AS 'wb.place',
                      wb.entryid AS 'wb.entryid',
                      case when wc.finalreroll > 0 then wc.finalreroll
                           when wc.final > 0 then wc.final
                           when wc.reroll > 0 then wc.reroll
                           when wc.prelim > 0 then wc.prelim
                           else NULL end AS 'wc.timesecs',
                      case when wc.DQ <> '0' then 'DQ' else nullif(wc.Place, 0) end AS 'wc.place',
                      wc.entryid AS 'wc.entryid',
                      case when wd.finalreroll > 0 then wd.finalreroll
                           when wd.final > 0 then wd.final
                           when wd.reroll > 0 then wd.reroll
                           when wd.prelim > 0 then wd.prelim
                           else NULL end AS 'wd.timesecs',
                      case when wd.DQ <> '0' then 'DQ' else nullif(wd.Place, 0) end AS 'wd.place',
                      wd.entryid AS 'wd.entryid'
                  FROM hist_raceentries ma
                  LEFT JOIN hist_raceentries mb ON ma.year=mb.year AND mb.class = 'M' AND ma.orgid = mb.orgid AND mb.team = 'B'
                  LEFT JOIN hist_raceentries mc ON ma.year=mc.year AND mc.class = 'M' AND ma.orgid = mc.orgid AND mc.team = 'C'
                  LEFT JOIN hist_raceentries md ON ma.year=md.year AND md.class = 'M' AND ma.orgid = md.orgid AND md.team = 'D'
                  LEFT JOIN hist_raceentries wa ON ma.year=wa.year AND wa.class = 'W' AND ma.orgid = wa.orgid AND wa.team = 'A'
                  LEFT JOIN hist_raceentries wb ON ma.year=wb.year AND wb.class = 'W' AND ma.orgid = wb.orgid AND wb.team = 'B'
                  LEFT JOIN hist_raceentries wc ON ma.year=wc.year AND wc.class = 'W' AND ma.orgid = wc.orgid AND wc.team = 'C'
                  LEFT JOIN hist_raceentries wd ON ma.year=wd.year AND wd.class = 'W' AND ma.orgid = wd.orgid AND wd.team = 'D'
                  WHERE ma.team = 'A' AND ma.class = 'M' AND ma.orgid = ?
                  ORDER BY year DESC;";

$entryResultSet = dbBoundQuery($HISTORY_DATABASE, $entryQuery, "s", $orgUrlKey);
$entryData = array();  // Just a flat list.
$entryTimes = array();   // Associative array of time-seconds by [year][ma/mb/wa/wb/etc]
while($e = $entryResultSet->fetch_assoc()) {
  foreach ($entrytypes as $et) {
    if (array_key_exists($et.".timesecs", $e)) {
      $e[$et.".time"] = displayTime($e[$et.".timesecs"]);
      $entryTimes[$e["year"]][$et] = $e[$et.".timesecs"];
    }

    // Check if we need to add trophies
    if (!empty($e[$et.".place"])) {
      $place = $e[$et.".place"];
      if ($place != "DQ" && $place > 0 && $place < 7) {
        // The keying here ensures we sort race medals above other medals
        // and better places are sorted above lower places, regardless of class.
        addtrophy($e["year"], "0".$e[$et.".place"].$et[0]);
      }
    }
  }
  array_push($entryData, $e);
}

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

function displayraceyear($year, $entry) {
  global $entrytypes;
  echo("<tr><td><a href=\"/history/raceday/".$year."\">".$year."</a></td>");
  foreach ($entrytypes as $entrytype) {
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
  echo("</tr>");
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
        echo("Chairman's Choice");
        break;
      case "99Spirit of Buggy":
        echo("Spirit of Buggy");
        break;
      default:
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

<h1><?php
      echo($org["longname"]);
      if ($org["shortname"]) {
        echo (" <span style=\"font-size:.5em\">(".$org["shortname"].")</span>");
      }
?></h1>

<p>Founded: <?php echo($org["yearfounded"]); ?></p>
<?php
  if($org["orgurl"]) {
    // We don't store these with a leading "http://" so....
    // Hopefully everyone redirects to https if they use it.
    echo ("<p>Website: <a href=\"http://".$org["orgurl"]."\">".$org["orgurl"]."</a></p>");
  }
  if($org["note"]) {
    echo ("<p>Notes: ".$org["note"]."</p>");
  }
?>


<?php if ($org["isracingorg"] == 1) { ?>
  <ul class="nav nav-tabs mb-2" role="tablist">
    <li class="nav-item">
      <a id="raceresults-tab" href="#tab-raceresults" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-raceresults" aria-selected="true">Race Results</a>
    </li>
    <li class="nav-item">
      <a id="records-tab" href="#tab-records" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-records" aria-selected="false">Records</a>
    </li>
    <li class="nav-item">
      <a id="buggies-tab" href="#tab-buggies" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-buggies" aria-selected="false">Buggies <span class="badge badge-primary"><?php echo($buggyList->num_rows); ?></span></a>
    </li>
    <li class="nav-item">
      <a id="trophies-tab" href="#tab-trophies" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-trophies" aria-selected="false">Trophies <span class="badge badge-primary"><?php echo($trophyCount); ?></span></a>
    </li>
    <li class="nav-item">
      <a id="trends-tab" href="#tab-trends" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-trends" aria-selected="false">Trends</a>
    </li>
  </ul>

  <div class="tab-content">
    <div class="tab-pane fade show active" id="tab-raceresults" role="tabpanel" aria-labelledby="raceresults-tab">
      <h2>Race Results</h2>
      <div class="table-responsive">
        <table class="table">
          <thead>
            <tr class="text-nowrap">
              <th>Year</th>
              <th colspan="2">Men's A</th>
              <th colspan="2">Men's B</th>
              <th colspan="2">Men's C</th>
              <th colspan="2">Men's D</th>
              <th colspan="2">Women's A</th>
              <th colspan="2">Women's B</th>
              <th colspan="2">Women's C</th>
              <th colspan="2">Women's D</th>
            </tr>
          </thead>
          <tbody>
            <?php
              foreach ($entryData as $e) {
                displayraceyear($e["year"], $e);
              }
            ?>
          </tbody>
        </table>
      </div>
    </div>
    <div class="tab-pane fade" id="tab-records" role="tabpanel" aria-labelledby="records-tab">
      <h2>Organization Records</h2>
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
            <tr>
              <th>Men's</th>
              <td><?php displayrecord("MA"); ?></td>
              <td><?php displayrecord("MB"); ?></td>
              <td><?php displayrecord("MC"); ?></td>
              <td><?php displayrecord("MD"); ?></td>
            </tr>
            <tr>
              <th>Women's</th>
              <td><?php displayrecord("WA"); ?></td>
              <td><?php displayrecord("WB"); ?></td>
              <td><?php displayrecord("WC"); ?></td>
              <td><?php displayrecord("WD"); ?></td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
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
                echo("<td>".$b["note"]."</td></tr>");
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
    <div class="tab-pane fade" id="tab-trends" role="tabpanel" aria-labelledby="trends-tab">
      <h2>Trends</h2>
      <?php // Only show trends for the last 20 years.
            //
            // TODO: Be smarter about when to show the trends tab at all (e.g. don't show it for orgs that haven't raced)
            //       in 20 years :)
            $thisYear = date("Y");
            $startYear = $thisYear-20;
            graphtrends(array("ma","mb","mc"), $startYear, $thisYear);
            graphtrends(array("wa","wb","wc"), $startYear, $thisYear);
      ?>
    </div>
  </div>
<?php
  } else { // NOT A RACING ORG - Simpler handling since we only worry about trophies.
?>
  <h2>Trophies <span class="badge badge-primary"><?php echo($trophyCount); ?></span></h2>

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
