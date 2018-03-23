<?php
$personArrInit = array(
  "Driver"=>"",
  "Hill 1"=>"",
  "Hill 2"=>"",
  "Hill 3"=>"",
  "Hill 4"=>"",
  "Hill 5"=>""
);
$personArr = array();

function displayteam($team){
  global $personArr, $personArrInit;
  $personArr = $personArrInit;

  $raceday = $team->GetRaceday();
  $rddesc = "Prelims";
  $reroll = "";
  if($raceday->isFinals == 1){$rddesc = "Finals";}
  if($team->isReroll == 1) {$reroll = " (reroll)";}

  echo("<div class=\"col-sm\">");

  echo("<h2>".$rddesc.$reroll."</h2>");

  $heat = $team->GetHeat();
  if($heat->headId>0){
    $videolist = $heat->GetVideoList();
    if($videolist){
      $video = $videolist[0];
      include("content/youtubevid.inc");
    }
  }

  $buggy = $team->GetBuggy();

  $pttlist = $team->GetPersontoteamList();
  foreach ($pttlist as $ptt){
    $person = $ptt->GetPerson();
    $teamRole = $ptt->GetTeamrole();
    $personStr = "";
    if(isset($person)){
      $personStr = "<a href=\"/history/person/".$person->personId."\">".$person->firstName." ".$person->lastName."</a>";
    }
    $personArr[$teamRole->description] = $personStr;
  }

  echo("<dl class=\"row\">");
  echo("<dt class=\"col-sm-5\">Buggy</dt><dd class=\"col-sm-7\"><a href=\"/history/buggy/".$buggy->urlKey."\">".$buggy->name."</a></dd>");
  echo("<dt class=\"col-sm-5\">Driver</dt><dd class=\"col-sm-7\">".$personArr["Driver"]."</dd>");
  echo("<dt class=\"col-sm-5\">Hill 1</dt><dd class=\"col-sm-7\">".$personArr["Hill 1"]."</dd>");
  echo("<dt class=\"col-sm-5\">Hill 2</dt><dd class=\"col-sm-7\">".$personArr["Hill 2"]."</dd>");
  echo("<dt class=\"col-sm-5\">Hill 3</dt><dd class=\"col-sm-7\">".$personArr["Hill 3"]."</dd>");
  echo("<dt class=\"col-sm-5\">Hill 4</dt><dd class=\"col-sm-7\">".$personArr["Hill 4"]."</dd>");
  echo("<dt class=\"col-sm-5\">Hill 5</dt><dd class=\"col-sm-7\">".$personArr["Hill 5"]."</dd>");
  echo("<dt class=\"col-sm-5\">Time</dt><dd class=\"col-sm-7\">".displayTime($team->time)."</dd>");
  echo("</dl>");

  echo("</div>");
}


if(isset($_GET["urlkey"])){
  $errormsg   = null;
  $urlkey     = $_GET["urlkey"];
  $entry    = new entry();
  $entrylist  = $entry->GetList(array(array("urlkey","=",$urlkey)));
  $teamlist   = null;
  if($entrylist){
    $entry    = $entrylist[0];
    $org      = $entry->GetOrg();
    $raceyear = $entry->GetRaceyear();
    $raceclass  = $entry->GetRaceclass();
    $teamlist   = $entry->GetTeamList();
  }else{
    $errormsg = "There is no team identified by \"".$urlkey."\"";
  }
} else {
  $errormsg = "There is no team specified in the url";
}
if(!is_null($errormsg)){
  echo($errormsg);
} else {

?>

<h1><?php echo("<a href=\"/history/raceday/".$raceyear->year."\">".$raceyear->year."</a> <a href=\"/history/org/".$org->urlkey."\">".$org->shortname."</a> ".$raceclass->description." ".$entry->abcd); ?></h1>

<div class="row">
  <?php
    foreach($teamlist as $team) {
      displayteam($team);
    }
  ?>
</div>

<?php } ?>
