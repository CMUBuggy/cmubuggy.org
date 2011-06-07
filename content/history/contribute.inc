<?php	
	if(!empty($_POST["submit"])){
		$newdata = new newdata();
		$newdata->timeSubmitted = time();
		$newdata->data = $_POST["data"];
		$newdata->title = $_POST["title"];
		$newdata->processed = 0;
		$newdata->submitter = $_POST["name"];
		$newdata->email = $_POST["email"];
		$newdata->source = $_POST["source"];
		$newdata->Save();
		
		$to = "data@cmubuggy.org";
		$subject = "Data Contribution: ".$_POST["title"];
		$message = "Submitter: ".$_POST["name"];
		$message .= "\nEmail: ". $_POST["email"];
		$message .= "\n\nData: \n".$_POST["data"];
		$message .= "\n\nSource: ".$_POST["source"];
		$from = "admin@cmubuggy.org";
		$headers = "From: $from";
		mail($to,$subject,$message,$headers);
	}
?>

<div class="box whitebox">
	Please use one of the forms below to submit addition or corrections to the data we've got.  It's just fine to submit multiple related pieces of information at once (e.g. the build dates of all your org's buggies).  If you have a large quantity of data, or if you find it easier, you can also e-mail information to <a href="mailto:data@cmubuggy.org">data@cmubuggy.org</a>
</div>	
<div class="box">
	In an effort to make it faster for us to import new data, we have added a couple of standardized forms for specific types of data:
	<ul>
		<li><b><a href="https://spreadsheets.google.com/viewform?hl=en&formkey=cHJrT3JoWXZvNDRlVFJTSjlCZWE4ZXc6MA..">Raceday Data</a></b> - pushers, drivers, buggies and their times and places</li>	
		<li><b><a href="https://spreadsheets.google.com/viewform?hl=en&formkey=cHJrT3JoWXZvNDRlOElXNjRoVllOT2c6MA..">Organization Data</a></b> - mechanics, chairmen, sweepstakes and other non-pushing, non-driving participants</li>	
		<li><b><a href="https://spreadsheets.google.com/viewform?hl=en&formkey=cHJrT3JoWXZvNDRkLTZHc1RTcGE0TkE6MA..">Buggy Data</a></b> - buggies and their years, pictures, awards</li>
		<li>For contributions that don't fit cleanly in those forms, submit what you have right here:</li>
	</ul>
	<form method="post" action="./?p=Contribute" />
	<table>
		<tr>
			<td>Your Name</td>
			<td><input type="text" name="name" /></td>
			<td></td>
			<td></td>
		</tr>
		<tr>
			<td>Your email</td>
			<td><input type="text" name="email" /></td>
			<td>It won't be public, but please include it so we may contact you to clarify if necessary</td>
			<td></td>
		</tr>
		<tr>
			<td>Description</td>
			<td><input type="text" name="title" /></td>
			<td>e.g Org Y's 2001 men's push teams
		</tr>
		<tr>
			<td>The data</td>
			<td colspan="2"><textarea name="data" id="data" rows="15" style="width:450px;"></textarea></td>
		</tr>
		<tr>
			<td>Your source</td>
			<td><input type="text" name="source"></td>
			<td>Were you there? From an old buggy book? Include a link if that makes sense
		</tr>
		<tr>
			<td></td>
			<td><input type="submit" name="submit" value="Submit"></td>
		</tr>			
	</table>
	</form>
</div>
<div class="box">
	<div class="title">Recent Contributions</div>
	Apologies to those contributions that aren't imported yet.  We are very glad to have your data, and it will be imported asap.  The only reason they are imported out of order is that some data is easier than others to import.
	<table class="data">
		<tr>
			<th>Description</th>
			<th>Submitted by</th>
			<th>Submitted on</th>
			<th>Status</th>
		</tr>
	<?php
		$newdata = new newdata();
		$newdataList = $newdata->GetList(array(array("newdataId", ">", "0")),"timeSubmitted", false, "50");
		foreach ($newdataList as $newdata)
		{
			$status = "";
			switch ($newdata->processed) {
				case 0 : $status = "Pending Approval";
					break;
				case 1 : $status = "Awaiting import. Thanks!";
					break;
				case 2 : $status = "Imported";
					break;
				case -1 : $status = "not approved :(";
					break;
			}
			//if ($newdata->processed == 1){ $status = "processed. Thanks!"; }
		   echo("<tr><td>".$newdata->title."</td><td>".$newdata->submitter."</td><td>".date("m/d/y h:i A",$newdata->timeSubmitted)."</td><td>".$status."</td></tr>");
		}
	?>
	</table>
</div>