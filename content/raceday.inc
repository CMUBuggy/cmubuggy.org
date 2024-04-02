<?php
  $page = $_GET['p'];
  $file = "content/raceday/".$page.".inc";
  if(!empty($page) && file_exists($file)) {
    include_once($file);
  } else {
    include_once("./content/404.inc");
  }
?>
