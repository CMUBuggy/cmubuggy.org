<?php
  include_once("dbconfig.inc");
  include_once("lib/pChart_includes.inc");
  include_once("util.inc");
  session_start();

  $s = null;
  if(isset($_GET["s"])) {
    $s = $_GET["s"];
  }
  $TITLE_TAG = "CMU Buggy Alumni Association";

  $OGMAP = array(
    "og:type" => "website",
    "og:site_name" => "CMU Buggy Alumni Association"
    // TODO: Default "og:url" (apparently facebook cannot render og:image without it?)
  );

  switch($s){
    case "history":
      include_once("./content/history/opengraph/opengraphdata.inc");
      $OGMAP = getHistoryOpenGraphContent($OGMAP);
      $TITLE_TAG = "History | ".$TITLE_TAG;
      break;
    case "search":
      $TITLE_TAG = "Search Results | ".$TITLE_TAG;
      break;
    case "raceday":
      include_once("./content/raceday/opengraph/opengraphdata.inc");
      $OGMAP = getRacedayOpenGraphContent($OGMAP);
      $TITLE_TAG = "Raceday | ".$TITLE_TAG;
      break;
    case "tvportal":
      $TITLE_TAG = "TV Portal | ".$TITLE_TAG;
      break;
  }

  // If we haven't yet found a specific opengraph title, use <title>.
  if (!isset($OGMAP["og:title"])) {
    $OGMAP["og:title"] = $TITLE_TAG;
    if ($OGMAP["og:site_name"] == $OGMAP["og:title"]) {
      unset($OGMAP["og:site_name"]);
    }
  }

  if(empty($s)){
    // Can't be relative URLs, sadly (so dev sites will behave in unexpected ways).
    // But, our homepage at least should have a logo for opengraph data.
    $OGMAP["og:image"] = "https://cmubuggy.org/img/logo-2022-opengraph.jpg";
    $OGMAP["og:url"] = "https://cmubuggy.org/";

    $content = ("./content/homepage.inc");
  } else if(file_exists("./content/".$s.".inc")){
    $content = "./content/".$s.".inc";
  } else {
    $content = "./content/404.inc";
    $TITLE_TAG = "Not Found | ".$TITLE_TAG;
  }
?>
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf8">
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
  <meta name="google-site-verification" content="GXsMGGkXYJADa-Rw8I0azRbCk_ILRSXWwTkiHODCBrw" />
  <!-- OpenGraph Metadata -->
<?php
  foreach ($OGMAP as $key => $value) {
    echo("  <meta property=\"".$key."\" content=\"".$value."\" />\n");
  }

  // Provides <title>
  include_once(ROOT_DIR."/content/cssjs.inc");
?>
</head>
<?php
  include_once("content/pre-content.inc");
  include_once($content);
  include_once("content/post-content.inc");
?>
</body>
</html>
