<?php
	$buggy = new buggy();
	$buggyList = $buggy->GetList(null,"yearBuilt",FALSE);
?>
<div class="pane">
	<h2>Buggies</h2>
	<table class="data">
		<tr><th>Year Built</th><th>Organization</th><th>Name</th></tr>
		<?php
		foreach($buggyList as $buggy){
			$year = $buggy->yearBuilt;
			if(!($year > 0)){
				$year = "";
			}
			echo("<tr><td>".$year."</td><td>".$buggy->GetOrg()->shortname."</td><td><a href=\"/history/buggy/".$buggy->urlKey."\">".$buggy->name."</a></td></tr>");
		}
		?>
	</table>
</div>
