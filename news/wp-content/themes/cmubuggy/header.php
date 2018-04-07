<?php
	include_once("../util.inc");
	include_once("../lib/pog/pog_includes.inc");
	//session_start();
	$headline = "News";
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<title>News | <?php the_title(); ?></title>
	
	<meta property="og:title" content="<?php the_title(); ?>"/>
	<meta property="og:type" content="article" />
   <meta property="og:site_name" content="CMU Buggy Alumni Association"/>
   <meta property="og:url" content="<?php the_permalink(); ?>"/>
	<meta property="og:description" content="Breaking buggy news and rolls reports from the Buggy Alumni Association"/>   
   <meta property="fb:admins" content="swiftsam"/>
   <meta property="fb:app_id" content="150469765045743"/>
   
   
	<?php include_once("../content/cssjs.inc"); ?>
	<link rel="stylesheet" type="text/css" href="/css/cmubuggy-wordpress.css" />
	<script type="text/javascript" src="https://apis.google.com/js/plusone.js"></script>
</head>
<?php 
	include_once("../content/pre-content.inc");

  wp_nav_menu(
    array(
      'theme_location' => 'primary',
      'menu_class' => 'sf-menu',
      'container' => 'div',
      'container_id' => 'topnav'
    )
  );
?>
