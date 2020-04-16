<nav class="navbar navbar-light navbar-expand bg-light mb-3">
  <ul class="navbar-nav flex-wrap">
    <li class="nav-item">
      <a class="nav-link" href="/raceday">Raceday Home</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/heats">Heat Schedule</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/history">Leaderboard</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" target="_blank" rel="noopener" href="https://discord.gg/PUwuUuj">Chat</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/live">Live</a>
    </li>
  </ul>
</nav>
<?php
  $page = "overview";
  if(isset($_GET['p'])){
    $page = $_GET['p'];
  }
  include_once("content/raceday/".$page.".inc");
?>
