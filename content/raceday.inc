<div id="topnav">
  <ul class="sf-menu">
    <li><a href="/raceday">Raceday Home</a></li>
    <li><a href="/raceday/heats">Heat Schedule</a></li>
    <li><a href="/raceday/leaderboard">Leaderboard</a></li>
    <li><a target="_blank" href="https://discord.gg/PUwuUuj">Chat</a></li>
<!--    <li><a href="/raceday/rosters">Rosters</a></li> -->
    <li><a target="_blank" href="http://new.livestream.com/cmuTVlive">cmuTV<img style="margin:0 0 2px 2px;" src="/img/icon-new-window.gif"></a></li>
  </ul>
</div>
<?php
  $page = "overview";
  if(isset($_GET['p'])){
    $page = $_GET['p'];
  }
  include_once("content/raceday/".$page.".inc");
?>
