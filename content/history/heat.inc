<?php

	$rdid = $_GET["rdid"];
	$raceclass = $_GET["raceclass"];
	$heat = $_GET["heat"];
	$year = substr($rdid, 0, 4);
	
	if(substr($rdid,-1,1)=="1") { $rdtype = "Prelims"; }
	if(substr($rdid,-1,1)=="2") { $rdtype = "Finals"; }
	if($raceclass=="m"){ $raceclassid = 1; $raceclassdisp = "Men's";}
	if($raceclass=="w"){ $raceclassid = 2; $raceclassdisp = "Women's";}

	$con = mysql_connect($dbhost, $dbuser, $dbpass);
	if (!$con) { die('Could not connect: ' . mysql_error());}
	mysql_select_db($dbname, $con);

	$sql="SELECT team.teamId, team.lane
			FROM team 
			WHERE racedayid = ".$rdid."
			AND raceclassid = ".$raceclassid."
			AND heat = ".$heat."
			ORDER BY lane";
	//echo($sql);
	
	$teamsList = mysql_query($sql);
	
	$teamsArr = array();
	
	while($row = mysql_fetch_array($teamsList)){
		$team = new team();
		//print_r($row);
		$lane = $row["lane"];
		$teamid = $row["teamId"];
		$teamsArr[$lane] = $team->Get($teamid);
	}
	$dispArr = array();	
	for($i=1;$i<4;$i++){
		if($teamsArr[$i] != null){
			$team = $teamsArr[$i];
			
			$org = $team->GetOrg();
			$reroll = "";
			if($team->isReroll == 1){ $reroll = "(Reroll)"; }
			$dispArr[$i]["teamlabel"] = "<a href=\"/histor/org/".$org->urlKey."\">".$org->shortName."</a> ".$team->abcd." ".$reroll."</td>";
			
			$pic = "";
			$buggy = $team->GetBuggy();
			if(file_exists("/var/www/cmubuggy.org/img/buggy/thumb_250/".$org->urlKey."-".$buggy->urlKey)){
				$pic="<img src=\"/img/buggy/thumb_250/".$org->shortName."-".$buggy->urlKey."\" />";
			} else {
				$pic="";
			}
			$dispArr[$i]["buggypic"] = "<a href=\"/history/buggy/".$buggy->urlKey."\">".$pic."</a>";
			$dispArr[$i]["buggylabel"] = "<a href=\"/history/buggy/".$buggy->urlKey."\">". $buggy->name . "</a> (".$buggy->yearBuilt.")";	
			
			foreach ($team->GetPersontoteamList() as $personToTeam){
				$person = $personToTeam->GetPerson();
				$teamRole = $personToTeam->GetTeamrole();
				$teamByRole[$teamRole->description] = $person;
			}
			
			$dispArr[$i]["driver"] = "<a href=\"/history/person/".$teamByRole["Driver"]->personId."\">".$teamByRole["Driver"]->firstName." ".$teamByRole["Driver"]->lastName."</a>";
			$dispArr[$i]["h1"] = "<a href=\"/history/person/".$teamByRole["Hill 1"]->personId."\">".$teamByRole["Hill 1"]->firstName." ".$teamByRole["Hill 1"]->lastName."</a>";
			$dispArr[$i]["h2"] = "<a href=\"/history/person/".$teamByRole["Hill 2"]->personId."\">".$teamByRole["Hill 2"]->firstName." ".$teamByRole["Hill 2"]->lastName."</a>";
			$dispArr[$i]["h3"] = "<a href=\"/history/person/".$teamByRole["Hill 3"]->personId."\">".$teamByRole["Hill 3"]->firstName." ".$teamByRole["Hill 3"]->lastName."</a>";
			$dispArr[$i]["h4"] = "<a href=\"/history/person/".$teamByRole["Hill 4"]->personId."\">".$teamByRole["Hill 4"]->firstName." ".$teamByRole["Hill 4"]->lastName."</a>";
			$dispArr[$i]["h5"] = "<a href=\"/history/person/".$teamByRole["Hill 5"]->personId."\">".$teamByRole["Hill 5"]->firstName." ".$teamByRole["Hill 5"]->lastName."</a>";
			
			$teamObj = new team();
			$courserecteam = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=",$raceclassid), array("abcd","=",$team->abcd), array(" and dqid is NULL")),"time", true, 1);
			if(count($courserecteam)>0){
				$courserecOrg = $courserecteam[0]->GetOrg();
				$courserecRD = $courserecteam[0]->GetRaceday();
				$dispArr[$i]["courseRec"] = displayTime($courserecteam[0]->time)." ".$courserecOrg->shortName." ".$team->abcd." (".$courserecRD->year." <span style=\"font-size:9px;\">".$courserecRD->day."</span>)";
			}

			$teamrecteam = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=",$raceclassid), array("abcd","=",$team->abcd), array("orgid","=",$org->orgId),array(" and dqid is NULL")),"time", true, 1);
			if(count($teamrecteam)>0){
				$teamrecRD = $teamrecteam[0]->GetRaceday();
			}
			$dispArr[$i]["teamRec"] = displayTime($teamrecteam[0]->time)." ".$org->shortName." ".$team->abcd." (".$teamrecRD->year." <span style=\"font-size:9px;\">".$teamrecRD->day."</span>)";
			
			$lastyearrdid = $year-1 . substr($rdid,-1,1);
			$lastyearteam = $teamObj->GetList(array(array("raceclassid","=",$raceclassid), array("abcd","=",$team->abcd), array("orgid","=",$org->orgId), array("racedayid","=",$lastyearrdid)),"time", true, 1);
			if(count($lastyearteam)>0){
				$lastyearplace = "";
				if($lastyearteam[0]->place > 0){
					$lastyearplace = " [ ".$lastyearteam[0]->place." ]";
				}
				$dispArr[$i]["lastyeartime"] = displayTime($lastyearteam[0]->time).$lastyearplace;
			} else {
				$dispArr[$i]["lastyeartime"] = "--";
			}
			
			if($team->time > 0){			
				$dispArr[$i]["time"] = displayTime($team->time);
			}
			if($_SESSION['admin']==TRUE){
					$dispArr[$i]["time"] = "<div class=\"eip\" id=\"time-".$team->teamId."\">".displayTime($team->time)."</div>";
			}
			
			$dispArr[$i]["broadcastnote"] = "<div class=\"eipTextArea\" id=\"broadcastnote-".$team->teamId."\">".stripslashes(nl2br($team->broadcastnote))."</div>";
		}
	}
	$team = new team();
	$nextheat = $heat + 1;
	$nextheatteams = count($team->GetList(array(array("raceclassid","=",$raceclassid), array("heat","=",$nextheat), array("racedayid","=",$rdid))));
	if($nextheatteams > 0){
		$nextheatdisp = "<a href=\"/history/heat/".$rdid."/".$raceclass."/".$nextheat."\">Next Heat ></a>";
	} elseif($raceclass=="w") {
		$nextheatdisp = "<a href=\"/history/heat/".$rdid."/m/1\">Men's Heats ></a>";
	} else {
		$nextheatdisp = "no more heats";
	}
	
	$prevheat = $heat - 1;
	$lastWheatlist= $team->GetList(array(array("raceclassid","=","2"), array("racedayid","=",$rdid)),"heat",false,1);
	$lastWheat = $lastWheatlist[0]->heat;
	if($heat > 1){
		$prevheatdisp = "<a href=\"/history/heat/".$rdid."/".$raceclass."/".$prevheat."\">< Previous Heat</a>";	
	} elseif($raceclass=="m") {
		$prevheatdisp = "<a href=\"/history/heat/".$rdid."/w/".$lastWheat."\">< Women's Heats</a>";
	} else {
		$prevheatdisp = "first heat";
	}
	
	

