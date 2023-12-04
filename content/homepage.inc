<div class="row">
  <div class="col-md-8">
    <?php
      // For when the auction goes live (includes a timeout for end of auction)
      // include("homepage-raceday-auction.inc");
      
      // Include at most one of the next two (probably starting around Mid-Feb).
      // The countdown one is short with less detail.

      include("homepage-raceday-countdown.inc");
      // include("homepage-raceday-infobox.inc");

      // Store/Merch Promo Box
      // Times out approximately when store closes.
      // include("homepage-raceday-merch.inc");

      // Endowment Application Promobox
      // Includes timeout
      // include("homepage-endowmentbox.inc");

      // Results from most recent raceday
      // 2 boxes: Teams that placed & Awards
      //
      // Goes up ASAP after a raceday completes.
      //
      // Can be removed around the beginning of Febuary when we start doing
      // next-raceday stuff like the countdown box.

      // include("homepage-raceday-results.inc");
    ?>
    <?php
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
    <section class="d-lg-none">
      <h2>Records</h2>
      <dl class="row">
        <dt class="col-5">Mens</dt>
        <dd class="col-7"><a href="/history/team/2017.SDC.MA">2:02.16</a></dd>

        <dt class="col-5">Womens</dt>
        <dd class="col-7"><a href="/history/team/2017.SDC.WA">2:23.27</a></dd>

        <dt class="col-5">All Gender</dt>
        <dd class="col-7"><a href="/history/team/2023.APX.NA">2:45.58</a></dd>
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
      <div class="media mb-3">
        <span class="align-self-center fa-layers fa-fw fa-2x mr-2">
          <i class="fas fa-square text-muted"></i>
          <i class="fas fa-bell fa-inverse" data-fa-transform="shrink-8"></i>
        </span>
        <div class="media-body">
          Local?  Hear about freerolls on our <a href="https://groups.google.com/g/buggy-watchers">Buggy Watchers</a> list.
        </div>
      </div>
      <div class="media mb-3">
        <span class="align-self-center fa-layers fa-fw fa-2x mr-2">
          <i class="fas fa-square text-muted"></i>
          <i class="fas fa-bolt fa-inverse" data-fa-transform="shrink-8"></i>
        </span>
        <div class="media-body">
          Got more time and energy?  There's <a href="/about/get-involved">lots to do</a>!
        </div>
      </div>
    </section>

    <?php include_once("contentfeed.inc"); ?>
  </div>
</div>
