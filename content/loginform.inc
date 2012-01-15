<div id="login">
<?php
//$file = file_get_contents("/var/www/cmubuggy.org/content/cache/userstats.json","r");
//$userstats = json_decode($file);

if (isset($_COOKIE["cmubuggy_auth"])){
	$uservars = getuservars($_COOKIE["cmubuggy_auth"]);
	echo("Logged in as <a href=\"/user/".$uservars["urlkey"]."\">".$uservars["username"]."</a><br />");
	echo("<a href=\"/logout.php\">Logout</a><br />");
} else { ?>
	<form action="/login.php" method="post" accept-charset="utf-8">
		<fieldset>
			<label for="username">Username</label>
			<input type="text" name="username" value="" id="username">
			<label for="password">Password</label>
			<input type="password" name="password" value="" id="password">
		</fieldset>
		<input id="loginbtn" type="submit" value="Login" class="button">
		<input type="hidden" name="loginsubmit" value="true" id="loginsubmit">
		<input type="hidden" name="redirecturl" value="<? echo($_SERVER['REQUEST_URI']); ?>" id="loginsubmit">
		<a style="margin-left:10px;" href="/user/register">Register</a>
	</form>
<?php } ?>
</div>