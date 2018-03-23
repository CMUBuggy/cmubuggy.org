<?php
$person = new person();
$person = $person->Get($_GET['id']);
$sweepstakesList = $person->GetSweepstakesList();
$pttList = $person->GetPersontoteamList();
?>

<div class="pane">
  <?php
    echo("<h2>".$person->firstName. " " . $person->lastName."</h2>");
    if(count($sweepstakesList)>0){
      echo("<h4 style=\"margin-top:20px;\">Sweepstakes Positions</h4>");
      foreach($sweepstakesList as $sweepstakes){
        $role = $sweepstakes->GetSweepstakesrole();
        echo($sweepstakes->year." ".$role->description."<br />");
      }
    }
    if(count($pttList)>0){
      $entryArr=array();
      echo("<h4 style=\"margin-top:20px;\">Teams</h4>");
      echo("<table class=\"data\"><tr><th>Year</th><th>Day</th><th>Team</th><th>Role</th><th>Time</th><th>Place</th></tr>");
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
      echo("</table>");
    }
  ?>
</div>
