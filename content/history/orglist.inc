<?php
  $org = new org();
  $activelist   = $org->GetList(array(array("isactive", "=", "1"),array("isracingorg", "=", "1")),"shortname");
  $pastlist     = $org->GetList(array(array("isactive", "=", "0"),array("isracingorg", "=", "1")),"shortname");
  $supportlist  = $org->GetList(array(array("isracingorg", "=", "0")),"shortname");
?>
<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="active-tab" href="#tab-active" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-active" aria-selected="true">Active Racing Orgs <span class="badge badge-primary"><?php echo(count($activelist)); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="past-tab" href="#tab-past" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-past" aria-selected="false">Past Racing Orgs <span class="badge badge-primary"><?php echo(count($pastlist)); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="support-tab" href="#tab-support" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-support" aria-selected="false">Supporting Orgs <span class="badge badge-primary"><?php echo(count($supportlist)); ?></span></a>
  </li>
</ul>
<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-active" role="tabpanel" aria-labelledby="active-tab">
    <h1>Active Racing Organizations</h1>
    <ul class="list-unstyled">
      <?php
        foreach ($activelist as $org) {
          echo("<li><a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a></li>");
        }
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-past" role="tabpanel" aria-labelledby="past-tab">
    <h1>Past Racing Organizations</h1>
    <ul class="list-unstyled">
      <?php
        foreach ($pastlist as $org) {
          echo("<li><a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a><li>");
        }
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-support" role="tabpanel" aria-labelledby="support-tab">
    <h1>Support Organizations</h1>
    <ul class="list-unstyled">
      <?php
        foreach ($supportlist as $org) {
          echo("<li><a href=\"/history/org/".$org->urlkey."\">".$org->shortname. "</a><li>");
        }
      ?>
    </ul>
  </div>
</div>
