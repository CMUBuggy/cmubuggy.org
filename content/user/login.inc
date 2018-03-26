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

<h1>Login</h1>

<?php if(isset($msg)){ echo("<div class=\"alert alert-danger\" role=\"alert\">".$msg."</div>"); }?>

<form action="/login.php" method="post">
  <fieldset>
    <input type="hidden" name="loginsubmit" value="1" id="loginsubmit">
    <div class="form-group">
      <label for="username">Username</label>
      <input type="text" name="username" value="" id="username" class="form-control" autocomplete="username">
    </div>
    <div class="form-group">
      <label for="password">Password</label>
      <input type="password" name="password" value="" id="password" class="form-control" autocomplete="current-password">
    </div>
  </fieldset>
  <div class="form-group">
    <button id="loginbtn" type="submit" class="btn btn-primary">Login</button>
    <a href="/user/register" class="btn btn-link">Register</a>
  </div>
</form>
