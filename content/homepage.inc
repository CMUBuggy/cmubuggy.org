<div id="homepage">
    <?php include_once("contentfeed.inc");   ?> 	 
    <div  class="yui3-g"  style="width:500px; height:145px;">
  		<div class="yui3-u-2-5">
			<?php include_once("freerollstatus.inc"); ?>			
		</div>
		<div class="yui3-u-3-5">
	        <h3><a href="/auction">Lead Truck Auction</h3></a>
	        <?php
	            date_default_timezone_set('America/New_York');
	            $auctionstart = mktime(9, 0, 0, 4,2, 2014);
	            $auctionend = mktime(21, 0, 0, 4,6, 2014);
	            $hourstilstart = floor(($auctionstart - time())/(60*60));
	            $hourstilend = floor(($auctionend - time())/(60*60));
	            $minutestilend = floor(($auctionend - time())/60);
	            $displayend = $hourstilend;
	            $displayunit = "Hours";
	            if($hourstilend == 1){
	                $displayunit = "Hour"; 					
	            }
	            if($hourstilend < 1){
	                $displayend = $minutestilend;
	                $displayunit = "Minutes";	
	            }
	            if($minutestilend < 0){
	                $displayend = "0";
	                $displayunit = "Time"; 					
	            }
	        ?>
	        <div style="float:left; text-align:center; color:#f6ab1e; margin:-6px 11px 12px 0;">
	            <div style="font-size:2.5em; font-family:impact;"><?echo $displayend ?></div>
	            <div style="font-size:.8em; font-weight: bold; margin-top: -2px;"><? echo $displayunit ?> Left<br />to Bid</div>
	        </div>
	        <div style="float:left; text-align:center; color:#f6ab1e; margin:-6px 11px 12px 10px;">
	            <div style="font-size:2.5em; font-family:impact;">
	                $<?php echo(file_get_contents("http://".$_SERVER['SERVER_NAME']."/bid/getTotalRaised.php"));?>
	            </div>
	            <div style="font-size:.8em; font-weight: bold; margin-top: -2px;">Total Amount<br />Raised</div>
	        </div>
	        <div style="clear:left; padding-right:6px;"><strong>Wed 9am --> Sunday 9pm</strong> <a href="/auction"><br />Get your bids in now.</a></div>
	    </div>
    <!--
    <div class="yui3-u-3-5">
        <h3><a href="/raceday">Everything Raceday</a></h3>      
        We've got everything you need for raceday in one place.  Schedules, chats, feeds, and downloads.  <a href="/raceday">Get it.</a><br />
        <b>Coming Up</b>: (<a href="/raceday">full details here</a>)<br />
        <?php
            $auctionstart	= mktime( 9, 0,0,4,16,2013);
            $auctionend 	=  mktime(21, 0,0,4,17,2013);
            $designcomp 	= mktime(10, 0,0,4,18,2013);
            $bartime 		= mktime(20, 0,0,4,18,2013);
            $prelims 		= mktime( 8, 0,0,4,19,2013);
            $reception 	= mktime(12,30,0,4,19,2013);
            $hob	= mktime(13,30,0,4,19,2013);
            $exhibitions 	= mktime( 8, 0,0,4,20,2013);
            $finals 			= mktime( 9, 0,0,4,20,2013);
            $awards 			= mktime(18, 0,0,4,20,2013);
            $breakfast 	= mktime(10, 0,0,4,21,2013);
              
            $events = array(
                $auctionstart	=> "Tue, 9am: <a href=\"/auction\">Lead Truck auction</a> starts",							
                $auctionend  	=> "Wed, 9pm: <a href=\"/auction\">Lead Truck auction</a> closes",	
                $designcomp  	=> "Thur, 9am: Design Comp",
                $bartime 	 	=> "Thur, 8pm: <a href=\"http://houghspgh.com\">Hough's Bar</a> (<a href=\"http://g.co/maps/a3qqk\">563 Greenfield Ave</a>)",	
                $prelims 	 	=> "Fri, 8am: Prelims",
                $reception 	=> "Fri, 12:30pm: BAA reception",	
                $hob	=> "Fri, 1:30pm: The History of Buggy",
                $exhibitions 	=> "Sat, 8am: Exhibitions",
                $finals 			=> "Sat, 9am: Finals",
                $awards 		 	=> "Sat, 6pm: Awards Ceremony",	
                $breakfast 	=> "Sun, 10am: Morning after breakfast"	
            );
             
            $currenttime = time();
            $dispcount = 0;
            foreach ($events as $eventtime => $desc){
                if($currenttime-60*60 < $eventtime && $dispcount < 4){
                    echo("<img src=\"/css/images/orange_bullet.gif\" /> ".$desc."<br />");
                    $dispcount++;	
                }
            }
        ?>  
    -->
    </div>
    <?php include_once("featurepic.inc"); ?>
    <div class="pane clearleft" style="margin-right:270px;">
        <h3 style="margin:0">Buggy Alumni Association?</h3>
        We were founded in 2008 to unite and connect alumni across teams and eras, and to support the coolest sport we know.  Join us! We're open to everyone: current students, Pittsburgh locals, enthusiasts of any kind. Find out more in <a href="/about">About Us section ...</a>	
    </div>
    <div class="pane" style="margin-right:270px;">
        <h3 style="margin:0">Buggy?</h3>
        Buggy (also called "Sweepstakes") is a unique race that has been held on and behind the Carnegie Mellon University campus during the spring carnival since 1920.  It is part uphill relay race (in which the baton is a vehicle and driver pushed by runners), and part downhill gravity racing with exciting sharp turns and speeds up to 40mph. Find out more in the <a href="/reference/What_is_buggy%3F">What is Buggy? section ...</a>
    </div>
</div>