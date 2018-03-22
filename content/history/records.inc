<?php

  $teamObj = new team();
  $top25men  = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1")),"time", "true", 50);
  //$top25menb = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1"), array("abcd","=","b")),"time", true, 25);
  //$top25menc = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1"), array("abcd","=","c")),"time", true, 25);
  //$top25mend = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","1"), array("abcd","=","d")),"time", true, 25);

  $top25women  = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2")),"time", true, 50);
  //$top25womenb = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2"), array("abcd","=","b")),"time", true, 25);
  //$top25womenc = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2"), array("abcd","=","c")),"time", true, 25);
  //$top25womend = $teamObj->GetList(array(array("time",">","0"), array("raceclassid","=","2"), array("abcd","=","d")),"time", true, 25);

  function displayRecordTable($teamlist){
    echo("<table class=\"table\">");
    $count = 1;
    foreach($teamlist as $team){
      $entry= $team->GetEntry();
      $raceday = $team->GetRaceday();
      $racedaynum = 1;
      if($raceday->isFinals==1){$racedaynum = 2;}
      $org = $entry->GetOrg();
      $year = $entry->GetRaceyear()->year;
      $buggy = $team->GetBuggy();
      $dq = $team->GetDq();
      $url = "/history/team/".$entry->urlkey;


      echo("<tr><td>".$count.".</td>");
      echo("<td><a href=\"/history/raceday/".$year."\">".$year."</a><sub>".$racedaynum."</sub></td>");
      echo("<td><a href=\"".$url."\">".$org->shortname."</a></td>");
      echo("<td><a href=\"/history/buggy/".$buggy->urlKey."\">".$buggy->name."</a></td>");
      echo("<td>".displayTime($team->time)."</td>");
      echo("<td>".$dq->description." ".$team->notes."</td></tr>");

      $count++;
    }
    echo("</table>");
  }
?>

<h1>Course Records</h1>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="mens-tab" href="#tab-mens" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-mens" aria-selected="true">Men's</a></li>
  <li class="nav-item">
    <a id="womens-tab" href="#tab-womens" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-womens" aria-selected="false">Women's</a></li>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-mens" role="tabpanel" aria-labelledby="mens-tab">
    <?php displayRecordTable($top25men); ?>
  </div>
  <div class="tab-pane fade" id="tab-womens" role="tabpanel" aria-labelledby="womens-tab">
    <?php displayRecordTable($top25women); ?>
  </div>
</div>











