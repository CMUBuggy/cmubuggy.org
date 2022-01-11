<?php

if (!isset($_GET["urlkey"])) {
  // Redirects should prevent this and send invalid urls elsewhere, but you never know...
  die("Oops! No entry provided.");
} else {
  $urlkey = $_GET["urlkey"];
}

$headerQuery = "SELECT year, o.orgid, o.shortname AS org,
                       case when Class = 'M' then 'Men\'s'
                            when Class = 'W' then 'Women\'s'
                            else 'Unknown' end AS class,
                       case when Class = 'M' then 'mens'
                            when Class = 'W' then 'womens'
                            else 'Unknown' end AS classanchor,
                       Team AS team,
                       case when Prelim > 0 then concat(floor(Prelim / 60), ':', right(concat('0',format(Prelim % 60, 2)),5)) else NULL end AS Prelim,
                       case when Reroll > 0 then concat(floor(Reroll / 60), ':', right(concat('0',format(Reroll % 60, 2)),5)) else NULL end AS 'Prelim Reroll',
		                   case when Final > 0 then concat(floor(Final / 60), ':', right(concat('0',format(Final % 60, 2)),5)) else NULL end AS 'Final',
		                   case when FinalReroll > 0 then concat(floor(FinalReroll / 60), ':', right(concat('0',format(FinalReroll % 60, 2)),5)) else NULL end AS 'Final Reroll',
                       b.buggyid AS buggyid, b.name AS buggy,
                       nullif(e.place,0) AS place, e.dq, e.note
                  FROM hist_raceentries e
                  LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                  LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                  WHERE entryid = ?;";
$headerResults = dbBoundQuery("history", $headerQuery, "s", $urlkey);

if ($headerResults->num_rows != 1) {
  echo("I'm sorry, I couldn't make sense of the entry descriptor: " . $urlkey);
  exit(0);
} else {
  $header = $headerResults->fetch_assoc();
}

// Fetch all videos relevant to this entry.
$videoQuery = "SELECT h.isfinals,h.isreroll,v.youtubeid,v.title,v.urlkey FROM video v
                 LEFT JOIN hist_heats h ON CAST(v.heatid AS CHAR) = h.heatid
                 LEFT JOIN hist_raceentries e ON (CONCAT(h.year,'.',h.lane1)=e.entryid
                                                  OR CONCAT(h.year,'.',h.lane2)=e.entryid
                                                  OR CONCAT(h.year,'.',h.lane3)=e.entryid)
                 WHERE e.entryid = ?;";
$videoResults = dbBoundQuery("history", $videoQuery, "s", $urlkey);

$teamQuery = "SELECT heattype, position, concat(p.firstname, ' ', p.lastname) as personname, p.personid
                  FROM hist_entrypeoplemap m
                  LEFT JOIN hist_people p ON p.personid = m.personid
                  WHERE entryid = ?
                  ORDER BY heattype, position;";
$teamResults = dbBoundQuery("history", $teamQuery, "s", $urlkey);

// Constant ordered list of the roles/heattypes we (might) want to display.
$displayHeatTypes = array("Prelim", "Prelim Reroll", "Final", "Final Reroll");
$displayRoles = array("Driver", "Hill 1", "Hill 2", "Hill 3", "Hill 4", "Hill 5");

// Create a map for any video objects we have available.
$videomap = array();
while ($v = $videoResults->fetch_assoc()) {
  $videoObject = array(
    "youtubeid" => $v["youtubeid"],
    "title" => $v["title"],
    "urlkey" => $v["urlkey"]
  );
  if ($v['isfinals'] == 0 && $v['isreroll'] == 0) {
    $videomap['Prelim'] = $videoObject;
  } else if ($v['isfinals'] == 0 && $v['isreroll'] == 1) {
    $videomap['Prelim Reroll'] = $videoObject;
  } else if ($v['isfinals'] == 1 && $v['isreroll'] == 0) {
    $videomap['Final'] = $videoObject;
  } else {
    $videomap['Final Reroll'] = $videoObject;
  }
}

// create a template array of blank names for the roles we want to display, in order.
// Since PHP copies arrays instead of just the reference, we can use this as a common
// baseline for each heat.
$teamArrInit = array();
foreach ($displayRoles as $role) {
  $teamArrInit[$role] = "";
}

// This will hold all of the teams.
// First Level: Prelim/Final/Etc
// Second Level: Position
// Value: String Name Surrounded By link to the person page for their ID. (or empty string)
$teamArr = array();


// First, populate empty sets where we have times.
//
// This ensures we at least display the times we have.
foreach($displayHeatTypes as $ht) {
  if (!empty($header[$ht])) {
    $teamArr[$ht] = $teamArrInit;
  }
}

// Now, populate the team results.
while($r = $teamResults->fetch_assoc()) {
  $heattype = $r["heattype"];
  $role = $r["position"];
  if (!isset($teamArr[$heattype])) {
    // Maybe we don't have a time for this, but we do have a team!
    $teamArr[$heattype] = $teamArrInit;
  }
  $teamArr[$heattype][$role] = "<a href=\"/history/person/".$r["personid"]."\">".$r["personname"]."</a>";
}

// Page rendering starts here.

$year = $header["year"];
$class = $header["class"];

echo("<h1>");
echo("<a href=\"/history/raceday/".$year."#".$header["classanchor"]."\">".$year."</a> ");
echo("<a href=\"/history/org/".$header["orgid"]."\">".$header["org"]."</a> ".$header["class"]." ".$header["team"]);
echo("</h1>");

// Add other entry-level metadata here as we have it
echo("<table>");
echo("<tr><th>Buggy:</th><td><a href=\"/history/buggy/".$header["buggyid"]."\">".$header["buggy"]."</a></td></tr>");
if (!empty($header["place"])) {
  echo("<tr><th>Place:</th><td>". $header["place"]."</td></tr>");
}
if (!empty($header["dq"])) {
  echo("<tr><th>DQ:</th><td>". $header["dq"]."</td></tr>");
}
if (!empty($header["note"])) {
  echo("<tr><th>Notes:</th><td>". $header["note"]."</td></tr>");
}
echo("</table>");
?>

<div class="row">
  <?php
    foreach($teamArr as $heattype => $team) {
      echo("<div class=\"col-sm\">");
      echo("<h2>".$heattype."</h2>");

      echo("<dl class=\"row\">");
      foreach ($displayRoles as $role) {
        echo("<dt class=\"col-sm-5\">".$role."</dt><dd class=\"col-sm-7\">".$team[$role]."</dd>");
      }
      if(!empty($header[$heattype])) {
        echo("<dt class=\"col-sm-5\">Time</dt><dd class=\"col-sm-7\">".$header[$heattype]."</dd>");
      }
      echo("</dl>");

      // If we have a relevant video, share it.
      // TODO: This formatting is a bit janky, but placing at the bottom of the list seems better than
      //       placing at the top, at least for now.
      echo("<div style=\"text-align: center;\">");
      if (!empty($videomap[$heattype])) {
        $video = $videomap[$heattype];
        include("content/youtubevid.inc");
      }
      echo("</div>");

      echo("</div>");
    }
  ?>
</div>
