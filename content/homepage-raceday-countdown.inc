<?php
  // When volunteer links are ready, set to true
  $SHOW_VOLUNTEER_LINKS = true;
?>
    <div class="card mb-3">
      <h5 class="card-header">Raceday 2024 is <?php echo($timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <div class="card-body text-center">
      <div id="countdownCarousel" class="carousel slide" data-ride="carousel">
        <div class="carousel-inner w-100">
          <div class="carousel-item active">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-jR7CdfK/0/S/i-jR7CdfK-S.jpg" alt="Equinox in the Chute">
          </div>
          <div class="carousel-item">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-crFx7DP/0/S/i-crFx7DP-S.jpg" alt="Equinox in the Chute">
          </div>
          <div class="carousel-item">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-sT3XPCh/0/S/i-sT3XPCh-S.jpg" alt="Kaycee and Stacie">
          </div>
          <div class="carousel-item">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-J8RBMzg/0/S/i-J8RBMzg-S.jpg" alt="Apex Firefly Catch">
          </div>
          <div class="carousel-item">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-fVGB5jN/0/S/i-fVGB5jN-S.jpg" alt="Invicid">
          </div>
          <div class="carousel-item">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-GXFfBpz/0/S/i-GXFfBpz-S.jpg" alt="Fringe Buggies At Design Comp">
          </div>
          <div class="carousel-item">
            <img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/i-zRGzZxb/0/S/i-zRGzZxb-S.jpg" alt="PiKA Mens A First Place">
          </div>
        </div>
        <a class="carousel-control-prev" href="#countdownCarousel" role="button" data-slide="prev">
          <span class="carousel-control-prev-icon" style="filter: invert(100%)" aria-hidden="true"></span>
          <span class="sr-only">Previous</span>
        </a>
        <a class="carousel-control-next" href="#countdownCarousel" role="button" data-slide="next">
          <span class="carousel-control-next-icon" style="filter: invert(100%)" aria-hidden="true"></span>
          <span class="sr-only">Next</span>
        </a>
      </div>
      <hr>
<?php if ($SHOW_VOLUNTEER_LINKS) { ?>
      <p>Our members help make raceday happen.  If you'll be in town, please sign up to help.</p>
      <a target="_blank" href="/volunteer" class="btn btn-primary">Help Us Out!</a>
      <a target="_blank" href="/broadcast-volunteer" class="btn btn-primary">Be A Commentator!</a>
<?php } else { ?>
      <i>Spring Carnival will be here before you know it!</i>
<?php } ?>
      </div>
    </div>