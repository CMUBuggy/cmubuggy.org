<?php
	 $miscvar = new miscvar();
	 $miscvarList = $miscvar->GetList(); 
	 

?>





<div class="pane">
	<h2>Misc. Settings</h2>


		<table class="editable">
		<tr>
			<th>Setting</th>
			<th>Value</th>
		</tr>
		<?php
			foreach($miscvarList as $miscvar){
				echo("<tr><td>".$miscvar->key."</td>");
				echo("<td><div class=\"eip\"id=\"miscvar-".$miscvar->miscvarId."-email\">".$miscvar->value."</div></td></tr>");
			}
		?>		
		</table>	



</div>