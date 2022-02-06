<?php
  include_once("dbconfig.inc");
  include_once("lib/pChart_includes.inc");
  include_once("util.inc");
  session_start();

  $s = null;
  if(isset($_GET["s"])) {
    $s = $_GET["s"];
  }
  $title = "CMU Buggy Alumni Association";

  switch($s){
    case "history":
      $title = "History | ".$title;
      break;
    case "search":
      $title = "Search Results | ".$title;
      break;
    case "raceday":
      $title = "Raceday | ".$title;
      break;
    case "events":
      $title = "Events | ".$title;
      break;
  }

  if(empty($s)){
    $content = ("./content/homepage.inc");
  } else if(file_exists("./content/".$s.".inc")){
    $content = "./content/".$s.".inc";
  } else {
    $content = "./content/404.inc";
    $title = "Not Found | ".$title;
  }
?>
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf8">
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
  <meta name="keywords" content="" />
  <meta name="description" content="" />
  <meta name="google-site-verification" content="GXsMGGkXYJADa-Rw8I0azRbCk_ILRSXWwTkiHODCBrw" />
  <title><?php echo($title); ?></title>
  <?php include_once(ROOT_DIR."/content/cssjs.inc"); ?>
</head>
<?php
  include_once("content/pre-content.inc");
  include_once($content);
  include_once("content/post-content.inc");
?>
</body>
</html>
