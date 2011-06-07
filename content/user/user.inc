<?php


$user = new user();
$userList = $user->GetList(array(array("urlkey", "=", $_GET["urlkey"])));
if(count($userList)>0){ 
$user = $userList[0];

echo($user->username);
}

?>