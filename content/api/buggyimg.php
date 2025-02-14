<?php
  include_once("../../dbconfig.inc");
  include_once("../../util.inc");

  if (empty($_GET["urlkey"])) {
    // We should not have been redirected here due to top level .htaccess.  What happened?
    die("Ooops, no buggy specified!");
  }

  $buggyUrlKey = $_GET["urlkey"];

  #(/buggy) metadata (existance, build year, org, notes)
  $metaDataQuery = "SELECT b.smugmug_slug FROM hist_buggies b WHERE b.buggyid=?;";

  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $buggyUrlKey);

  if ($metaData->num_rows == 1) {
    $buggy = $metaData->fetch_assoc();
  } else if ($metaData->num_rows == 0) {
    http_response_code(404);
    echo("I'm sorry, I don't know about buggy: " . $buggyUrlKey);
    exit(0);
  } else {
    http_response_code(404);
    echo("I'm sorry, I seem to be confused and think there are more than one buggy called: " . $buggyUrlKey);
    exit(0);
  }

  // Buggy found, only one.
  if(isset($buggy["smugmug_slug"])) {
    $size = "S";
    // See if we've been asked for a nondefault size.
    if (!empty($_GET["size"])) {
      $requestSize = $_GET["size"];
      if (validSmugmugSize($requestSize)) {
        $size = $requestSize;
      }
    }
    $image_url = makeSmugmugUrl($buggy["smugmug_slug"], $size);
    header('Location: '.$image_url, true, 302);
  } else {
    // Buggy didn't have an image.
    http_response_code(404);
    echo("No image available.");
  }
?>