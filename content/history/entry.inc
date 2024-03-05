<?php

if (!isset($_GET["urlkey"])) {
  // Redirects should prevent this and send invalid urls elsewhere, but you never know...
  die("Oops! No entry provided.");
} else {
  $urlkey = $_GET["urlkey"];
}

// To fetch the videos requires a somwhat complex join against all possible lanes in the heats table.
// This, combined with the fact that we need 2 bits of video data for each of (up to) 4 heats makes this a bit
// less readable than it could be.
$headerQuery = "SELECT e.year, o.orgid, o.shortname AS org,
                       case when e.Class = 'M' then 'Men\'s'
                            when e.Class = 'W' then 'Women\'s'
                            when e.Class = 'N' then 'All Gender'
                            when e.Class = 'R' then 'Robotic'
                            else 'Unknown' end AS class,
                       case when e.Class = 'M' then 'mens'
                            when e.Class = 'W' then 'womens'
                            when e.Class = 'N' then 'allgender'
                            when e.Class = 'N' then 'Robotic'
                            else 'Unknown' end AS classanchor,
                       Team AS team,
                       Prelim, Reroll AS 'Prelim Reroll', Final, FinalReroll AS 'Final Reroll',
                       b.buggyid AS buggyid, b.name AS buggy,
                       nullif(e.place,0) AS place, e.dq, e.note,
                       vp.youtubeid AS pyoutubeid, vp.title AS ptitle,
                       vr.youtubeid AS ryoutubeid, vr.title AS rtitle,
                       vf.youtubeid AS fyoutubeid, vf.title AS ftitle,
                       vfr.youtubeid AS fryoutubeid, vfr.title AS frtitle
                  FROM hist_raceentries e
                  LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                  LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                  LEFT JOIN hist_heats hp ON hp.isfinals = 0 AND hp.isreroll = 0
                                             AND (CONCAT(hp.year,'.',hp.lane1)=e.entryid
                                                  OR CONCAT(hp.year,'.',hp.lane2)=e.entryid
		                                              OR CONCAT(hp.year,'.',hp.lane3)=e.entryid)
                  LEFT JOIN video vp ON vp.heatid = hp.heatid
                  LEFT JOIN hist_heats hr ON hr.isfinals = 0 AND hr.isreroll = 1
                                             AND (CONCAT(hr.year,'.',hr.lane1)=e.entryid
                                                  OR CONCAT(hr.year,'.',hr.lane2)=e.entryid
		                                              OR CONCAT(hr.year,'.',hr.lane3)=e.entryid)
                  LEFT JOIN video vr ON vr.heatid = hr.heatid
                  LEFT JOIN hist_heats hf ON hf.isfinals = 1 AND hf.isreroll = 0
                                             AND (CONCAT(hf.year,'.',hf.lane1)=e.entryid
                                                  OR CONCAT(hf.year,'.',hf.lane2)=e.entryid
		                                              OR CONCAT(hf.year,'.',hf.lane3)=e.entryid)
                  LEFT JOIN video vf ON vf.heatid= hf.heatid
                  LEFT JOIN hist_heats hfr ON hfr.isfinals = 1 AND hfr.isreroll = 1
                                             AND (CONCAT(hfr.year,'.',hfr.lane1)=e.entryid
                                                  OR CONCAT(hfr.year,'.',hfr.lane2)=e.entryid
		                                              OR CONCAT(hfr.year,'.',hfr.lane3)=e.entryid)
                  LEFT JOIN video vfr ON vfr.heatid = hfr.heatid
                  WHERE entryid = ?;";
$headerResults = dbBoundQuery($HISTORY_DATABASE, $headerQuery, "s", $urlkey);

if ($headerResults->num_rows != 1) {
  echo("I'm sorry, I couldn't make sense of the entry descriptor: " . $urlkey);
  exit(0);
} else {
  $header = $headerResults->fetch_assoc();
}

$teamQuery = "SELECT heattype, position, concat(p.firstname, ' ', p.lastname) as personname, p.personid
                  FROM hist_entrypeoplemap m
                  LEFT JOIN hist_people p ON p.personid = m.personid
                  WHERE entryid = ?
                  ORDER BY heattype, position;";
$teamResults = dbBoundQuery($HISTORY_DATABASE, $teamQuery, "s", $urlkey);

// Constants to provide an ordered list of the roles/heattypes we (might) want to display.
$displayHeatTypes = array("Prelim", "Prelim Reroll", "Final", "Final Reroll");
$displayRoles = array("Driver", "Hill 1", "Hill 2", "Hill 3", "Hill 4", "Hill 5");

