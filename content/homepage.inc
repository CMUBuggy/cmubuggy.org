<div id="homepage">
    <?php include_once("contentfeed.inc");   ?> 	 
    <div  class="yui3-g"  style="width:510px; height:145px;">
        <div class="yui3-u-1-2">
            <div style="margin-right:10px">
                <h3><a href="/raceday">Everything Raceday</a></h3>      
                Quick Links:
                <ul class="list">
                    <li><a href="/raceday/heats">Heat Schedule</a></li>
                    <li><a href="/raceday/leaderboard">2014 Leaderboard</a></li>
                    <li>Streams <a href="http://wrct.org">WRCT</a> | cmuTV</li>
                </ul>
            </div>
        </div>
        <div class="yui3-u-1-2" style="">
             <h3><a href="/raceday">Schedule</a></h3>
            <b>Coming Up Next</b><br />
            <?php
                $auctionstart   = mktime( 9, 0,0,4,2,2014);
                $auctionend     = mktime(21, 0,0,4,6,2014);
                $wrct           = mktime(19, 0,0,4,9,2014);
                $designcomp 	= mktime(10, 0,0,4,10,2014);
                $mattwagner     = mktime(11, 0,0,4,10,2014);
                $bartime 		= mktime(20, 0,0,4,10,2014);
                $openingcer     = mktime( 8, 0,0,4,11,2014);
                $wprelims 		= mktime(8, 25,0,4,11,2014);
                $mprelims       = mktime(10, 0,0,4,11,2014);
                $reception 	    = mktime(12,30,0,4,11,2014);
                $hob	        = mktime(13,30,0,4,11,2014);
                $exhibitions 	= mktime( 8, 0,0,4,12,2014);
                $mfinals 		= mktime( 9, 0,0,4,12,2014);
                $wfinals        = mktime(10, 15,0,4,12,2014);
                $awards 		= mktime(18, 0,0,4,12,2014);
                $breakfast 	    = mktime(10, 0,0,4,13,2014);
                  
                $events = array(
                    $auctionstart	=> "Wed, 9am:<a href=\"/auction\">Lead Truck auction</a> starts",		
                    $auctionend  	=> "Sun, 9pm: <a href=\"/auction\">Lead Truck auction</a> closes",	
                    $wrct           => "<code>Wed 07:00p</code> Buggy talk on <a href\"http://www.wrct.org/\">WRCT</a>",
                    $designcomp  	=> "<code>Thu 10:00a</code> Design Comp",
                    $mattwagner     => "<code>Thu 11:00a</code> Matt Wagner Talk",
                    $bartime 	 	=> "<code>Thu 08:00p</code> <a href=\"http://houghspgh.com\">Hough's</a> (<a href=\"http://g.co/maps/a3qqk\">map</a>)",	
                    $openingcer	 	=> "<code>Fri 08:00a</code> Opening Ceremonies",
                    $wprelims       => "<code>Fri 08:25a</code> Women's Prelims",
                    $mprelims       => "<code>Fri 10:00a</code> Men's Prelims",
                    $reception 	    => "<code>Fri 12:30p</code> BAA reception, BH Lounge",	
                    $hob	        => "<code>Fri 01:30p</code> The History of Buggy",
                    $exhibitions 	=> "<code>Sat 08:00a</code> Exhibitions",
                    $wfinals 		=> "<code>Sat 09:00a</code> Women's Finals",
                    $mfinals        => "<code>Sat 10:15a</code> Men's Finals",
                    $awards 		=> "<code>Sat 06:00p</code> Awards Ceremony",	
                    $breakfast 	    => "<code>Sun 10:00a</code> Morning after breakfast"	
                );
                 
                $currenttime = time();
                $dispcount = 0;
                foreach ($events as $eventtime => $desc){
                    if($currenttime-60*60 < $eventtime && $dispcount < 6){
                        echo("<img src=\"/css/images/orange_bullet.gif\" /> ".$desc."<br />");
                        $dispcount++;	
                    }
                }
            ?>  
        </div>
    </div>
    <br />
    <?php include_once("twitterwidget.inc"); ?>
    <div class="pane clearleft" style="margin-right:270px;">
        <h3 style="margin:0">Buggy Alumni Association?</h3>
        We were founded in 2008 to unite and connect alumni across teams and eras, and to support the coolest sport we know.  Join us! We're open to everyone: current students, Pittsburgh locals, enthusiasts of any kind. Find out more in <a href="/about">About Us section ...</a>	
    </div>
    <div class="pane" style="margin-right:270px;">
        <h3 style="margin:0">Buggy?</h3>
        Buggy (also called "Sweepstakes") is a unique race that has been held on and behind the Carnegie Mellon University campus during the spring carnival since 1920.  It is part uphill relay race (in which the baton is a vehicle and driver pushed by runners), and part downhill gravity racing with exciting sharp turns and speeds up to 40mph. Find out more in the <a href="/reference/What_is_buggy%3F">What is Buggy? section ...</a>
    </div>
</div>

