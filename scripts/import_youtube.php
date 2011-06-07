youtube data importer:<br /><br />
<?php
include("../lib/pog/pog_includes.inc");
include("../dbconfig.inc");
include("../util.inc");

$row = 1;
$file = fopen("youtube-data.csv", "r");

//0 = year
//1 = day
//2 = raceclass
//3 = heat
//4 = lane 1
//5 = lane 2
//6 = lane 3
//7 = youtubeId
//8 = notes

while (($data = fgetcsv($file, 8000, ";")) !== FALSE) {
	echo("------------------------<br />");
	echo($data[0].":".$data[1].":".$data[2]."--".$data[4]."--".$data[5]."--".$data[6]."<br/>");
   $num = count($data);
   $row++;
	
	$video = new video();
	$video->title = $data[0]." ".$data[1]." ".$data[2].$data[3].": ".$data[4].", ".$data[5].", ".$data[6];
	$video->youtubeID = $data[7];   
	$video->Save();   

	$isfinals = 0;
	if($data[1] == "Finals"){ $isfinals =1; }
	$isreroll = 0;
	$raceclassid = 1;
	if($data[2]=="W"){ $raceclassid = 2; }
	if($data[2]=="Ex") {$raceclassid = 3; }
	if($data[2]=="MRR") {$raceclassid = 1; $isreroll = 1; }
	if($data[2]=="WRR") {$raceclassid = 2; $isreroll = 1; }
	$raceclass = new raceclass();
	$raceclass = $raceclass->Get($raceclassid);
   
	$raceyear = new raceyear();
	$raceday = new raceday();
	$heat = new heat();
	
	$raceyear->Get($data[0]);	
	$racedaylist = $raceyear->GetRacedayList(array(array("isFinals","=",$isfinals)));
	echo("rd count: ". count($racedaylist)."<br />");	
	if($racedaylist){
		$raceday = $racedaylist[0];
		$heatlist = $raceday->GetHeatList(array(array("raceclassid","=",$raceclassid),array("number","=",$data[3]),array("isreroll","=",$isreroll)));
		echo("heat count: ".count($heatlist)."<br />");
		if($heatlist){
			$heat = $heatlist[0];
		} else {
			$heat->number = $data[3];
			$heat->isreroll = $isreroll;
			$heat->SetRaceday($raceday);
			$heat->SetRaceclass($raceclass);
			$heat->Save();
		}
	} else {
		echo("raceday ".$raceyear->year.": ".$isfinals." not found. skipping<br />");	
	}
   
  	$video->SetHeat($heat);
   $video->Save();
  	
  	if($raceclassid<3){
		for($c=4; $c<7; $c++){
			$teamstr = $data[$c];
			if($teamstr){
				$orgname = substr($teamstr,0,strrpos($teamstr," "));
				$abcd = substr($teamstr,strrpos($teamstr," ")+1,1);

				$org = new org();
				$orglist = $org->GetList(array(array("shortname","=",$orgname)));
				if($orglist){
					$org = $orglist[0];
					$entry = new entry();
					$entrylist = $org->GetEntryList(array(array("raceyearid","=",$raceyear->raceyearId),array("raceclassid","=",$raceclassid),array("abcd","=",$abcd)));
					if($entrylist){
						//echo(count($entrylist)." entries found<br />");
						$entry = $entrylist[0];
						$team = new team();
						$teamlist = $entry->GetTeamList(array(array("racedayid","=",$raceday->racedayId)));
						if($teamlist){
							//echo(count($teamlist)." teams found<br />");
							$team = $teamlist[0];
							$team->SetHeat($heat);
						} else {
							echo("teams for entry:".$entry->entryId." and rd:".$raceday->racedayId." not found ... creating<br />");
							$team->SetEntry($entry);
							$team->SetRaceclass($raceclass);
							$team->SetHeat($heat);
							$team->SetRaceday($raceday);
						}
						$team->lane = $c-3;
						$team->isReroll = $isreroll;
						$team->Save();	
						echo($team->GetEntry()->GetOrg()->shortname." ".$abcd." -- ");
					}else{
						echo("entry not found ... creating<br />");
						$entry->SetRaceyear($raceyear);
						$entry->SetOrg($org);
						$entry->SetRaceclass($raceclass);
						$entry->abcd = $abcd;
					}
					$entry->Save();
				} else {
					echo("org:".$orgname." not found<br />");	
				}
			}
		}
		echo("<br />");
	}	  	 	
   //echo($video->title."<br />");
}

fclose($file);
?>