<?php
  // Time out the merch box when the sale closes.
  // (default timezone already set in pre-content.inc)
  //
  // IMPORTANT: REVIEW TEXT AND DATES BELOW (e.g. "Raceday 2026")
  //
  $gtstartdate = mktime(0, 0, 0, 11, 30, 2025);  // Thanksgiving Friday
  $gtenddate = mktime(3, 00, 0, 12, 3, 2025);  // Midnight PT Giving Tuesday
  $gtnow = time();

  if ($gtnow > $gtstartdate && $gtnow < $gtenddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Giving Tuesday</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline align-self-center mr-3" style="width:150px; height: 150px" src="<?php echo(makeSmugmugUrl("i-kh37xmt", "Th")); ?>">
        <div class="media-body">
          <p>The end of November brings the holiday season and Carnegie Mellon's Giving Tuesday!
          </p>
          <p>Through Tuesday, you can power up the BAA and play a part in making buggy
          more engaging for students, alumni, and fans.  Your gift will enable the BAA to
          support an event we all love, and make you a BAA member for <?php echo($RACEDAY_WORD); ?> 2026!
          </p>
          <a target="_blank" href="/givingtuesday-web" class="btn btn-primary">Give Now!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
