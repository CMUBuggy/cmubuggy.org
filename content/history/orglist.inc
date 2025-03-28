<?php
  $query = "SELECT orgid, shortname, longname, isactive, isracingorg FROM hist_orgs ORDER BY shortname;";
  $orgResults = dbQuery($HISTORY_DATABASE, $query);

  $orgData = $orgResults->fetch_all(MYSQLI_ASSOC);

  // Active and Racing should be 1 or 0.
  function countOrgs($active, $racing) {
    global $orgData;
    $result = 0;
    foreach ($orgData as $o) {
      if ($active == $o["isactive"] && $racing == $o["isracingorg"]) {
        $result++;
      }
    }
    return $result;
  }

  // Active and Racing should be 1 or 0.
  function echoOrgs($active, $racing) {
    global $orgData;
    foreach ($orgData as $o) {
      if ($active == $o["isactive"] && $racing == $o["isracingorg"]) {
        $longname = "";
        if ($o["shortname"] != $o["longname"]) {
          $longname = " (".$o["longname"].")";
        }
        echo("<li><a href=\"/history/org/".$o["orgid"]."\">".$o["shortname"]."</a>$longname</li>");
      }
    }
  }
?>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="active-tab" href="#tab-active" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-active" aria-selected="true">Racing Orgs <span class="badge badge-primary"><?php echo(countOrgs(1,1)); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="past-tab" href="#tab-past" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-past" aria-selected="false">Past Racing Orgs <span class="badge badge-primary"><?php echo(countOrgs(0,1)); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="support-tab" href="#tab-support" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-support" aria-selected="false">Support Orgs <span class="badge badge-primary"><?php echo(countOrgs(1,0)); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="support-past-tab" href="#tab-support-past" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-support-past" aria-selected="false">Past Support Orgs <span class="badge badge-primary"><?php echo(countOrgs(0,0)); ?></span></a>
  </li>
</ul>
<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-active" role="tabpanel" aria-labelledby="active-tab">
    <h1>Active Racing Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs(1, 1);
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-past" role="tabpanel" aria-labelledby="past-tab">
    <h1>Past Racing Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs(0, 1);
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-support" role="tabpanel" aria-labelledby="support-tab">
    <h1>Support Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs(1, 0);
      ?>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-support-past" role="tabpanel" aria-labelledby="support-past-tab">
    <h1>Past Support Organizations</h1>
    <ul class="list-unstyled">
      <?php
        echoOrgs(0, 0);
      ?>
    </ul>
  </div>
</div>
