<?php
$items = array();
$newsitems = array();
//only look for items from the last 90 days
$cutoff = time()-(60*60*24*90);
$cutoffDate = date("Y-m-d",$cutoff);
$cutoffWiki = date("Ymd",$cutoff)."000000";
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
    array_push($items,$a);
  }
}

##REFERENCE ITEMS##
$referenceSQL = "SELECT revision.rev_id,revision.rev_timestamp,user.user_name, page.page_title, revision.rev_page
  FROM revision
  JOIN user
  ON revision.rev_user=user.user_id
  JOIN page
  ON revision.rev_page=page.page_id
  WHERE rev_minor_edit=0
  AND page.page_namespace=0
  and rev_timestamp > $cutoffWiki
  ORDER BY rev_timestamp DESC";
$referenceResults = dbQuery("cmubuggy_wiki",$referenceSQL);

$referenceClusterItems = array();

if ($referenceResults) {
  $icon_map["reference"] = '<span class="fa-layers fa-fw fa-2x mr-2"><i class="fas fa-square text-muted"></i><i class="fas fa-info fa-inverse" data-fa-transform="shrink-8"></i></span>';
  while ($post = mysqli_fetch_row($referenceResults)) {
    $timestamp = $post[1];
    $year = substr($timestamp, 0, 4);
    $month = substr($timestamp, 4, 2);
    $day = substr($timestamp, 6, 2);
    $hour = substr($timestamp, 8, 2);
    $minute = substr($timestamp, 10, 2);
    $second = substr($timestamp, 12, 2);
    $timestamp = mktime($hour, $minute, $second, $month, $day, $year)+$UTCdiff;

    $href = "/reference/".$post[3];
    $clusterKey = $post[4].$year.$month.$day;
    if (array_key_exists($clusterKey, $referenceClusterItems)) {
      $referenceClusterItems[$clusterKey]["count"]++;
      $referenceClusterItems[$clusterKey]["content"] = $referenceClusterItems[$clusterKey]["count"] . ' changes to <a href="' . $href . '">' . str_replace("_"," ",$post[3]) . '</a>';
    } else {
      $referenceClusterItems[$clusterKey] = array(
        "timestamp"=>$timestamp,
        "count"=>1,
        "content"=>$post[2] . ' edited <a href="' . $href . '">' . str_replace("_"," ",$post[3]) . '</a>',
        "type"=>"reference"
      );
    }
  }
  foreach ($referenceClusterItems as $a) {
    array_push($items,$a);
  }
}
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
    $items = array_slice($items, 0, 150);
    foreach ($items as $item) {
      $media = $icon_map[$item['type']];
      if (isset($item['media'])) { $media = $item['media']; }
      echo '<div class="media mb-3">' . $media . '<div class="media-body">' . $item['content'] . '<time class="d-block text-right text-muted" datetime="' . date(DATE_RFC3339, $item['timestamp']) . '">' . timeago($item['timestamp']) . '</time></div></div>';
    }
  ?>
</section>
