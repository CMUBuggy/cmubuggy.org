<?php
  function show_countdown_carousel_image($slug, $alttext, $active=false) {
    $divclass = "carousel-item" . ($active ? " active" : "");
    echo('<div class="'.$divclass.'">');
    echo('<img class="d-block mx-auto w-100" src="https://photos.smugmug.com/photos/'.$slug.'/0/S/'.$slug.'-S.jpg" alt="'.$alttext.'">');
    echo('</div>');
  }

  // When volunteer links are ready, set to true
  $SHOW_VOLUNTEER_LINKS = false;
  $CURRENT_YEAR = date("Y");
?>
    <div class="card mb-3">
      <h5 class="card-header"><?php echo($RACEDAY_WORD." ".$CURRENT_YEAR." is ".$timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <div class="card-body text-center">
      <div id="countdownCarousel" class="carousel slide" data-bs-ride="carousel">
        <div class="carousel-inner w-100">
<?php
          // These should be from the previous year as much as possible.
          show_countdown_carousel_image("i-HvfRZRR", "RD25 Raptor Blackbird Start", true);
          show_countdown_carousel_image("i-Vzb9Jw9", "RD25 CIA/Apex Design Comp Buggies");
          show_countdown_carousel_image("i-spkzb3B", "BRD25 Baltic and Jaeger");
          show_countdown_carousel_image("i-VcbDn9w", "BRD25 Apex WA 12 Transition");
          show_countdown_carousel_image("i-wBjfzW6", "RD24 Broadcasters");
          show_countdown_carousel_image("i-4HNrBpz", "RD25 Loading Streak");
          show_countdown_carousel_image("i-xs5NtTP", "RD25 Lead Truck");
          show_countdown_carousel_image("i-F7jPsff", "RD24 Spectators");
          show_countdown_carousel_image("i-X6DjTrH", "RD25 TV Truck");
          show_countdown_carousel_image("i-pZ6VgMc", "BRD25 Paranoia Monument");
          show_countdown_carousel_image("i-9mtDxkR", "RD25 DG Finish");

          show_countdown_carousel_image("i-jx7VfXp/A", "BRD25 Group Photo");

          show_countdown_carousel_image("i-cRqwQnk", "RD25 SDC First Place All Gender");
          show_countdown_carousel_image("i-Jj3mtxb", "BRD25 CIA First Place Mens");
          show_countdown_carousel_image("i-HckbSP7", "BRD25 SDC First Place Womens");
?>
        </div>
        <a class="carousel-control-prev" href="#countdownCarousel" role="button" data-bs-slide="prev">
          <span class="carousel-control-prev-icon" style="filter: invert(100%)" aria-hidden="true"></span>
          <span class="sr-only">Previous</span>
        </a>
        <a class="carousel-control-next" href="#countdownCarousel" role="button" data-bs-slide="next">
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
