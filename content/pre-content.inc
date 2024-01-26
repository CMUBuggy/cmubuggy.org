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
    if ($timerCount < 4){
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
<body>

  <header id="masthead" class="">
    <div class="bg-primary px-0 py-0 fixed-top">
      <div class="container d-flex justify-content-between py-3" >
        <a href="/" class="navbar-brand d-inline-flex text-light">
          <img src="/img/logo-2022-circle.svg" alt="CMU Buggy Alumni Association logo" class="d-lg-none mr-2" height="30" width="30">
          <span class="d-sm-inline d-md-none" title="Buggy Alumni Association">BAA</span>
          <span class="d-none d-md-inline">Buggy Alumni Association</span>
        </a>
        <span class="navbar-text d-none d-md-inline text-light" title="<?php echo("$timerCount $timerUnit"); ?>">Raceday 2024 is April 12&ndash;13</span>
        <button class="navbar-toggler d-lg-none collapsed" type="button" data-toggle="collapse" data-target="#navigation" aria-controls="navigation" aria-expanded="false" aria-label="toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
      </div>
    </div>

    <div class="container d-flex justify-content-between pt-3 pb-4">
      <a href="/" class="d-none d-lg-block">
        <img src="/img/logo-2022-white.svg" width=125 alt="CMU Buggy Alumni Assocation logo" class="img-fluid mx-auto d-block">
      </a>

      <div class="ml-3 flex-grow-1 d-flex flex-column ">
        <ul class="nav nav-tabs justify-content-end border-bottom border-2 border-primary mb-2">
          <!-- TODO: mobile nav -->
          <!-- TODO: Active tab, better styles -->
          <li class="nav-item">
            <a class="nav-link text-dark" href="/news">News</a>
          </li>
          <li class="nav-item">
            <a class="nav-link text-dark" href="/reference">What is Buggy?</a>
          </li>
          <li class="nav-item">
            <a class="nav-link text-dark " href="/history">History</a>
          </li>
          <li class="nav-item">
            <a class="nav-link text-dark" href="/about">About the BAA</a>
          </li>
          <li class="nav-item">
            <a class="nav-link text-dark" href="https://cmubuggy.smugmug.com" target="_blank">Gallery</a>
          </li>
        </ul>
        <!-- TODO: Actual breadcrumbs -->
        <div>
          Home > <?php echo("$BASE_TITLE"); ?>
        </div>
        <h1><?php echo("$BASE_TITLE"); ?></h1>
      </div>
    </div>

  </header>

  <div class="container">
    <div class="row">
