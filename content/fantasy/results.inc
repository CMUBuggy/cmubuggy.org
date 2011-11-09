<?php
	$fe = new fantasyentry();
	$feList = $fe->GetList(null,"timestamp",FALSE);
?>


<h3>Results</h3>
Congrats to Jake Mohin who won our first ever Fantasy Buggy game, and to Numberfire.com for sponsoring the grand prize.<br />
<br />
The full results are below.  Don't forget to check the 4 tabs at the bottom for more details, or follow this <a target="_blank" href="https://docs.google.com/spreadsheet/ccc?key=0AuJqrzitvsWSdEsxWkczcUF3Y0VNcGNPM2NRSmpJUnc">Google Docs direct link for easier viewing or download.</a>
<iframe width='750' height='1000' frameborder='0' src='https://docs.google.com/spreadsheet/pub?hl=en_US&hl=en_US&key=0AuJqrzitvsWSdEsxWkczcUF3Y0VNcGNPM2NRSmpJUnc&output=html&widget=true'></iframe>


<!--
So far there have been <?php echo(count($feList)); ?> entries.<br />
<br />
The content of the picks will be revealed once rolls start on Sunday.<br />
All picks and their owners will be revealed once rolls are over and the scores have been calculated.<br />

<?php if (time() > mktime(07,30, 0, 11, 06, 2011)){ ?>

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
<?php } ?>
-->