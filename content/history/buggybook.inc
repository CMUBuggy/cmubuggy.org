<div class="pane">
	<div class="title">Buggy Books</div>
<?php
	for($year=1965;$year<2014;$year++){
		echo("<a href=\"/files/buggybooks/buggybook_".$year.".pdf\"  
					target=\"_blank\" onclick=\"_gaq.push(['_trackEvent','Download','PDF',this.href]);\">
				<img alt=\"".$year." buggy book\" 
					  title=\"Download a PDF of the ".$year." buggy book\" 
					  style=\"margin:10px; border:1px solid white;\" 
					  src=\"/files/buggybooks/thumb_200/buggybook_".$year.".pdf.jpg\" />
				</a>");
	}
?>

</div>