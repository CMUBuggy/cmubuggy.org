<?php
// Front Page Feed Limits:
// Total Items: 15
// Comments: Only 5, regardless of source.
// Only back 90 days.
$MAX_FEED_ITEMS_COMMENT = 5;
$MAX_FEED_ITEMS_ALL = 15;
$MAX_FEED_DAYS = 90;

// set our cutoff time
$cutoff = time()-(60*60*24*$MAX_FEED_DAYS);
$cutoffDate = date("Y-m-d",$cutoff);

// Our various arrays to track our content.
$items = array();
$commentitems = array();
$newsitems = array();
$icon_map = array();

##NEWS ITEMS##
$newsSQL = "SELECT wp_posts.ID,wp_posts.post_date,wp_users.display_name,wp_posts.post_name,wp_posts.post_title,wp_posts.comment_count
  FROM wp_posts
  JOIN wp_users
  ON wp_posts.post_author=wp_users.ID
  WHERE post_status LIKE 'publish'
  AND post_type LIKE 'post'
  and post_date > '$cutoffDate'
  ORDER BY post_date DESC
  LIMIT 0,15";
$newsResults  = dbQuery("cmubuggy_wp",$newsSQL);

$count = 1;
if ($newsResults) {
  $icon_map["news"] = '<span class="fa-layers fa-fw fa-2x mr-2"><i class="fas fa-square text-warning"></i><i class="fas fa-newspaper fa-inverse" data-fa-transform="shrink-8"></i></span>';
  while ($post = mysqli_fetch_row($newsResults)) {
    //date format: YYYY-MM-DD HH:MM:SS
    $timestamp = $post[1];
    $year = substr($timestamp, 0, 4);
    $month = substr($timestamp, 5, 2);
    $day = substr($timestamp, 8, 2);
    $hour = substr($timestamp, 11, 2);
    $minute = substr($timestamp, 14, 2);
    $second = substr($timestamp, 17, 2);
    $timestamp = mktime($hour, $minute, $second, $month, $day, $year);

    $a = array(
      "timestamp"=>$timestamp,
      "content"=>'<a href="/news/'.$post[3].'">'.$post[4].'</a>',
      "type"=>"news"
    );
    if ($count < 3){
      array_push($newsitems,$a);
    } else {
      array_push($items,$a);
    }
    $count++;
  }
}

##phpBB FORUM ITEMS##
$forumSQL = "SELECT posts.post_id, posts.post_time, users.username, topics.topic_title, posts.topic_id
  FROM posts
  JOIN users
  ON posts.poster_id=users.user_id
  JOIN topics
  ON posts.topic_id=topics.topic_id
  where post_time > $cutoff
  ORDER BY post_time DESC";
$forumResults = dbQuery("cmubuggy_phpBB",$forumSQL);

$forumClusterItems = array();

if ($forumResults) {
  $icon_map["forum"] = '<span class="fa-layers fa-fw fa-2x mr-2"><i class="fas fa-square text-muted"></i><i class="fas fa-comments fa-inverse" data-fa-transform="shrink-8"></i></span>';
  while ($post = mysqli_fetch_row($forumResults)) {
    $clusterKey = $post[4].date("md",$post[1]);
    $threadtitle = $post[3];
    // if (strlen($threadtitle) > 25) { $threadtitle = substr($threadtitle, 0, 23)."..."; }
    $href = "/forum/viewtopic.php?f=3&t=".$post[4]."&p=".$post[0]."#p".$post[0];
    if (array_key_exists($clusterKey, $forumClusterItems)) {
      $forumClusterItems[$clusterKey]["count"]++;
      $forumClusterItems[$clusterKey]["content"] = $forumClusterItems[$clusterKey]["count"] . ' new posts in the thread <a href="' . $href . '">' . $threadtitle . '</a>';
      $forumClusterItems[$clusterKey]["person"] = "people";
    } else {
      $forumClusterItems[$clusterKey] = array(
        "timestamp"=>$post[1],
        "count"=>1,
        "content" => $post[2] . ' posted in <a href="' . $href . '">' . $threadtitle . '</a>',
        "type"=>"forum"
      );
    }
  }
  foreach ($forumClusterItems as $a) {
    array_push($items,$a);
  }
}

##NEWS COMMENTS##
$ncommentSQL = "SELECT wp_comments.comment_ID, wp_comments.comment_date, wp_comments.comment_author, wp_comments.comment_content, wp_comments.comment_post_ID, wp_posts.post_name, wp_posts.post_title
  FROM wp_comments
  JOIN wp_posts
  ON wp_comments.comment_post_ID=wp_posts.ID
  WHERE wp_comments.comment_approved = 1
  and wp_comments.comment_date > '$cutoffDate'
  ORDER BY wp_comments.comment_date DESC";
$ncommentResults = dbQuery("cmubuggy_wp",$ncommentSQL);

$ncommentClusterItems = array();

