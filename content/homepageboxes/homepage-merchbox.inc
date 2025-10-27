<?php
  // Time out the merch box when the sale closes.
  // (default timezone already set in pre-content.inc)
  $merchenddate = mktime(23, 59, 0, 11, 8, 2025);

  if (time() < $merchenddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Buggy Merch!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline align-self-center mr-3" style="width:150px; height:150px"
             src="<?php echo(makeSmugmugUrl("i-vkrsvHT", "Th")); ?>">
        <div class="media-body">
          <p>Be warm in style!</p>
          <p>Show your buggy pride and stay warm with these amazing sweatshirts!</p>
          <p>Get your orders in before November 9.  Delivery expected before the holidays.</p>
          <a target="_blank" href="/merch" class="btn btn-primary">Get My Stuff!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
