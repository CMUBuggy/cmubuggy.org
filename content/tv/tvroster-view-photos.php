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

  * {
    box-sizing: border-box;
  }

  div.fullscreen {
    height: 100%;
    width: 100%;

    padding: 10px;
    color: #fff;

    background-color: #00ff00;
    overflow: hidden;
  }

  div.content-box {
    background-color: #27266a;
  }

  span.team-header {
    font-size: 5vh;
    font-weight: bold;
  }

  div.team-member {
    font-size: 2vh;
  }

  span.buggy-header {
    font-size: 3vh;
    font-weight: bold;
    align: center;
  }

  span.buggy-birth {
    font-size: 2vh;
    font-weight: bold;
    align: center;
  }

  .vertical-center {
    min-height: 100%;  /* Fallback for browsers do NOT support vh unit */
    min-height: 100vh; /* These two lines are counted as one :-)       */

    display: flex;
    align-items: center;
  }

  .height-img-fluid {
    max-height: 100%;
    max-width: 100%;
    height: auto;
    width: auto;
  }

  img.blue-border {
    border: 1px solid #27266a;
    padding: 0.5rem;
    background-color: #27266a;
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
  // pusherRoles is just the pushers, since the driver gets their own special box
  $orderedRoles = array("Driver", "Hill 1", "Hill 2", "Hill 3", "Hill 4", "Hill 5");
  $pusherRoles = array_slice($orderedRoles, 1, 5);

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
                        b.birthyear AS birthyear,
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
  $teamQuery = "SELECT position, m.personid as personid,
                       concat(p.firstname, ' ', p.lastname) as personname
                  FROM hist_entrypeoplemap m
                  LEFT JOIN hist_people p ON p.personid = m.personid
                  WHERE entryid = ? && heattype = ?
                  ORDER BY heattype, position;";
  $teamResults = dbBoundQuery($HISTORY_DATABASE, $teamQuery, "ss", $urlkey, 'Prelim');

  // If we don't have a prelim roster, try a finals roster just in case (likely with
  // All Gender heats or past years were prelims were canceled)
  if ($teamResults->num_rows == 0) {
    $teamResults = dbBoundQuery($HISTORY_DATABASE, $teamQuery, "ss", $urlkey, 'Final');
  }

  // Its better if we render _something_ if we still have no names, so we just list everyone
  // as unknown by default.  This also fills in anyone missing as unknown.
  $teamArr = array();
  $teamIdArr = array();
  foreach ($orderedRoles as $role) {
    $teamArr[$role] = "<i>Unknown</i>";
  }

  // Robots get a special driver default.
  if ($header["class"] == 'Robotic') {
    $teamArr["Driver"] = "<i>Robotic Buggy</i>";
  }

  // Now, populate the people on the team.
  while($r = $teamResults->fetch_assoc()) {
    $role = $r["position"];
    $teamArr[$role] = $r["personname"];
    $teamIdArr[$role] = $r["personid"];
  }

  // TODO: check for missing photos, if any photos are missing, revert
  // to names only (2 columns, 3 names each, below centered buggy photo)

  // Note: Total page only allocates 95vh (not 100), so we can get a
  // transparent border around it.
?>

<div class="container-fluid vertical-center justify-content-center p-2">
<div class="container-fluid h-100">
  <div class="row content-box rounded-lg" style="height:10vh">
    <div class="col-6 my-auto">
        <?php
          // Team header
          $teamName = $header['org']." ".$header['class']." ".$header['team'];
          echo "<span class=\"team-header\">".$teamName."</span>";
        ?>
    </div>
    <div class="col-6 my-auto text-right">
        <?php
          echo "<span class=\"buggy-header\">".$header['buggy']."</span><br>";
          echo "<span class=\"buggy-birth\">Built: ".$header['birthyear']."</span>";
        ?>
    </div>
  </div>
  <div class="row" style="height:45vh">
        <div class="h-100 col-6 p-3 my-auto">
          <?php
            // TODO: Robots with no named safety driver

            echo("<div class=\"row my-auto mx-auto h-100 w-50\"><div class=\"col w-100 p-3\">");

            // It would be nice if this could work the same as the pusher photos, but because
            // of the different containers around it, it is easier to just implement it twice
            // to allow us to optimize the formatting separately.
            echo("<div class=\"row h-75\"><div class=\"col h-100 text-center \">");
            echo("<img class=\"mw-100 mh-100 img-thumbnail blue-border\" src=\"/files/2025rosterphotos/".$teamIdArr["Driver"].".jpg\">");
            echo("</div></div>");
            echo("<div class=\"row h-25\"><div class=\"col content-box team-member rounded-lg my-auto text-center\">");
            echo("<b>Driver</b><br>".$teamArr["Driver"]);
            echo("</div></div>");

            echo("</div></div>");
          ?>
        </div>
        <div class="h-100 col-6 my-1 p-3 text-center rounded-lg">
        <?php
          if (!empty($header["buggy_smugmug_slug"])) {
            $buggy_image_url = makeSmugmugUrl($header["buggy_smugmug_slug"], "L");
            echo "<img class=\"h-100 img-fluid img-thumbnail blue-border\" src=\"".$buggy_image_url."\">";
          } else {
            $buggy_image_url = "/img/logos/sweepstakes_logo_notext.svg";
            $style = "max-height: 40vh; filter: invert(100%) sepia(0%) saturate(0%) hue-rotate(93deg) brightness(103%) contrast(103%);";
            echo "<div class=\"content-box rounded-lg\"><img class=\"img-fluid\" style=\"" . $style . "\" src=\"".$buggy_image_url."\"></div>";
          }
        ?>
        </div>
  </div>

  <div class="row h-50" style="height:40vh">
    <div class="col my-auto content-box p-2 rounded-lg"><div class="row">
      <?php
        foreach ($pusherRoles as $role) {
          echo("<div class=\"col-sm\">");

          echo("<div class=\"row\"><div class=\"col\">");
          echo("<img class=\"img-fluid h-100\" src=\"/files/2025rosterphotos/".$teamIdArr[$role].".jpg\">");
          echo("</div></div>");
          echo("<div class=\"row\"><div class=\"col team-member\">");
          echo("<b>".$role."</b>:<br>".$teamArr[$role]);
          echo("</div></div>");

          echo("</div>");
        }
      ?>
    </div></div>
  </div>
</div>
</div>

</div>
</body>
</html>