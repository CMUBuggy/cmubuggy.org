<html>
<head>
<title>TV Roster View</title>
<link rel="stylesheet" href="/css/cmubuggy-bootstrap.css?ver=2023091303" />

<style>
  html,
  body {
    margin: 0;
    padding: 0;
  }

  body {
    height: 100vh;
    width: 100vw;
  }

  hr { 
    border-top: 4px solid rgba(255,255,255,1);
  }

  * {
    box-sizing: border-box;
  }

  div.fullscreen {
    height: 100%;
    width: 100%;

    padding: 10px;
    font-size: 20px;
    color: #fff;
    background-color: #27266a;

    counter-reset: place;
  }

  div.roster-header {
    height: 10%;
  }
</style>
</head>
<body>
<div class="fullscreen">

<?php
  include_once("../../dbconfig.inc");
  include_once("../../util.inc");

  if (!isset($_GET["t"])) {
    // Redirects should prevent this and send invalid urls elsewhere, but you never know...
    die("Oops! No entry provided.");
  } else {
    $urlkey = $_GET["t"];
  }

  // Constants to provide an ordered list of the roles want to display.
  $displayRoles = array("Driver", "Hill 1", "Hill 2", "Hill 3", "Hill 4", "Hill 5");

  // Nearly identical query to /history/entry.php, except we don't need the video,
  // linking, or timing data.
  $headerQuery = "SELECT e.year, o.orgid, o.shortname AS org,
                         case when e.Class = 'M' then 'Men\'s'
                              when e.Class = 'W' then 'Women\'s'
                              when e.Class = 'N' then 'All Gender'
                              when e.Class = 'R' then 'Robotic'
                              else 'Unknown' end AS class,
                        Team AS team,
                        b.buggyid AS buggyid, b.name AS buggy,
                        b.smugmug_slug AS buggy_smugmug_slug
                    FROM hist_raceentries e
                    LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                    LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                    WHERE entryid = ?;";
  $headerResults = dbBoundQuery($HISTORY_DATABASE, $headerQuery, "s", $urlkey);

  if ($headerResults->num_rows != 1) {
    echo("I'm sorry, I couldn't make sense of the entry descriptor: " . $urlkey);
    exit(0);
  } else {
    $header = $headerResults->fetch_assoc();
  }

  // Similar to the same query in entry.inc, but only fetches prelims!
  $teamQuery = "SELECT position, concat(p.firstname, ' ', p.lastname) as personname
                  FROM hist_entrypeoplemap m
                  LEFT JOIN hist_people p ON p.personid = m.personid
                  WHERE entryid = ? && heattype='Prelim'
                  ORDER BY heattype, position;";
  $teamResults = dbBoundQuery($HISTORY_DATABASE, $teamQuery, "s", $urlkey);

  if ($teamResults->num_rows == 0) {
    echo("I'm sorry, there do not appear to be any people on the team: " . $urlkey);
    exit(0);
  } else {
    // Now, populate the people on the team.

    $teamArr = array();
    foreach ($displayRoles as $role) {
      $teamArr[$role] = "<i>Unknown</i>";
    }

    while($r = $teamResults->fetch_assoc()) {
      $role = $r["position"];
      $teamArr[$role] = $r["personname"];
    }
  }
?>

<div class="roster-header">
    <img height="95%" src="/img/logos/sweepstakes_logo_notext.svg"
         style="filter: invert(100%) sepia(0%) saturate(0%) hue-rotate(93deg) brightness(103%) contrast(103%);">
<?php
  $teamName = $header['org']." ".$header['class']." ".$header['team'];
  echo "<span class=\"h2\">".$teamName." Roster</span>";
?>
  </div>

<?php
  echo "<hr>";
  echo "<b>Buggy</b>: ".$header['buggy']."<br>";
  echo "<hr>";

  foreach ($displayRoles as $role) {
    echo "<b>".$role."</b>: ".$teamArr[$role]."<br>";
  }

  echo "<hr>";

  if (!empty($header["buggy_smugmug_slug"])) {
    $buggy_image_url = makeSmugmugUrl($header["buggy_smugmug_slug"], "S");
    echo "<img class=\"img-fluid img-thumbnail\" src=\"".$buggy_image_url."\">";
  }
?>

</div>
</body>
</html>