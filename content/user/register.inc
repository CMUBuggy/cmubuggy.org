<?php

require_once("recaptchalib.php");
include_once("lib/send_smtp.inc");

$publickey = "6LetmAoAAAAAABd0RWbVCJaJx0XmmRDuvSuV1M42";
$privatekey = "6LetmAoAAAAAABeHUUQk5wXGdAwhDdd5-DoPdCcw";

$errormsg=NULL;
$successmsg=NULL;

# the response from reCAPTCHA
$RCresp = null;
# the error code from reCAPTCHA, if any
$RCerror = null;

if (isset($_POST["recaptcha_response_field"])) {
  $RCresp = recaptcha_check_answer ($privatekey, $_SERVER["REMOTE_ADDR"], $_POST["recaptcha_challenge_field"], $_POST["recaptcha_response_field"]);
   if ($RCresp->is_valid) {
    //echo("Captcha OK<br />");
    if(isset($_POST["humantest"]) && strlen($_POST["humantest"])>0){
        //echo("Human test completed<br />");
      if(isset($_POST["registrationsubmit"])){
        //echo("form key OK<br />");
        $user = new user();
        $userList = $user->GetList(array(array("username", "=", $_POST["username"])));
        if(!$userList){
          //echo("username not used<br />");
          $userList = $user->GetList(array(array("email", "=", $_POST["email"])));
          if(!$userList){
            //echo("email not used<br />");
            if($_POST["password"] == $_POST["password2"]){
              //echo("passwords match<br />");
              if(strlen($_POST["password"])> 5){
                //echo("passwords long enough ... creating user<br />");
                $hashobj = hashpassword($_POST["password"]);
                $user->username = $_POST["username"];
                $user->password = $hashobj["hash"];
                $user->salt    = $hashobj["salt"];
                $user->email   = $_POST["email"];
                $user->urlkey  = filter_var($user->username, FILTER_SANITIZE_URL);
                $user->membersince = time();
                $user->registerip = $_SERVER['REMOTE_ADDR'];
                $user->registerhumantest = $_POST["humantest"];
                $user->emailvalidatekey = md5($user->salt.$user->email);
                if($user->Save()){

                  $mail = array(
                    "to" => $user->email,
                    "subject" => "CMUBuggy.org account confirmation",
                    "body" => "Thanks for registering on cmubuggy!\n\nYour username is ".$user->username.".\n\nTo confirm your account, just click this link and you'll be on your way:\nhttps://cmubuggy.org/confirm.php?key=".$user->emailvalidatekey."\n\n If you have any trouble logging in, just reply to this e-mail."
                  );

                  if(send($mail)){
                    $successmsg = "Thank you for registering.  Your account information has been e-mailed to you.  Follow the link in your e-mail to complete your registration.";
                  } else {
                    $errormsg = "There was a problem sending the email";
                  }
                } else {
                  $errormsg = "Error saving new user information to the database";
                }

                //$file = file_get_contents("/var/www/cmubuggy.org/content/cache/userstats.json","r");
                //$userstats = json_decode($file);
                //$userstats->usercount++;
                //$userstats->newestuser = $user->username;
                //$fp = fopen("/var/www/cmubuggy.org/content/cache/userstats.json","w");
                //fwrite($fp, json_encode($userstats));
                //fclose($fp);
              } else {
                $errormsg = "Passwords must be at least 6 characters";
              }
            } else {
              $errormsg = "The passwords entered did not match";
            }
          } else {
            $errormsg = "The email \"".$_POST["email"]."\" is already in use.  Please try the password recovery tool if you've just forgotten the password.";
          }
        } else {
          $errormsg = "The username \"".$_POST["username"]."\" is already in use.  Please select another username or try the password recovery tool if you've just forgotten the password.";
        }
      }
    } else {
      $errormsg = "You're not a spammer or a robot are you?  You must answer the question about CMU's location";
    }
  } else {
      $errormsg = "reCaptcha human test not completed correctly, please try again";
   }
}

?>

<div class="pane">
<h2>Register</h2>
<?php
  if(isset($successmsg)){
    echo("<div class=\"msg good\">".$successmsg."</div>");
  }else{
    if(isset($errormsg)){ echo("<div class=\"msg bad\">".$errormsg."</div>");}
?>

By registering an account on cmubuggy.org, you'll be able to post in the forums, upload pictures to the gallery, and contribute knowledge to our reference section.  We also send out 1 or 2 emails per year to all registered users so you'll know when big things are happening.  Once you complete the form, check your e-mail for a confirmation link to finish your registration.
<form action="/user/register" method="post" accept-charset="utf-8">
  <fieldset>
      <div class="floatright">
        <?php  echo recaptcha_get_html($publickey); ?>
      </div>
      <label for="username">Username</label>
      <input type="text" name="username" value="<?php if(isset($_POST['username'])){echo($_POST['username']);} ?>" id="username">
      <label for="password">Password<div class="detail">(at least 6 characters)</div></label>
      <input type="password" name="password" value="" id="password">
      <label for="password2">Retype Password</label>
      <input type="password" name="password2" value="" id="password2">
      <label for="email">E-mail</label>
      <input type="text" name="email" value="<?php if(isset($_POST['email'])){echo($_POST['email']);} ?>" id="email">
      <label for="humantest">Where is CMU located?<div class="detail">(anti-spam)</div></label>
      <input type="text" name="humantest" value="" id="humantest">
      <input type="hidden" name="registrationsubmit" value="1" />
  </fieldset>
  <input id="registerbtn" type="submit" value="Register" class="button" style="margin:10px 0 0 190px">
</form>

<?php } ?>

</div>
