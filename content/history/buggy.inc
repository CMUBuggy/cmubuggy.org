<?php
$buggy = new buggy();

if(!empty($_GET["urlkey"])){
  $buggyList = $buggy->GetList(array(array("urlkey","=",$_GET["urlkey"])));
  if(count($buggyList)>0){
    $buggy = $buggyList[0];
  }
}

$yearBuilt = "";
if($buggy->yearBuilt <> 0){
  $yearBuilt = $buggy->yearBuilt;
}

$org = new org();
$org = $buggy->GetOrg();

$teamList = $buggy->GetTeamList(array(array("teamId", ">", "0")),"racedayId",false);
$buggyAwardList = $buggy->GetBuggyawardList(array(array("buggyAwardId", ">", "0")),"year",false);

?>

<h1><?php echo($buggy->name);?></h1>

<?php
  if (file_exists("../../img/buggy/".$buggy->urlKey)) {
    echo("<img class=\"mb-3\" alt=\"".$buggy->urlKey."\" src=\"/img/buggy/".$buggy->urlKey."\" />");
  }
?>

<dl class="row">
  <dt class="col-sm-5">Built</dt>
  <dd class="col-sm-7"><?php echo($yearBuilt); ?></dd>

  <dt class="col-sm-5">Organization</dt>
  <dd class="col-sm-7"><?php echo("<a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a>"); ?></dd>
</dl>

<ul class="nav nav-tabs" role="tablist">
  <li class="nav-item">
    <a id="races-tab" href="#tab-races" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-races" aria-selected="true">Races <span class="badge badge-primary"><?php echo(count($teamList)); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="awards-tab" href="#tab-awards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-awards" aria-selected="false">Awards <span class="badge badge-primary"><?php echo(count($buggyAwardList)); ?></span></a>
  </li>
</ul>
<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-races" role="tabpanel" aria-labelledby="races-tab">
    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr class="text-nowrap">
            <th></th>
            <th>Year</th>
            <th>Day</th>
            <th>Team</th>
            <th>Time</th>
            <th>DQ / Notes</th>
          </tr>
        </thead>
        <tbody>
          <?php
          foreach ($teamList as $team){
            $entry= $team->GetEntry();
            $teamdesc = $entry->GetRaceclass()->description." ".$entry->abcd;
            $raceday = $team->GetRaceday();
            $racedaytype = "Prelims";
            if($raceday->isFinals==1){$racedaytype = "Finals";}
            $org = $entry->GetOrg();
            $year = $entry->GetRaceyear()->year;
            $buggy = $team->GetBuggy();
            $dq = $team->GetDq();
            if(strlen($dq->description)>0){$dq = "DQ: ".$dq->description; } else {$dq=""; }
            $url = "/history/".$entry->urlkey;
            $videolist = null;
            $videolist = $team->GetHeat()->GetVideoList();
            $video = null;
            if($videolist){ $video = reset($videolist); }
            echo("<td>");
            include("content/youtubevid.inc");
            echo("</td>");
            echo("<td><a href=\"/history/raceday/".$year."\">".$year."</a></td>");
            echo("<td>".$racedaytype."</td>");
            echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$teamdesc."</a></td>");
            echo("<td>".displayTime($team->time)."</td>");
            echo("<td>".$dq." ".$team->notes."</td></tr>");
          }
          ?>
        </tbody>
      </table>
    </div>
  </div>
  <div class="tab-pane fade" id="tab-awards" role="tabpanel" aria-labelledby="awards-tab">
    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr class="text-nowrap">
            <th>Year</th>
            <th>Awards</th>
          </tr>
        </thead>
        <tbody>
          <?php
            foreach($buggyAwardList as $buggyAward){
              $awardType = $buggyAward->GetAwardtype();
              echo("<tr><td>".$buggyAward->year."</td><td>$awardType->description</td></tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>
</div>
