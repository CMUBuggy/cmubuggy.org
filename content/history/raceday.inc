<?php
  $year = $_GET['year'] * 1;
  $prevlink = "";
  $nextlink = "";

  if($year > 1920) {
    $prevlink = "<a href=\"/history/raceday/".($year - 1)."\">&laquo ".($year - 1)."</a>";
  }
  if($year < date("Y")){
    $nextlink = " | <a href=\"/history/raceday/".($year + 1)."\">".($year + 1)." &raquo</a>";
  }

  $mentriesArr = array();
  $wentriesArr = array();
  $pheatsArr = array();
  $fheatsArr = array();
  $raceyear = new raceyear();
  $raceyear = $raceyear->Get($year);
  $racedayList = $raceyear->GetRacedayList();
  foreach($racedayList as $raceday){
    $tempArr = array();
    $heatlist = $raceday->GetHeatList(null,"number");
    foreach($heatlist as $heat){
      $heattype = (string)$heat->raceclassId.(string)$heat->isreroll;
      $tempArr[$heattype][$heat->number]=$heat;
    }
    if($raceday->isFinals == 1){
      $fheatsArr=$tempArr;
    } else {
      $pheatsArr=$tempArr;
    }
  }
  $entryList = $raceyear->GetEntryList(null,"place");
  $noplacecounter = 100;
  foreach($entryList as $entry){
    $place = $entry->place;
    if(!($place>0)){
      $place = $noplacecounter;
      $noplacecounter++;
    }
    switch($entry->raceclassId) {
      case 1:
        $mentriesArr[$place] = $entry;
        break;
      case 2:
        $wentriesArr[$place] = $entry;
        break;
    }
  }

  function displayEntries($entryArr) {
    global $racedayList;
    ksort($entryArr);
    echo("<div class=\"table-responsive\"><table class=\"table\">");
    if(count($racedayList)>1){
      echo("<thead><tr><th>Place</th><th>Team</th><th>Prelims Time</th><th>Finals Time</th><th>Notes</th></tr></thead>");
    } else {
      echo("<thead><tr><th>Place</th><th>Team</th><th>Time</th><th>DQ / Notes</th></tr></thead>");
    }
    echo("<tbody>");
    foreach($entryArr as $entry){
      $entrylabel = $entry->GetOrg()->shortname." ".$entry->abcd;
      $teamList = $entry->GetTeamList();
      $teamArr = array();
      $notes = "";
      foreach($teamList as $team){
        $raceday = $team->GetRaceday();
        $teamArr[$raceday->isFinals] = $team;
        if($team->GetDq()->dqId>0){
          $notes .= "DQ: ".$team->GetDQ()->description;
        }
      }

      $place = "";
      if($entry->place>0){$place = $entry->place; }

      $url = "/history/team/".$entry->urlkey;
       echo("<tr><td>".$place."</td>");
       echo("<td><a href=\"".$url."\">".$entrylabel."</a></td>");
       if(isset($teamArr[0])){
        echo("<td>".displayTime($teamArr[0]->time)."</td>");
       }
       if(count($racedayList)>1){
        if(isset($teamArr[1])){
          echo("<td>".displayTime($teamArr[1]->time)."</td>");
        } else {
          echo("<td></td>");
        }
       }
       echo("<td>".$notes."</td></tr>");
    }
    echo("</tbody></table></div>");
  }

  function displayHeats($heatArr){
    ksort($heatArr);
    $heattypes = array("30","20","21","10","11");
    $heattypelabels = array("10"=>"Men's",
                    "11"=>"Men's Rerolls",
                    "20"=>"Women's",
                    "21"=>"Women's Rerolls",
                    "30"=>"Exhibitions");
    foreach($heattypes as $type){
      if(isset($heatArr[$type])){
        echo("<h4>".$heattypelabels[$type]."</h4>");
        echo("<div class\"table-responsive\"><table class=\"table\"><thead><tr><th></th><th></th><th>Lane 1</th><th>Lane 2</th><th>Lane 3</th><th>Notes</th></tr></thead>");
        echo("<tbody>");
        foreach($heatArr[$type] as $heat){
          echo("<tr><td>".$heat->number."</td><td>");
          $videolist = $heat->GetVideoList();
          $video = null;
          if($videolist){ $video = reset($videolist); }
          include("content/youtubevid.inc");
          echo("</td>");
          $teamsArr = array();
          foreach($heat->GetTeamList() as $team){
            $teamsArr[$team->lane]=$team;
          }
          for($l=1;$l<4;$l++){
            if(isset($teamsArr[$l])){
              $team = $teamsArr[$l];
              $entry = $team->GetEntry();
              echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$entry->GetOrg()->shortname." ".$entry->abcd."</a><br />".displayTime($team->time)."</td>");
            } else {
              echo("<td></td>");
            }
          }
          echo("<td></td></tr>");
        }
        echo("</tbody></table></div>");
      }
    }
  }

?>
<h1>Raceday <?php echo($year);?></h1>

<div class="my-2">
  <?php echo($prevlink.$nextlink); ?>
</div>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's Results</a>
  </li>
  <li class="nav-item">
    <a id="womens-tab" href="#tab-womens" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's Results</a>
  </li>
  <?php if(count($pheatsArr)>0) { ?>
    <li class="nav-item">
      <a id="prelimheats-tab" href="#tab-prelimheats" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-prelimheats" aria-selected="false">Prelim Heats</a>
    </li>
  <?php } ?>
  <?php if(count($fheatsArr)>0) { ?>
    <li class="nav-item">
      <a id="finalsheats-tab" href="#tab-finalsheats" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-finalsheats" aria-selected="false">Finals Heats</a>
    </li>
  <?php } ?>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayEntries($mentriesArr); ?>
  </div>
  <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
    <?php displayEntries($wentriesArr); ?>
  </div>
  <?php if(count($pheatsArr)>0) { ?>
    <div class="tab-pane fade" id="tab-prelimheats" role="tabpanel" aria-labelledby="prelimheats-tab">
      <?php displayHeats($pheatsArr); ?>
    </div>
  <?php } ?>
  <?php if(count($fheatsArr)>0) { ?>
    <div class="tab-pane fade" id="tab-finalsheats" role="tabpanel" aria-labelledby="finalsheats-tab">
      <?php displayHeats($fheatsArr); ?>
    </div>
  <?php } ?>
</div>
<?php
