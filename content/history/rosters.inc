<?php
	$year = $_GET['year'] * 1;
	$racedayId = $year."1";
	$team = new team();
	$teamListM = $team->GetList(array(array("racedayId", "=", $racedayId),array("raceclassId", "=", "1")),"orgId");
	$teamListW = $team->GetList(array(array("racedayId", "=", $racedayId),array("raceclassId", "=", "2")),"orgId");
	
	function displayTeam($team){
		if($team != null){ 
			$buggy = $team->GetBuggy();
			$org = $team->GetOrg();
			echo("<tr>");
			echo("<td><a href=\"/histor/org/".$org->urlKey."\">".$org->shortName."</a> ".$team->abcd."</td>");
			if($buggy->name != null){
				echo("<td><a href=\"/history/buggy/".$buggy->urlKey."\">" . $buggy->name . "</a></td>");
			}
			
			$teamByRole = array();
			foreach ($team->GetPersontoteamList() as $personToTeam){
				$person = $personToTeam->GetPerson();
				$teamRole = $personToTeam->GetTeamrole();
				$teamByRole[$teamRole->description] = $person;
			}
				echo("<td><a href=\"/history/person/".$teamByRole["Driver"]->personId."\">".$teamByRole["Driver"]->firstName." ".$teamByRole["Driver"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 1"]->personId."\">".$teamByRole["Hill 1"]->firstName." ".$teamByRole["Hill 1"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 2"]->personId."\">".$teamByRole["Hill 2"]->firstName." ".$teamByRole["Hill 2"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 3"]->personId."\">".$teamByRole["Hill 3"]->firstName." ".$teamByRole["Hill 3"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 4"]->personId."\">".$teamByRole["Hill 4"]->firstName." ".$teamByRole["Hill 4"]->lastName."</a></td>");
				echo("<td><a href=\"/history/person/".$teamByRole["Hill 5"]->personId."\">".$teamByRole["Hill 5"]->firstName." ".$teamByRole["Hill 5"]->lastName."</a></td>");
			
			echo("</tr>");
		}
	}	
	
?>

<div class="box">
	<div class="title">Women's Teams <?php echo($year); ?></div>
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
			foreach ($teamListW as $team){
				displayTeam($team);
			}
		?>
	</table>
</div>
<div class="box">
	<div class="title">Men's Teams <?php echo($year); ?></div>
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
			foreach ($teamListM as $team){
				displayTeam($team);
			}
		?>
	</table>
</div>