<?php
	//used to authenticate users for gallery3
  include("../../util.inc");
   
  if (isset($_COOKIE["cmubuggy_auth"])){
	$uservars = getuservars($_COOKIE['cmubuggy_auth']);
  	echo($uservars["username"]);
  }

?>
