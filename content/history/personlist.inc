<?php
	$person = new person();
	$personListLast = $person->GetList(array(array("personId", ">", "0")),"lastName");
	$personListFirst = $person->GetList(array(array("personId", ">", "0")),"firstName");
?>


<div class="pane">
	<div class="title">Search</div>
	The history database currently includes people that we have records for as raceday pushers, drivers, and members of the sweepstakes committee (<?php echo(count($personListLast)); ?> people at the moment).  We plan to include mechanics and organization leaders soon.
	<table>
		<tr>
			<td>
				First Name
			 	<div id="personautocomplete2" style="width:15em; padding-bottom:2em; z-index:9000;">
				    <input id="personinput2" type="text">
				    <div id="personcontainer2"></div>
				</div>
			</td>
			<td>
				Last Name
			 	<div id="personautocomplete" style="width:15em; padding-bottom:2em; z-index:9000;">
				    <input id="personinput" type="text">
				    <div id="personcontainer"></div>
				</div>
			</td>
		</tr>
	</table>
</div>


<script type="text/javascript">

<?php
	echo("var personArrLast = [");
	foreach ($personListLast as $person)
	{
		echo("[\"".$person->lastName."\",\"".$person->firstName."\",\"".$person->personId."\"],");
	}
	echo("];");

	echo("var personArrFirst = [");
	foreach ($personListFirst as $person)
	{
		echo("[\"".$person->firstName."\",\"".$person->lastName."\",\"".$person->personId."\"],");
	}
	echo("];");
?>

    var oACDS = new YAHOO.widget.DS_JSArray(personArrLast);
    var personAC = new YAHOO.widget.AutoComplete('personinput','personcontainer', oACDS);
    personAC.prehighlightClassName = "yui-ac-prehighlight";
    personAC.typeAhead = false;
    personAC.useShadow = true;
    personAC.forceSelection = true;
    personAC.maxResultsDisplayed = 25;
    personAC.formatResult = function(oResultItem, sQuery) {
        var sMarkup = oResultItem[0] + ", " + oResultItem[1];
        return (sMarkup);
    };

    var oACDS2 = new YAHOO.widget.DS_JSArray(personArrFirst);
    var personAC2 = new YAHOO.widget.AutoComplete('personinput2','personcontainer2', oACDS2);
    personAC2.prehighlightClassName = "yui-ac-prehighlight";
    personAC2.typeAhead = false;
    personAC2.useShadow = true;
    personAC2.forceSelection = true;
    personAC2.maxResultsDisplayed = 25;
    personAC2.formatResult = function(oResultItem, sQuery) {
        var sMarkup = oResultItem[0] + " " + oResultItem[1];
        return (sMarkup);
    };
	function fnCallback(e, args) {
	    window.location='http://cmubuggy.org/history/person/'+args[2][2];
	 }
	 personAC.itemSelectEvent.subscribe(fnCallback);
	 personAC2.itemSelectEvent.subscribe(fnCallback);

</script>
