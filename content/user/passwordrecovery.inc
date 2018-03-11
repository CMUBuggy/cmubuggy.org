<?php
include_once("lib/pog/pog_includes.inc");
include_once("util.inc");
include_once("lib/send_smtp.inc");

$errormsg=NULL;
$successmsg=NULL;

if(isset($_POST["passwordrecoverysubmit"])){
	if(isset($_POST["email"])){
		$user = new user();
		$userList = $user->GetList(array(array("email", "=", $_POST["email"])));
		if($userList){
			$user = $userList[0];
			$user->emailvalidatekey = md5($user->salt.$user->email);

			$mail = array(
				"to" => $user->email,
				"subject" => "CMUBuggy.org account confirmation",
				"body" => "Thanks for registering on cmubuggy!\n\nYour username is ".$user->username.".\n\nTo confirm your account, just click this link and you'll be on your way:\nhttps://cmubuggy.org/confirm.php?key=".$user->emailvalidatekey."\n\n If you have any trouble logging in, just reply to this e-mail."
			);

			if(send($mail)){
				$successmsg = "Your account information has been e-mailed to you";
			} else {
				$errormsg = "There was a problem sending the email";
			}
		} else {
			$errormsg = "The email, \"".$_POST["email"]."\" is not associated with any accounts at cmubuggy.org.  Perhaps you'd like to <a href=\"/user/register\">register</a>?";
		}
	} else {
		$errormsg  = "No e-mail was submitted";
	}
}
?>



<div class="pane">
	<h2>Password and Username Recovery</h2>
	<?php if(isset($errormsg)){ echo("<div class=\"msg bad\">".$errormsg."</div>");	}?>
	<?php if(isset($successmsg)){ echo("<div class=\"msg good\">".$successmsg."</div>");	}?>
	To retrieve your username and reset your password, enter the e-mail address associated with your account.  If you have any trouble, just email admin@cmubuggy.org for assistance.
	<form action="/user/passwordrecovery" method="post" accept-charset="utf-8">
		<fieldset>
			<label for="email">Email</label>
			<input type="text" name="email" value="" id="email"><br />
			<input type="hidden" name="passwordrecoverysubmit" value="TRUE" id="passwordrecoverysubmit">
		</fieldset>
		<input id="submitbtn" type="submit" value="submit" class="button">
	</form>
</div>
