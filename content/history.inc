<?php
    $org = new org();
    $orgList = $org->GetList(array(array("isactive", "=", "1"),array("isracingorg", "=", "1")),"shortname");
?>

<div id="topnav">
  <ul class="sf-menu">
    <li><a href="/history/sweepstakes">Sweepstakes</a></li>
    <li><a href="/history/org">Organizations</a>
      <ul>
        <?php
        foreach ($orgList as $org)
        {
            echo("<li><a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a></li>");
        }
        ?>
        <li><a href="/history/org#past">Past Racing Orgs</a></li>
        <li><a href="/history/org#support">Supporting Orgs</a></li>
      </ul>
    </li>
    <li><a href="/history/raceday">Races</a></li>
    <li><a href="/history/record">Records</a></li>
    <li><a href="/history/award">Awards</a></li>
    <li><a href="/history/buggy">Buggies</a></li>
    <!--<li><a href="/history/person">People</a></li>-->
    <li><a href="/history/buggybook">Buggy Books</a></li>
  </ul>
</div>
<?php
$cachefile = str_replace("/","_",$_SERVER['REQUEST_URI'].".inc");
if(file_exists("content/cache/history/".$cachefile)){
  include_once("content/cache/history/".$cachefile);
} else {
  $page = "intro";
  if(isset($_GET['p'])){
      $page = $_GET['p'];
    }
  ob_start();
    include_once("content/history/".$page.".inc");
  if (file_exists("content/cache/history/")) {
    file_put_contents("content/cache/history/".$cachefile,ob_get_contents());
  }
  ob_end_flush();
}
?>
