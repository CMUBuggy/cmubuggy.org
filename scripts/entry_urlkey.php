Entry URL Key maker:<br /><br />
<?php
include("../lib/pog/pog_includes.inc");
include("../dbconfig.inc");
include("../util.inc");

$entry = new entry();
$entrylist = $entry->GetList(array(array("entryid",">",1831)));

foreach($entrylist as $entry){
	$org = $entry->GetOrg();
	$rc = $entry->GetRaceclass();
	$abcd = $entry->abcd;
	$raceyear = $entry->GetRaceyear(); 
	 
	$urlkey = $raceyear->year . ".". $org->urlkey . "." . substr($rc->description,0,1) . $abcd;
	echo($urlkey."<br />");
 	$entry->urlkey = $urlkey;
 	$entry->Save();
}


?>