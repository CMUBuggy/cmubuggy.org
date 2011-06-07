<?php
include("../lib/pog/pog_includes.inc");
include("../dbconfig.inc");
include("../util.inc");

$file = fopen("heats2011.csv", "r");
$racedayid = 1335;

//0 = racedayid
//1 = raceclassid
//2 = heat number
//3 = lane1
//4 = lane2
//5 = lane3


while (($data = fgetcsv($file, 8000, ";")) !== FALSE) {
	$heat = new heat();
	$heat->number = $data[2];
	$heat->racedayId = $data[0];
	$heat->raceclassId = $data[1];
	$heat->Save();
	
	for($i=3;$i<6;$i++){
		$entry = new entry();
		$entryList = $entry->GetList(array(array("urlkey","=",$data[3])));
		if($entryList){
			$entry = $entryList[0];
			$teamList = $entry->GetTeamList(array(array("racedayId","=",$racedayid)));
			if($teamList){
				$team = $teamList[0];
				$team->heat = $data[2];
				$team->lane = $i-2;
				$team->Save();
			}
		}
	}
}

fclose ($file);

?>