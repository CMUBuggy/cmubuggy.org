<?php
$org = new org();

if(!empty($_GET["urlkey"])){
	$orgList = $org->GetList(array(array("urlkey","=",$_GET["urlkey"])));
	if($orgList){
		$org = $orgList[0];
	}
}

$shortname = "";
$longname = $org->longname;
if($org->isgreek){
	$longname = "<span class=\"greek\">".$org->greekname."</span>";
}
if($org->shortname <> $org->longname || $org->isgreek==1){
	$shortname = "<span style=\"font-size:.5em\">(".$org->shortname.")</span>";
}

$yearfounded = "";
if($org->yearfounded > 0){
	$yearfounded = $org->yearfounded;
} 

$orgAwardList = $org->GetOrgawardList(null,"year");
$buggyList = $org->GetBuggyList(null,"yearBuilt",false);
$entryList = $org->GetEntryList(null,"raceyearId", false);
$trophyArr = array();

$entryArr  = array();
$recordArr = array();
$entrytypes = array("1A", "1B", "1C", "1D", "2A", "2B", "2C", "2D");

foreach($entryList as $entry){
	$year			= $entry->GetRaceyear()->year;
	$raceclass 	= $entry->GetRaceclass();
	$abcd 		= $entry->abcd;
	$place 		= $entry->place;
	$teamlist 	= $entry->GetTeamList();
	$entrytype 	= $raceclass->raceclassId.$abcd;
	$entryArr[$year][$entrytype] = $entry;
	
	//Check for org-record time
	foreach($teamlist as $team){
		//echo($team->time);
		if($team->time > 0){
			if(array_key_exists($entrytype, $recordArr)){
				if($team->time < $recordArr[$entrytype]->time){
					$recordArr[$entrytype] = $team;
				}
			} else {
				$recordArr[$entrytype] = $team;
			}
		}
	}
	
	//save any Men's trophies won to the TrophyArr
	if($raceclass->raceclassId == 1 && $place < 7 && $place >0){
		$awardType = "1".$place;
		addtrophy($year, $awardType);
	}
	//save any Women's trophies won to the TrophyArr
	if($raceclass->raceclassId == 2 && $place < 4 && $place >0){
		$awardType = "2".$place;
		addtrophy($year, $awardType);
	}
}
//print_r($entryArr);

foreach($orgAwardList as $orgAward){
	$year = $orgAward->year;
	$awardType = "99".$orgAward->GetAwardtype()->description;
	addtrophy($year, $awardType);
}

foreach($buggyList as $buggy){
	$buggyawards = $buggy->GetBuggyawardList(null,"awardtypeid");
	foreach($buggyawards as $award){
		addtrophy($award->year, "98".$award->GetAwardtype()->description);
	} 	
}

function addtrophy($year, $awardType){
	global $trophyArr;
	if(array_key_exists($year, $trophyArr)){
		array_push($trophyArr[$year],$awardType);	
	} else {
		$trophyArr[$year]= array($awardType);
	}
}

function displayraceyear($entries,$year) {
	global $entrytypes;
	echo("<tr><td style=\"width:30px\"><a href=\"/history/raceday/".$year."\">".$year."</a></td>");	
	foreach($entrytypes as $entrytype){
		if(isset($entries[$entrytype])){
			$entry = $entries[$entrytype];
			$teamlist = $entry->GetTeamList();
			$dq = null;
			$time = null;
			foreach($teamlist as $team){
				$time = $team->time;
				if($team->dqId>0) {$dq = "dq"; }
			}

			$outcome = "";
			if($entry->place > 0){
				$outcome = $entry->place;
			}
			if($dq){$outcome = $dq; }
			if($time>0){$time = displayTime($time); } else {$time = "- -"; }
				
			echo("<td style=\"width:60px\"><a href=\"/history/team/".$entry->urlkey."\">".$time."</a></td><td style=\"width:15px\">".$outcome."</td>");
			
		} else {
			echo("<td></td><td></td>");	
		}
	}
}

