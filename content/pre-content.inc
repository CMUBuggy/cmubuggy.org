<?php
  date_default_timezone_set('America/New_York');
  $rddate = mktime(8, 0, 0, 4, 8, 2022);
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
  if ($hoursleft < 0) {
    $timerSmallWord = 'now:';
    $timerCount = "GO";
    $timerUnit = "TIME";
  }
?>
<body>

  <header id="masthead" class="fixed-top mb-3">
    <nav class="navbar navbar-dark bg-primary px-0">
      <div class="container">
        <span class="navbar-text d-none d-lg-inline text-light" title="<?php echo("$timerCount $timerUnit"); ?>">Raceday 2022 is April 8&ndash;9</span>
        <a href="/" class="navbar-brand d-inline-flex">
          <img src="/img/logo-2022-circle.svg" alt="CMU Buggy Alumni Association logo" class="d-lg-none mr-2" height="30" width="30">
          <span class="d-none d-sm-inline d-lg-none">Buggy Alumni Association</span>
          <span class="d-sm-none" title="Buggy Alumni Association">BAA</span>
        </a>
        <span class="navbar-text d-none d-md-inline d-lg-none text-light" title="<?php echo("$timerCount $timerUnit"); ?>">Raceday 2022 is April 8&ndash;9</span>
        <span class="navbar-text d-none d-lg-inline text-light">
          <strong>Records</strong> / Mens: 2:02.16 / Womens: 2:23.27
        </span>
    </section>
        <button class="navbar-toggler d-lg-none collapsed" type="button" data-toggle="collapse" data-target="#navigation" aria-controls="navigation" aria-expanded="false" aria-label="toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
      </div>
    </nav>
  </header>

  <div class="container">
    <div class="row">
      <div id="navigation" class="col-lg-3 collapse d-lg-block">
        <style>
        a.logolink:hover { color: var(--primary); text-decoration: none; }
        </style>
        <a href="/" class="d-none d-lg-block logolink">
          <img src="/img/logo-2022.svg" width=238 height=282 alt="CMU Buggy Alumni Assocation logo" class="img-fluid mx-auto d-block">
          <h2 style="text-align: center">Buggy Alumni Association</h2>
        </a>
        <?php include_once 'leftmenu.inc'; ?>
      </div>

      <div class="col-lg-9">
