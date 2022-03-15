<nav class="navbar navbar-light navbar-expand bg-light mb-3">
  <ul class="navbar-nav flex-wrap">
    <li class="nav-item">
      <a class="nav-link" href="/raceday">Raceday Home</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/heats">Heat Schedule</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/history/rosters/2022">Rosters</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/leaderboard">Leaderboard</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" target="_blank" rel="noopener" href="/chat">Chat</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/livestream">Livestream</a>
    </li>
  </ul>
</nav>
<?php
  if(isset($_GET['p'])){
    $page = $_GET['p'];
  } else {
    die('It looks like nothing was found at this location. Maybe try one of the links on the side?');
  }
  include_once("content/raceday/".$page.".inc");
?>
