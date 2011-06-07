<?php

include_once("lib/pog/pog_includes.inc");
include_once("util.inc");

$errorcode="";
$authenticated = FALSE;
$user = new user();

if(isset($_POST["loginsubmit"])){
	if(isset($_POST["username"])){
		$userList = $user->GetList(array(array("username", "=", $_POST["username"])));
		if(count($userList)>0){ 
			$user = $userList[0];
			if(strlen($user->password)>0){
				if(strlen($user->emailvalidatekey)<1){			
					$authenticated = checkpassword($_POST["password"],$user->salt,$user->password);
					if($authenticated){
						setcookie("cmubuggy_auth", $user->password,time()+31536000,"/",".cmubuggy.org");
						$user->lastlogintime = time();
						$user->lastloginip = $_SERVER['REMOTE_ADDR'];
						$user->Save();
					} else {
						$errorcode = 1; //"That password is not correct";
					}
				} else {
					$errorcode = 4; //"You need to verify your e-mail address by clicking the link";	
				}
			} else {
				$errorcode = -1; //"You haven't activated your account on the new website";	
			}
		} else {
			$errorcode = 2; //"Sorry, that username is not in the database";	
		}
	} else {
		$errorcode = 3; //"username was not set";	
	}
}

//print_r($user);

$url = "/";
if(isset($_POST["redirecturl"])){
	$url = $_POST["redirecturl"];
}
if($errorcode > 0){
	$url = "/user/login/".$errorcode;
}
if($errorcode == -1){
	$url = "/user/newsiteactivation/".$user->urlkey;
}
header("Location: ".$url);

?>