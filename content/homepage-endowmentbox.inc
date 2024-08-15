<?php
  // Time out the endowment box shortly after Jan 31 Midnight.
  // (default timezone already set in pre-content.inc)
  //
  // When you change the end date, make sure ot update the text below!
  $enddate = mktime(3, 00, 0, 9, 16, 2024);
  $END_DATE_TEXT = "midnight, September 15th";

  $ENDOWMENT_IMAGE_SLUG = "i-JWHzQxQ"; // drone   (info table: "i-qpSmJ4V")
  $GRANT_APPLICATION_LINK = "/2024fallgrant";
  $GRANT_ANNOUNCEMENT_LINK = "/news/2024/08/fall-2024-buggy-enhancement-grants-now-open/";

  if (time() < $enddate) {
?>
  <div class="card mb-3">
    <h5 class="card-header">Buggy Enhancement Grant Applications Open!</h5>
    <div class="card-body">
      <div class="media">
        <img class="d-none d-md-inline-flex align-self-center mr-3" src="<?php echo(makeSmugmugUrl($ENDOWMENT_IMAGE_SLUG,"Th")); ?>">
        <div class="media-body align-self-center">
          <p>Applications for Buggy Enhancement Grants are open now until <?php echo($END_DATE_TEXT); ?>.</p>
          <a target="_blank" href="<?php echo($GRANT_APPLICATION_LINK); ?>" class="btn btn-primary">Apply Now</a>
          <a target="_blank" href="<?php echo($GRANT_ANNOUNCEMENT_LINK); ?>" class="btn btn-info">Learn More</a>
        </div>
      </div>
    </div>
  </div>
<?php
  }
?>
