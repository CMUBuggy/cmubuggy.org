<div class="pane">
  <div class="title">Racedays</div>
  <table class="data">
    <tr>
      <th></th>
      <th colspan="4"><h4>Men's</h4></th>
      <th colspan="4"><h4>Women's</h4></th>
    </tr>
    <tr>
      <th>Year</th>
      <th class="newcol">Champ</th>
      <th>Time</th>
      <th>2nd Place</th>
      <th>3rd Place</th>
      <th class="newcol">Champ</th>
      <th>Time</th>
      <th>2nd Place</th>
      <th>3rd Place</th>
    </tr>

<?php

  $raceyear = new raceyear();
  $raceyearlist = $raceyear->GetList(array(array("raceyearId",">","0")),"year",false);

  foreach($raceyearlist as $raceyear){
    $m1 = $raceyear->GetEntryList(array(array("place","=","1"),array("raceclassId","=",1)));
    $m2 = $raceyear->GetEntryList(array(array("place","=","2"),array("raceclassId","=",1)));
    $m3 = $raceyear->GetEntryList(array(array("place","=","3"),array("raceclassId","=",1)));
    $entryarr = array($m1,$m2,$m3);
    if($raceyear->year > 1978){
      $w1 = $raceyear->GetEntryList(array(array("place","=","1"),array("raceclassId","=",2)));
      $w2 = $raceyear->GetEntryList(array(array("place","=","2"),array("raceclassId","=",2)));
      $w3 = $raceyear->GetEntryList(array(array("place","=","3"),array("raceclassId","=",2)));
      array_push($entryarr,$w1,$w2,$w3);
    }
    if(isset($m1[0])){
      echo("<tr><td><a href=\"/history/raceday/".$raceyear->year."\">".$raceyear->year."</a></td>");
      $col = 1;
      foreach($entryarr as $entrylist){
        $entry = null;
        if(isset($entrylist[0])){
          $entry = $entrylist[0];
          $org = $entry->GetOrg()->shortname;
          $teamlist = $entry->GetTeamList(array(array("teamId",">","0")));
          $time = null;
          $colclass = null;
          foreach($teamlist as $team){
            $time = displayTime($team->time);
          }
          if($entry->abcd != "A"){
            $org.= " ". $entry->abcd;
          }
          if($entry->place == 1){
            $colclass = "newcol";
          }
          echo("<td class=\"".$colclass."\"><a href=\"/history/team/".$entry->urlkey."\">".$org."</td>");
          if($col==1 || $col == 5){
            echo("<td>".$time."</td>");
            $col++;
          }
        } else {
          echo("<td></td>");
        }
        $col++;
      }
    } else {
      echo("<tr><td><a href=\"/history/raceday/".$raceyear->year."\">".$raceyear->year."</a></td><td class=\"newcol\"></td><td></td><td></td><td></td></tr>");
    }
  }

?>
  </table>
</div>
