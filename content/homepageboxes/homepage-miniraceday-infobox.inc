<?php
  // Time Box For the Mini Raceday Box
  $mrdstartdate = mktime(13, 00, 0, 11, 6, 2025);
  $mrdenddate = mktime(21, 00, 0, 11, 8, 2025);
  $now = time();

  if ($now > $mrdstartdate && $now < $mrdenddate) {
?>

  <div class="card mb-3">
    <h5 class="card-header">Mini Raceday &amp; Homecoming</h5>
    <div class="card-body">
      <p><b>Streams & Links:</b></p>
      <div class="d-flex justify-content-center">
        <a href="/live" class="btn btn-info m-1 d-flex align-items-center">Mini Raceday Live (6:45am)</a>
        <a href="/rewatch2025" class="btn btn-info m-1 d-flex align-items-center">2025 Rewatch Stream (1pm)</a>

      </div>
      <div class="d-flex justify-content-center mb-2">
        <a href="/raceday/leaderboard" class="btn btn-secondary m-1 d-flex align-items-center">Leaderboard</a>
        <a href="/chat" class="btn btn-secondary m-1 d-flex align-items-center">Chat</a>
      </div>

      <p><b>In-Person Events:</b></p>
      <ul>
        <li>History of Buggy: 10am, CUC Danforth Conference Room</li>
        <li>In-Person Rewatch Party: 1pm, CUC Danforth Conference Room</li>
      </ul>
      <p><i>All events are Saturday, November 8</i></p>
    </div>
  </div>

<?php } ?>