<?php
  // Time out the merch box when the sale closes.
  // (default timezone already set in pre-content.inc)
  $gtstartdate = mktime(0, 0, 0, 11, 29, 2024);  // Thanksgiving Friday
  $gtenddate = mktime(3, 00, 0, 12, 4, 2024);
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
          <p>Until Tuesday, December 3, you can power up the BAA and play a part in making buggy
          more engaging for students, alumni, and fans.  Your gift will enable the BAA to
          support an event we all love, and make you a BAA member for Raceday 2025!
          </p>
          <a target="_blank" href="/givingtuesday-web" class="btn btn-primary">Give Now!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
