<?php
  // Time out the merch box after March 14 Midnight.
  // (default timezone already set in pre-content.inc)
  $merchenddate = mktime(23, 59, 0, 3, 14, 2023);

  if (time() < $merchenddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Buggy Merch!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline align-self-center mr-3" style="max-height:180px" src="https://www.customink.com/mms/images/catalog/colors/421208/views/alt/front_large_extended.png?design=xyd0-00cq-75cp&pblegacy=1&pblegacysize=big&pblegacywm=1">
        <div class="media-body">
          <p>Order your BAA tshirt before Raceday!</p>
          <p>Supplies are limited, store closes midnight March 14th.</p>
          <a target="_blank" href="/merch" class="btn btn-primary">Get My Stuff!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
