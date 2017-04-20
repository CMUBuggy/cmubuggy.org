<div id="homepage">
     <?php include_once("contentfeed.inc");   ?>     
     <div  class="yui3-g"  style="width:510px; height:145px;">
        <div class="yui3-u-1-2">
            <div style="margin-right:10px">
                <h3><a href="/raceday">Everything Raceday</a></h3>      
                Quick Links:
                <ul class="list">
                    <li><a href="/raceday/heats">Heat Schedule</a></li>
                    <li><a href="/raceday/leaderboard">2017 Leaderboard</a></li>
                    <li>Streams <a href="http://wrct.org">WRCT</a> | <a href="http://livestream.com/cmuTVlive/">cmuTV</a></li>
                    <li><a href="https://discordapp.com/invite/PUwuUuj">Live Chat</a></li>
                    <li><a href="http://timing.cmubuggy.org">Live Course Times</a> | <a href="/files/course_map_tents_2017.png">Map</a></li>
                    <li>
                </ul>
            </div>
        </div>
        <div class="yui3-u-1-2" style="">
             <h3><a href="/files/carnival_schedule_2017.png">Carnival Schedule</a></h3>
            <b>Coming Up Next</b><br />
            <?php
                $auctionstart   = mktime( 9, 0,0,4,18,2017);
                $wrct           = mktime(19, 0,0,4,19,2017);
                $auctionend     = mktime(23, 0,0,4,19,2017);
                $designcomp     = mktime(12, 0,0,4,20,2017);
                $dctalk         = mktime(12,30,0,4,20,2017);
                $bartime        = mktime(19, 0,0,4,20,2017);
                $wprelims       = mktime(8, 20,0,4,21,2017);
                $mprelims       = mktime(10, 0,0,4,21,2017);
                $reception      = mktime(12,30,0,4,21,2017);
                $hob            = mktime(13,30,0,4,21,2017);
                $exhibitions    = mktime( 8,55,0,4,22,2017);
                $wfinals        = mktime( 9,50,0,4,22,2017);
                $mfinals        = mktime(10,15,0,4,22,2017);
                $happyhr        = mktime(16,00,0,4,22,2017);
                $awards         = mktime(16,30,0,4,22,2017);
                  
                $events = array(
                    $auctionstart   => "<code>Tue 09:00a</code> <a href=\"/news/2017/04/lead-truck-auction-is-live-2/\">Lead Truck auction</a> starts",       
                    $wrct           => "<code>Wed 08:00p</code> Buggy talk on <a href\"http://www.wrct.org/\">WRCT</a>",
                    $auctionend     => "<code>Wed 11:59p</code> <a href=\"/news/2016/04/auction/\">Lead Truck auction</a> closes",  
                    $designcomp     => "<code>Thu 12:00a</code> Buggy Showcase",
                    $bartime        => "<code>Thu 07:00p</code> <a href=\"http://houghspgh.com\">Buggy Drinks @ Hough's</a>", 
                    $wprelims       => "<code>Fri 08:20a</code> Women's Prelims",
                    $mprelims       => "<code>Fri 10:00a</code> Men's Prelims",
                    $reception      => "<code>Fri 12:30p</code> BAA Lunch",  
                    $hob            => "<code>Fri 01:30p</code> History of Buggy",
                    $exhibitions    => "<code>Sat 08:55a</code> Exhibitions",
                    $wfinals        => "<code>Sat 09:50a</code> Women's Finals",
                    $mfinals        => "<code>Sat 10:50a</code> Men's Finals",
                    $happyhr        => "<code>Sat 4:00p</code> BAA Happ Hour @Porch",
                    $awards         => "<code>Sat 04:30p</code> Awards Ceremony"    
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