function displaytrophyyear($trophies, $year){
	sort($trophies,SORT_NUMERIC);
	echo("<tr><td>".$year."</td><td>");
	foreach($trophies as $trophy){
		switch($trophy) {
			case "11":
				echo("Men's 1st Place<br />");
				break;
			case "12":
				echo("Men's 2nd Place<br />");
				break;
			case "13":
				echo("Men's 3rd Place<br />");
				break;
			case "14":
				echo("Men's 4th Place<br />");
				break;
			case "15":
				echo("Men's 5th Place<br />");
				break;
			case "16":
				echo("Men's 6th Place<br />");
				break;
			case "21":
				echo("Women's 1st Place<br />");
				break;
			case "22":
				echo("Women's 2nd Place<br />");
				break;
			case "23":
				echo("Women's 3rd Place<br />");
				break;
			case "98Design Competition - 1st Place":
				echo("Design Comp - 1st Place<br />");
				break;
			case "98Design Competition - 2nd Place":
				echo("Design Comp - 2nd Place<br />");
				break;
			case "98Design Competition - 3rd Place":
				echo("Design Comp - 3rd Place<br />");
				break;
			case "98Design Competition - People's Choice":
				echo("Design Comp - People's Choice<br />");
				break;
			case "99T-Shirt Award":
				echo("Best T-Shirt Award<br />");
				break;	
			case "99Chairman's Choice":
				echo("Chairman's Choice<br />");
				break;
			case "99Spirit of Buggy":
				echo("Spirit of Buggy<br />");
				break;
				
			default:
				echo($trophy);
		}
	}
	echo("</td></tr>");
}

function displayrecord($entrytype) {
	global $recordArr;
	if(isset($recordArr[$entrytype])){
		$team = $recordArr[$entrytype];
		$entry= $team->GetEntry();
		$raceday = $team->GetRaceday();
		$racedaynum = 1;
		if($raceday->isFinals==1){$racedaynum = 2;}
		echo("<a href=\"/history/team/".$entry->urlkey."\">".displayTime($team->time)."<br />".$raceday->GetRaceyear()->year."<sub>".$racedaynum."</sub></a>");
	}
}

function graphtrends($entrytypes, $firstyear, $lastyear) {
	global $entryArr, $org;
	$graphArr = array();	 
	$chartData = new pData();
	$filename = "trend".$org->urlkey.$firstyear.$lastyear;
	foreach($entrytypes as $et){
		$filename.=$et;
	}
	if(file_exists("/content/cache/graph/".$filename)){
		echo("<img src=\"/content/cache/graph/".$filename.".png\" alt=\"\">");
	} else {
		for($year=$firstyear;$year<=$lastyear;$year++){
			$chartData->addPoints($year,"Year"); 
			if(isset($entryArr[$year])){		
				$entries = $entryArr[$year];
				foreach($entrytypes as $entrytype){
					if(isset($entries[$entrytype])){
						$entry = $entries[$entrytype];
						$teamlist = $entry->GetTeamList();
						$time = VOID;
						foreach($teamlist as $team){
							$teamtime = $team->time;
							if($teamtime > 0 && ($teamtime < $time || $time == VOID)){
								$time = $teamtime; 
							}
						}
						$graphArr[$entrytype][$year] = $time;
					} else {
						$graphArr[$entrytype][$year]= VOID;
					}
				}
			} else {
				foreach($entrytypes as $entrytype){
					$graphArr[$entrytype][$year]= VOID;
				}	
			}
		}
	
		foreach($entrytypes as $type){
			//remove series for which there are no records in the time range.  the "VOID" points end up being counted as 1.something, so > 100 filters out non-real entries
			if(array_sum($graphArr[$type])> 100){
				$label = "";
				switch($type) {
					case "1A": $label = "Men's A"; break;
					case "1B": $label = "Men's B"; break;	
					case "1C": $label = "Men's C"; break;	
					case "1D": $label = "Men's D"; break;	
					case "2A": $label = "Women's A"; break;
					case "2B": $label = "Women's B"; break;
					case "2C": $label = "Women's C"; break;
					case "2D": $label = "Women's D"; break;
				}	
				$chartData->addPoints($graphArr[$type],$label);
				$chartData->setSerieWeight($label,1);
			}
		}
		$chartTitle = $org->shortname." ".$firstyear."-".$lastyear;
		$chartFilename = $org->urlkey."Mtrends";
		
		include("content/history/trendchart.inc");
	}
}

