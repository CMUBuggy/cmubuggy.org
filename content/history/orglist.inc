<?php
  $query = "SELECT orgid, shortname FROM hist_orgs WHERE isactive=1 AND isracingorg=1 ORDER BY shortname;";
  $activeOrgs = dbQuery("history",$query);
  $query = "SELECT orgid, shortname FROM hist_orgs WHERE isactive=0 AND isracingorg=1 ORDER BY shortname;";
  $pastOrgs = dbquery("history",$query);
  $query = "SELECT orgid, shortname FROM hist_orgs WHERE isactive=1 and isracingorg=0 ORDER BY shortname;";
  $supportOrgs = dbquery("history", $query);

  function echoOrgs($orgList) {
    while ($o = $orgList->fetch_assoc()) {
      echo("<li><a href=\"/history/org/".$o["orgid"]."\">".$o["shortname"]."</a></li>");
    }
  }
?>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="active-tab" href="#tab-active" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-active" aria-selected="true">Active Racing Orgs <span class="badge badge-primary"><?php echo($activeOrgs->num_rows); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="past-tab" href="#tab-past" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-past" aria-selected="false">Past Racing Orgs <span class="badge badge-primary"><?php echo($pastOrgs->num_rows); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="support-tab" href="#tab-support" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-support" aria-selected="false">Support Orgs <span class="badge badge-primary"><?php echo($supportOrgs->num_rows); ?></span></a>
  </li>
</ul>
<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-active" role="tabpanel" aria-labelledby="active-tab">
    <h1>Active Racing Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs($activeOrgs);
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-past" role="tabpanel" aria-labelledby="past-tab">
    <h1>Past Racing Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs($pastOrgs);
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-support" role="tabpanel" aria-labelledby="support-tab">
    <h1>Support Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs($supportOrgs);
      ?>
    </ul>
  </div>
</div>
