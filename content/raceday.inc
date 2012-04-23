<div id="topnav">
	<ul class="sf-menu">
		<li><a href="/raceday/buzz">Buzz</a></li>
		<li><a target="_blank" "href=http://new.livestream.com/cmuTVlive/Buggy2012Day1">cmuTV</a></li>
		<li><a href="/raceday/rosters">Rosters</a></li>
		<li><a href="/raceday/leaderboard">Leaderboard</a></li>
	</ul>
</div>
<?php
	$page = "overview";
	if(isset($_GET['p'])){
		$page = $_GET['p'];
	}
	include_once("content/raceday/".$page.".inc");	
?>