<?php
  function show_countdown_carousel_image($slug, $alttext, $active=false) {
    $divclass = "carousel-item" . ($active ? " active" : "");
    echo('<div class="'.$divclass.'">');
    echo('<img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/'.$slug.'/0/S/'.$slug.'-S.jpg" alt="'.$alttext.'">');
    echo('</div>');
  }

  // When volunteer links are ready, set to true
  $SHOW_VOLUNTEER_LINKS = true;
  $CURRENT_YEAR = date("Y");
?>
    <div class="card mb-3">
      <h5 class="card-header"><?php echo($RACEDAY_WORD." ".$CURRENT_YEAR." is ".$timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <div class="card-body text-center">
      <div id="countdownCarousel" class="carousel slide" data-ride="carousel">
        <div class="carousel-inner w-100">
<?php
          show_countdown_carousel_image("i-bqX7K5z", "Group Photo", true);

          show_countdown_carousel_image("i-9WCDKch", "CIA/APEX Design Comp Buggies");
          show_countdown_carousel_image("i-vZ9M6wp", "Barbie Chute");
          show_countdown_carousel_image("i-rnVkqnL", "Womens Heat 3 Hill 1");
          show_countdown_carousel_image("i-5bg2V9b", "Hydra Driver");
          show_countdown_carousel_image("i-wBjfzW6", "Broadcasters");
          show_countdown_carousel_image("i-L2VRdkL", "Invicid Chute");
          show_countdown_carousel_image("i-F7jPsff", "Spectators");

          show_countdown_carousel_image("i-6qzDGX8", "SDC First Place All Gender");
          show_countdown_carousel_image("i-3Bwj8jV", "CIA First Place Mens");
          show_countdown_carousel_image("i-DrKbQbg", "CIA First Place Womens");
?>
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
      <p>Our members help make <?php echo($RACEDAY_WORD); ?> happen.  If you'll be in town, please sign up to help.</p>
      <a target="_blank" href="/volunteer" class="btn btn-primary">Help Us Out!</a>
      <a target="_blank" href="/broadcast-volunteer" class="btn btn-primary">Be A Commentator!</a>
<?php } else { ?>
      <i>Spring Carnival will be here before you know it!</i>
<?php } ?>
      </div>
    </div>
