<?php
include_once("lib/pog/pog_includes.inc");
include_once("util.inc");
include_once("lib/send_smtp.inc");

$errormsg=NULL;
$successmsg=NULL;
$user = new user();


if(isset($_POST["newsiteactivationsubmit"])){
	if(isset($_POST["userid"])){
		$user = $user->Get($_POST["userid"]);
		if(isset($_POST["password"]) && isset($_POST["password2"])){
			if($_POST["password"] == $_POST["password2"]){
				$plaintext = $_POST["password"];
				$hashobj = hashpassword($plaintext);
				$user->password = $hashobj["hash"];
				$user->salt 	 = $hashobj["salt"];
				$user->emailvalidatekey = md5($user->salt.$user->email);
				$user->Save();
				$mail = array(
					"to" => $user->email,
					"subject" => "CMUBuggy.org account confirmation",
					"body" => "Thanks for registering on cmubuggy!\n\nYour username is ".$user->username.".\n\nTo confirm your account, just click this link and you'll be on your way:\nhttp://cmubuggy.org/confirm.php?key=".$user->emailvalidatekey."\n\n If you have any trouble logging in, just reply to this e-mail."
				);

				if(send($mail)){
					$successmsg = "Your account information has been e-mailed to you";
				} else {
					$errormsg = "There was a problem sending the email";
				}
			} else {
				$errormsg = "The passwords were not the same.";
			}
		} else {
			$errormsg = "Please enter your desired password twice.";
		}
	} else {
		$errormsg = "No user was set";
	}
}




if(isset($_GET["urlkey"])){
	$userList = $user->GetList(array(array("urlkey", "=", $_GET["urlkey"])));
	if(count($userList)>0){
		$user = $userList[0];
	?>
		<div class="pane">
			<h2>New Site Activation</h2>
			<?php if(isset($errormsg)){ echo("<div class=\"msg bad\">".$errormsg."</div>");	}?>
			<?php if(isset($successmsg)){ echo("<div class=\"msg good\">".$successmsg."</div>");	}?>
			Hi, <b><? echo($user->username); ?></b> welcome to the new cmubuggy! To activate your account on our new site just enter and confirm a password you'd like to use from now on.  A confirmation e-mail will be sent to your address on file, <b><? echo($user->email) ?></b>.   If you have any trouble, just email admin@cmubuggy.org for assistance.
			<form action="/user/newsiteactivation/<? echo($_GET["urlkey"]); ?>" method="post" accept-charset="utf-8">
				<fieldset>
					<label for="password">Password</label>
					<input type="password" name="password" value="" id="password">
					<label for="password2">Retype Password</label>
					<input type="password" name="password2" value="" id="password2">
					<input type="hidden" name="userid" value="<? echo($user->userId); ?>" id="userid">
					<input type="hidden" name="newsiteactivationsubmit" value="TRUE" id="newsiteactivationsubmit">
				</fieldset>
				<input id="submitbtn" type="submit" value="submit" class="button">
			</form>
		</div>
<?php
	}
}
?>
