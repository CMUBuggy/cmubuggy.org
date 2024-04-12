<?php
  // Pick one single random image for this box - no carousel currently.
  $raceday_images = [ "i-HDjQKn8", // Spirit B Mens Hill 1
                      "i-QrjFLMV", // DG Insite Drops
                      "i-SNt258X", // SigNu/Spirit Womens Hill 1
                      "i-9ZPTkPs", // Krait Freeroll
                      "i-S2XcWs4", // Pika Women Hill 2
                      "i-RrLG22N", // Apex Tunnel
                      "i-pcRHdjB"  // Robo Chute
  ];

  // Guide button only shows if we have a path in this variable.
  // $raceday_guide_file = "";
  $raceday_guide_file = "/files/raceday-previews/2024PrelimsGuide.pdf";
?>

  <div class="card mb-3">
      <h5 class="card-header"><?php echo($RACEDAY_WORD); ?> 2024 is <?php echo($timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <img class="card-img-top" src="<?php echo(makeSmugmugUrl($raceday_images[array_rand($raceday_images)], "M")); ?>">
      <div class="card-body">
<?php
  // Set this to true the week of raceday itself after confirming the pages are all ready.
  $RACEDAY_WEEK = true;

  if ($RACEDAY_WEEK) {
?>
        <div class="d-flex justify-content-center">
          <a href="/<?php echo($RACEDAY_URL_PART) ?>" class="btn btn-primary m-1 d-flex align-items-center"><?php echo($RACEDAY_WORD); ?> Schedule</a>
          <a href="/live" class="btn btn-info m-1 d-flex align-items-center">Livestream</a>
          <a href="/chat" class="btn btn-info m-1 d-flex align-items-center">Chat</a>
        </div><div class="d-flex justify-content-center mb-2">
          <a href="/raceday/rosters" class="btn btn-secondary m-1 d-flex align-items-center">Rosters</a>
          <a href="/raceday/heats" class="btn btn-secondary m-1 d-flex align-items-center">Heats</a>
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
          <li>Buggy Showcase: Thursday Apr 11, Noon</li>
          <li>Preliminary Races: Friday Apr 12, 7:30am-Noon</li>
          <li>Finals Races: Saturday Apr 13, 8am-Noon</li>
        </ul>
<?php
  if (!$RACEDAY_WEEK) {
?>
        <p>Our members help make <?php echo($RACEDAY_WORD); ?> happen.  If you'll be in town, please sign up to help.</p>

        <a target="_blank" href="/volunteer" class="btn btn-primary">Help Us Out!</a>
        <a target="_blank" href="/broadcast-volunteer" class="btn btn-primary">Be A Commentator!</a>
<?php } ?>
      </div>
    </div>
