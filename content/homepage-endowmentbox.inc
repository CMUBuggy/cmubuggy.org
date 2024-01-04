<?php
  // Time out the endowment box shortly after Jan 31 Midnight.
  // (default timezone already set in pre-content.inc)
  $enddate = mktime(3, 00, 0, 2, 1, 2024);

  if (time() < $enddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Endowment Grant Applications Open!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline-flex align-self-center mr-3" src="<?php echo(makeSmugmugUrl("i-qpSmJ4V","Th")); ?>">
        <div class="media-body align-self-center">
          <p>Applications for Endowed Fund Grants are open now until the end of September.</p>
          <a target="_blank" href="/2024springgrant" class="btn btn-primary">Apply Now</a>
          <a target="_blank" href="/news/2024/01/spring-2024-buggy-enhancement-grants-open/" class="btn btn-info">Learn More</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
