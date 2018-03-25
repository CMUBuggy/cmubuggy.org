<?php
  $org = new org();
  $activelist   = $org->GetList(array(array("isactive", "=", "1"),array("isracingorg", "=", "1")),"shortname");
  $pastlist     = $org->GetList(array(array("isactive", "=", "0"),array("isracingorg", "=", "1")),"shortname");
  $supportlist  = $org->GetList(array(array("isracingorg", "=", "0")),"shortname");
?>
<ul class="tabs">
  <li><a id="t1" href="#active">Active Racing Orgs (<? echo(count($activelist)); ?>)</a></li>
  <li><a id="t2" href="#past">Past Racing Orgs (<? echo(count($pastlist)); ?>)</a></li>
  <li><a id="t3" href="#support">Supporting Orgs (<? echo(count($supportlist)); ?>)</a></li>
</ul>
<div class="panes">
  <div class="pane">
    <div class="title">Active Racing Organizations</div>
    <?php
      foreach ($activelist as $org) {
          echo("<a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a><br />");
      }
    ?>
  </div>
  <div class="pane">
    <div class="title">Past Racing Organizations</div>
    <?php
      foreach ($pastlist as $org){
          echo("<a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a><br />");
      }
    ?>
  </div>
  <div class="pane">
    <div class="title">Support Organizations</div>
    <?php
      foreach ($supportlist as $org){
          echo("<a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a><br />");
      }
    ?>
  </div>
</div>
