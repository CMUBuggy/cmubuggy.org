<?php
	$racedayId = 20102;
	if($_GET["rdid"]!=null){
		
	}

	$team = new team();
	$teamTimeListM = $team->GetList(array(array("racedayId", "=", $racedayId),array("time", ">", "0"),array("raceclassId", "=", "1")),"time");
	$teamTimeListW = $team->GetList(array(array("racedayId", "=", $racedayId),array("time", ">", "0"),array("raceclassId", "=", "2")),"time");	
	$teamNoTimeListM = $team->GetList(array(array("racedayId", "=", $racedayId),array("time", "=", "NULL"),array("raceclassId", "=", "1")),"heat");
	$teamNoTimeListW = $team->GetList(array(array("racedayId", "=", $racedayId),array("time", "=", "NULL"),array("raceclassId", "=", "2")),"heat");	
?>

<div class="box whitebox">
	<div class="title">Leaderboard : Finals 2010</div>
	<table class="topalign data">
		<tr>
			<th style="width:150px;">Women's</th><th style="width:150px;">Men's</th>
		</tr>
		<tr>
			<td>
			<?php
				$Wplace = 1;
				foreach ($teamTimeListW as $team)
				{
					$org = $team->GetOrg();
					$raceClass = $team->GetRaceclass();
					$url = "./?p=team&year=2010&org=".$org->shortName."&rc=".substr($raceClass->description,0,1)."&abcd=".$team->abcd;
					echo($Wplace." - ".displayTime($team->time)." - <a href=\"".$url."\">".$org->shortName." ".$team->abcd."</a>");
				   echo("<br />");
				   $Wplace++;
				}
			?>		
			</td>		
			<td>
			<?php
				$Mplace = 1;
				foreach ($teamTimeListM as $team)
				{
					$org = $team->GetOrg();
					$raceClass = $team->GetRaceclass();
					$url = "./?p=team&year=2010&org=".$org->shortName."&rc=".substr($raceClass->description,0,1)."&abcd=".$team->abcd;
					echo($Mplace." - ".displayTime($team->time)." - <a href=\"".$url."\">".$org->shortName." ".$team->abcd."</a>");
				   echo("<br />");
				   $Mplace++;
				}
			?>			
			</td>
		</tr>
	</table>
</div>
<!-- <div class="box">
	<div class="title">Rerolls</div>
	System not set up for rerolls, results will be displayed here manually, but not integrated in the DB.<br />
	<ul><li>Spirit Women's B : spin in the chute</li>
	<li>Fringe D - 2:23.20</li>
	<li>PikA A - 2:09.31</li>
	</ul>
</div> -->
<div class="box">
	<div class="title">Still to Race</div>
	<table class="topalign">
		<tr>
			<th style="width:150px;">Women's</th><th style="width:150px;">Men's</th>		
		</tr>
		<tr>
			<td>
			<?php
				foreach ($teamNoTimeListW as $team)
				{
					$org = $team->GetOrg();
					$raceClass = $team->GetRaceclass();
					$url = "./?p=team&year=2010&org=".$org->shortName."&rc=".substr($raceClass->description,0,1)."&abcd=".$team->abcd;  //id=".$team->teamId;
					echo("heat ".$team->heat." - <a href=\"".$url."\">".$org->shortName." ".$team->abcd."</a>");
				   echo("<br />");
				}
			?>		
			</td>		
			<td>
			<?php
				foreach ($teamNoTimeListM as $team)
				{
					$org = $team->GetOrg();
					$raceClass = $team->GetRaceclass();
					$url = "./?p=team&year=2010&org=".$org->shortName."&rc=".substr($raceClass->description,0,1)."&abcd=".$team->abcd;  //id=".$team->teamId;
					echo("heat ".$team->heat." - <a href=\"".$url."\">".$org->shortName." ".$team->abcd."</a>");
				   echo("<br />");
				}
			?>			
			</td>
		</tr>
	</table>
</div>
