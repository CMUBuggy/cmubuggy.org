<?php include_once("../util.inc"); 
$headline = "Auction 2011";
$title = "Auction 2011";	
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
	<head>
		<title>Auction | CMU Buggy Alumni Association</title>
		<!-- <script type="text/javascript" src="jquery-1.3.2.min.js"></script> -->
		<?php include_once("../content/cssjs.inc"); ?>
		<script type="text/javascript" src="jquery.corners.js"></script>
		<script type="text/javascript"> 
		     type = '<?echo $type?>';
		</script>
		<script type="text/javascript" src="auction_lib.js"></script>
		<script type="text/javascript"> 
		     globalTimeAdjustment = 1110;
		     numberOfAuctions = 13
		
		     function reloadAuctionListFadeIn(){
		       cgiVars = getCgiVars();
		       $('#auctions').empty();
		       displayAuctionList(cgiVars['gender'],cgiVars['day']);
				 $('#auctions').show()	       
		       //$('#auctions').fadeTo('fast',1.0,dummyFunc);
		       setTimeout ( "reloadAuctionListFadeOut()", 10000 );
		     }
		
		     function dummyFunc(){
		
		     }
		
		     function reloadAuctionListFadeOut(){
				 reloadAuctionListFadeIn(); 
		       //$('#auctions').fadeTo('fast',0.01,reloadAuctionListFadeIn);
		     }
		
		     $(document).ready(function(){
		      cgiVars = getCgiVars();
		      if(cgiVars['gender']=="m"){
		       raceType = "Men's"
		      } else {
		       raceType = "Women's"
		      }
		      if(cgiVars['day']=="1"){
		       raceDay = "Prelim";
		      } else {
		       raceDay = "Final";
		      }
		
		      $('#genderType').html(raceType+" "+raceDay+" ");
		      $('#auctions').empty();
		      displayAuctionList(cgiVars['gender'],cgiVars['day']);
		      window.setTimeout ( "reloadAuctionListFadeOut()", 5000 );
		      getAuctionAjax("get_json_auction_end",{},displayTimeTillEndOfAuctionCallback);
		      if(readCookie('userid')!= null){
		       $("#user_span").html("You are logged in as "+readCookie('userid'));
		       $("#logoutOrLogin").html("<a href='logout.php'>Logout</a>");
		      } else {
		       $("#user_span").html("You are NOT logged in - <a href='/bid2011/login.php'>click here to login </a> ");
		       $("#logoutOrLogin").html("<a href='login.php'>Login</a>");
		     }
		
		     })
		
		    </script>
			>
	</head>
<?php
		include_once("../content/pre-content.inc");
?>
		      	<span id="genderType"></span> Heats
			   <div style="height:800px" id="auctions"></div>
			   <div id="errorbox" style="visibility:hidden">
			    	<div id="errorboxtext" class='box redbox'></div>
			   </div> 

<?php
		include_once("../content/post-content.inc");
?>	
	</body>
</html>








