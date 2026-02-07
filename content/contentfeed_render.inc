<?php
  // Render the right hand column (or below, on mobile) for the content feed.

  // Data should have been fetched earlier by including contentfeed_fetch.inc, but
  // we'll make another go at it here just in case.
  include_once("contentfeed_fetch.inc");
?>

<?php
  if (count($newsitems) > 0) {
?>
<section>
  <h2>Recent News</h2>
  <?php
    foreach ($newsitems as $item) {
      echo '<div class="d-flex mb-3"><div class="flex-shrink-0">' . $icon_map[$item['type']] . '</div><div class="flex-grow-1 pl-3">' . $item['content'] . '<time class="d-block text-end text-muted" datetime="' . date(DATE_RFC3339, $item['timestamp']) . '">' . timeago($item['timestamp']) . '</time></div></div>';
    }
  ?>
</section>
<?php
  }
?>

<section>
  <h2>Recent Activity</h2>
  <?php
    ##OVERALL DISPLAY##
    uasort($items, "timestamp_sort");
    $items = array_slice($items, 0, $MAX_FEED_ITEMS_ALL);
    foreach ($items as $item) {
      $media = $icon_map[$item['type']];
      if (isset($item['media'])) { $media = $item['media']; }
      echo '<div class="d-flex mb-3"><div class="flex-shrink-0">' . $media . '</div><div class="flex-grow-1 pl-3">' . $item['content'] . '<time class="d-block text-end text-muted" datetime="' . date(DATE_RFC3339, $item['timestamp']) . '">' . timeago($item['timestamp']) . '</time></div></div>';
    }
  ?>
</section>
