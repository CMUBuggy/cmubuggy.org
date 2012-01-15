<script type="text/javascript">

$(document).ready(function(){
	$("input.memberyear").change(function(){
			var newval = 0;
			if($(this).is(':checked')){
				newval = 1;	
			}
			$.post("/data.php", { type: "update", element_id: $(this).attr("id"), update_value: newval },
			   function(data) {
			     //alert("success");
			   });
		});
	$(".eip").editInPlace({
		default_text: "- - - -",
		params:"type=update",
		url: "/data.php",
		success:function(enteredText){
			$(this).html(enteredText);
			//alert ("success");
		}
	})
	
	$("#InitAddMember").click(function(){
		$("#addmember").slideToggle();
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

<div class="pane admin">
	<h2>Manage Membership Records</h2>
	<input type="button" class="button" value="Add a Member" id="InitAddMember"  />		
	<div id="message"></div>
	<div id="addmember" class="hidden">
	<form action="" method="">
		<fieldset>
			<legend></legend>
			<label for="firstname">First Name</label>
			<input type="text" name="firstname" />
			<label for="lastname">Last Name</label>
			<input type="text" name="lastname" />
			<label for="email">E-mail</label>
			<input type="email" name="email" />
			<label for="gradyear">Graduation Year<div class="detail">(YYYY)</div></label>
			<input type="text" name="gradyear" size="5" />
		</fieldset>
		<input type="button" class="button" value="Add Member" style="margin:10px 0 0 190px" />		
	</form>	
	</div>
	<div id="memberlist">
		<h3>Current and Past Members</h3>
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
				echo("<td><div class=\"eip\" id=\"member-".$member->memberId."-gradyear\">".$member->gradyear."</div></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2009\" class=\"memberyear\"".$mem2009." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2010\" class=\"memberyear\"".$mem2010." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2011\" class=\"memberyear\"".$mem2011." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2012\" class=\"memberyear\"".$mem2012." /></td></tr>");
			}
		?>		
		</table>	
	</div>
</div>