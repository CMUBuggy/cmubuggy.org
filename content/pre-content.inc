<?php
  date_default_timezone_set('America/New_York');
  $rddate = mktime(8, 0, 0, 4, 12, 2024);
  $currenttime = time();
  $hoursleft = floor(($rddate - $currenttime) / (60 * 60));
  $daysleft = floor($hoursleft / 24);
  $weeksleft = floor($daysleft / 7);
  $monthsleft = floor($daysleft / 30);
  $timerCount = $monthsleft;
  $timerUnit = "months";
  if ($timerCount < 4){
    $timerCount = $weeksleft;
    $timerUnit = "weeks";
    if ($timerCount < 8){
      $timerCount = $daysleft;
      $timerUnit = "days";
      if ($timerCount < 4){
        $timerCount = $hoursleft;
        $timerUnit = "hours";
      }
    }
  }
  $timerSmallWord = 'in';

  // when we get close or go past the time, add excitement.
  if ($hoursleft < 0) {
    $timerSmallWord = 'now:';
    $timerCount = "GO";
    $timerUnit = "TIME";
  } else if ($hoursleft < 1) {
    $timerSmallWord = '';
    $timerCount = "so very";
    $timerUnit = "soon";
  }
?>

<header id="header">
  <div class="navbar navbar-expand-lg navbar-dark bg-primary fixed-top shadow">
    <div class="container d-flex justify-content-between" >
      <a href="/" class="navbar-brand d-inline-flex">
        <img src="/img/logo-2022-circle.svg" alt="CMU Buggy Alumni Association logo" class="d-md-none mr-2" height="30" width="30">
        <span class="d-sm-inline d-md-none" title="Buggy Alumni Association">BAA</span>
        <span class="d-none d-md-inline">Buggy Alumni Association</span>
      </a>
      <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>
      <div class="collapse navbar-collapse" id="navbarNavAltMarkup">
        <?php include_once(ROOT_DIR."/content/nav.inc") ?>
      </div>
    </div>
  </div>

  <?php include_once(ROOT_DIR."/content/masthead.inc") ?>
</header>
