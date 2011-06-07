<?php
//used to pull data for creating a user in the phpbb db.
include("../../util.inc");

if (isset($_COOKIE["cmubuggy_auth"])){
	$uservars = getuservars($_COOKIE['cmubuggy_auth']);
	echo(implode(",", $uservars));
}
?>