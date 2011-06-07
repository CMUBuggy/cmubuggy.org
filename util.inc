<?php
	//session_start();
	define( 'ROOT_DIR', dirname(__FILE__) );
	$UTCdiff = -60*60*4;
	$footermsg = "";

	function displayTime($time){
		$displayTime = "";
		if($time > 0){
			$timeMin = intval($time / 60);
			$timeSec = ($time)-($timeMin*60);
			if($timeSec<10){ $timeSec = "0".$timeSec; }
			if(strlen($timeSec)>5){$timeSec = substr($timeSec,0,5); } 
			$displayTime = str_pad(str_pad($timeMin.":".$timeSec,5,"."),7,"0");
		}
		return $displayTime;
	}
	
	function pdoQuery($dbname, $sql){
		include("dbconfig.inc");
		try { 
			$dbh = new PDO("mysql:host=".$dbhost.";dbname=".$dbname,$dbuser,$dbpass);
		} catch(PDOException $e) {
    		echo $e->getMessage();
    	}
    	$stmt = $dbh->query($sql);
    	$result = $stmt->fetch(PDO::FETCH_ASSOC);
		return $result;
	}
	
	function dbQuery($dbname, $sql){
		include("dbconfig.inc");
		$con = mysql_connect($dbhost, $dbuser, $dbpass);
		if (!$con)	{  die('Could not connect: ' . mysql_error()); }
		mysql_select_db($dbname, $con);
		return mysql_query($sql);
		mysql_close($con);		
	}
	
	function dbClose(){
		mysql_close($con);
	}
	
	function timestamp_sort($a, $b){
		if ($a["timestamp"] == $b["timestamp"]) return 0;
		return ($a["timestamp"] > $b["timestamp"]) ? -1 : 1;
	}
	
	function timeago($timestamp){
		$diff = time()-$timestamp;
		
		//hack to solve daylight savings bug		
		if($diff<0){$diff = time()+60*60 - $timestamp;}
		
		$msg = "";
		if($diff<60){ 
			$msg = $diff." seconds ago";
		} elseif($diff<60*60) {
			$mins = round($diff/60);
			if($mins==1){
				$msg = "1 minute ago";
			} else {
				$msg = $mins." minutes ago";
			}
		} elseif($diff<60*60*24) {
			$hrs = round($diff/(60*60));
			if($hrs==1){
				$msg = "1 hour ago";
			} else {
				$msg = $hrs." hours ago";
			}
		} elseif($diff<60*60*24*7) { 
			$days = round($diff/(60*60*24));
			if($days==1){
				$msg = "1 day ago";
			} else {
				$msg = $days." days ago";
			}
		}else {
			$msg = "on ".date('M d', $timestamp);
		}
		//return date("Y-M-d H:m:i", $timestamp)." ".$msg;
		return $msg;
	}
	
	function checkpassword($plaintext, $salt, $hash){
		return sha1(md5($plaintext).$salt) == $hash;
	}
	
	function hashpassword($plaintext){
		$salt = substr(md5(uniqid(rand(), true)), 0, 10);
		return array("hash"=>sha1(md5($plaintext).$salt), "salt"=>$salt);
	}
	
	function getuservars($hash){
		$dbname = "cmubuggy";
		$sql = "SELECT * FROM user WHERE password = '".$hash."'";
		$result = pdoQuery($dbname, $sql);
		return $result;
	}
	
	function validateemail($email){
		//filter_var() sanitizes the e-mail
	  //address using FILTER_SANITIZE_EMAIL
	  $field=filter_var($email, FILTER_SANITIZE_EMAIL);
	
	  //filter_var() validates the e-mail
	  //address using FILTER_VALIDATE_EMAIL
	  if(filter_var($email, FILTER_VALIDATE_EMAIL)){
	  	return TRUE;
	  }else{
	   return FALSE;
	  }
	}
	
?>