<?php
  // Time out the endowment box after Sep 30 Midnight.
  // (default timezone already set in pre-content.inc)
  $enddate = mktime(23, 59, 0, 9, 30, 2023);

  if (time() < $enddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Endowment Grant Applications Open!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline-flex align-self-center mr-3" src="<?php echo(makeSmugmugUrl("i-qpSmJ4V","Th")); ?>">
        <div class="media-body align-self-center">
          <p>Applications for Endowed Fund Grants are open now until the end of September.</p>
          <a target="_blank" href="/2023fallgrant" class="btn btn-primary">Apply Now</a>
          <a target="_blank" href="/news/2023/09/fall-2023-enhancment-grant-applications-open/" class="btn btn-info">Learn More</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
