<?php
	//used to authenticate users for phpbb
  include("../../util.inc");
   
  if (isset($_COOKIE["cmubuggy_auth"])){
	$uservars = getuservars($_COOKIE['cmubuggy_auth']);
  	$username = ($uservars["username"]);
	
	$dbname = "cmubuggy_phpBB";
	$sql = "SELECT user_id FROM users WHERE username = '$username'";
	
	$result = pdoQuery($dbname, $sql);  	
	echo($result["user_id"]);  	
  	
  } else {
  	echo("ANONYMOUS");
  }

?>