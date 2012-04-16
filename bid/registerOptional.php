<?php

include "functions.php";

$userId=$_GET['userId'];
$firstName="";
$lastName="";
$phoneNum="";

if(isset($_GET['registerFirstName'])){
 $firstName=$_GET['registerFirstName'];
} 

if(isset($_GET['registerLastName'])){
 $lastName=$_GET['registerLastName'];
} 

if(isset($_GET['registerPhoneNum'])){
 $phoneNum=$_GET['registerPhoneNum'];
} 

echo registerUserOptional($userId,$firstName,$lastName,$phoneNum);

?>