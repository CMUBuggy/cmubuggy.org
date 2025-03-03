<?php
  // Time out the merch box when the sale closes.
  // (default timezone already set in pre-content.inc)
  $merchenddate = mktime(23, 59, 0, 3, 9, 2025);

  if (time() < $merchenddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Buggy Merch!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline align-self-center mr-3" style="width:150px; height:150px"
             src="<?php echo(makeSmugmugUrl("i-JDwvjcL", "Th")); ?>">
        <div class="media-body">
          <p>Get your Raceday Gear!</p>
          <p>Make sure you're ready to show your buggy pride on Raceday, wearing a new
             BAA Raceday tshirt!</p>
          <p>Get your orders in before March 10.  Delivery expected by March 26.</p>
          <a target="_blank" href="/merch" class="btn btn-primary">Get My Stuff!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
