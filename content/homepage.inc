<div class="row">
  <div class="col-md-8">
    <?php
      // Useful to quickly enable in the case of rain on raceday.
      // include("homepage-raceday-rainout.inc");

      // For when the auction goes live (includes a timeout for end of auction)
      // include("homepage-raceday-auction.inc");

      // Endowment Application Promobox (includes a timeout)
      // include("homepage-endowmentbox.inc");

      // Store/Merch Promo Box (times out approximately when store closes)
      // include("homepage-raceday-merch.inc");

      // -----------------------------------
      // All Announcement Go Above This Line
      // All Standard Boxes Go Below
      // -----------------------------------

      // Handle Left Column Recent News Box Here!
      include("homepage-recent-newsbox.inc");

      // Include at most one of the next two (probably starting around Mid-Feb).
      // The countdown one is short with less detail.
      // include("homepage-raceday-countdown.inc");

      // Leaderboard (disables via config spreadsheet, but still reads firebase
      // if code is included)
      // include("homepage-raceday-leaderbox.inc");

      // Full Raceday Infobox
      // include("homepage-raceday-infobox.inc");

      // Results from most recent raceday
      // 2 boxes: Teams that placed & Awards
      //
      // Goes up ASAP after a raceday completes.
      //
      // Should be removed sometime in the fall when it starts to feel stale.
      // include("homepage-raceday-results.inc");

      // Twitter Embed content
      //
      // Disabled because it is both slow and twitter has broken their API so it is much harder
      // for us to use.  Can be reenabled if we need for, say, raceday.
      if (false) {
        include("homepage-twitterbox.inc");
      }
    ?>

    <div class="card mb-3">
      <h5 class="card-header">Chute The Sh!t: The Buggy Podcast</h5>
      <div class="card-body">
      <iframe src="https://open.spotify.com/embed-podcast/show/3wbaYb92dfzuWDUbOOxHWi" width="100%" height="232" frameborder="0" allowtransparency="true" allow="encrypted-media"></iframe>
      </div>
    </div>

    <div class="card mb-3">
      <div class="card-body">
        <h5 class="card-title">Buggy Alumni Association</h5>
        <p>We were founded in 2008 to unite and connect alumni across teams and eras, and to support the coolest sport we know. Join us! We're open to everyone: current students, Pittsburgh locals, enthusiasts of any kind.</p>
        <a href="/about" class="btn btn-primary">Learn More</a>
      </div>
    </div>

    <div class="card mb-3">
      <div class="card-body">
        <h5 class="card-title">Buggy</h5>
        <p>Buggy (also called "Sweepstakes") is a unique race that has been held on and behind the Carnegie Mellon University campus during the spring carnival since 1920. It is part uphill relay race (in which the baton is a vehicle and driver pushed by runners), and part downhill gravity racing with exciting sharp turns and speeds up to 40mph.</p>
        <a href="/reference" class="btn btn-primary">Learn More</a>
      </div>
    </div>

  </div>
  <div class="col-md-4">
    <section>
      <h2>Next <?php echo($RACEDAY_WORD) ?></h2>
      <div class="mb-3">
        <span title="<?php echo("$timerCount $timerUnit"); ?>">
          <?php echo($RACEDAY_WORD) ?> 2025 is April 4&ndash;5
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
        <dd class="col-7 text-right"><a href="/history/team/2024.SDC.NA">2:36.27</a></dd>
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
