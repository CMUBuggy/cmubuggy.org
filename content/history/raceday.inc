<?php
	$year = $_GET['year'] * 1;
	$prevlink = "";
	$nextlink = "";

	if($year > 1920) {
		$prevlink = "<a href=\"/history/raceday/".($year - 1)."\">&laquo ".($year - 1)."</a>";
	}
	if($year < date("Y")){
		$nextlink = " | <a href=\"/history/raceday/".($year + 1)."\">".($year + 1)." &raquo</a>";
	}

	$mentriesArr = array();
	$wentriesArr = array();
	$pheatsArr = array();
	$fheatsArr = array();
	$raceyear = new raceyear();
	$raceyear = $raceyear->Get($year);
	$racedayList = $raceyear->GetRacedayList();
	foreach($racedayList as $raceday){
		$tempArr = array();
		$heatlist = $raceday->GetHeatList(null,"number");
		foreach($heatlist as $heat){
			$heattype = (string)$heat->raceclassId.(string)$heat->isreroll;
			$tempArr[$heattype][$heat->number]=$heat;
		}
		if($raceday->isFinals == 1){
			$fheatsArr=$tempArr;
		} else {
			$pheatsArr=$tempArr;
		}
	}
	$entryList = $raceyear->GetEntryList(null,"place");
	$noplacecounter = 100;
	foreach($entryList as $entry){
		$place = $entry->place;
		if(!($place>0)){
			$place = $noplacecounter;
			$noplacecounter++;
		}
		switch($entry->raceclassId) {
			case 1:
				$mentriesArr[$place] = $entry;
				break;
			case 2:
				$wentriesArr[$place] = $entry;
				break;
		}
	}

	function displayEntries($entryArr) {
		global $racedayList;
		ksort($entryArr);
		echo("<table class=\"data\">");
		if(count($racedayList)>1){
			echo("<tr><th>Place</th><th>Team</th><th>Prelims Time</th><th>Finals Time</th><th>Notes</th></tr>");
		} else {
			echo("<tr><th>Place</th><th>Team</th><th>Time</th><th>DQ / Notes</th></tr>");
		}
		foreach($entryArr as $entry){
			$entrylabel = $entry->GetOrg()->shortname." ".$entry->abcd;
			$teamList = $entry->GetTeamList();
			$teamArr = array();
			$notes = "";
			foreach($teamList as $team){
				$raceday = $team->GetRaceday();
				$teamArr[$raceday->isFinals] = $team;
				if($team->GetDq()->dqId>0){
					$notes .= "DQ: ".$team->GetDQ()->description;
				}
			}

			$place = "";
			if($entry->place>0){$place = $entry->place; }

			$url = "/history/team/".$entry->urlkey;
		   echo("<tr><td>".$place."</td>");
		   echo("<td><a href=\"".$url."\">".$entrylabel."</a></td>");
		   if(isset($teamArr[0])){
		   	echo("<td>".displayTime($teamArr[0]->time)."</td>");
		   }
		   if(count($racedayList)>1){
		   	if(isset($teamArr[1])){
		   		echo("<td>".displayTime($teamArr[1]->time)."</td>");
		   	} else {
		   		echo("<td></td>");
		   	}
		   }
		   echo("<td>".$notes."</td></tr>");
		}
		echo("</table>");
	}

	function displayHeats($heatArr){
		ksort($heatArr);
		$heattypes = array("30","20","21","10","11");
		$heattypelabels = array("10"=>"Men's",
										"11"=>"Men's Rerolls",
										"20"=>"Women's",
										"21"=>"Women's Rerolls",
										"30"=>"Exhibitions");
		foreach($heattypes as $type){
			if(isset($heatArr[$type])){
				echo("<h4>".$heattypelabels[$type]."</h4>");
				echo("<table class=\"data\"><tr><th></th><th></th><th style=\"width:100px\">Lane 1</th><th style=\"width:100px\">Lane 2</th><th>Lane 3</th style=\"width:100px\"><th>Notes</th>");
				foreach($heatArr[$type] as $heat){
					echo("<tr><td>".$heat->number."</td><td>");
					$videolist = $heat->GetVideoList();
					$video = null;
					if($videolist){ $video = reset($videolist); }
					include("content/youtubevid.inc");
					echo("</td>");
					$teamsArr = array();
					foreach($heat->GetTeamList() as $team){
						$teamsArr[$team->lane]=$team;
					}
					for($l=1;$l<4;$l++){
						if(isset($teamsArr[$l])){
							$team = $teamsArr[$l];
							$entry = $team->GetEntry();
							echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$entry->GetOrg()->shortname." ".$entry->abcd."</a><br />".displayTime($team->time)."</td>");
						} else {
							echo("<td></td>");
						}
					}
					echo("<td></td></tr>");
				}
				echo("</table>");
			}
		}
	}

	?>
	<div class="pane">
		<?php
			if(file_exists("/var/www/cmubuggy.org/files/buggybooks/buggybook_".$year.".pdf")){
				echo("<a class=\"floatright\" href=\"/files/buggybooks/buggybook_".$year.".pdf\"><img alt=\"".$year." buggy book\" height=\"100px\" title=\"Download a PDF of the ".$year." buggy book\" src=\"/files/buggybooks/thumb_100/buggybook_".$year.".jpg\" /></a>");
			}
		?>
		<h2>Raceday <?php echo($year);?></h2>
		<?php echo($prevlink.$nextlink); ?>
	</div>
	<ul class="tabs">
		<li><a id="t1" href="#mens">Men's Results</a></li>
		<li><a id="t2" href="#womens">Women's Results</a></li>
		<?php if(count($pheatsArr)>0){echo("<li><a id=\"t3\" href=\"#prelimheats\">Prelim Heats</a></li>");}?>
		<?php if(count($fheatsArr)>0){echo("<li><a id=\"t4\" href=\"#finalsheats\">Finals Heats</a></li>");}?>
	</ul>

	<div class="panes">
		<div class="pane">
			<?php displayEntries($mentriesArr); ?>
		</div>
		<div class="pane">
			<?php displayEntries($wentriesArr); ?>
		</div>
		<div class="pane">
			<?php displayHeats($pheatsArr); ?>
		</div>
		<div class="pane">
			<?php displayHeats($fheatsArr); ?>
		</div>
	</div>


	<?php
	/*
	} else {
		echo("<div class=\"pane\"><h3>Raceday ".$year."?</h3>".$prevlink.$nextlink."<br />I don't think that has happened yet.</div>");
	}
	*/
?>
