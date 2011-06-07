<?php
$personArrInit = array("Driver"=>"",
							  "Hill 1"=>"",
							  "Hill 2"=>"",
							  "Hill 3"=>"",
							  "Hill 4"=>"",
							  "Hill 5"=>"");
$personArr = array();

function displayteam($team){
	global $personArr, $personArrInit;
	$personArr = $personArrInit;

	$raceday = $team->GetRaceday();
	$rddesc = "Prelims";
	$reroll = "";
	if($raceday->isFinals == 1){$rddesc = "Finals";}
	if($team->isReroll == 1) {$reroll = " (reroll)";}
	echo("<div class=\"floatleft\"><h4>".$rddesc.$reroll."</h4>");

	$heat = $team->GetHeat();
	if($heat->headId>0){
		$videolist = $heat->GetVideoList();
		if($videolist){
			$video = $videolist[0];
			include("content/youtubevid.inc");
		}
	}

	$buggy = $team->GetBuggy();

	$pttlist = $team->GetPersontoteamList();
	foreach ($pttlist as $ptt){
		$person = $ptt->GetPerson();
		$teamRole = $ptt->GetTeamrole();
		$personStr = "";
		if(isset($person)){
			$personStr = "<a href=\"/history/person/".$person->personId."\">".$person->firstName." ".$person->lastName."</a>";
		}
		$personArr[$teamRole->description] = $personStr; 
	}
	
	echo("<table class=\"data\">");
	echo("<tr><td>Buggy</td><td><a href=\"/history/buggy/".$buggy->urlKey."\">".$buggy->name."</a></td></tr>");
	echo("<tr><td>Driver</td><td>".$personArr["Driver"]."</td></tr>");
	echo("<tr><td>Hill 1</td><td>".$personArr["Hill 1"]."</td></tr>");
	echo("<tr><td>Hill 2</td><td>".$personArr["Hill 2"]."</td></tr>");
	echo("<tr><td>Hill 3</td><td>".$personArr["Hill 3"]."</td></tr>");
	echo("<tr><td>Hill 4</td><td>".$personArr["Hill 4"]."</td></tr>");
	echo("<tr><td>Hill 5</td><td>".$personArr["Hill 5"]."</td></tr>");
	echo("<tr><td>Time</td><td>".displayTime($team->time)."</td></tr>");
	echo("</table>");
	echo("</div>");
}


if(isset($_GET["urlkey"])){
	$errormsg 	= null;
	$urlkey 		= $_GET["urlkey"];
	$entry		= new entry();
	$entrylist 	= $entry->GetList(array(array("urlkey","=",$urlkey)));
	$teamlist 	= null;
	if($entrylist){ 
		$entry 		= $entrylist[0];
		$org 			= $entry->GetOrg();
		$raceyear	= $entry->GetRaceyear();
		$raceclass	= $entry->GetRaceclass();
		$teamlist 	= $entry->GetTeamList();
	}else{
		$errormsg = "There is no team identified by \"".$urlkey."\"";	
	}
} else {
	$errormsg = "There is no team specified in the url";
}
if(!is_null($errormsg)){	
	echo($errormsg);	
} else {
	
?>
<div class="pane">
<?php
	echo("<h2><a href=\"/history/raceday/".$raceyear->year."\">".$raceyear->year."</a> <a href=\"/history/org/".$org->urlkey."\">".$org->shortname."</a> ".$raceclass->description." ".$entry->abcd."</h2>");
	
	foreach($teamlist as $team){
		displayteam($team);
	}
}
	
?>


</div>