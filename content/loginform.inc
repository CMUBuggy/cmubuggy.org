<div id="login" class="card bg-light my-3">
  <div class="card-body">
    <?php
      if (isset($_COOKIE["cmubuggy_auth"])) {
        $uservars = getuservars($_COOKIE["cmubuggy_auth"]);
        echo("Logged in as <a href=\"/user/".$uservars["urlkey"]."\">".$uservars["username"]."</a><br />");
        echo("<a href=\"/logout.php\">Logout</a>");
        if (isset($uservars["adminlevel"])){
          if ($uservars["adminlevel"] > 0){
            echo(" | <a href=\"/admin\">Admin</a>");
          }
        }
      } else {
    ?>
      <form action="/login.php" method="post">
        <input type="hidden" name="redirecturl" value="<?php echo($_SERVER['REQUEST_URI']); ?>">
        <input type="hidden" name="loginsubmit" value="true" id="loginsubmit">
        <fieldset>
          <div class="form-group">
            <label for="username">Username</label>
            <input type="text" name="username" value="" id="username" class="form-control" autocomplete="username">
          </div>
          <div class="form-group">
            <label for="password">Password</label>
            <input type="password" name="password" value="" id="password" class="form-control" autocomplete="current-password">
          </div>
        </fieldset>
        <div class="text-center">
          <input id="loginbtn" type="submit" value="Login" class="btn btn-secondary">
          <a href="/user/register" class="btn btn-link">Register</a>
        </div>
      </form>
    <?php
      }
    ?>
  </div>
</div>
