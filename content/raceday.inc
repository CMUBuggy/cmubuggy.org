<nav class="navbar navbar-light navbar-expand bg-light mb-3">
  <ul class="navbar-nav flex-wrap">
    <li class="nav-item">
      <a class="nav-link" href="/raceday">Raceday Home</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/heats">Heat Schedule</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="/raceday/leaderboard">Leaderboard</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" target="_blank" rel="noopener" href="https://discord.gg/PUwuUuj">Chat</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" target="_blank" rel="noopener" href="http://new.livestream.com/cmuTVlive">cmuTV<img class="ml-1" alt="" src="/img/icon-new-window.gif"></a>
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
