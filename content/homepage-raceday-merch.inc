<?php
  // Time out the merch box after Dec 2 Midnight
  // (default timezone already set in pre-content.inc)
  $merchenddate = mktime(23, 59, 0, 12, 2, 2023);

  if (time() < $merchenddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Buggy Merch!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline align-self-center mr-3" style="width:150px; height:150px" src="<?php echo(makeSmugmugUrl("i-sCG2kqR", "Th")); ?>">
        <div class="media-body">
          <p>Show your Buggy Spirit this Fall!</p>
          <p>BAA Beanies are here in 2 different colors.  Store closes the evening of Dec 2!</p>
          <a target="_blank" href="/merch" class="btn btn-primary">Get My Stuff!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
