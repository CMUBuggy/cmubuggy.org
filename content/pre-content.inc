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

  <header id="masthead">
    <div class="navbar navbar-expand-lg navbar-dark bg-primary fixed-top shadow">
      <div class="container d-flex justify-content-between" >
        <a href="/" class="navbar-brand d-inline-flex">
          <img src="/img/logo-2022-circle.svg" alt="CMU Buggy Alumni Association logo" class="d-lg-none mr-2" height="30" width="30">
          <span class="d-sm-inline d-md-none" title="Buggy Alumni Association">BAA</span>
          <span class="d-none d-md-inline">Buggy Alumni Association</span>
        </a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarNavAltMarkup">
          <?php
            $nav_class = "";
            include(ROOT_DIR."/content/nav.inc");
          ?>
        </div>
      </div>
    </div>

    <!-- Breadcrumbs, countdown -->
    <div class="container d-none d-md-flex justify-content-between align-middle my-3">
      <a href="/">
        <img src="/img/logo-2022-white.svg" width=125 alt="CMU Buggy Alumni Assocation logo" class="img-fluid mx-auto d-block">
      </a>

      <div class="ml-3 flex-grow-1 d-flex flex-column ">
        <div class="border-bottom border-2 border-primary my-2 py-2 text-right">
          <span class="my-2"
            title="<?php echo("$timerCount $timerUnit"); ?>">
            Raceday 2024 is April 12&ndash;13
          </span>
        </div>
        <div>

          <?php
            // Check to see if someone has disabled breadcrumbs on this page
            if ($SHOW_BREADCRUMBS && count($BREADCRUMB_LIST) > 0) {
              // Breadcrumps are a list of 2-item lists (url, title).
              // If the URL is an empty string, don't linkify it.

              $first_crumb = true;
              foreach($BREADCRUMB_LIST as $crumb) {
                if (!$first_crumb) {
                  echo(" > ");
                } else {
                  $first_crumb = false;
                }
                $url = $crumb[0];
                $text = $crumb[1];
                if ($url != "") {
                  // We use text-reset here to keep the link black, but still retain the hover-underline effect.
                  echo("<a class=\"text-reset\" href=\"$url\">");
                }
                echo($text);
                if ($url != "") {
                  echo("</a>");
                }
              }
            } else {
              // Needed for consistent spacing on the home page.
              echo("&nbsp;");
            }
          ?>
        </div>
        <h1><?php echo("$BASE_TITLE"); ?></h1>
      </div>
    </div>
    <?php
      // Provide title on mobile.  SHOW_BREADCRUMBS is a hack to detect
      // the home page, so we don't show the extra title on the home page.
      //
      // TODO: Show Breadcrumbs Too?
      if ($SHOW_BREADCRUMBS) {
    ?>
      <div class="container d-md-none justify-content-between align-left my-3">
        <h1><?php echo("$BASE_TITLE"); ?></h1>
      </div>
    <?php
      }
    ?>
  </header>

  <div class="container">
    <div class="row">
      <div class="col-lg">
