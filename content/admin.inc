<div id="topnav">
	<ul class="sf-menu">
		<li><a href="/admin">Admin Home</a></li>
		<li><a href="/admin/changelog">Change Log</a></li>
	</ul>
</div>
<?php
	if (isset($uservars["adminlevel"])){
		if($uservars["adminlevel"] > 0){
			$p = null;
			if(isset($_GET["p"])) {
				$p = $_GET["p"];
			}
			if(empty($p)){
				include_once("content/admin/default.inc");
			}else { 
				include_once("admin/".$p.".inc");
			}
		} else {
			include_once("admin/noaccess.inc");	
		}
	} else {
		include_once("admin/noaccess.inc");		
	}
?>