<?php
include("../lib/pog/pog_includes.inc");
include("../dbconfig.inc");
include("../util.inc");

$file = fopen("teams2011.csv", "r");

//0 = entryurlkey
//1 = racedayid
//2 = buggy
//3 = driver
//4 = hill1
//5 = hill2
//6 = hill3
//7 = hill4
//8 = hill5


while (($data = fgetcsv($file, 8000, ";")) !== FALSE) {
	$entry = new entry();
	$entrylist = $entry->GetList(array(array("urlkey","=",$data[0])));
	if($entrylist){
		$entry = $entrylist[0];
		
		$team = new team();
		$team->SetEntry($entry);
		$team->racedayId = $data[1];
		
		$buggy = new buggy();
		$buggyList = $buggy->GetList(array(array("name","=",$data[2])),"yearbuilt");
		if($buggyList){
			$buggy = $buggyList[0];
			$team->SetBuggy($buggy);	
		}
		
		for($i=3; $i<=8; $i++){
			if($data[$i]!= NULL){
				$name = explode(' ',trim($data[$i],2));
				$person = new person();
				$personList = $person->GetList(array(array("firstName","=",$name[0]),array("lastName","=",$name[1])));
				if(count($personList)>0){
					$person = $personList[0];
				} else {
					$person->firstName = $name[0];
					$person->lastName = $name[1];
					$person->Save();
				}
				if($data[4]=="Men's"){ $person->gender = 1; }
				if($data[4]=="Women's") {$person->gender = 2; }
				$person->Save();
				
				switch($i){
					case 3:
						$roledesc = "Driver";
						break;
					case 4:
						$roledesc = "Hill 1";
						break;
					case 5:
						$roledesc = "Hill 2";
						break;
					case 6:
						$roledesc = "Hill 3";
						break;
					case 7:
						$roledesc = "Hill 4";
						break;
					case 8:
						$roledesc = "Hill 5";
						break;																				
				}
				
				$teamRole = new teamRole();
				$teamRoleList = $teamRole->GetList(array(array("description","=",$roledesc)));
				$teamRole = $teamRoleList[0];
				
				$personToTeam = new personToTeam();
				$personToTeam->SetPerson($person);
				$personToTeam->SetTeamrole($teamRole);
				$personToTeam->Save();
				$team->AddPersontoteam($personToTeam);
				
				$role = new role();
				if($roledesc == "Driver"){
					$roleList = $role->GetList(array(array("description","=","Driver")));
				} else {
					$roleList = $role->GetList(array(array("description","=","Pusher")));			
					$role = $roleList[0];
				}
			}
		}
		$team->Save(true);
		echo("saved ".$data[0]."<br />");
	}
}

fclose ($file);

?>