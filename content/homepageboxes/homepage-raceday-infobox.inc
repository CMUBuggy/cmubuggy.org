<?php
  // Pick one single random image for this box - no carousel to speed loading and
  // show larger images.
  $raceday_images = [ "i-jx7VfXp", // 2025 Group Photo
                      "i-h4h997L", // 2025 SDC Design Comp Buggies
                      "i-CqnSVb3", // 2025 Spirit Design Comp Buggies
                      "i-xT7Nf9f", // 2025 Design Comp Overhead

                      "i-spkzb3B", // 2025 Baltic and Jaeger
                      "i-pZ6VgMc", // 2025 Paranoia Monument
                      "i-F7jPsff", // 2024 Spectators
                      "i-4HNrBpz", // 2025 Loading Streak
                      "i-5bg2V9b", // 2024 Hydra Driver
                      "i-dGV79CH", // 2025 AG 2 Hill 2 Zuke Insite
                      "i-Pb6sL4V", // 2025 SDC AG Finish Paranoia

                      "i-wBjfzW6", // 2024 Broadcasters
                      "i-X6DjTrH", // 2025 TV Truck

                      "i-cRqwQnk", // 2025 SDC First Place All Gender
                      "i-Jj3mtxb", // 2025 CIA First Place Mens
                      "i-HckbSP7", // 2025 SDC First Place Womens
  ];

  // Assumes we only run this in the actual year of raceday.
  $CURRENT_YEAR = date("Y");

  // Can be used to override the countdown in the card header.
  $COUNTDOWN_STRING = $RACEDAY_WORD." ".$CURRENT_YEAR." is ".$timerSmallWord." ".$timerCount." ".$timerUnit;

  // Set this to true the week of raceday itself after confirming the pages are all ready.
  $RACEDAY_WEEK = true;

  // Set this when the schedule link is ready.
  $SHOW_SCHEDULE = true;

  // set to true when the DB update with the current rosters is available.
  //
  // only matters if RACEDAY_WEEK=true
  $ROSTERS_READY = false;
  // $ROSTERS_READY = true;

  // set to true when the sweepstakes-published public heat schedule is ready.
  // (you also need to update the relevant wordpress page with that link)
  //
  // only matters if RACEDAY_WEEK=true
  // $HEATS_READY = false;
  $HEATS_READY = true;

  // Guide button only shows if we have a path in this variable.
  $raceday_guide_file = "";
  // $raceday_guide_file = "/files/raceday-previews/2025PrelimsGuide.pdf";

?>

  <div class="card mb-3">
      <h5 class="card-header"><?php echo($COUNTDOWN_STRING); ?>!</h5>
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
          if ($raceday_guide_file != "") {
?>
            <a href="<?php echo($raceday_guide_file); ?>" class="btn btn-secondary m-1 d-flex align-items-center">Spotting Guide</a>
<?php
          }
        echo("</div><hr>");
  } else {
?>
        <p>Our <a href="/<?php echo($RACEDAY_URL_PART) ?>"><?php echo($RACEDAY_WORD); ?> schedule</a> is the place to go for everything you need to know about what is happening.</p>
<?php } ?>

      <p>Key Events:</p>
      <ul>
        <li>Buggy Showcase: Thursday Apr 9, Noon-2:45pm</li>
        <li>Preliminary Races: Friday Apr 10, Approx 8am-1pm</li>
        <li>Finals Races: Saturday Apr 11, Approx 8am-Noon</li>
      </ul>

<?php
  if (!$RACEDAY_WEEK) {
?>
        <hr class="w-50 mx-auto">

        <p>Our members help make <?php echo($RACEDAY_WORD); ?> happen.  If you'll be in town, please sign up to help.</p>

        <div class="text-center">
          <a target="_blank" href="/volunteer" class="btn btn-primary">Help Us Out!</a>
          <a target="_blank" href="/broadcast-volunteer" class="btn btn-primary">Be A Commentator!</a>
        </div>
<?php } ?>
      </div>
    </div>
