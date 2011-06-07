<?php

$racedayid = 1335;
$raceday = new raceday();
$raceday->Get($racedayid);
$MheatList = $raceday->GetHeatList(array(array("raceclassId","=",1)),"number");
$WheatList = $raceday->GetHeatList(array(array("raceclassId","=",2)),"number");

?>

<ul class="tabs">
	<li><a id="t1" href="#women">Women's Heats</a></li>
	<li><a id="t2" href="#men">Men's Heats</a></li>
</ul>
<div class="panes">
	<div class="pane">
		<table class="data">
			<tr>
				<th>Heat</th>
				<th>Lane 1</th>
				<th>Lane 2</th>
				<th>Lane 3</th>
			</tr>
			<?php 
				foreach ($WheatList as $heat){
					echo("<tr><td>".$heat->number."</td>");
					echo("<td></td>");
					echo("<td></td>");
					echo("<td></td></tr>");
				}
			?>
		</table>
	</div>
	<div class="pane">
		<table class="data">
			<tr>
				<th>Heat</th>
				<th>Lane 1</th>
				<th>Lane 2</th>
				<th>Lane 3</th>
			</tr>
			<?php 
				foreach ($MheatList as $heat){
					echo("<tr><td>".$heat->heatId."</td></tr>");
				}
			?>
		</table>
	</div>
</div>