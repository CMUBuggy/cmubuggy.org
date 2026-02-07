<?php
// This file performs the database queries to populate recent activity from
// various sources, including wordpress (news), and the smugmug activity feeds.
//
// It should only run once per page, make sure you include it using the include_once
// directive.  These next 2 lines will help you find the problem.
!defined('CONTENT_FEED_FETCHED') || die("Content feed already fetched.  Use include_once?");
define('CONTENT_FEED_FETCHED', true);

// Front Page Feed Limits:
// Total Items: 15 (on main page, this lines up nicely with the left nav)
// Comments: Only 7, regardless of source (avoid talkative photos).
// Smugmug Uploads: No more than 7 galleries (avoid bulk uplodes).
// Only back 90 days (keep us recent).
$MAX_FEED_ITEMS_COMMENT = 7;
$MAX_FEED_ITEMS_SMUGMUG = 7;
$MAX_FEED_ITEMS_ALL = 15;
$MAX_FEED_DAYS = 90;

// Disable the forum feed, since it is mostly spam.
$FORUM_FEED_ENABLED = false;

// set our cutoff time
$cutoff = time()-(60*60*24*$MAX_FEED_DAYS);
$cutoffDate = date("Y-m-d",$cutoff);

// Our various arrays to track our content.
$items = array();  // Output: All content feed items except recent news
$commentitems = array();  // Temporary: comment items to limit # of comments shown
$newsitems = array();  // Output: "Recent" news items
$icon_map = array();  // Output: code for icons used in content feed.

##NEWS ITEMS##
$newsSQL = "SELECT post_date,
                   post_name,
                   post_title,
                   post_excerpt,
                   post_content
  FROM wp_posts
  WHERE post_status LIKE 'publish'
  AND post_type LIKE 'post'
  and post_date > '$cutoffDate'
  ORDER BY post_date DESC
  LIMIT 0,15";

$newsResults = false;
try {
  $newsResults  = dbQuery("cmubuggy_wp",$newsSQL);
} catch (Exception $e) {
  // If there's an error (e.g. no wordpress in this database because it is a dev db),
  // then we just have no results.
}

$count = 1;
if ($newsResults) {
  $icon_map["news"] = '<span class="fa-layers fa-fw fa-2x"><i class="fas fa-square text-warning"></i><i class="fas fa-newspaper fa-inverse" data-fa-transform="shrink-8"></i></span>';
  while ($post = mysqli_fetch_row($newsResults)) {
    //date format: YYYY-MM-DD HH:MM:SS
    $timestamp = $post[0];
    $year = substr($timestamp, 0, 4);
    $month = substr($timestamp, 5, 2);
    $day = substr($timestamp, 8, 2);
    $hour = substr($timestamp, 11, 2);
    $minute = substr($timestamp, 14, 2);
    $second = substr($timestamp, 17, 2);
    $timestamp = mktime($hour, $minute, $second, $month, $day, $year);

    $excerpt = '';
    if (empty($post[3])) {
      // No provided summary.
      //
      // This is a bit hacky.  It is based on how WP generates excerpts when one
      // is not provided.  See wp-includes/formatting.php.
      //
      // However, we've simplified many of the more complex things that code deals with.
      // 
      // PHP excerpts are 55 words.
      $NUM_WORDS = 55;

      $text = strip_tags($post[4]);
      $words_array = preg_split( "/[\n\r\t ]+/", $text, $NUM_WORDS + 1, PREG_SPLIT_NO_EMPTY );
      $sep         = ' ';

      if (count($words_array) > $NUM_WORDS) {
        array_pop( $words_array );
        $text = implode( ' ', $words_array );
        $excerpt = $text . "...";
      } else {
        $excerpt = implode( ' ', $words_array );
      }
    } else {
      // Just use the provided summary
      $excerpt = $post[3];
    }

    $a = array(
      // These are used for rendering the sidebar
      "type" => "news",
      "timestamp" => $timestamp,
      "content" => '<a href="/news/'.$post[1].'">'.$post[2].'</a>',

      // These are used for rendering outside the sidebar.
      "rellink" => "/news/".$post[1],
      "title" => $post[2],
      "excerpt" => $excerpt
    );
    if ($count <= 2){
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

$forumResults = false;
if ($FORUM_FEED_ENABLED) {
  $forumResults = dbQuery("cmubuggy_phpBB",$forumSQL);
}

$forumClusterItems = array();

if ($forumResults) {
  $icon_map["forum"] = '<span class="fa-layers fa-fw fa-2x"><i class="fas fa-square text-muted"></i><i class="fas fa-comments fa-inverse" data-fa-transform="shrink-8"></i></span>';
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

$ncommentResults = false;
try {
  $ncommentResults = dbQuery("cmubuggy_wp",$ncommentSQL);
} catch (Exception $e) {
  // If there's an error (e.g. no wordpress in this database because it is a dev db),
  // then we just have no results.
}

$ncommentClusterItems = array();

if ($ncommentResults) {
  $icon_map["ncomment"] = '<span class="fa-layers fa-fw fa-2x"><i class="fas fa-square text-muted"></i><i class="fas fa-newspaper fa-inverse" data-fa-transform="shrink-8"></i><i class="fas fa-comment" data-fa-transform="shrink-10 right-6 down-6"></i></span>';
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
  $icon_map["icomment"] = '<span class="fa-layers fa-fw fa-2x"><i class="fas fa-square text-muted"></i><i class="fas fa-image fa-inverse" data-fa-transform="shrink-8"></i><i class="fas fa-comment" data-fa-transform="shrink-10 right-6 down-6"></i></span>';
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
                    ORDER BY created DESC
                    LIMIT $MAX_FEED_ITEMS_SMUGMUG;";
$smugMugImageResults = dbQuery($HISTORY_DATABASE, $smugMugImageSQL);

if ($smugMugImageResults) {
  $icon_map["smugmug_img"] = '<span class="fa-layers fa-fw fa-2x"><i class="fas fa-square text-success"></i><i class="fas fa-image fa-inverse" data-fa-transform="shrink-8"></i></span>';
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