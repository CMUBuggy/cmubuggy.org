<div id="topnav">
	<ul class="sf-menu">
		<li><a href="/admin">Admin Home</a></li>
	</ul>
</div>
<?php
	$p = $_GET["p"];
	if(empty($p)){
		include_once("content/admin/default.inc");
	}else { 
		include_once("admin/".$p.".inc");
	}
?>