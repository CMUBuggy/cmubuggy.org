<?php
	 $miscvar = new miscvar();
	 $miscvarList = $miscvar->GetList(); 
?>

<script type="text/javascript" >

	function dispmsg(valence, msg){
		$("#message").addClass(valence).html(msg).fadeIn().delay(800).fadeOut();
	}

	$(document).ready(function(){
	
	//Edit MiscVar
		$(".eip").editInPlace({
			default_text: "- - - -",
			params:"type=update",
			url: "/data.php",
			success:function(enteredText){
				$(this).html(enteredText);
				dispmsg("good", "Value updated.");
			}
		})
})
		
</script>

<div class="pane">
	<div id="message" class="msg hidden floatright"></div>
	<h2>Misc. Settings</h2>


		<table class="editable">
		<tr>
			<th>Setting</th>
			<th>Value</th>
		</tr>
		<?php
			foreach($miscvarList as $miscvar){
				echo("<tr><td>".$miscvar->key."</td>");
				echo("<td><div class=\"eip\"id=\"miscvar-".$miscvar->miscvarId."-value\">".$miscvar->value."</div></td></tr>");
			}
		?>		
		</table>	
</div>