<h3>Upcoming Freerolls</h3>
<?php
	$freeroll = new freeroll();
	$upcomingrolls = $freeroll->GetList(array(array("date", ">=", date('Y-m-d'))),"date");
	$remainingrolls = $freeroll->GetList(array(array("date", ">=", date('Y-m-d')),array("status","=","Rolling")),"date");
	if(count($upcomingrolls)>0){
		for($i=0;$i<2;$i++){
			$displaytime = "- -";
			if($upcomingrolls[$i]->firstroll > 0){
				$displaytime = date('g:i a',strtotime($upcomingrolls[$i]->firstroll));
				if($displaytime == "12:00 pm") { $displaytime = "- -"; }
			}
			$displaystatus = "<span style=\"color:green;\">Rolling</span>";
			if($upcomingrolls[$i]->status != "Rolling"){
				$displaystatus = "<span style=\"color:red;\">".$upcomingrolls[$i]->status."</span>";
			}
			echo("<b>".date('l, F d',strtotime($upcomingrolls[$i]->date))."</b><br />");
			echo("First roll : ".$displaytime."<br />");
			echo("Status : ".$displaystatus."<br />");
		}
		echo(count($remainingrolls)." potential days remaining");
	} else {
		echo("Freerolls are over for the semester.");	
	}
?>
