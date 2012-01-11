<script type="text/javascript">

$(document).ready(function(){
	$("input.memberyear").change(function(){
			var newval = 0;
			if($(this).is(':checked')){
				newval = 1;	
			}
			
			$.post("/data.php", { type: "admin", id: $(this).attr("id"), newval:  newval },
			   function(data) {
			     alert("success");
			   });
		});
})

</script>

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
			$mem2009 = "";
			$mem2010 = "";
			$mem2011 = "";
			$mem2012 = "";
			if($member->mem2009){$mem2009 = "checked=\"checked\"";}
			if($member->mem2010){$mem2010 = "checked=\"checked\"";}
			if($member->mem2011){$mem2011 = "checked=\"checked\"";}			
			if($member->mem2012){$mem2012 = "checked=\"checked\"";}
			echo("<tr><td>".$member->firstname." ".$member->lastname."</td>");
			
			echo("<td>".$member->gradyear."</td>");
			echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2009\" class=\"memberyear\"".$mem2009." /></td>");
			echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2010\" class=\"memberyear\"".$mem2010." /></td>");
			echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2011\" class=\"memberyear\"".$mem2011." /></td>");
			echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2012\" class=\"memberyear\"".$mem2012." /></td></tr>");
		}
	?>		
	</table>
</div>