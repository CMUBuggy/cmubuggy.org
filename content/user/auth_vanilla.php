<?php
//used to authenticate users for vanilla
include("../../util.inc");

if (isset($_COOKIE["cmubuggy_auth"])){
	$uservars = getuservars($_COOKIE['cmubuggy_auth']);
	//There is a bug in the vanilla parser, so it junks the first field we send it...
	//So we send it some spaces and a field we don't care about first 
	//echo("    \n");
	echo("UniqueID=".$uservars["userid"]."\n");
	echo("Name=".$uservars["username"]."\n");
	echo("Email=".$uservars["email"]."\n");
}
?>