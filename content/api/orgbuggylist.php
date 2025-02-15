<?php
  include_once("../../dbconfig.inc");
  include_once("../../util.inc");

  if (empty($_GET["urlkey"])) {
    // We should not have been redirected here due to top level .htaccess.  What happened?
    die("Ooops, no org specified!");
  }

  $orgUrlKey = $_GET["urlkey"];

  #(/buggy) metadata (existance, build year, org, notes)
  $orgCheckQuery = "SELECT orgid FROM hist_orgs WHERE orgid=?;";
  $orgList = dbBoundQuery($HISTORY_DATABASE, $orgCheckQuery, "s", $orgUrlKey);

  if ($orgList->num_rows != 1) {
    http_response_code(404);
    echo("Didn't recognize org: ". $orgUrlKey);
    exit(0);
  }

  $buggyListQuery = "SELECT name, birthyear, note, buggyid, smugmug_slug, formerly
                        FROM hist_buggies
                        WHERE orgid = ?
                        ORDER BY birthyear DESC;";
  $buggyList = dbBoundQuery($HISTORY_DATABASE, $buggyListQuery, "s", $orgUrlKey);

  $buggyOutput = array();

  while ($b = $buggyList->fetch_assoc()) {
    // If formerly is null, don't include it.
    if (array_key_exists('formerly', $b) && $b['formerly'] === null) {
      unset($b['formerly']);
    }

    // If notes are blank, don't include them.
    if (array_key_exists('note', $b) && $b['note'] === "") {
      unset($b['note']);
    }

    $newItem = $b;
    array_push($buggyOutput, $b);
  }

  header('Content-Type: application/json');
  echo(json_encode($buggyOutput));
?>