// Create a map for any video objects we have available from the fetched "header" data.
// The keys must match $displayHeatTypes.
$heatTypeVideoPrefix = array('Prelim' => 'p','Prelim Reroll' => 'r','Final' => 'f', 'Final Reroll' => 'fr');
$videomap = array();
foreach ($heatTypeVideoPrefix as $type => $vp) {
  if (!empty($header[$vp."youtubeid"])) {
    $videomap[$type] = array(
      "youtubeid" => $header[$vp."youtubeid"],
      "title" => $header[$vp."title"]
    );
  }
}

$year = $header["year"];
$class = $header["class"];

// create a template array of blank names for the roles we want to display, in order.
// Since PHP copies arrays instead of just the reference, we can use this as a common
// baseline for each heat.
$teamArrInit = array();
foreach ($displayRoles as $role) {
  $teamArrInit[$role] = "<i>Unknown</i>";
}

// Robotic buggies don't (generally), have drivers, so "unknown" isn't accurate.  However,
// this can be overridden later by the presense of a driver in the entrypeoplemap (say, for an R/C pilot).
if ($class == 'Robotic') {
  $teamArrInit['Driver']  = '<i>Robotic Buggy</i>';
}


// This will hold all of the teams.
// First Level: Prelim/Final/Etc
// Second Level: Position
// Value: String Name Surrounded By link to the person page for their ID. (or empty string)
$teamArr = array();

// We use the presense of a $teamArr entry for a given heat type to indicate we have _some_ data
// for that heat.  So, we treat our 3 sources of data each slightly separately, and only
// create a team array (even an unknown one), if any have data.
//
// Our 3 data sources: times, the entrypeople map, and videos.
//
// First, populate empty sets where we have times.  This is pretty simple.
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
    // We haven't yet seen this heat for either times or people, so add a blank people array.
    $teamArr[$heattype] = $teamArrInit;
  }
  $teamArr[$heattype][$role] = "<a href=\"/history/person/".$r["personid"]."\">".$r["personname"]."</a>";
}

// If we are still missing a heat that we have data for we first need to check to see
// if this is the result of the heats table keying "finals reroll" based on day, but the times being based
// on when rerolls are earned.  So:
//
// If we have a a final reroll video, but no other heat data for final reroll, _and_ we have
// no prelim reroll video, reattribute the final reroll video to the prelim reroll heat.
//
// Example heats that get us into trouble without this:
//   2004.SPI.MB
//   2004.PKT.MA
//
// This is a hack that might break if the final reroll _acutally_ had no time (e.g. crash).
//
// This, naturally, relies on adding a blank team array for both times and people _first_.
if (isset($videomap["Final Reroll"])
    && !isset($teamArr["Final Reroll"])
    && !isset($videomap["Prelim Reroll"])) {
      $videomap["Prelim Reroll"] = $videomap["Final Reroll"];
      unset($videomap["Final Reroll"]);
}

// Finally, populate empty team data if we don't have a team for a given heat, but we do have
// either a time or a video.
foreach($displayHeatTypes as $ht) {
  if (!isset($teamArr[$ht]) && !empty($videomap[$ht])) {
    $teamArr[$ht] = $teamArrInit;
  }
}

// Page rendering starts here.

// Add entry-level metadata here as we have it
echo("<table>");
echo("<tr><th class=\"pr-3\">Buggy:</th><td><a href=\"/history/buggy/".$header["buggyid"]."\">".$header["buggy"]."</a></td></tr>");
if (!empty($header["place"])) {
  echo("<tr><th class=\"pr-3\">Place:</th><td>". $header["place"]."</td></tr>");
}
if (!empty($header["dq"])) {
  echo("<tr><th class=\"pr-3\">DQ:</th><td>". $header["dq"]."</td></tr>");
}
if (!empty($header["note"])) {
  echo("<tr><th class=\"pr-3\">Notes:</th><td>". $header["note"]."</td></tr>");
}
echo("<tr><th class=\"pr-3\">See Also:</th><td>");
echo("<a href=\"/history/raceday/".$year."#".$header["classanchor"]."\">Raceday ".$year."</a>,&nbsp;");
echo("<a href=\"/history/org/".$header["orgid"]."\">".$header["org"]."</a>");
echo("</td></tr>");


echo("</table>");
echo("<hr>");
?>

<div class="row">
  <?php
    // Use $displayHeatTypes to force an ordering on the display.
    foreach($displayHeatTypes as $heattype) {
      if (!isset($teamArr[$heattype])) {
        // If we have no data for this heattype, skip it.
        continue;
      }
      $team = $teamArr[$heattype];

      echo("<div class=\"col-sm\">");
      echo("<h2>".$heattype."</h2>");

      echo("<dl class=\"row\">");
      foreach ($displayRoles as $role) {
        echo("<dt class=\"col-sm-5\">".$role."</dt><dd class=\"col-sm-7\">".$team[$role]."</dd>");
      }
      if(!empty($header[$heattype])) {
        echo("<dt class=\"col-sm-5\">Time</dt><dd class=\"col-sm-7\">".displayTime($header[$heattype])."</dd>");
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
