<?php // Logo, page title, breadcrumbs, countdown

if (!$SHOW_BREADCRUMBS) {
  // Special homepage hero

  // Note, the "swish" overlay, as an SVG, must:
  //  - not have width and height attributes on the svg tag
  //  - have preserveAspectRatio="none" as an attribute on the svg tag.

  //$imageUrl = makeSmugmugUrl("i-MbmV7ks", "X2");
  // i-HdckVMb Blackbird H2
  // i-FcQ3Ddm Scorch H2
  // i-sQhCG45 Barbie Freeroll
  // i-cmGx3MF Raptor H5
  // i-qJPW5L3 Emperor H5
  // i-JJXb8TS Brimstone H5
  $imageSet = [
    "i-HdckVMb", // RD24 Blackbird H2
    "i-FcQ3Ddm", // RD24 Scorch H2
    "i-sQhCG45", // RD24 Barbie Freeroll
    "i-cmGx3MF", // RD24 Raptor H5
    "i-qJPW5L3", // RD24 Emperor H5
    "i-JJXb8TS"  // RD24 Brimstone H5
  ];
  $imageSlug = array_rand($imageSet);
  $imageUrl = makeSmugmugUrl($imageSet[$imageSlug], "X2");

  // We need to use the style attribute in the hero-content div below.  This is because
  // it lets us put in a random image.  However, for some reason, we need to include
  // background-position and background-size as well, otherwise it looks incorrect, even
  // though they never change.

  // We only display the title on smaller displays where we lose the more complete
  // name out of the navbar (see pre-content.inc).
?>

<div class="d-flex hero-content"
     style="background: linear-gradient(rgba(0, 40, 84, 0.35),rgba(0, 40, 84, 0.35)),url('<?php echo($imageUrl); ?>'); background-position: center center; background-size: cover;">
<div class="d-block d-md-none mx-auto align-self-center">
  <h2>Buggy Alumni Association</h1>
</div>
<img class="hero-swish" src="../img/swish.svg">
</div>

<?php } else {
  // SHOW_BREADCRUMBS.  Not the homepage.
?>
<div class="container d-none d-md-flex justify-content-between align-middle my-3">
  <a href="/">
    <img src="/img/logo-2022-white.svg" width=125 alt="CMU Buggy Alumni Assocation logo" class="img-fluid mx-auto d-block">
  </a>

  <div class="ml-3 flex-grow-1 d-flex flex-column ">
    <div class="border-bottom border-2 border-primary my-2 py-2 text-right">
      <span class="my-2"
        title="<?php echo("$timerCount $timerUnit"); ?>">
        Raceday 2025 is April 4&ndash;5
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
}
?>