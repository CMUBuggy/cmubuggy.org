<script type="text/javascript">

function dispmsg(valence, msg){
	$("#message").addClass(valence).html(msg).fadeIn().delay(800).fadeOut();
}

$(document).ready(function(){
	//Edit membership years
	$("input.memberyear").change(function(){
			var newval = 0;
			if($(this).is(':checked')){
				newval = 1;	
			}
			$.post("/data.php", { type: "update", element_id: $(this).attr("id"), update_value: newval },
			   function(data) {
			     dispmsg("good", "Membership status updated");
			   });
		});
		
	//Edit GradYear
	$(".eip").editInPlace({
		default_text: "- - - -",
		params:"type=update",
		url: "/data.php",
		success:function(enteredText){
			$(this).html(enteredText);
			dispmsg("good", "Graduation year updated");
		}
	})
	
	//Add Member
	$("#InitAddMember").click(function(){
		$("#addmember").slideToggle();
	});
	
	$("#AddMemberSubmit").click(function(){
		var data = $("#addmember input").serializeArray();
		$.post("/data.php", data, function(data){
			$("#addmember input:text").val("");
			$("#addmember input:checkbox").removeAttr('checked');
			dispmsg("good", "Member added");
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
	$list13 = $member->GetList(array(array("mem2013","=","1")));
	$list14 = $member->GetList(array(array("mem2014","=","1")));
?>

<div class="pane">
	<div id="message" class="msg hidden floatright"></div>
	<h2>Manage Membership Records</h2>
	<input type="button" class="button" value="Add a Member?" id="InitAddMember"  />		
	<div id="addmember" class="hidden">
	<form action="" method="">
		<fieldset>
			<legend></legend>
			<label for="firstname">First Name</label>
			<input type="text" class="val" name="firstname" />
			<label for="lastname">Last Name</label>
			<input type="text" class="val" name="lastname" />
			<label for="email">E-mail</label>
			<input type="text" class="val" name="email" />
			<label for="gradyear">Graduation Year<div class="detail">(YYYY)</div></label>
			<input type="text" class="val" name="gradyear" size="5" />
			<!-- TODO: Generalize to current (race) year -->
			<label for="mem2013">Mebership 2014</label>
			<input type="checkbox" class="val" name="mem2014" value="1">
			<input type="hidden" name="type" value="add" />
			<input type="hidden" name="objtype" value="member" />
		</fieldset>
		<input type="button" class="button" value="Add Member" id="AddMemberSubmit" style="margin:10px 0 0 190px" />		
	</form>	
	</div>
	<br />
	<div id="memberlist">
		<h3>Current and Past Members</h3>
		<table class="editable">
		<tr>
			<th>Member</th>
			<th>Email</th>
			<th style="width:60px">Grad<br />Year</th>
			<th style="width:50px;">2009</th>
			<th style="width:50px;">2010</th>
			<th style="width:50px;">2011</th>
			<th style="width:50px;">2012</th>
			<th style="width:50px;">2013</th>
			<th style="width:50px;">2014</th>
		</tr>
		<tr><th>Total Members</th><th></th><th></th><th><?php echo(count($list09)); ?></th><th><?php echo(count($list10)); ?></th><th><?php echo(count($list11)); ?></th><th><?php echo(count($list12)); ?></th><th><?php echo(count($list13)); ?></th><th><?php echo(count($list14)); ?></th></tr>		<?php
			foreach($memberList as $member){
				$mem2009 = "";
				$mem2010 = "";
				$mem2011 = "";
				$mem2012 = "";
				$mem2013 = "";
				$mem2014 = "";
				if($member->mem2009){$mem2009 = "checked=\"checked\"";}
				if($member->mem2010){$mem2010 = "checked=\"checked\"";}
				if($member->mem2011){$mem2011 = "checked=\"checked\"";}			
				if($member->mem2012){$mem2012 = "checked=\"checked\"";}
				if($member->mem2013){$mem2013 = "checked=\"checked\"";}
				if($member->mem2014){$mem2014 = "checked=\"checked\"";}
				echo("<tr><td>".$member->firstname." ".$member->lastname."</td>");
				echo("<td><div class=\"eip\"id=\"member-".$member->memberId."-email\">".$member->email."</div></td>");
				echo("<td><div class=\"eip\" id=\"member-".$member->memberId."-gradyear\">".$member->gradyear."</div></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2009\" class=\"memberyear\"".$mem2009." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2010\" class=\"memberyear\"".$mem2010." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2011\" class=\"memberyear\"".$mem2011." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2012\" class=\"memberyear\"".$mem2012." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2013\" class=\"memberyear\"".$mem2013." /></td>");
				echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2014\" class=\"memberyear\"".$mem2014." /></td></tr>");
			}
		?>		
		</table>	
	</div>
</div>