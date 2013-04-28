<?
 include "functions.php";

 $memcache = new Memcache;
 $memcache->connect('localhost', 11211) or die ("Could not connect");
 $users = $memcache->get("users");

 foreach($users as $userName=>$userRegisterNum){
   $tempRefresh = $userName." ".$userRegisterNum;	       
 }
 echo json_encode(getAllAuctions());
?>