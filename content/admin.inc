<nav class="navbar navbar-light navbar-expand bg-light mb-3">
  <ul class="navbar-nav flex-wrap">
    <li class="nav-item"><a class="nav-link" href="/admin">Admin Home</a></li>
    <li class="nav-item"><a class="nav-link" href="/admin/changelog">Change Log</a></li>
  </ul>
</nav>

<?php
  if (isset($uservars["adminlevel"])){
    if($uservars["adminlevel"] > 0){
      $p = null;
      if(isset($_GET["p"])) {
        $p = $_GET["p"];
      }
      if(empty($p)){
        include_once("content/admin/default.inc");
      }else {
        include_once("admin/".$p.".inc");
      }
    } else {
      include_once("admin/noaccess.inc");
    }
  } else {
    include_once("admin/noaccess.inc");
  }
?>
