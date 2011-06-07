DB Rearranger:<br /><br />
<?php
include("pog/pog_includes.inc");
include("dbconfig.inc");
include("util.inc");

/*
//Raceyear setup
for($y=1920;$y<2012;$y++) {
	$raceyear = new raceyear();
	$raceyear->raceyearId = $y;
	$raceyear->year = $y;
	$raceyear->Save();
	echo($raceyear->year);
}
*/

//Team import/convert
$oldteamsql = "SELECT * FROM oldteam WHERE 1";	$raceday = new raceday();
$oldteams = dbQuery("cmubuggy_dev", $oldteamsql);

while($row = mysql_fetch_array($oldteams)){
	$team = new team();	
	echo($row["teamid"]."<br />");
	
	$team->lane 	 		= $row["lane"];
	$team->isReroll 		= $row["isreroll"];
	$team->time 			= $row["time"];
	$team->broadcastnote = $row["broadcastnote"];

	$raceclass = new raceclass();
	$raceclass = $raceclass->Get($row["raceclassid"]);
	$team->SetRaceclass($raceclass);

	if($row["buggyid"]>0){
		$buggy = new buggy();
		$buggy = $buggy->Get($row["buggyid"]);
		$team->SetBuggy($buggy);
	}	
	
	if($row["dqid"]>0){
		$dq = new dq();
		$dq = $dq->Get($row["dqid"]);
		$team->SetDq($dq);
	}
	
	$team->Save();

	if($row["racedayid"]>0){
		$racedayid = $row["racedayid"];
		$year = substr($racedayid, 0, 4);
		$day = substr($racedayid, 4, 1);
	}
	
	$raceyear = new raceyear();
	$raceyear->Get($year);
	
	$raceday = new raceday();
	if($day==2){
		$isfinals = 1;
	}else{
		$isfinals = 0;	
	}
	
	
	$racedaylist = $raceday->GetList(array(array("raceyearid","=",$raceyear->year),array("isfinals","=",$isfinals)));
	if(count($racedaylist)>0){
		$raceday = $racedaylist[0];	
	}else {
		$raceday->SetRaceyear($raceyear);
		$raceday->isFinals = $isfinals;
	}
	$raceday->Save();
	$team->SetRaceday($raceday);
	$team->Save();

	if($row["heat"]>0){
		$heat = new heat();
		$heatnumber = $row["heat"];
		$heatlist = $heat->GetList(array(array("racedayId","=",$raceday->racedayId),array("raceclassId","=",$raceclass->raceclassId),array("number","=",$heatnumber)));
		if(count($heatlist)>0){
			$heat = $heatlist[0];	
		} else {
			$heat->SetRaceday($raceday);
			$heat->SetRaceclass($raceclass);
			$heat->number = $heatnumber;
		}
		$heat->Save();
		$team->SetHeat($heat);
	}
		
	$entry = new entry();
	$abcd = $row["abcd"];
	$notes = $row["notes"];
	$compubookieplace = $row["compubookieplace"];
	$place = $row["place"];
	$org = new org();
	$org = $org->Get($row["orgid"]);
	$entrylist = $entry->GetList(array(array("raceyearId","=",$year),array("orgId","=",$org->orgId),array("raceclassId","=",$raceclass->raceclassId),array("abcd","=",$abcd)));
	if(count($entrylist)>0){
		$entry = $entrylist[0];
		if($place>0 && $day==2 && $row["dqid"]==0){
			$entry->place = $place;	
		}
	} else {
		$entry->SetRaceyear($raceyear);
		$entry->SetOrg($org);
		$entry->SetRaceclass($raceclass);
		$entry->abcd = $abcd;
		if($place>0){
			$entry->place = $place;	
		}	
	}
	if($compubookieplace>0) {
		$entry->compubookieplace = $compubookieplace;
	}
	$entry->Save();
	$team->SetEntry($entry);
	
	$team->Save();
	
	$oldteamId = $row["teamid"];
	$ptt = new persontoteam();
	$pttlist = $ptt->GetList(array(array("teamid","=",$oldteamId)));
	foreach($pttlist as $ptt){
		$ptt->SetTeam($team);
		$ptt->Save();	
	}
}

?>