<?php
  // Time out shortly before auction end. (2024: 9pm Apr 11)
  // (default timezone already set in pre-content.inc)
  $merchenddate = mktime(20, 59, 0, 4, 11, 2024);

  $auctionType = "Prelim";
  //$auctionType = "Finals";

  if (time() < $merchenddate) {
?>
    <div class="card mb-3">
      <h5 class="card-header"><?php echo($auctionType) ?> Lead Truck Auction!</h5>
      <div class="card-body">
        <p>Now's your chance to watch the races from the best possible seat -- the back of
        the lead truck!  Place your bids for your favorite heat now.</p>

        <a target="_blank" href="/auction" class="btn btn-primary">Bid Now!</a>
      </div>
    </div>
<?php } ?>
    
