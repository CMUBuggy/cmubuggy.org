<?php
	$dataedit = new dataedit();
	$editList = $dataedit->GetList(null,"timestamp",FALSE);
?>

<div class="pane">
<table class="data" summary="" >
	<tr>
		<th>Type</th>
		<th>Object</th>
		<th>ID</th>
		<th>Old Value</th>
		<th>New Value</th>
		<th>Time</th>
		<th>User</th>	
	</tr>
<?php
foreach($editList as $edit){
	$user = $edit->GetUser();
	echo("<tr>");
	echo("<td>".$edit->edittype."</td>");
	echo("<td>".$edit->objtype."</td>");
	echo("<td>".$edit->objid."</td>");
	echo("<td>".$edit->oldvalue."</td>");
	echo("<td>".$edit->newvalue."</td>");
	echo("<td>".$edit->timestamp."</td>");
	echo("<td>".$user->username."</td>");
 	echo("</tr>");
}
?>	
</table>

</div>