<?php
  // This requires the contentfeed fetching to be done, so we load that using
  // include_once.  It should only run once, of course.
  include_once("contentfeed_fetch.inc");
  $MAX_RECENT_NEWS = 2;

  // Sanity check!
  $mynewsitems = $newsitems;
  if (count($mynewsitems) > $MAX_RECENT_NEWS) {
    $mynewsitems = array_slice($newsitems, 0, $MAX_RECENT_NEWS);
  }

  // Because we have displayed the news items in this box, don't let the RHS column show them.
  $newsitems = array();
?>

<div class="row">

<?php
  foreach ($mynewsitems as $item) {

  // Notes about how this works:
  //
  // We use col-md to ensure below that breakpoint we still only have one column of boxes.
  // The margin (mb-3) has to be added on the columns instead of on the row for this reason.
?>
  <div class="col-md mb-3">
    <div class="card text-white h-100" style="background-color: var(--gray);">
      <div class="card-body d-flex flex-column">
        <h5 class="card-title mb-2"><?php echo($item["title"]) ?></h5>

        <?php
          echo('<time class="d-block text-right mb-4 small" datetime="'.date(DATE_RFC3339, $item['timestamp']) . '">' . timeago($item['timestamp']) . '</time>');
        ?>

        <p class="card-text"><?php echo($item["excerpt"]) ?></p>
        <a href="<?php echo($item["rellink"]) ?>" class="btn btn-primary mt-auto align-self-end">Read It</a>
      </div>
    </div>
  </div>
<?php
  }
?>

</div>