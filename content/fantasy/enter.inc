<?php
	if(isset($_POST["entrysubmit"])){
		$fantasyentry = new fantasyentry();
		$fantasyentry->email = $_POST["email"];
		$fantasyentry->username = $_POST["username"];
		$fantasyentry->name = $_POST["name"];
		$fantasyentry->freeroll1 = $_POST["fr1buggy"]."-".$_POST["fr1roll"];
		$fantasyentry->freeroll2 = $_POST["fr2buggy"]."-".$_POST["fr2roll"];
		$fantasyentry->freeroll3 = $_POST["fr3buggy"]."-".$_POST["fr3roll"];
		$fantasyentry->freeroll4 = $_POST["fr4buggy"]."-".$_POST["fr4roll"];
		$fantasyentry->backhills1 = $_POST["bh1buggy"]."-".$_POST["bh1roll"];
		$fantasyentry->backhills2 = $_POST["bh2buggy"]."-".$_POST["bh2roll"];
		$fantasyentry->backhills3 = $_POST["bh3buggy"]."-".$_POST["bh3roll"];
		$fantasyentry->backhills4 = $_POST["bh4buggy"]."-".$_POST["bh4roll"];
		$fantasyentry->tiebreaker = $_POST["tiebreaker"];
		$fantasyentry->timestamp = time();
		$fantasyentry->ip = $_SERVER['REMOTE_ADDR'];
		$fantasyentry->key = uniqid();

		$fantasyentry->Save();
		$fe = $fantasyentry;

		include('Mail.php');
		include('Mail/mime.php');
		$to = $fe->email;
		$subject = "Fantasy Buggy entry confirmation";
		$message = "Thanks for playing the very first Fantasy Buggy!  Good luck with your picks, hopefully you'll be the lucky winner of a \"ticket to carnival\" ($250) sponsored by numberFire (http://numberfire.com)\n\n";
		$message .= "Your entry was:\n";
		$message .= "Name: ".$fe->name." (username:".$fe->username.")\n";
		$message .= "Freeroll Pick #1 : ".$_POST["fr1org"]."-".$fe->freeroll1."\n";
		$message .= "Freeroll Pick #2 : ".$_POST["fr2org"]."-".$fe->freeroll2."\n";
		$message .= "Freeroll Pick #3 : ".$_POST["fr3org"]."-".$fe->freeroll3."\n";
		$message .= "Freeroll Pick #4 : ".$_POST["fr4org"]."-".$fe->freeroll4."\n";
		$message .= "Backhills Pick #1 : ".$_POST["bh1org"]."-".$fe->backhills1."\n";
		$message .= "Backhills Pick #2 : ".$_POST["bh2org"]."-".$fe->backhills2."\n";
		$message .= "Backhills Pick #3 : ".$_POST["bh3org"]."-".$fe->backhills3."\n";
		$message .= "Backhills Pick #4 : ".$_POST["bh4org"]."-".$fe->backhills4."\n";
		$message .= "Tiebreaker : ".$fe->tiebreaker."\n";
		$message .= "Entry ID : ".$fe->key."\n\n";
		$message .= "Good Luck!";
		$from = "Buggy Alumni Association <admin@cmubuggy.org>";
		$headers = "From:" . $from;
		if (mail($to,$subject,$message,$headers) ) {

		} else {
	   	echo "email could not be sent";
		}

?>


	<h3>Entry Submitted</h3>
	Good luck!  Your entry has been submitted.<br /><br />Here is a summary of your picks (which has also been e-mailed to you for your records):<br />
	<br />
	<table summary="" class="data">
		<tr><td>Who are you?</td><td><?php echo($fe->email." / ".$fe->name." / ".$fe->username);  ?></td></tr>
		<tr><td>Freeroll Pick #1</td><td><?php echo($_POST["fr1org"]."-".$fe->freeroll1); ?></td></tr>
		<tr><td>Freeroll Pick #2</td><td><?php echo($_POST["fr2org"]."-".$fe->freeroll2); ?></td></tr>
		<tr><td>Freeroll Pick #3</td><td><?php echo($_POST["fr3org"]."-".$fe->freeroll3); ?></td></tr>
		<tr><td>Freeroll Pick #4</td><td><?php echo($_POST["fr4org"]."-".$fe->freeroll4); ?></td></tr>
		<tr><td>Backhills Pick #1</td><td><?php echo($_POST["bh1org"]."-".$fe->backhills1); ?></td></tr>
		<tr><td>Backhills Pick #2</td><td><?php echo($_POST["bh2org"]."-".$fe->backhills2); ?></td></tr>
		<tr><td>Backhills Pick #3</td><td><?php echo($_POST["bh3org"]."-".$fe->backhills3); ?></td></tr>
		<tr><td>Backhills Pick #4</td><td><?php echo($_POST["bh4org"]."-".$fe->backhills4); ?></td></tr>
		<tr><td>Tiebreaker</td><td><?php echo($fe->tiebreaker); ?></td></tr>
		<tr><td>EntryID</td><td><?php echo($fe->key); ?></td></tr>
	</table>
	<br />
	If you haven't become a member yet, now is an excellent time to do it.<br />
	<br />
	<div class="button"><a href="/membership">Step 1. Become a Member</a></div>
<?php
	} else {
?>

	<h3>Submit an Entry</h3>
	<form action="/fantasy/enter" method="post" id="entryform">
		<h4>Who are you?</h4>
		<table width="700px;">
			<tr>
				<td>
					<label for="email">Email (required)</label><br />
					<span class="detail">(to contact the winner)</span><br />
					<input type="text" name="email" value="" id="email" size="35">
				</td>
				<td>
					<label for="name">Real Name (required)</label><br />
					<span class="detail">(the check will be written to this name)</span><br />
					<input type="text" name="name" value="" id="name" size="35">
				</td>
				<td>
					<label for="username">cmubuggy.org Username</label><br />
					<span class="detail">(optional, but good for bragging rights)</span><br />
					<input type="text" name="username" value="" id="username" size="35">
				</td>
			</tr>
		</table>
		<br />
		<a href="" onclick="$('#rulesreminder').slideToggle(); return false;">Need a reminder on the basic rules?</a><br />
		<div id="rulesreminder" style="display:none;">
			<h4>Basics</h4>
			<ul class="list">
				<li>Pick 4 freerolls and 4 back hills</li>
				<li>Each pick specifies Org-Roll-Buggy-Segment  (e.g. SigEp-Roll2-Barracuda-Freeroll)</li>
				<li>Must make 1 and only 1 pick from each org</li>
				<li>1 entry per person</li>
			</ul>
			<h4>Scoring</h4>
			<ul class="list">
				<li>Score = total of 4 freeroll times + 4 back hill times</li>
				<li>Segments that don't happen (the buggy isn't out or doesn't roll the specified roll) are given that org's worst time +1 second</li>
				<li>Spins or stops are given the overall worst time + 2 seconds</li>
				<li>Women's freerolls are given their time - 3 seconds</li>
				<li>Women's backhills are given their time - 6 seconds</li>
				<li>Tie-breaker: closest guess on winning men's hill 2->finish time</li>
			</ul>
		</div>
		<br />
		<table summary="" >
			<tr>
				<td></td>
				<td colspan="3" style="text-align:center; font-size:1.3em; font-weight:bold;" width="275px">Freeroll Picks</td>
				<td colspan="3" style="text-align:center; font-size:1.3em; font-weight:bold;" width="325px">Backhills Picks</td>
			</tr>
			<tr>
				<td style="font-size:2.8em; vertical-align:center; padding:5px; font-weight:bold;">1</td>
				<td>
					<label for="fr1org">Org</label><br />
					<select name="fr1org" id="fr1org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="fr1buggy">Buggy</label><br />
					<select name="fr1buggy" id="fr1buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="fr1roll">Roll #</label><br />
					<select name="fr1roll" id="fr1roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
				<td style="padding-left:50px;">
					<label for="bh1org">Org</label><br />
					<select name="bh1org" id="bh1org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="bh1buggy">Buggy</label><br />
					<select name="bh1buggy" id="bh1buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="bh1roll">Roll #</label><br />
					<select name="bh1roll" id="bh1roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
			</tr>
			<tr>
				<td style="font-size:2.8em; vertical-align:center; padding:5px; font-weight:bold;">2</td>
				<td>
					<label for="fr2org">Org</label><br />
					<select name="fr2org" id="fr2org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="fr2buggy">Buggy</label><br />
					<select name="fr2buggy" id="fr2buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="fr2roll">Roll #</label><br />
					<select name="fr2roll" id="fr2roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
				<td style="padding-left:50px;">
					<label for="bh2org">Org</label><br />
					<select name="bh2org" id="bh2org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
				</td>
				<td>
					<label for="bh2buggy">Buggy</label><br />
					<select name="bh2buggy" id="bh2buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="bh2roll">Roll #</label><br />
					<select name="bh2roll" id="bh2roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
			</tr>
			<tr>
				<td style="font-size:2.8em; vertical-align:center; padding:5px; font-weight:bold;">3</td>
				<td>
					<label for="fr3org">Org</label><br />
					<select name="fr3org" id="fr3org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="fr3buggy">Buggy</label><br />
					<select name="fr3buggy" id="fr3buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="fr3roll">Roll #</label><br />
					<select name="fr3roll" id="fr3roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
				<td style="padding-left:50px;">
					<label for="bh3org">Org</label><br />
					<select name="bh3org" id="bh3org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="bh3buggy">Buggy</label><br />
					<select name="bh3buggy" id="bh3buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="bh3roll">Roll #</label><br />
					<select name="bh3roll" id="bh3roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
			</tr>
			<tr>
				<td style="font-size:2.8em; vertical-align:center; padding:5px; font-weight:bold;">4</td>
				<td>
					<label for="fr4org">Org</label><br />
					<select name="fr4org" id="fr4org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="fr4buggy">Buggy</label><br />
					<select name="fr4buggy" id="fr4buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="fr4roll">Roll #</label><br />
					<select name="fr4roll" id="fr4roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
				<td style="padding-left:50px;">
					<label for="bh4org">Org</label><br />
					<select name="bh4org" id="bh4org" class="orgselect">
						<option value="null"></option>
						<option value="AEPi">AEPi</option>
						<option value="CIA">CIA</option>
						<option value="Fringe">Fringe</option>
						<option value="KapSig">KapSig</option>
						<option value="SDC">SDC</option>
						<option value="SigEp">SigEp</option>
						<option value="Spirit">Spirit</option>
						<option value="SN/DF">SN / DeltaForce</option>
					</select>
				</td>
				<td>
					<label for="bh4buggy">Buggy</label><br />
					<select name="bh4buggy" id="bh4buggy" style="width:95px;" disabled="disabled"><option value="null"></option></select>
				</td>
				<td>
					<label for="bh4roll">Roll #</label><br />
					<select name="bh4roll" id="bh4roll">
						<option value="1">1</option>
						<option value="2">2</option>
						<option value="3">3</option>
					</select>
				</td>
			</tr>
		</table>
		<h4>In case of a tie</h4>
		<label for="tiebreaker">Make your best guess of the fastest time of the day from the end of hill 2 to the finish line<br /></label>
		<input type="text" name="tiebreaker" value="" id="tiebreaker" size="6"> <span class="detail">(mm:ss)</span><br />
		<br />
		<div id="errors" style="color:red"></div>
		<input type="hidden" name="entrysubmit" value="true">
		<input id="" name="" type="button" value="Submit Entry" class="button" onclick="validate()">
	</form>
</div>

<script type="text/javascript" >
	var orgs = new Array();
	orgs["AEPi"] 	= new Array("Kamikaze");
	orgs["CIA"] 	= new Array("Quasar","Firebird","Renaissance","Freyja","Ascension");
	orgs["Fringe"] = new Array("Blizzard","Banyan","Bedlam","Borealis","Bonsai");
	orgs["KapSig"]	= new Array("Apache");
	orgs["SDC"] 	= new Array("Rage","Malice","Avarice","Bane");
	orgs["SigEp"]	= new Array("Pandora","Barracuda","Mamba");
	orgs["Spirit"] = new Array("Haraka","Fuko","Seraph","Mapambazuko");
	orgs["SN/DF"] 	= new Array("SN/DF");

	$(".orgselect").change(function() {
		var value = this.value;
		var options = "";
		var targid = this.id.replace("org","buggy");

		if(value == "null"){
			$("#"+targid).attr("disabled","disabled");
			$("#"+targid).html("");
		}else{
			for (i=0; i<orgs[value].length; i++){
				var bname = orgs[value][i];
				options += "<option value='"+bname+"'>"+bname+"</option>";
			}
			$("#"+targid).attr("disabled","");
			$("#"+targid).html(options);
		}
	});

	function validate(){
		var error = "";
		$("#errors").empty();

		//check for valid email
		var email = $("#email").val();
		if(email==""){
			error += "Please enter an email<br />";
		} else {
			var atpos=email.indexOf("@");
			var dotpos=email.lastIndexOf(".");
			if (atpos<1 || dotpos<atpos+2 || dotpos+2>=email.length)
	  		{
	  			error+= "Please enter a valid email address<br />";
	  		}
	  	}

	  	//check for real name
	  	if($("#name").val()==""){
	  		error += "Please enter your real name<br />";
	  	}

	  	//check for duplicate orgs
		var orgs = [$("#fr1org").val(),$("#fr2org").val(),$("#fr3org").val(),$("#fr4org").val(),$("#bh1org").val(),$("#bh2org").val(),$("#bh3org").val(),$("#bh4org").val()];
		var orgs = orgs.sort();
		var duporgs = [];
		for (var i = 0; i < orgs.length - 1; i++){
			if(orgs[i+1] == orgs[i]){
				duporgs.push(orgs[i]);
			}
		}
		if(duporgs.length>0) { var count = duporgs.length+1;  error+= "Each pick must be from a different org. You've used the same org "+count+" times. <br />"; }

		if(error != "") {
			$("#errors").append(error);
		} else {
			$("#entryform").submit();
		}
	}
</script>

<?php
}
?>
