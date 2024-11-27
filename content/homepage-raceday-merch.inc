<?php
  // Time out the merch box when the sale closes.
  // (default timezone already set in pre-content.inc)
  $merchenddate = mktime(23, 59, 0, 8, 5, 2024);

  if (time() < $merchenddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Buggy Merch!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline align-self-center mr-3" style="width:150px; height:150px" src="<?php echo(makeSmugmugUrl("i-gwXwwFK", "Th")); ?>">
        <div class="media-body">
          <p>Tired of boring reusable tote bags?
             Worry not! You can now get your groceries in style and support Buggy
             at the same time!</p>
          <p>Store closes August 5!</p>
          <a target="_blank" href="/merch" class="btn btn-primary">Get My Stuff!</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
