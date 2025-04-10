<?php
  // Pick one single random image for this box - no carousel to speed loading and
  // show larger images.
  $raceday_images = [ "i-bqX7K5z", // 2024 Group Photo
                      "i-h4h997L", // 2025 SDC Design Comp Buggies
                      "i-CqnSVb3", // 2025 Spirit Design Comp Buggies
                      "i-xT7Nf9f", // 2025 Design Comp Overhead

                      "i-L2VRdkL", // 2024 Invicid Chute
                      "i-F7jPsff", // 2024 Spectators
                      "i-5bg2V9b", // 2024 Hydra Driver
                      "i-wBjfzW6", // 2024 Broadcasters
                      "i-dGV79CH", // 2025 AG 2 Hill 2 Zuke Insite
                      "i-Pb6sL4V", // 2025 SDC AG Finish Paranoia

                      "i-cRqwQnk", // 2025 SDC First Place All Gender
                      "i-3Bwj8jV", // 2024 CIA First Place Mens
                      "i-DrKbQbg", // 2024 CIA First Place Womens
  ];

  $CURRENT_YEAR = date("Y");

  $COUNTDOWN_STRING = $RACEDAY_WORD." ".$CURRENT_YEAR." is ".$timerSmallWord." ".$timerCount." ".$timerUnit;

  // Bonus Raceday
  $COUNTDOWN_STRING = "Raceday 2025 is ongoing";

  // Set this to true the week of raceday itself after confirming the pages are all ready.
  $RACEDAY_WEEK = true;

  // Hack for RD2025
  // $SHOW_SCHEDULE = true;
  // $SHOW_BONUS = false;
  $SHOW_SCHEDULE = false;
  $SHOW_BONUS = true;

  // set to true when the DB update with the current rosters is available.
  //
  // only matters if RACEDAY_WEEK=true
  $ROSTERS_READY = true;

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
<?php if ($SHOW_SCHEDULE) { ?>
          <a href="/<?php echo($RACEDAY_URL_PART) ?>" class="btn btn-primary m-1 d-flex align-items-center"><?php echo($RACEDAY_WORD); ?> Schedule</a>
<?php } ?>
<?php if ($SHOW_BONUS) { ?>
          <a href="/raceday/bonus-raceday" class="btn btn-primary m-1 d-flex align-items-center">Bonus Raceday Info</a>
<?php } ?>
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
        <p>Our <a href="/<?php echo($RACEDAY_URL_PART) ?>"><?php echo($RACEDAY_WORD); ?> schedule</a> is the place to go for everything you need to know about all the events.</p>
<?php } ?>

        <p class="text-center">Any time sensitive updates about the bonus April 12 and April 13 races will be posted <a href="/raceday/bonus-raceday">here</a>.</p>
<?php
//        <p><i>Any schedule updates will be published in our <a href="/news">news feed</a> as we become aware</i></p>
//
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
