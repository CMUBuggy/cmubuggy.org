<?php
	$page = "userlist";
	if(isset($_GET['p'])){
  		$page = $_GET['p'];
  	}
  	include_once("content/user/".$page.".inc");
?>
