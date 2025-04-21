<?php
  if(isset($_GET['p'])){
    $page = $_GET['p'];
    include_once("content/tv/".$page.".inc");
  } else {
    // No page selected, just show the index (included below)
?>

<ul>
  <li><a href="/tvportal/leaderboard">Leaderboard Views</li>
  <li><a href="/tvportal/rosters">Roster Views</li>
  <li><a href="/tvportal/heats">Heat Labels</li>
</ul>

<?php
  }
?>