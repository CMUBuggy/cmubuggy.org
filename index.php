<?php 
	include_once("dbconfig.inc");
	include_once("lib/pog/pog_includes.inc");
	include_once("lib/pChart/pChart_includes.inc");
	include_once("util.inc");
	session_start();

	$s = null;
	if(isset($_GET["s"])) {
		$s = $_GET["s"];
	}
	$title = "CMU Buggy Alumni Association";
	$headline = "Happy Build Season to All";
	switch($s){
		case "about":
			$title = "About | ".$title;
			$headline = "About";
			break;
		case "auction":
			$title = "Lead Truck Auction | ".$title;
			$headline = "Lead Truck Auction";
			break;
		case "admin":
			$title = "Admin | ".$title;
			$headline = "Admin";	
			break;
		case "buzz":
			$title = "Buzz | ".$title;
			$headline = "Live Buggy Chat";
			break;
		case "fantasy":
			$title = "Fantasy Buggy | ".$title;
			$headline = "Fantasy Buggy Fall '11";	
			break;						
		case "history": 
			$title = "History | ".$title;
			$headline = "History";
			$dbname = "cmubuggy_pog";
			break;
		case "live":
			$title = "Live! | ".$title;
			$headline = "Live Streaming Buggy";
			break;
		case "membership":
		case "join": 
			$title = "Membership | ".$title;
			$headline = "Join or Renew";
			break;
		case "search": 
			$title = "Search Results | ".$title;
			$headline = "Search Results";
			break;
		case "seniors":
			$title = "Seniors | ".$title;
			$headline = "You're alumni now, class of 2011";
			break;
		case "store": 
			$title = "Store | ".$title;
			$headline = "Merchandise and souveniers!";
			break;
		case "user":
			$title = "Users | ".$title;
			$headline = "Users";
			break;
		case "raceday":
			$title = "Raceday | ".$title;
			$headline = "Raceday!";
			break;
		case "video":
		case "videolist":
			$title = "Videos | ".$title;
			$headline = "Video Archives";
			break;
	}
	
	if(empty($s)){
		$content = ("./content/homepage.inc");
	} else if(file_exists("./content/".$s.".inc")){
		$content = "./content/".$s.".inc";
	} else {
		$content = "./content/404.inc";
		$title = "Not Found | ".$title;
		$headline = "Not Found";
	}
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<meta name="google-site-verification" content="GXsMGGkXYJADa-Rw8I0azRbCk_ILRSXWwTkiHODCBrw" />
	<title><?php echo($title); ?></title>
	<?php include_once(ROOT_DIR."/content/cssjs.inc"); ?>
</head>
<?php
		include_once("content/pre-content.inc");
		include_once($content);
		include_once("content/post-content.inc");
?>	
</body>
</html>
