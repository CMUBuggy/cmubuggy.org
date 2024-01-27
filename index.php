<?php
  include_once("dbconfig.inc");
  include_once("lib/pChart_includes.inc");
  include_once("util.inc");
  session_start();

  $s = null;
  if(isset($_GET["s"])) {
    $s = $_GET["s"];
  }

  $SHOW_BREADCRUMBS = true;  // False will indicate to hide the breadcrumbs (e.g. home page)
  $BREADCRUMB_LIST = [["/", "Home"]];  // List of breadcrumb (url, text) pairs.
  $BAA_TITLE = "CMU Buggy Alumni Association";  // Used to build titles.
  $BASE_TITLE = "";  // Title visible on the page, if any
  $TITLE_TAG = "";  // HTML <title> tag contents

  $OGMAP = array(
    "og:type" => "website",
    "og:site_name" => "CMU Buggy Alumni Association"
    // TODO: Default "og:url" (apparently facebook cannot render og:image without it?)
  );

  // Pre-Content Data Collection.
  // - Opengraph
  // - Title
  // - Breadcrumbs
  // TODO: Call down into a module and return a better BASE_TITLE and additional breadcrumbs, where appropriate.
  switch($s){
    case "history":
      include_once("./content/history/opengraph/opengraphdata.inc");
      $OGMAP = getHistoryOpenGraphContent($OGMAP);
      $BASE_TITLE = "History";
      array_push($BREADCRUMB_LIST, ["/history", "History"]);
      break;
    case "search":
      // Disabled in new design
      $BASE_TITLE = "Search Results";
      break;
    case "raceday":
      include_once("./content/raceday/opengraph/opengraphdata.inc");
      $OGMAP = getRacedayOpenGraphContent($OGMAP);
      $BASE_TITLE = "Raceday";
      array_push($BREADCRUMB_LIST, ["/raceday", "Raceday"]);
      break;
    case "tvportal":
      $BASE_TITLE = "TV Portal";
      array_push($BREADCRUMB_LIST, ["/tvportal", "TV Portal"]);
      break;
  }

  // If we don't have a base title yet, just use BAA_TITLE.
  // Otherwise, append BAA_TITLE into TITLE_TAG.
  if (empty($BASE_TITLE)) {
    $BASE_TITLE = $BAA_TITLE;
    $TITLE_TAG = $BAA_TITLE;
  } else {
    $TITLE_TAG = $BASE_TITLE." | ".$BAA_TITLE;
  }

  // If we haven't yet found a specific opengraph title, use <title>.
  if (!isset($OGMAP["og:title"])) {
    $OGMAP["og:title"] = $TITLE_TAG;
    if ($OGMAP["og:site_name"] == $OGMAP["og:title"]) {
      unset($OGMAP["og:site_name"]);
    }
  }

  if(empty($s)){
    // We are running the home page itself.

    // Opengraph Data can't be relative URLs, sadly (so dev sites will behave in unexpected ways).
    // But, our homepage at least should have a logo for opengraph data.
    $OGMAP["og:image"] = "https://cmubuggy.org/img/logo-2022-opengraph.jpg";
    $OGMAP["og:url"] = "https://cmubuggy.org/";

    $SHOW_BREADCRUMBS = false;

    $content = ("./content/homepage.inc");
  } else if(file_exists("./content/".$s.".inc")){
    // We are running some other page that is in the non-wordpress codebase (e.g. history, tvportal)
    $content = "./content/".$s.".inc";
  } else {
    // We don't know what the user wants.
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
  try {
    include_once($content);
  } catch (Exception $e) {}
  include_once("content/post-content.inc");
?>
</body>
</html>
