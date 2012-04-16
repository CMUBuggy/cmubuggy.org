<?php
	$year = "2012";
	$raceyear = new raceyear();
	$raceyear = $raceyear->Get($year);

	$Mentrylist = $raceyear->GetEntryList(array(array("raceclassId","=","1")));
	$Wentrylist = $raceyear->GetEntryList(array(array("raceclassId","=","2")));
	

	function displayTeam($team){
		if($team != null){ 
			$buggy = $team->GetBuggy();
			$entry = $team->GetEntry();
			$org = $entry->GetOrg();
			echo("<tr>");
			echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$org->shortname." ".$entry->abcd."</a></td>");
			echo("<td>");
			if($buggy->name != null){
				echo("<a href=\"/history/buggy/".$buggy->urlKey."\">" . $buggy->name . "</a>");
			}
			echo("</td>");
			
			$teamByRole = array();
			foreach ($team->GetPersontoteamList() as $personToTeam){
				$person = $personToTeam->GetPerson();
				$teamRole = $personToTeam->GetTeamrole();
				$teamByRole[$teamRole->description] = $person;
			}
				echo("<td><a href=\"/history/person/".$teamByRole["Driver"]->personId."\">".substr($teamByRole["Driver"]->firstName,0,1).". ".$teamByRole["Driver"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 1"]->personId."\">".substr($teamByRole["Hill 1"]->firstName,0,1).". ".$teamByRole["Hill 1"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 2"]->personId."\">".substr($teamByRole["Hill 2"]->firstName,0,1).". ".$teamByRole["Hill 2"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 3"]->personId."\">".substr($teamByRole["Hill 3"]->firstName,0,1).". ".$teamByRole["Hill 3"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 4"]->personId."\">".substr($teamByRole["Hill 4"]->firstName,0,1).". ".$teamByRole["Hill 4"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 5"]->personId."\">".substr($teamByRole["Hill 5"]->firstName,0,1).". ".$teamByRole["Hill 5"]->lastName."</a></td>");
			
			echo("</tr>");
		}
	}	
	
?>
<ul class="tabs">
	<li><a id="t1" href="#women">Women's Teams</a></li>
	<li><a id="t2" href="#men">Men's Teams</a></li>
</ul>
<div class="panes">
<div class="pane">
	<h3>Women's Teams <?php echo($year); ?></h3>
	<table class="data">
		<tr>
			<th>Team</th>
			<th>Buggy</th>
			<th>Driver</th>
			<th>Hill 1</th>
			<th>Hill 2</th>
			<th>Hill 3</th>
			<th>Hill 4</th>
			<th>Hill 5</th>
		</tr>
		<?php 
			foreach ($Wentrylist as $entry){
				$teamlist = $entry->GetTeamList(array(array("racedayId","=","1335")));
				if($teamlist){
					displayTeam($teamlist[0]);
				}
			}
		?>
	</table>
</div>
<div class="pane">
	<h3>Men's Teams <?php echo($year); ?></h3>
	<table class="data">
		<tr>
			<th>Team</th>
			<th>Buggy</th>
			<th>Driver</th>
			<th>Hill 1</th>
			<th>Hill 2</th>
			<th>Hill 3</th>
			<th>Hill 4</th>
			<th>Hill 5</th>
		</tr>
		<?php 
			foreach ($Mentrylist as $entry){
				$teamlist = $entry->GetTeamList(array(array("racedayId","=","1335")));
				if($teamlist){
					displayTeam($teamlist[0]);
				}
			}
		?>
	</table>
</div>
</div>