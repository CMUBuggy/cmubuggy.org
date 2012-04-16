<?php

//echo json_encode(array("loginId"=>$_GET['userId']));
include "functions.php";
$userName=$_GET['userIdFull'];
$userNameEnd=strpos($userName,"@");
$shortName=substr($userName,0,$userNameEnd);

echo json_encode(array("registered"=>registerConfirm($_GET['randomNum']),"shortName"=>$shortName));

?>