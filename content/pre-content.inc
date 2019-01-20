<?php
  date_default_timezone_set('America/New_York');
  $rddate = mktime(9, 0, 0, 4, 12, 2019);
  $currenttime = time();
  $hoursleft = floor(($rddate - $currenttime) / (60 * 60));
  $daysleft = floor($hoursleft / 24);
  $weeksleft = floor($daysleft / 7);
  $monthsleft = floor($daysleft / 30);
  $count = $monthsleft;
  $unit = "months";
  if ($count < 4){
    $count = $weeksleft;
    $unit = "weeks";
    if ($count < 4){
      $count = $daysleft;
      $unit = "days";
      if ($count < 4){
        $count = $hoursleft;
        $unit = "hours";
      }
    }
  }
  $small_word = 'in';
  if ($hoursleft < 0) {
    $small_word = 'now:';
    $count = "GO";
    $unit = "TIME";
  }
?>
<body>

  <header id="masthead" class="fixed-top mb-3">
    <nav class="navbar navbar-dark bg-primary px-0">
      <div class="container">
        <a href="/" class="navbar-brand d-inline-flex">
          <img src="/img/logo-square-small.png" alt="CMU Buggy Alumni Association logo" class="d-lg-none mr-2" height="30" width="30">
          <span class="d-none d-sm-inline">Buggy Alumni Association</span><span class="d-sm-none" title="Buggy Alumni Association">BAA</span>
        </a>
        <span class="navbar-text d-none d-md-inline text-warning" title="<?php echo("$count $unit"); ?>">Raceday 2019 is April 12&ndash;13</span>
        <button class="navbar-toggler d-lg-none collapsed" type="button" data-toggle="collapse" data-target="#navigation" aria-controls="navigation" aria-expanded="false" aria-label="toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
      </div>
    </nav>
  </header>

  <div class="container">
    <div class="row">
      <div id="navigation" class="col-lg-3 collapse d-lg-block">
        <a href="/" class="d-none d-lg-block">
          <img src="/img/logo-sidebar.png" alt="CMU Buggy Alumni Assocation logo" class="img-fluid mx-auto d-block">
        </a>
        <?php include_once 'leftmenu.inc'; ?>
      </div>

      <div class="col-lg-9">
