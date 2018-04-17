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
        $user->salt    = $hashobj["salt"];
        $user->emailvalidatekey = md5($user->salt.$user->email);
        $user->Save();
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
    <h1>New Site Activation</h1>

    <?php if(isset($errormsg)){ echo("<div class=\"alert alert-danger\" role=\"alert\">".$errormsg."</div>"); }?>
    <?php if(isset($successmsg)){ echo("<div class=\"alert alert-success\" role=\"alert\">".$successmsg."</div>");  }?>

    <p>Hi, <b><?php echo($user->username); ?></b> welcome to the new cmubuggy! To activate your account on our new site just enter and confirm a password you'd like to use from now on. A confirmation e-mail will be sent to your address on file, <b><?php echo($user->email) ?></b>. If you have any trouble, just email <a href="mailto:admin@cmubuggy.org">admin@cmubuggy.org</a> for assistance.</p>

    <form action="/user/newsiteactivation/<?php echo($_GET["urlkey"]); ?>" method="post">
      <fieldset>
        <input type="hidden" name="userid" value="<?php echo($user->userId); ?>" id="userid">
        <input type="hidden" name="newsiteactivationsubmit" value="TRUE" id="newsiteactivationsubmit">
        <div class="form-group">
          <label for="password">Password</label>
          <input type="password" name="password" value="" id="password" class="form-control" autocomplete="new-password">
        </div>
        <div class="form-group">
          <label for="password2">Retype Password</label>
          <input type="password" name="password2" value="" id="password2" class="form-control" autocomplete="new-password">
        </div>
      </fieldset>
      <div class="form-group">
        <button id="submitbtn" type="submit" class="btn btn-primary">Sumbit</button>
      </div>
    </form>
<?php
  }
}
?>
