<?php
  $query = "SELECT orgid, shortname FROM 0orgs WHERE isactive=1 AND isracingorg=1 ORDER BY shortname;";
  $orgs = dbQuery("history",$query);
?>

<nav class="navbar navbar-light navbar-expand bg-light mb-3">
  <ul class="navbar-nav flex-wrap">
    <li class="nav-item"><a class="nav-link" href="/history/sweepstakes">Sweepstakes</a></li>
    <li class="nav-item dropdown">
      <a href="#" class="nav-link dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Organizations</a>
      <div class="dropdown-menu">
        <?php
          while ($org = $orgs->fetch_assoc()) {
            echo '<a class="dropdown-item" href="/history/org/' . $org["orgid"]. '">' . $org["shortname"] . '</a>';
          }
        ?>
        <div class="dropdown-divider"></div>
        <a class="dropdown-item" href="/history/org">All Organizations</a>
        <a class="dropdown-item" href="/history/org#past">Past Racing Orgs</a>
        <a class="dropdown-item" href="/history/org#support">Supporting Orgs</a>
      </div>
    </li>
    <li class="nav-item"><a class="nav-link" href="/history/raceday">Races</a></li>
    <li class="nav-item"><a class="nav-link" href="/history/record">Records</a></li>
    <li class="nav-item"><a class="nav-link" href="/history/award">Awards</a></li>
    <li class="nav-item"><a class="nav-link" href="/history/buggy">Buggies</a></li>
    <li class="nav-item"><a class="nav-link" href="/history/buggybook">Buggy Books</a></li>
  </ul>
</nav>

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
