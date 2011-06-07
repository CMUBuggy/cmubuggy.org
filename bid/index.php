<?php 
$headline = "Auction 2011";
$title = "Auction 2011";	
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<title><?php echo($title); ?></title>
	<?php include_once("../content/cssjs.inc"); ?>
</head>

<?php
		include_once("../content/pre-content.inc");
?>
     <div id="content" class="yui3-u"> 
	<br />
	<h3 style='color:red'>In order to use the auction site, you must use firefox, and have cookies enabled</h3>
   	<br />
   	To participate in the auction, you need to log in with your cmubuggy.org forum username and password<br>
   	<br />
	
   <form action='/bid2011/login.php' method='POST'>
    <table>
     <tr>
	     <td>User Name</td><td><input type='text' name='userid'/></td><td rowspan="2">If you are not registered on the cmubuggy.org forum<br /><span style="font-size:large"><a href="http://www.cmubuggy.org/user/register">Register Now</a></span></td>
     </tr>
     <tr>
     	<td>Password</td><td><input type='password' name='password'/></td>
     </tr>
     <tr>
     	<td align=center colspan=2><input type='submit' value='Login'></td>
     </tr>
    </table>
   </form>
   </div>
<?php
		include_once("../content/post-content.inc");
?>	
</body>
</html>
