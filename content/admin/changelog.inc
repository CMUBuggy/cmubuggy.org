<?php
	$dataedit = new dataedit();
	$editList = $dataedit->GetList(null,"timestamp",FALSE);
?>

<div class="pane">
<table class="editable" summary="" >
	<tr>
		<th>Type</th>
		<th>Object</th>
		<th>Attribute</th>
		<th>ID</th>
		<th>Old<br />Value</th>
		<th>New<br />Value</th>
		<th style="width:115px;">Time</th>
		<th>User</th>	
	</tr>
<?php
foreach($editList as $edit){
	$user = $edit->GetUser();
	echo("<tr>");
	echo("<td>".$edit->edittype."</td>");
	echo("<td>".$edit->objtype."</td>");
	echo("<td>".$edit->objattr."</td>");
	echo("<td>".$edit->objid."</td>");
	echo("<td>".$edit->oldvalue."</td>");
	echo("<td>".$edit->newvalue."</td>");
	echo("<td>".strftime("%m/%d/%y %X",$edit->timestamp)."</td>");
	echo("<td>".$user->username."</td>");
 	echo("</tr>");
}
?>	
</table>

</div>