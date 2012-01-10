<?php
	$member = new member();
	$memberList = $member->GetList(null,"lastname");
	$list09 = $member->GetList(array(array("mem2009","=","1")));
	$list10 = $member->GetList(array(array("mem2010","=","1")));
	$list11 = $member->GetList(array(array("mem2011","=","1")));
	$list12 = $member->GetList(array(array("mem2012","=","1")));
?>

<div class="pane">
	<h2>Manage Membership Records</h2>
	<table class="data">
	<tr><th>Member</th><th>Grad<br />Year</th><th>2009</th><th>2010</th><th>2011</th><th>2012</th></tr>
	<tr><th>Total Members</th><th></th><th><?php echo(count($list09)); ?></th><th><?php echo(count($list10)); ?></th><th><?php echo(count($list11)); ?></th><th><?php echo(count($list12)); ?></th></tr>
	<?php
		foreach($memberList as $member){
			$icon = "<img src=\"/img/icon_buggy.gif\" />";	
			$mem2009 = "";
			$mem2010 = "";
			$mem2011 = "";
			$mem2012 = "";
			if($member->mem2009){$mem2009 = $icon;}
			if($member->mem2010){$mem2010 = $icon;}
			if($member->mem2011){$mem2011 = $icon;}			
			if($member->mem2012){$mem2012 = $icon;}
			echo("<tr><td>".$member->firstname." ".$member->lastname."</td>");
			
			echo("<td>".$member->gradyear."</td>");
			echo("<td>".$mem2009."</td>");
			echo("<td>".$mem2010."</td>");
			echo("<td>".$mem2011."</td>");
			echo("<td>".$mem2012."</td></tr>");
		}
	?>		
	</table>
</div>