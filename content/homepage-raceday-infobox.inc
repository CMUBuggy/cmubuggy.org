    <div class="card mb-3">
      <h5 class="card-header">Raceday 2023 is <?php echo($timerSmallWord." ".$timerCount." ".$timerUnit); ?>!</h5>
      <img class="card-img-top" src="<?php echo(makeSmugmugUrl("i-PbQzFc5")); ?>">
      <div class="card-body">
<?php
  // Set this to true the week of raceday itself.
  $RACEDAY_WEEK = false;

  if ($RACEDAY_WEEK) {
?>
        <div class="d-flex justify-content-center">
          <a href="/raceday" class="btn btn-primary m-1">Raceday Info Center</a>
          <a href="/live" class="btn btn-info m-1">Livestream</a>
          <a href="/chat" class="btn btn-info m-1">Chat</a>
        </div><div class="d-flex justify-content-center mb-2">
          <a href="/raceday/rosters" class="btn btn-secondary m-1">Rosters</a>
          <a href="/raceday/heats" class="btn btn-secondary m-1">Heats</a>
          <a href="/raceday/leaderboard" class="btn btn-secondary m-1">Leaderboard</a>
        </div>
<?php } ?>

        <p>Our <a href="/raceday">raceday info center</a> is the place to go for everything you need to know about all the activites.</p>
        <p>Key Events:</p>
        <ul>
          <li>Buggy Showcase: Thursday Apr 13, Noon</li>
          <li>Preliminary Races: Friday Apr 14, 8am-Noon</li>
          <li>Finals Races: Saturday Apr 15, 8am-Noon</li>
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