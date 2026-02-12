<html>
<head>
<title>TV Heat View</title>
<link rel="stylesheet" href="/css/cmubuggy-bootstrap.css?ver=2026020601" />

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

  div.team-header {
    font-size: 4vh;
    font-weight: bold;
  }

  div.reroll {
    font-size: 3vh;
    font-weight: bold;
    font-style: italic;
  }

  .vertical-center {
    min-height: 100%;  /* Fallback for browsers do NOT support vh unit */
    min-height: 100vh; /* These two lines are counted as one :-)       */

    display: flex;
    align-items: center;
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

  $lane1out = $lane2out = $lane3out = "";
  $rerolltext = "";

  if (isset($_GET["l1"]) || isset($_GET["l2"]) || isset($_GET["l3"]) || isset($_GET["rr"])) {
    // Manual Mode.
    function escapeIfParameterSet($param) {
      if (isset($_GET[$param])) {
        return htmlspecialchars($_GET[$param]);
      } else {
        return "";
      }
    }
    $lane1out = escapeIfParameterSet("l1");
    $lane2out = escapeIfParameterSet("l2");
    $lane3out = escapeIfParameterSet("l3");
    $rerolltext = escapeIfParameterSet("rr");
  } else if (!isset($_GET["t"])) {
    // Note: this page is not protected by redirects!
    die("Oops! No heat provided.");
  } else {
    // Database Mode
    $urlkey = $_GET["t"];

    // Nearly identical query to /history/entry.php, except we don't need the video,
    // linking, or timing data.
    $heatQuery = "SELECT number, isreroll, h.class AS heatclass,
        o1.shortname AS sn1, e1.team AS t1, e1.entryid AS teamid1, e1.class AS oclass1,
        o2.shortname AS sn2, e2.team AS t2, e2.entryid AS teamid2, e2.class AS oclass2,
        o3.shortname AS sn3, e3.team AS t3, e3.entryid AS teamid3, e3.class AS oclass3
      FROM hist_heats h
      LEFT JOIN hist_raceentries e1 ON concat(h.year, '.', Lane1) = e1.entryid LEFT JOIN hist_orgs o1 ON e1.orgid = o1.orgid
      LEFT JOIN hist_raceentries e2 ON concat(h.year, '.', Lane2) = e2.entryid LEFT JOIN hist_orgs o2 ON e2.orgid = o2.orgid
      LEFT JOIN hist_raceentries e3 ON concat(h.year, '.', Lane3) = e3.entryid LEFT JOIN hist_orgs o3 ON e3.orgid = o3.orgid
      WHERE h.heatid = ?";
    $heatResults = dbBoundQuery($HISTORY_DATABASE, $heatQuery, "s", $urlkey);

    if ($heatResults->num_rows != 1) {
      echo("I'm sorry, I couldn't make sense of the entry descriptor: " . $urlkey);
      exit(0);
    } else {
      $heat = $heatResults->fetch_assoc();
    }

    function getClassString($class) {
      $classMap = array(
        "M" => "Mens",
        "N" => "All Gender",
        "W" => "Womens",
        "R" => "Robotic",
        "Z" => "Mixed"
      );

      if (empty($class)) {
        return "";
      }

      if (array_key_exists($class, $classMap)) {
        return $classMap[$class]." ";
      } else {
        return "Unknown ";
      }
    }

    $classtext1 = $classtext2 = $classtext3 = "";

    if ($heat["heatclass"] == 'Z') {
      $classtext1 = getClassString($heat["oclass1"]);
      $classtext2 = getClassString($heat["oclass2"]);
      $classtext3 = getClassString($heat["oclass3"]);
    }

    if ($heat["isreroll"] == 1) {
      $rerolltext = "Reroll";
    }

    $lane1out = $heat["sn1"]." ".$classtext1.$heat["t1"];
    $lane2out = $heat["sn2"]." ".$classtext1.$heat["t2"];
    $lane3out = $heat["sn3"]." ".$classtext1.$heat["t3"];
  }
?>

<div class="container-fluid p-2">
  <div class="row mx-auto" style="width:95%; height:9vh;">
    <div class="col" style="height:100%">
      <div class="row content-box rounded-2" style="height:100%">
        <div class="col-1 my-auto">
        <img height="95%" src="/img/logos/sweepstakes_logo_notext.svg" class="py-1"
               style="filter: invert(100%) sepia(0%) saturate(0%) hue-rotate(93deg) brightness(103%) contrast(103%);">
        </div>
        <div class="col-1 my-auto"></div>
        <div class="col-3 my-auto team-header"><?php echo($lane1out); ?></div>
        <div class="col-3 my-auto team-header"><?php echo($lane2out); ?></div>
        <div class="col-3 my-auto team-header"><?php echo($lane3out); ?></div>
        <div class="col-1 my-auto reroll"><?php echo($rerolltext); ?></div>
      </div>
    </div>
  </div>
</div>

</div>
</body>
</html>