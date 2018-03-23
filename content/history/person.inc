<?php
$person = new person();
$person = $person->Get($_GET['id']);
$sweepstakesList = $person->GetSweepstakesList();
$pttList = $person->GetPersontoteamList();
?>

<?php
  echo("<h1>".$person->firstName. " " . $person->lastName."</h1>");
  if(count($sweepstakesList)>0){
    echo("<h2>Sweepstakes Positions</h2>");
    echo("<ul class=\"list-unstyled\">");
    foreach($sweepstakesList as $sweepstakes){
      $role = $sweepstakes->GetSweepstakesrole();
      echo("<li>".$sweepstakes->year." ".$role->description."</li>");
    }
    echo("</ul>");
  }
  if(count($pttList)>0){
    $entryArr=array();
    echo("<h2>Teams</h2>");
    echo("<div class=\"table-responsive\"><table class=\"table\"><thead><tr><th>Year</th><th>Day</th><th>Team</th><th>Role</th><th>Time</th><th>Place</th></tr></thead><tbody>");
    foreach($pttList as $ptt){
      $team = $ptt->GetTeam();
      $entry = $team->GetEntry();
      $raceday = $team->GetRaceday();
      $role = $ptt->GetTeamRole();
      $org = $entry->GetOrg();
      $raceclass = $entry->GetRaceclass();
      $raceyear = $entry->GetRaceyear();
      $day = "Prelims";
      if($raceday->isFinals == 1) { $day = "Finals"; }
      $time = displayTime($team->time);

      echo("<tr>");
      echo("<td>".$raceyear->year."</td>");
      echo("<td>".$day."</td>");
      echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$org->shortname." ".$raceclass->description." ".$entry->abcd."</a></td>");
      echo("<td>".$role->description."</td>");
      echo("<td>".$time."</td>");
      echo("<td>".$entry->place."</td>");
      echo("</tr>");
    }
    echo("</tbody></table></div>");
  }
?>