?>

<div class="box whitebox">
	<div class="title">
		<div class="rightDetail">
			<?php echo($prevheatdisp); ?> | <?php echo($nextheatdisp); ?>
		</div>
		<?php echo($year." ".$rdtype.": ".$raceclassdisp." Heat ".$heat); ?>
	</div>
	<table class="data">
		<tr>
			<th></th>
			<th style="width:250px;">Lane 1</th>
			<th style="width:250px;">Lane 2</th>
			<th style="width:250px;">Lane 3</th>
		</tr>
		<tr>
			<td></td>
			<td><h3><?php echo($dispArr[1]["teamlabel"]); ?></h3></td>
			<td><h3><?php echo($dispArr[2]["teamlabel"]); ?></h3></td>
			<td><h3><?php echo($dispArr[3]["teamlabel"]); ?></h3></td>		
		</tr>
		<tr>
			<td></td>
			<td style="vertical-align: baseline;" ><?php echo($dispArr[1]["buggypic"]); ?></td>
			<td style="vertical-align: baseline;"><?php echo($dispArr[2]["buggypic"]); ?></td>
			<td style="vertical-align: baseline;"><?php echo($dispArr[3]["buggypic"]); ?></td>	
		</tr>
		<tr>
			<td></td>
			<td><?php echo($dispArr[1]["buggylabel"]); ?></td>
			<td><?php echo($dispArr[2]["buggylabel"]); ?></td>
			<td><?php echo($dispArr[3]["buggylabel"]); ?></td>	
		</tr>
		<tr>
			<td>Driver</td>
			<td><?php echo($dispArr[1]["driver"]); ?></td>
			<td><?php echo($dispArr[2]["driver"]); ?></td>
			<td><?php echo($dispArr[3]["driver"]); ?></td>	
		</tr>
		<tr>
			<td>Hill 1</td>
			<td><?php echo($dispArr[1]["h1"]); ?></td>
			<td><?php echo($dispArr[2]["h1"]); ?></td>
			<td><?php echo($dispArr[3]["h1"]); ?></td>	
		</tr>
		<tr>
			<td>Hill 2</td>
			<td><?php echo($dispArr[1]["h2"]); ?></td>
			<td><?php echo($dispArr[2]["h2"]); ?></td>
			<td><?php echo($dispArr[3]["h2"]); ?></td>	
		</tr>
		<tr>
			<td>Hill 3</td>
			<td><?php echo($dispArr[1]["h3"]); ?></td>
			<td><?php echo($dispArr[2]["h3"]); ?></td>
			<td><?php echo($dispArr[3]["h3"]); ?></td>	
		</tr>
		<tr>
			<td>Hill 4</td>
			<td><?php echo($dispArr[1]["h4"]); ?></td>
			<td><?php echo($dispArr[2]["h4"]); ?></td>
			<td><?php echo($dispArr[3]["h4"]); ?></td>	
		</tr>
		<tr>
			<td>Hill 5</td>
			<td><?php echo($dispArr[1]["h5"]); ?></td>
			<td><?php echo($dispArr[2]["h5"]); ?></td>
			<td><?php echo($dispArr[3]["h5"]); ?></td>	
		</tr>
		<tr>
			<td><h3>Time</h3></td>
			<td><h3><?php echo($dispArr[1]["time"]); ?></h3></td>
			<td><h3><?php echo($dispArr[2]["time"]); ?></h3></td>
			<td><h3><?php echo($dispArr[3]["time"]); ?></h3></td>	
		</tr>
		<tr>
			<td><?php $lastyear = $year-1; echo($rdtype." ".$lastyear); ?></td>
			<td><?php echo($dispArr[1]["lastyeartime"]); ?></td>
			<td><?php echo($dispArr[2]["lastyeartime"]); ?></td>
			<td><?php echo($dispArr[3]["lastyeartime"]); ?></td>	
		</tr>
		<tr>
			<td>Team Record</td>
			<td><?php echo($dispArr[1]["teamRec"]); ?></td>
			<td><?php echo($dispArr[2]["teamRec"]); ?></td>
			<td><?php echo($dispArr[3]["teamRec"]); ?></td>	
		</tr>		
		<tr>
			<td>Course Record</td>
			<td><?php echo($dispArr[1]["courseRec"]); ?></td>
			<td><?php echo($dispArr[2]["courseRec"]); ?></td>
			<td><?php echo($dispArr[3]["courseRec"]); ?></td>	
		</tr>
		<?php if($_SESSION['admin']==TRUE || $_SESSION['broadcaster']==TRUE){ ?>
		<tr>
			<td>Broadcast notes</td>
			<td><?php echo($dispArr[1]["broadcastnote"]); ?></td>
			<td><?php echo($dispArr[2]["broadcastnote"]); ?></td>
			<td><?php echo($dispArr[3]["broadcastnote"]); ?></td>	
		</tr>
		<?php		
		}
		?>
	</table>
</div>