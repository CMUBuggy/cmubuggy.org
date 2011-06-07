<?php
	if(isset($_GET["e"])){
		$e = $_GET["e"];
		$msg = NULL;
		switch($e) {
			case 1:
				$msg = "That password is not correct.  You can try again, or try our <a href=\"/user/passwordrecovery\">password recovery tool</a>.";				
				break;
			case 2:
				$msg = "Sorry, that username is not in the database";				
				break;
			case 3:
				$msg = "No username was entered. Try telling us who you are and we'll see about logging you in.";				
				break;
			case 4:
				$msg = "Please follow the link in the Account Confirmation e-mail you received to complete your registration.  If you can not find the e-mail, please visit the <a href=\"/user/passwordrecovery\">Retrieve username / password page</a> ";
				break;
		}
	}
?>

<div class="pane">
	<h2>Login</h2>
	<?php if(isset($msg)){ echo("<div class=\"msg bad\">".$msg."</div>");	}?>
	<form action="/login.php" method="post" accept-charset="utf-8">
		<fieldset>
			<label for="username">Username</label>
			<input type="text" name="username" value="" id="username"><br />
			<label for="password">Password</label>
			<input type="password" name="password" value="" id="password">
			<input type="hidden" name="loginsubmit" value="1" id="loginsubmit">
		</fieldset>
		<input id="loginbtn" type="submit" value="login" class="button"> 
		<a style="margin-left:10px;" href="/user/register">Register</a>
	</form>
</div>