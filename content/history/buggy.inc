<?php
$buggy = new buggy();

if(!empty($_GET["urlkey"])){
	$buggyList = $buggy->GetList(array(array("urlkey","=",$_GET["urlkey"])));
	if(count($buggyList)>0){
		$buggy = $buggyList[0];
	}
}

$yearBuilt = "";
if($buggy->yearBuilt <> 0){
	$yearBuilt = $buggy->yearBuilt;
}

$org = new org();
$org = $buggy->GetOrg();

$teamList = $buggy->GetTeamList(array(array("teamId", ">", "0")),"racedayId",false);
$buggyAwardList = $buggy->GetBuggyawardList(array(array("buggyAwardId", ">", "0")),"year",false);

?>

<div class="pane">
	<?php 
		if(file_exists("/var/www/cmubuggy.org/img/buggy/".$buggy->urlKey)){
			echo("<img class=\"floatright\" alt=\"\" src=\"/img/buggy/".$buggy->urlKey."\" />");
		}	
	?>	
	<h2><?php echo($buggy->name);?></h2>
	Built: <?php echo($yearBuilt); ?><br />
	Org : <?php echo("<a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a>"); ?>
</div>	


<ul class="tabs">
	<li><a id="t1" href="#races">Races (<?php echo(count($teamList)); ?>)</a></li>
	<li><a id="t2" href="#awards">Awards (<?php echo(count($buggyAwardList)); ?>)</a></li>
</ul>
<div class="panes">
	<div class="pane">
		<table class="data">
			<tr><th></th><th>Year</th><th>Day</th><th>Team</th><th>Time</th><th>DQ / Notes</th></tr>
			<?php
			foreach ($teamList as $team){
				$entry= $team->GetEntry();
				$teamdesc = $entry->GetRaceclass()->description." ".$entry->abcd;
				$raceday = $team->GetRaceday();
				$racedaytype = "Prelims";
				if($raceday->isFinals==1){$racedaytype = "Finals";}
				$org = $entry->GetOrg();
				$year = $entry->GetRaceyear()->year;
				$buggy = $team->GetBuggy();
				$dq = $team->GetDq();
				if(strlen($dq->description)>0){$dq = "DQ: ".$dq->description; } else {$dq=""; }
				$url = "/history/".$entry->urlkey;
				$videolist = null;
				$videolist = $team->GetHeat()->GetVideoList();
				$video = null;
				if($videolist){ $video = reset($videolist); }
				echo("<td>");
				include("content/youtubevid.inc");
				echo("</td>");
				echo("<td><a href=\"/history/raceday/".$year."\">".$year."</a></td>");
				echo("<td>".$racedaytype."</td>");
				echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$teamdesc."</a></td>");
				echo("<td>".displayTime($team->time)."</td>");
				echo("<td>".$dq." ".$team->notes."</td></tr>");
			}
			?>
		</table>
	</div>
	<div class="pane">
		<table class="data">
		<?php
			foreach($buggyAwardList as $buggyAward){
				$awardType = $buggyAward->GetAwardtype();
				echo("<tr><td>".$buggyAward->year."</td><td>$awardType->description</td></tr>");
			}
		?>		
		</table>
	</div>
</div>
