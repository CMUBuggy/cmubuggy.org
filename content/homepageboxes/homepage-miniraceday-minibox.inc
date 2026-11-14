<?php
  // Time Box For the Mini Raceday Box
  $mrdstartdate = mktime(15, 00, 0, 11, 13, 2026);
  $mrdenddate = mktime(21, 00, 0, 11, 15, 2026);
  $now = time();

  if ($now > $mrdstartdate && $now < $mrdenddate) {
?>

  <div class="card mb-3">
    <h5 class="card-header">Mini Raceday 2026</h5>
    <div class="card-body">
      <img class="rounded mx-auto d-block" alt="Helios gets a good shove off of Hill 2"
             src="<?php echo(makeSmugmugUrl("i-3WndZm6", "S")); ?>">
      <hr width="30%" class="mx-auto">
      <p>Mini-Raceday will happen, weather permitting, starting approximately 7:15 am on
         November 15, 2026.</p>
      <div class="d-flex justify-content-center mb-2">
        <a href="/raceday/leaderboard" class="btn btn-primary m-1 d-flex align-items-center">Leaderboard</a>
<?php
//        <a href="/heats" class="btn btn-secondary m-1 d-flex align-items-center">Heat Schedule</a>
?>
        <a href="/live" class="btn btn-secondary m-1 d-flex align-items-center">Livestream</a>
        <a href="/chat" class="btn btn-secondary m-1 d-flex align-items-center">Chat</a>
      </div>
    </div>
  </div>

<?php } ?>
