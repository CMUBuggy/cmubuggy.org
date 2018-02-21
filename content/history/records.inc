<?php

	$teamObj = new team();
	$top25men  = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1")),"time", "true", 50);
	//$top25menb = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1"), array("abcd","=","b")),"time", true, 25);
	//$top25menc = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1"), array("abcd","=","c")),"time", true, 25);
	//$top25mend = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1"), array("abcd","=","d")),"time", true, 25);

	$top25women  = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2")),"time", true, 50);
	//$top25womenb = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2"), array("abcd","=","b")),"time", true, 25);
	//$top25womenc = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2"), array("abcd","=","c")),"time", true, 25);
	//$top25womend = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2"), array("abcd","=","d")),"time", true, 25);

	function displayRecordTable($teamlist){
		echo("<table class=\"data\">");
		$count = 1;
		foreach($teamlist as $team){
			$entry= $team->GetEntry();
			$raceday = $team->GetRaceday();
			$racedaynum = 1;
			if($raceday->isFinals==1){$racedaynum = 2;}
			$org = $entry->GetOrg();
			$year = $entry->GetRaceyear()->year;
			$buggy = $team->GetBuggy();
			$dq = $team->GetDq();
			$url = "/history/team/".$entry->urlkey;


			echo("<tr><td>".$count.".</td>");
			echo("<td><a href=\"/history/raceday/".$year."\">".$year."</a><sub>".$racedaynum."</sub></td>");
			echo("<td><a href=\"".$url."\">".$org->shortname."</a></td>");
			echo("<td><a href=\"/history/buggy/".$buggy->urlKey."\">".$buggy->name."</a></td>");
			echo("<td>".displayTime($team->time)."</td>");
			echo("<td>".$dq->description." ".$team->notes."</td></tr>");

			$count++;
		}
		echo("</table>");
	}
?>

</h2>Course Records</h2>
<ul class="tabs">
	<li><a id="t1" href="#mens">Men's</a></li>
	<li><a id="t2" href="#womens">Women's</a></li>
	<!--<li><a id="t2" href="#mensb">Men's B</a></li>
	<li><a id="t6" href="#womensb">Women's B</a></li>
	<li><a id="t3" href="#mensc">Men's C</a></li>
	<li><a id="t7" href="#womensc">Women's C</a></li>
	<li><a id="t4" href="#mensd">Men's D</a></li>-->
</ul>

<div class="panes">
	<div class="pane">
		<?php displayRecordTable($top25men); ?>
	</div>
	<div class="pane">
		<?php displayRecordTable($top25women); ?>
	</div>
	<!--
	<div class="pane">
		<?php //displayRecordTable($top25menb); ?>
	</div>
	<div class="pane">
		<?php //displayRecordTable($top25womenb); ?>
	</div>
	<div class="pane">
		<?php //displayRecordTable($top25menc); ?>
	</div>
	<div class="pane">
		<?php //displayRecordTable($top25womenc); ?>
	</div>
	<div class="pane">
		<?php //displayRecordTable($top25mend); ?>
	</div>
	<div class="pane">
		<?php //displayRecordTable($top25womend); ?>
	</div>-->
</div>











