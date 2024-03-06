<?php
// Disable the caching behavior, since it isn't obviosuly saving us much in practice and it is easy to reenable.
//
$CACHE_ENABLE = false;
$cachefile = str_replace("/","_",$_SERVER['REQUEST_URI'].".inc");
if($CACHE_ENABLE && file_exists("content/cache/history/".$cachefile)){
  include_once("content/cache/history/".$cachefile);
} else {
  $page = "intro";
  if(isset($_GET['p'])){
      $page = $_GET['p'];
    }
  ob_start();
  include_once("content/history/".$page.".inc");
  if ($CACHE_ENABLE && file_exists("content/cache/history/")) {
    file_put_contents("content/cache/history/".$cachefile,ob_get_contents());
  }
  ob_end_flush();
}
?>
