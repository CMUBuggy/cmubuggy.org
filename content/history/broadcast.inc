<?php
	if($_POST['username']=="broadcaster"&&$_POST['password']=="rd2010"){
		$_SESSION['broadcaster']=TRUE;
		$message = "You are now logged in as a broadcaster";
	} else {
		if($_POST['Submit']=="Login"){
			$message = "Username or password is incorrect<br />";
		}
	}

	if($_SESSION['broadcaster']!=TRUE){

	?>
<div class="box">
	<div class="title">Login as a Broadcaster</div>
		<form method="post" action="/history/broadcast" autocomplete="off">
			<table class="clean">
				<tr><td style="text-align:right; padding-top:10px;">Login:</td><td><input name="username" type="text" id="myusername"></td></tr>
				<tr><td style="text-align:right; padding-top:10px;">Password:</td><td><input name="password" type="password" id="mypassword"></td></tr>
				<tr><td></td><td><input type="submit" name="Submit" value="Login"></td></tr>
			</table>
			<?php echo($message); ?>
		</form>
</div>

<?php } ?>


<?php

if (time() <= strtotime('2010-04-16 14:00')) {
  $rdid = "20101";
} else {
  $rdid = "20102";
}

?>
<div class="box whitebox">
	<div class="title">Broadcast Essentials</div>
	<ul>
		<li><a href="/history/heat/<?php echo($rdid); ?>/w/1">First heat of the day</a></li>
		<li><a href="/history/heats/<?php echo($rdid); ?>">Schedule of heats</a></li>
		<li><a href="/history/leaderboard">Leaderboard</a></li>
		<li><a href="/askthebroadcasters/">Ask the Broadcasters</a></li>
		<li><a href="/history/roster/2010">Full rosters by team</a></li>
		<li><a href="/buzz">Raceday "buzz" chatroom</a></li>
		<li><a href="/files/racedayguide_2010_prelims.pdf">PDF of raceday guide</a></li>
	</ul>
</div>
