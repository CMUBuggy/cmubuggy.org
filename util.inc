<?php
	define( 'ROOT_DIR', dirname(__FILE__) );
    date_default_timezone_set('America/New_York');

    /// April 1, 2024
    $RACEDAY_WORD = "Raceday";
    $RACEDAY_URL_PART = "raceday";
    if (date("m.d") == "04.01") {
      $RACEDAY_WORD = "Buggy Day";
      $RACEDAY_URL_PART = "buggyday";
    }
    ///

	// Renders times in a standardized way.
	//
	// Time is input as a floating point number of seconds.
	//
	// Renders zero time as a blank string.
	// Renders nonzero times as m:ss.cc
	//
	// Times longer than 10 minutes will be longer and not align with shorter times,
	// obviously.  This should be very rare and therefore acceptable.
	//
	// If we need to render times over an hour at some point, we might want to
	// consider some rule changes :)
	function displayTime($time){
		$renderedTime = "";
		if($time > 0){
			$timeMin = intval($time / 60);
			$timeSec = ($time)-($timeMin*60);

			// Produce a string in the format m:ss.cc.
			// String will round to the nearest hundredth second.
			$renderedTime = sprintf("%d:%05.2f", $timeMin, $timeSec);
		}
		return $renderedTime;
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

	// Create a smugmug url for an image given a slug and a size.
	//
	// Note that Ti and Th will _crop_ to the correct aspect ratio.
	// See https://www.smugmughelp.com/en/articles/390-change-the-display-size-of-my-photos
	function makeSmugmugUrl($slug, $size = 'S') {
	  if(empty($slug)) {
	 	die("no slug in makeSmugmugUrl");
	  }
	  if (!in_array($size, ['Ti','Th','S','M','L','XL','X2','X3','X4','X5','4k','5k','O'])) {
		die("invalid size: '$size' in makeSmugmugUrl");
	  }		
	  return "https://photos.smugmug.com/photos/".$slug."/0/".$size."/".$slug."-".$size.".jpg";
	}

    // Returns a "Default" year to use when one is not specified on the raceday pages.  Utility function
    // to keep it consistent.
    //
    // Starting in March, default to the current year to allow Raceday mode to be turned on a month out.
    // Otherwise use the prior year. Not 100% perfect, but uses of the default value should be rare.
    function getDefaultRacedayYear() {
      $CURRENT_YEAR = date("Y");
      $year = $CURRENT_YEAR;
      if (date("m") < 3) {
        // Not yet March, use prior year.
        $year = $year - 1;
      }
      return $year;
    }

	// Verifies that the class ('m', 'w', or 'n') in the given year actually awarded
    // up to $place places.  Returns false if not (or if class is invalid).
    function checkTrophyYear($class, $year, $place) {
	  if ($place <= 0) {
	    return false;
	  }

	  $class = strtolower($class);

	  if ($class == 'm') {
	    // Mens
	    // 3 Until 1964, 6 after
	    if ($year < 1964 && $place <= 3) {
		  return true;
	    } else if ($year >= 1964 && $place <= 6) {
		  return true;
	    }
	  } else if ($class == 'w') {
	    // Womens
	    // 3 Until 2013
	    // 4 2013-2016
	    // 6 After 2016
	    if ($year < 2013 && $place <= 3) {
		  return true;
	    } else if ($year >= 2013 && $year <= 2016 && $place <= 4) {
		  return true;
	    } else if ($year > 2016 && $place <= 6) {
		  return true;
	    }
	  } else if ($class = 'n') {
	    // All Gender: Only 3 Places (so far)
	    if ($place <= 3) {
		  return true;
	    }
	  }

	return false;
  }

  // Die if the paramter (which should have been required
  // for our routing to the current page) is not present.

  // Return it otherwise.
  function dieOrGetParam($param) {
    if (empty($_GET[$param])) {
        // Should not have been routed here.
        die("routed without url key:" . $param);
    }
    return $_GET[$param];
  }
?>
