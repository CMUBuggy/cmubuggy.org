<?php

  //NEED TO ADD COOKIE FUNCTIONALITY TO MAINTAIN USER INFO

include "functions.php";
setcookie('secret_number','',0);
setcookie('userid','',0);
$_COOKIE['secret_number']="";
$_COOKIE['userid']="";
header( 'Location: index.php?error=LoggedOut');


?>


