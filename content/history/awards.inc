<?php
  $buggyAward = new buggyAward();
  $buggyAwardList = $buggyAward->GetList(null,"year",false);
  $buggyAwardArr = array();
  foreach($buggyAwardList as $buggyAward){
    $awardType = $buggyAward->GetAwardtype();
    $buggyAwardArr[$buggyAward->year][$awardType->description] = $buggyAward->GetBuggy();
  }
  krsort($buggyAwardArr);

  $orgAward = new orgAward();
  $orgAwardList = $orgAward->GetList(null,"year",false);
  $orgAwardArr = array();
  foreach($orgAwardList as $orgAward){
    $awardType = $orgAward->GetAwardtype();
    $orgAwardArr[$orgAward->year][$awardType->description] = $orgAward->GetOrg();
  }
  krsort($orgAwardArr);

?>
<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="designcomp-tab" href="#tab-designcomp" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-designcomp" aria-selected="true">Design Competition</a>
  </li>
  <li class="nav-item">
    <a id="orgawards-tab" href="#tab-orgawards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-orgawards" aria-selected="false">Organization Awards</a>
  </li>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-designcomp" role="tabpanel" aria-labelledby="designcomp-tab">
    <h1>Design Competition</h1>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Year</th>
            <th>1st Place</th>
            <th>2nd Place</th>
            <th>3rd Place</th>
            <th>People's Choice</th>
          </tr>
        </thead>
        <tbody>
          <?php
            for($year = 2011; $year >= 1920; $year--){
              $buggy1 = new buggy();
              $buggy2 = new buggy();
              $buggy3 = new buggy();
              $buggyPC = new buggy();
              if(array_key_exists($year,$buggyAwardArr)){
                if(isset($buggyAwardArr[$year]["Design Competition - 1st Place"])){
                  $buggy1 = $buggyAwardArr[$year]["Design Competition - 1st Place"];
                }
                if(isset($buggyAwardArr[$year]["Design Competition - 2nd Place"])){
                  $buggy2 = $buggyAwardArr[$year]["Design Competition - 2nd Place"];
                }
                if(isset($buggyAwardArr[$year]["Design Competition - 3rd Place"])){
                  $buggy3 = $buggyAwardArr[$year]["Design Competition - 3rd Place"];
                }
                if(isset($buggyAwardArr[$year]["Design Competition - People's Choice"])){
                  $buggyPC = $buggyAwardArr[$year]["Design Competition - People's Choice"];
                }

                $org = new org();
                if($buggy1 != null){
                  $org = $buggy1->GetOrg();
                  if($buggy1->yearBuilt > 0) { $yearbuilt = $buggy1->yearBuilt; } else { $yearbuilt = ""; }
                  $alt1 = $org->shortName." ".$yearbuilt;
                }
                if($buggy2 != null){
                  $org = $buggy2->GetOrg();
                  if($buggy2->yearBuilt > 0) { $yearbuilt = $buggy2->yearBuilt; } else { $yearbuilt = ""; }
                  $alt2 = $org->shortName." ".$yearbuilt;
                }
                if($buggy3 != null){
                  $org = $buggy3->GetOrg();
                  if($buggy3->yearBuilt > 0) { $yearbuilt = $buggy3->yearBuilt; } else { $yearbuilt = ""; }
                  $alt3 = $org->shortName." ".$yearbuilt;
                }
                if($buggyPC != null){
                  $org = $buggyPC->GetOrg();
                  if($buggyPC->yearBuilt > 0) { $yearbuilt = $buggyPC->yearBuilt; } else { $yearbuilt = ""; }
                  $altPC = $org->shortName." ".$yearbuilt;
                }

                echo("<tr><td>".$year."</td>");
                echo("<td><a title=\"".$alt1."\" href=\"./buggy/".$buggy1->urlKey."\">".$buggy1->name."</a></td>");
                echo("<td><a title=\"".$alt2."\" href=\"./buggy/".$buggy2->urlKey."\">".$buggy2->name."</a></td>");
                echo("<td><a title=\"".$alt3."\" href=\"./buggy/".$buggy3->urlKey."\">".$buggy3->name."</a></td>");
                echo("<td><a title=\"".$altPC."\" href=\"./buggy/".$buggyPC->urlKey."\">".$buggyPC->name."</a></td>");
                echo("</tr>");
              }
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>

  <div class="tab-pane fade" id="tab-orgawards" role="tabpanel" aria-labelledby="orgawards-tab">
    <h1>Organization Awards</h1>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Year</th>
            <th>Chairman's Choice</th>
            <th>Spirit of Buggy</th>
            <th>T-Shirt Award</th>
          </tr>
        </thead>
        <tbody>
          <?php
            for($year = 2011; $year >= 1965; $year--){
              if(array_key_exists($year,$orgAwardArr)){
                $orgCC = new org();
                $orgSP = new org();
                $orgTS = new org();
                if(isset($orgAwardArr[$year]["Chairman's Choice"])){
                  $orgCC = $orgAwardArr[$year]["Chairman's Choice"];
                }
                if(isset($orgAwardArr[$year]["Spirit of Buggy"])){
                  $orgSP = $orgAwardArr[$year]["Spirit of Buggy"];
                }
                if(isset($orgAwardArr[$year]["T-Shirt Award"])){
                  $orgTS = $orgAwardArr[$year]["T-Shirt Award"];
                }
                echo("<tr><td>".$year."</td>");
                echo("<td><a href=\"./org/".$orgCC->urlkey."\">".$orgCC->shortname."</a></td>");
                echo("<td><a href=\"./org/".$orgSP->urlkey."\">".$orgSP->shortname."</a></td>");
                echo("<td><a href=\"./org/".$orgTS->urlkey."\">".$orgTS->shortname."</a></td>");
                echo("</tr>");
              }
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>
</div>
