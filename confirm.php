<?php

include_once("lib/pog/pog_includes.inc");
include_once("util.inc");

echo($_GET["key"]);

if(isset($_GET["key"])){
	$user = new user();
	$userList = $user->GetList(array(array("emailvalidatekey", "=", $_GET["key"])));
	if(count($userList)>0){
		$user = $userList[0];
	}
	$user->emailvalidatekey = "";
	$user->lastlogintime = time();
	$user->lastloginip = $_SERVER['REMOTE_ADDR'];
	$user->save();
	
	setcookie("cmubuggy_auth", $user->password,time()+31536000,"/",".cmubuggy.org");
	header("Location: /");
}

?>
