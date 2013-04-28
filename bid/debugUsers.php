<?php

include "functions.php";

$memcache = new Memcache;
$memcache->connect('localhost', 11211) or die ("Could not connect");
$users = $memcache->get("users");
$usersOptional = $memcache->get("usersOptional");

foreach($users as $userName=>$userRegisterNum){
  echo $userName." ".$userRegisterNum."<br>";	       

}

foreach($usersOptional as $userName=>$userRegisterNum){
  echo $userName." ".$userRegisterNum."<br>";	       
}
?>