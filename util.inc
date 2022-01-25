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

	// We provide 2 utility functions for raw SQL queries -- one that just takes the query verbatim
	// and another that allows the use of bound parameters, necessary if we have user input.
	//
	// TODO: It is debatable how useful this approach is.  It is certainly simple, but it
	// means that on pages that do more than one query we open several database
	// connections.  However, many pages just do a single query, or at most 2, so in most cases it is
	// 6 of one, half a dozen...  However, the most complex pages (such as org) do  multiple (5+)
	// and might be better with some local optimization if we see issues in production.
	//
	// Including dbconfig.inc here allows us to provide the history database name
	// throughout the code (via $HISTORY_DATABASE)
	include("dbconfig.inc");

	// Do a simple query against the named database.
	//
	// WARNING: Do not allow any user input into the statement!
	// You absolutely should prefer dbBoundQuery() if user input is necessary (with the user input as bound values)
	function dbQuery($dbname, $sql){
		global $dbhost, $dbuser, $dbpass;
		$con = mysqli_connect($dbhost, $dbuser, $dbpass);
		if (!$con)	{  die('Could not connect: ' . mysqli_connect_error()); }
		mysqli_select_db($con, $dbname);
		return mysqli_query($con, $sql);

		// Note: Connection will close when $con is garbage collected.
	}

	// Do a query against the database, allowing the use of bound parameters to prevent SQL injection.
	//
	// If you are at all in doubt, use this function in preference to dbQuery().
	function dbBoundQuery($dbname, $sql, $bindings = NULL, ...$values) {
		global $dbhost, $dbuser, $dbpass;
		$con = mysqli_connect($dbhost, $dbuser, $dbpass);
		if (!$con)	{  die('Could not connect: ' . mysqli_connect_error()); }

		mysqli_select_db($con, $dbname);

		$stmt = mysqli_prepare($con, $sql);
		if (!$stmt) {  die('Could not prepare statement "' . $sql . ': ' . mysqli_error($con)); }

		if ($bindings) {
			mysqli_stmt_bind_param($stmt, $bindings, ...$values);
		}

		mysqli_stmt_execute($stmt) or die ('could not execute statement: ' . mysqli_error($con));

		return mysqli_stmt_get_result($stmt);

		// Note: Connection will close when $con is garbage collected.
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
?>
