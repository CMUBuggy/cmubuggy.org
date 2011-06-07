<?php
	//used to authenticate users for gallery3 and mediawiki
  include("../../util.inc");
   
  if (isset($_COOKIE["cmubuggy_auth"])){
	$uservars = getuservars($_COOKIE['cmubuggy_auth']);
  	echo($uservars["username"]);
  }

?>