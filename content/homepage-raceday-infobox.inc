<?php
  // Pick one single random image for this box - no carousel currently.
  $raceday_images = [ "i-HDjQKn8", // Spirit B Mens Hill 1
                      "i-QrjFLMV", // DG Insite Drops
                      "i-SNt258X", // SigNu/Spirit Womens Hill 1
                      "i-9ZPTkPs", // Krait Freeroll
                      "i-S2XcWs4", // Pika Women Hill 2
                      "i-RrLG22N", // Apex Tunnel
                      "i-pcRHdjB"  // Robo Chute
  ]
?>

  <div class="card mb-3">
      <h5 class="card-header">Raceday 2024 is <?php echo($timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <img class="card-img-top" src="<?php echo(makeSmugmugUrl($raceday_images[array_rand($raceday_images)], "M")); ?>">
      <div class="card-body">
<?php
  // Set this to true the week of raceday itself after confirming the pages are all ready.
  $RACEDAY_WEEK = false;

  if ($RACEDAY_WEEK) {
?>
        <div class="d-flex justify-content-center">
          <a href="/raceday" class="btn btn-primary m-1">Raceday Schedule</a>
          <a href="/live" class="btn btn-info m-1">Livestream</a>
          <a href="/chat" class="btn btn-info m-1">Chat</a>
        </div><div class="d-flex justify-content-center mb-2">
          <a href="/raceday/rosters" class="btn btn-secondary m-1">Rosters</a>
          <a href="/raceday/heats" class="btn btn-secondary m-1">Heats</a>
          <a href="/raceday/leaderboard" class="btn btn-secondary m-1">Leaderboard</a>
        </div>
<?php } ?>

        <p>Our <a href="/raceday">raceday schedule</a> is the place to go for everything you need to know about all the events.</p>
        <p>Key Events:</p>
        <ul>
          <li>Buggy Showcase: Thursday Apr 11, Noon</li>
          <li>Preliminary Races: Friday Apr 12, 8am-Noon</li>
          <li>Finals Races: Saturday Apr 13, 8am-Noon</li>
        </ul>
<?php
  if (!$RACEDAY_WEEK) {
?>
        <p>Our members help make raceday happen.  If you'll be in town, please sign up to help.</p>

        <a target="_blank" href="/volunteer" class="btn btn-primary">Help Us Out!</a>
        <a target="_blank" href="/broadcast-volunteer" class="btn btn-primary">Be A Commentator!</a>
<?php } ?>
      </div>
    </div>