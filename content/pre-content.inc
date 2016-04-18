<?php
   date_default_timezone_set('America/New_York');
   $rddate = mktime(9, 0, 0, 4, 21, 2017);
   $currenttime = time();
   $hoursleft = floor(($rddate - $currenttime)/(60*60));
   $daysleft = floor($hoursleft/24);
   $weeksleft = floor($daysleft/7);
   $monthsleft = floor($daysleft/30);
   $count = $monthsleft;
   $unit = "MONTHS";
   if($count < 4){
	   $count = $weeksleft;
	   $unit = "WEEKS";
	   if($count < 4){
	   	$count = $daysleft;
	   	$unit = "DAYS";
	   	if($count < 4){
	   		$count = $hoursleft;
	   		$unit = "HOURS";
	   	}
	   }
	}
	if($hoursleft < 0){
   	$count = "GO";
   	$unit = "TIME";	
   }
?>
<body id="doc">
	<div id="hd">
		<img id="end" src="/img/headerend.gif" alt="" />
		<div id="rddate">Raceday 2016<br/>April 15-16 </div>
		<div id="countdown">
			<div id="count"><?php echo $count ?></div>
			<div id="unit"><?php echo $unit ?></div>
		</div>
		<div id="title"><?php echo($headline); ?></div>
	</div>
	<div id="bd" class="yui3-g">
     <div id="left" class="yui3-u"> 
         <a href="/"><img id="logo" alt="CMU Buggy Alumni Association logo" src="/img/logo-web.png" /></a>
			<?php include_once("leftmenu.inc"); ?>	
     </div> 
     <div id="content" class="yui3-u">
     
