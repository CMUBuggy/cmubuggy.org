<nav class="navbar navbar-light navbar-expand bg-light mb-3">
  <ul class="navbar-nav flex-wrap">
    <li class="nav-item">
      <a class="nav-link" href="/raceday">Raceday Home</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/heats">Heat Schedule</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/rosters">Rosters</a>
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
  $page = $_GET['p'];
  $file = "content/raceday/".$page.".inc";
  if(!empty($page) && file_exists($file)) {
    include_once($file);
  } else {
    include_once("./content/404.inc");
  }
?>
