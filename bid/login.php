<?php

include "functions.php";

$memcache = new Memcache;
$memcache->connect('localhost', 11211) or die ("Could not connect");
$users = $memcache->get("users");

foreach($users as $userName=>$userRegisterNum){
  if($userName == $_GET['userId'] && $userRegisterNum == "good"){
    $userNameEnd=strpos($userName,"@");
    $shortName=substr($userName,0,$userNameEnd);
    echo json_encode(array("loginId"=>$shortName));
    return;
  }
}

/*
$user = new user();
$userList = $user->GetList(array(array("email", "like",'%@%' )));
foreach($userList as $userObj){
   if($userObj->email == $_GET['userId']){
    $userName=$userObj->email;
    $userNameEnd=strpos($userName,"@");
    $shortName=substr($userName,0,$userNameEnd);
    echo json_encode(array("loginId"=>$shortName));
    return;
  }
}*/

echo json_encode(array("loginId"=>"FuckThatNoise"));

?>