if ($ncommentResults) {
  $icon_map["ncomment"] = '<span class="fa-layers fa-fw fa-2x mr-2"><i class="fas fa-square text-muted"></i><i class="fas fa-newspaper fa-inverse" data-fa-transform="shrink-8"></i><i class="fas fa-comment" data-fa-transform="shrink-10 right-6 down-6"></i></span>';
  while ($post = mysqli_fetch_row($ncommentResults)) {
    $timestamp = $post[1];
    $year = substr($timestamp, 0, 4);
    $month = substr($timestamp, 5, 2);
    $day = substr($timestamp, 8, 2);
    $hour = substr($timestamp, 11, 2);
    $minute = substr($timestamp, 14, 2);
    $second = substr($timestamp, 17, 2);
    $timestamp = mktime($hour, $minute, $second, $month, $day, $year);

    $parent_id = $post[4];
    $clusterKey = $parent_id.$month.$day;
    $title = $post[6];
    // if (strlen($title) > 29) {$title = substr($title, 0, 26)."..."; }
    $commenter = $post[2];
    if (strlen($commenter) == 0) { $commenter = "Anonymous"; }
    $href = "/news/".$post[5]."#comments";
    if (array_key_exists($clusterKey, $ncommentClusterItems)) {
      $ncommentClusterItems[$clusterKey]["count"]++;
      $ncommentClusterItems[$clusterKey]["content"] = $ncommentClusterItems[$clusterKey]["count"] . ' new comments on <a href="' . $href. '">' . $title . '</a>';
    } else {
      $ncommentClusterItems[$clusterKey] = array(
        "timestamp"=>$timestamp,
        "count"=>1,
        "content" => $commenter . ' commented on <a href="' . $href . '">' . $title . '</a>',
        "type"=>"ncomment"
      );
    }
  }
  foreach ($ncommentClusterItems as $a) {
    array_push($commentitems,$a);
  }
}

// smugmug comments
$smugMugCommentSQL = "SELECT comment_url, author, created_at
                      FROM smugmug_comments
                      WHERE created_at > '$cutoffDate'
                      ORDER BY created_at DESC;";
$smugMugCommentResults = dbQuery($HISTORY_DATABASE, $smugMugCommentSQL);

if ($smugMugCommentResults) {
  $icon_map["icomment"] = '<span class="fa-layers fa-fw fa-2x mr-2"><i class="fas fa-square text-muted"></i><i class="fas fa-image fa-inverse" data-fa-transform="shrink-8"></i><i class="fas fa-comment" data-fa-transform="shrink-10 right-6 down-6"></i></span>';
  while($row = $smugMugCommentResults->fetch_assoc()) {
    $timestamp = $row["created_at"];
    $year = substr($timestamp, 0, 4);
    $month = substr($timestamp, 5, 2);
    $day = substr($timestamp, 8, 2);
    $hour = substr($timestamp, 11, 2);
    $minute = substr($timestamp, 14, 2);
    $second = substr($timestamp, 17, 2);
    $timestamp = gmmktime($hour, $minute, $second, $month, $day, $year);

    $nextItem = array(
      "timestamp" => $timestamp,
      "content" => $row["author"] . ' commented on <a target="_blank" href="' . $row["comment_url"] . '">an image</a>',
      "type" => "icomment"
    );
    array_push($commentitems, $nextItem);
  }
}
// smugmug images
$smugMugImageSQL = "SELECT gallery_url, gallery_name, count(photo_id) AS photo_count, MAX(created_at) AS created
                    FROM smugmug_uploads
                    WHERE created_at > '$cutoffDate'
                    GROUP BY gallery_url, gallery_name, gallery_slug
                    ORDER BY created DESC;";
$smugMugImageResults = dbQuery($HISTORY_DATABASE, $smugMugImageSQL);

if ($smugMugImageResults) {
  $icon_map["smugmug_img"] = '<span class="fa-layers fa-fw fa-2x mr-2"><i class="fas fa-square text-success"></i><i class="fas fa-image fa-inverse" data-fa-transform="shrink-8"></i></span>';
  while($row = $smugMugImageResults->fetch_assoc()) {
    $timestamp = $row["created"];
    $year = substr($timestamp, 0, 4);
    $month = substr($timestamp, 5, 2);
    $day = substr($timestamp, 8, 2);
    $hour = substr($timestamp, 11, 2);
    $minute = substr($timestamp, 14, 2);
    $second = substr($timestamp, 17, 2);
    $timestamp = gmmktime($hour, $minute, $second, $month, $day, $year);

    $count = ($row["photo_count"] >= 500) ? "500+" : $row["photo_count"];

    $nextItem = array(
      "timestamp" => $timestamp,
      "content" => 'Gallery <a target="_blank" href="' . $row["gallery_url"] . '">' . $row["gallery_name"] . '</a> has '
                   . $count . ' recent photos ',
      "type" => "smugmug_img"
    );
    array_push($items, $nextItem);
  }
}

// Now, take the max number of comments we want to see, and append them to the end of items.
uasort($commentitems, "timestamp_sort");
$items = array_merge($items, array_slice($commentitems, 0, $MAX_FEED_ITEMS_COMMENT));
?>

<?php if (count($newsitems) > 0) { ?>
  <section>
    <h2>Recent News</h2>
    <?php
      foreach ($newsitems as $item) {
        echo '<div class="media mb-3">' . $icon_map[$item['type']] . '<div class="media-body">' . $item['content'] . '<time class="d-block text-right text-muted" datetime="' . date(DATE_RFC3339, $item['timestamp']) . '">' . timeago($item['timestamp']) . '</time></div></div>';
      }
    ?>
  </section>
<?php } ?>

<section>
  <h2>Recent Activity</h2>
  <?php
    ##OVERALL DISPLAY##
    uasort($items, "timestamp_sort");
    $items = array_slice($items, 0, $MAX_FEED_ITEMS_ALL);
    foreach ($items as $item) {
      $media = $icon_map[$item['type']];
      if (isset($item['media'])) { $media = $item['media']; }
      echo '<div class="media mb-3">' . $media . '<div class="media-body">' . $item['content'] . '<time class="d-block text-right text-muted" datetime="' . date(DATE_RFC3339, $item['timestamp']) . '">' . timeago($item['timestamp']) . '</time></div></div>';
    }
  ?>
</section>
