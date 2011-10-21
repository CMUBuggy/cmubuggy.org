<?php
	$fe = new fantasyentry();
	$feList = $fe->GetList(null,"timestamp",FALSE);
?>


<h3>Results</h3>
So far there have been <?php echo(count($feList)); ?> entries.<br />
<br />
The content of the picks will be revealed once rolls start on Saturday.<br />
All picks and their owners will be revealed once rolls are over and the scores have been calculated.<br />

<!--
<table class="data" style="font-size:.85em">
	<tr>
		<td></td>
		<th colspan="4">Freeroll Picks</th>
		<th colspan="4">Backhills Picks</th>
		<td></td>
	</tr>
	<tr>
		<th>Entry ID</th>
		<th>1</th><th>2</th><th>3</th><th>4</th>
		<th>1</th><th>2</th><th>3</th><th>4</th>
		<th>Tiebreaker</th>
	</tr>
	<?php
	foreach($feList as $fe){
		echo("<tr>
				<td>".$fe->key."</td>
				<td>".$fe->freeroll1."</td>
				<td>".$fe->freeroll2."</td>
				<td>".$fe->freeroll3."</td>
				<td>".$fe->freeroll4."</td>
				<td>".$fe->backhills1."</td>
				<td>".$fe->backhills2."</td>
				<td>".$fe->backhills3."</td>
				<td>".$fe->backhills4."</td>
				<td>".$fe->tiebreaker."</td>
				</tr>");	
	}		
	?>		
</table>
-->