?>

<div class="pane">
<h1><?php echo($longname . " " . $shortname); ?></h1>
Founded: <?php echo($yearfounded); ?><br />	

</div>

<?php if($org->isracingorg == 1){ ?>
<ul class="tabs">
	<li><a id="t1" href="#raceresults">Race Results</a></li>
	<li><a id="t2" href="#records">Records</a></li>
	<li><a id="t3" href="#buggies">Buggies (<? echo(count($buggyList)); ?>)</a></li>
	<li><a id="t4" href="#trophies">Trophies (<? echo(count($trophyArr, COUNT_RECURSIVE)-count($trophyArr)); ?>)</a></li>
	<li><a id="t5" href="#trends">Trends</a></li>
</ul>
<?php } else { ?>
<ul class="tabs">
	<li><a id="t1" href="#trophies">Trophies (<? echo(count($trophyArr, COUNT_RECURSIVE)-count($trophyArr)); ?>)</a></li>
</ul>
<?php } ?>

<div class="panes">
<?php if($org->isracingorg == 1){ ?>
	<div class="pane">
		<div class="title">Race Results</div>
			<table class="data">
				<tr>
					<th style="width:30px">Year</th>
					<th style="width:75px">Men's A</th>
					<th style="width:75px">Men's B</th>
					<th style="width:75px">Men's C</th>
					<th style="width:75px">Men's D</th>
					<th style="width:75px">Women's A</th>
					<th style="width:75px">Women's B</th>
					<th style="width:75px">Women's C</th>
				</tr>
			</table>
		<div>
			<table class="data">
				<?php
					array_walk($entryArr,"displayraceyear");
				?>
			</table>
		</div>
	</div>
<?php } if($org->isracingorg == 1){ ?>
	<div class="pane">
		<div class="title">Organization Records</div>
		<table class="data">
			<tr>
				<th></th>
				<th>A team</th>
				<th>B team</th>
				<th>C team</th>
				<th>D team</th>
			</tr>
			<tr>
				<th>Men's</th>
				<td><?php displayrecord("1A"); ?></td>
				<td><?php displayrecord("1B"); ?></td>
				<td><?php displayrecord("1C"); ?></td>
				<td><?php displayrecord("1D"); ?></td>
			</tr>
			<tr>
				<th>Women's</th>
				<td><?php displayrecord("2A"); ?></td>
				<td><?php displayrecord("2B"); ?></td>
				<td><?php displayrecord("2C"); ?></td>
				<td><?php displayrecord("2D"); ?></td>		
			</tr>
		</table>
	</div>
<?php } if($org->isracingorg == 1){ ?>
	<div class="pane">
		<div class="title">Buggies</div>
		<table class="data">
		<?php
		foreach ($buggyList as $buggy)
		{
			$year = $buggy->yearBuilt;
			if($year == 0) { $year = ""; }
			$picIco = "";
			if($buggy->pictureId != 0) { $picIco = "<a href=\"/history/buggy/".$buggy->urlKey."\"><img height=\"16\" width=\"16\" src=\"/img/cameraIcon.gif\" /></a>"; }
			echo("<tr><td><a href=\"./?p=buggies&year=".$year."\">".$year."</a></td><td>".$picIco."</td><td><a href=\"/history/buggy/".$buggy->urlKey."\">" . $buggy->name . "</a></td></tr>");
		}
		
		?>
		</table>
	</div>
<?php } ?>
	<div class="pane">
		<div class="title">Awards</div>
		<table class="data">
		<?php
			krsort($trophyArr);
			array_walk($trophyArr,"displaytrophyyear");
		?>
		</table>
	</div>
<?php if($org->isracingorg == 1){ ?>
	<div class="pane">
		<div class="title">Trends</div>
		<?php	graphtrends(array("1A","1B","1C"),"2001","2017");?>
		<?php	graphtrends(array("2A","2B"),"2001","2017");?>
	</div>
<?php } ?>
</div>
