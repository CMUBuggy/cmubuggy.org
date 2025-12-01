<div class="row">
  <div class="col-md-8">
    <?php
      // MOTD Box -- Should be the very first thing.  Does a database read and will show only if
      // a message is configured.
      include ("homepageboxes/homepage-motd.inc");

      // Useful to quickly enable in the case of rain on raceday.
      // include("homepageboxes/homepage-raceday-rainout.inc");

      // For when the auction goes live (includes a timeout for end of auction)
      // include("homepageboxes/homepage-raceday-auction.inc");

      // Endowment Application Promobox (includes a timeout)
      // include("homepageboxes/homepage-endowmentbox.inc");

      // Giving Tuesday Promo Box (has start: Black Friday & end dates: End of GT)
      include("homepageboxes/homepage-givingtuesday.inc");

      // Store/Merch Promo Box (times out approximately when store closes)
      // include("homepageboxes/homepage-merchbox.inc");

      // -----------------------------------
      // All Announcement Go Above This Line
      // All Raceday Boxes Next
      // -----------------------------------

      // Mini Raceday Highlights
      // include ("homepageboxes/homepage-miniraceday-infobox.inc");

      // Include at most one of the next two (probably starting around Mid-Feb).
      // The countdown one is short with less detail.
      // include("homepageboxes/homepage-raceday-countdown.inc");

      // Leaderboard (disables via config spreadsheet, but still reads firebase
      // if code is included, so make sure it is commented out if it isn't raceday)
      // include("homepageboxes/homepage-raceday-leaderbox.inc");

      // Full Raceday Infobox
      // include("homepageboxes/homepage-raceday-infobox.inc");

      // -----------------------------------
      // All Long Running Boxes Go Below
      // -----------------------------------

      // Handle Left Column Recent News Box Here!
      include("homepageboxes/homepage-recent-newsbox.inc");

      // Results from most recent raceday
      // 2 boxes: Teams that placed & Awards
      //
      // Goes up ASAP after a raceday completes.
      //
      // Should be removed sometime in the fall when it starts to feel stale.
      // include("homepageboxes/homepage-raceday-results.inc");

      // Twitter Embed content
      //
      // Disabled because it is both slow and twitter has broken their API so it is much harder
      // for us to use.  Can be reenabled if we need for, say, raceday.
      //
      // include("homepageboxes/homepage-twitterbox.inc");

      // About Buggy and About the BAA Boxes.
      include("homepageboxes/homepage-aboutboxes.inc");

      // CTS Box.  Might want to move higher in the list when new episodes are happening.
      include("homepageboxes/homepage-ctsbox.inc");
?>


  </div>
  <div class="col-md-4">
    <section>
      <h2>Next <?php echo($RACEDAY_WORD) ?></h2>
      <div class="mb-3">
        <span title="<?php echo("$timerCount $timerUnit"); ?>">
          <?php echo($RACEDAY_NEXT_TEXT) ?>
        </span>
      </div>
    </section>

    <section>
      <h2>Records</h2>
      <dl class="row">
        <dt class="col-5">Mens</dt>
        <dd class="col-7 text-right"><a href="/history/team/2017.SDC.MA">2:02.16</a></dd>

        <dt class="col-5">Womens</dt>
        <dd class="col-7 text-right"><a href="/history/team/2017.SDC.WA">2:23.27</a></dd>

        <dt class="col-5">All Gender</dt>
        <dd class="col-7 text-right"><a href="/history/team/2025.SDC.NA">2:25.62</a></dd>
      </dl>
    </section>

    <section>
      <h2>Get Involved</h2>
      <div class="media mb-3">
        <span class="align-self-center fa-layers fa-fw fa-2x mr-2">
          <i class="fas fa-square text-muted"></i>
          <i class="fas fa-graduation-cap fa-inverse" data-fa-transform="shrink-8"></i>
        </span>
        <div class="media-body">
          <a href="/seniors">Seniors!</a> Get your first year of membership free!
        </div>
      </div>
      <div class="media mb-3">
        <span class="align-self-center fa-layers fa-fw fa-2x mr-2">
          <i class="fas fa-square text-muted"></i>
          <i class="fab fa-discord fa-inverse" data-fa-transform="shrink-8"></i>
        </span>
        <div class="media-body">
          Hang out with us on the BAA <a target="_blank" href="/chat">Discord</a>.
        </div>
      </div>
    </section>

    <?php include_once("contentfeed_render.inc"); ?>
  </div>
</div>
