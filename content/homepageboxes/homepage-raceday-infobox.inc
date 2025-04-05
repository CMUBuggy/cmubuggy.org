<?php
  // Pick one single random image for this box - no carousel to speed loading and
  // show larger images.
  $raceday_images = [ "i-bqX7K5z", // Group Photo
                      "i-9WCDKch", // CIA/APEX Design Comp Buggies
                      "i-vZ9M6wp", // Barbie Chute                      
                      "i-rnVkqnL", // Womens Heat 3 Hill 1
                      "i-5bg2V9b", // Hydra Driver
                      "i-wBjfzW6", // Broadcasters
                      "i-L2VRdkL", // Invicid Chute
                      "i-F7jPsff", // Spectators

                      "i-6qzDGX8", // SDC First Place All Gender
                      "i-3Bwj8jV", // CIA First Place Mens
                      "i-DrKbQbg", // CIA First Place Womens
  ];

  $CURRENT_YEAR = date("Y");

  // Set this to true the week of raceday itself after confirming the pages are all ready.
  $RACEDAY_WEEK = true;

  // set to true when the DB update with the current rosters is available.
  //
  // only matters if RACEDAY_WEEK=true
  $ROSTERS_READY = true;

  // set to true when the sweepstakes-published public heat schedule is ready.
  // (you also need to update the relevant wordpress page with that link)
  //
  // only matters if RACEDAY_WEEK=true
  $HEATS_READY = true;

  // Guide button only shows if we have a path in this variable.
  // $raceday_guide_file = "";
  $raceday_guide_file = "/files/raceday-previews/2025PrelimsGuide.pdf";

?>

  <div class="card mb-3">
      <h5 class="card-header"><?php echo($RACEDAY_WORD." ".$CURRENT_YEAR." is ".$timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <img class="card-img-top" src="<?php echo(makeSmugmugUrl($raceday_images[array_rand($raceday_images)], "M")); ?>">
      <div class="card-body">
<?php
  if ($RACEDAY_WEEK) {
?>
        <div class="d-flex justify-content-center">
          <a href="/<?php echo($RACEDAY_URL_PART) ?>" class="btn btn-primary m-1 d-flex align-items-center"><?php echo($RACEDAY_WORD); ?> Schedule</a>
          <a href="/live" class="btn btn-info m-1 d-flex align-items-center">Livestream</a>
          <a href="/chat" class="btn btn-info m-1 d-flex align-items-center">Chat</a>
          <a href="/raceday/faq" class="btn btn-info m-1 d-flex align-items-center">FAQ</a>
        </div><div class="d-flex justify-content-center mb-2">

<?php if ($ROSTERS_READY) { ?>
          <a href="/raceday/rosters" class="btn btn-secondary m-1 d-flex align-items-center">Rosters</a>
<?php }
      if ($HEATS_READY) { ?>
          <a href="/raceday/heats" class="btn btn-secondary m-1 d-flex align-items-center">Heats</a>
<?php } ?>

          <a href="/raceday/leaderboard" class="btn btn-secondary m-1 d-flex align-items-center">Leaderboard</a>

<?php
          if (!empty($raceday_guide_file)) {
?>
            <a href="<?php echo($raceday_guide_file); ?>" class="btn btn-secondary m-1 d-flex align-items-center">Spotting Guide</a>
<?php
          }
        echo("</div><hr>");
  } else {
?>
        <p>Our <a href="/<?php echo($RACEDAY_URL_PART) ?>"><?php echo($RACEDAY_WORD); ?> schedule</a> is the place to go for everything you need to know about all the events.</p>
<?php } ?>
        <p>Key Events:</p>
        <ul>
          <li>Mens &amp; Womens Finals: Saturday Apr 5: <b>RACES ARE DELAYED</b></li>
        </ul>
        <p><i>Any changes due to weather overnight will be published in our <a href="/news">news feed</a> as we become aware</i></p>
<?php
//        <ul>
//          <li>Buggy Showcase: Thursday Apr 3, Noon-2pm</li>
//          <li>Preliminary Races: Friday Apr 4, 8am-1pm</li>
//         <li>Finals Races: Saturday Apr 5, 8am-Noon</li>
//        </ul>
?>
<?php
  if (!$RACEDAY_WEEK) {
?>
        <p>Our members help make <?php echo($RACEDAY_WORD); ?> happen.  If you'll be in town, please sign up to help.</p>

        <a target="_blank" href="/volunteer" class="btn btn-primary">Help Us Out!</a>
        <a target="_blank" href="/broadcast-volunteer" class="btn btn-primary">Be A Commentator!</a>
<?php } ?>
      </div>
    </div>
