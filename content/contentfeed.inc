<?php
$items = array();
$newsitems = array();
//only look for items from the last 10 days
$cutoff = time()-(60*60*24*10);
$cutoffDate = date("Y-m-d",$cutoff);
$cutoffWiki = date("Ymd",$cutoff)."000000";

##NEWS ITEMS##
$newsSQL = "SELECT wp_posts.ID,wp_posts.post_date,wp_users.display_name,wp_posts.post_name,wp_posts.post_title,wp_posts.comment_count
  FROM wp_posts
  JOIN wp_users
  ON wp_posts.post_author=wp_users.ID
  WHERE post_status LIKE 'publish'
  AND post_type LIKE 'post'
  ORDER BY post_date DESC
  LIMIT 0,15";
$newsResults  = dbQuery("cmubuggy_wp",$newsSQL);

$count = 1;
if ($newsResults){
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
    $href = "/news/".$post[3];
    $content = "<a href=\"/news/".$post[3]."\">".$post[4]."</a>";

    $a = array(
      "timestamp"=>$timestamp,
      "content"=>"<a href=\"".$href."\"><div class=\"icon newsicon\"><img src=\"/img/icon_news.png\" /></div></a><a href=\"".$href."\">".$post[4]."</a>",
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

$galleryParents = array();

##GALLERY ITEMS##
$gallerySQL = "SELECT items.id, items.created, users.name, items.name, items.relative_url_cache, items.parent_id, items.relative_path_cache
  FROM items
  JOIN users
  ON items.owner_id=users.id
  WHERE type LIKE 'photo'
  ORDER BY created DESC
  LIMIT 0,100";
$galleryResults = dbQuery("cmubuggy_g3",$gallerySQL);

$galleryClusterItems = array();

if ($galleryResults) {
  while ($post = mysqli_fetch_row($galleryResults)) {
    $clusterKey = $post[2].$post[5];
    $parent_id = $post[5];
    if (array_key_exists($clusterKey, $galleryClusterItems)) {
      $galleryClusterItems[$clusterKey]["count"]++;
      if (!array_key_exists($parent_id, $galleryParents)) {
        $parentSQL = "SELECT album.title, album.relative_url_cache, cover.relative_path_cache
          FROM items album
          LEFT OUTER JOIN items cover
          ON album.album_cover_item_id = cover.id
          WHERE album.id =".$parent_id;
        $parentResults = dbQuery("cmubuggy_g3",$parentSQL);
        while ($parent = mysqli_fetch_row($parentResults)) {
          $galleryParents[$parent_id]= array("title"=>$parent[0], "relative_url_cache"=>$parent[1], "thumburl"=>"/gallery/var/thumbs/".$parent[2]);
        }
      }
      $href = "/gallery/".$galleryParents[$parent_id]["relative_url_cache"];
      $galleryClusterItems[$clusterKey]["content"] = "<a href=\"".$href."\"><div class=\"icon galleryicon\" style=\"background-image:url('".$galleryParents[$parent_id]["thumburl"]."')\"></div></a>".$post[2]." uploaded ".$galleryClusterItems[$clusterKey]["count"]." pics to <a href=\"".$href."\">".$galleryParents[$parent_id]["title"]."</a>";
    } else {
      $href = "/gallery/".$post[4];
      $galleryClusterItems[$clusterKey] = array(
        "timestamp"=>$post[1],
        "count"=>1,
        "content" =>"<a href=\"".$href."\"><div class=\"icon galleryicon\" style=\"background-image:url('/gallery/var/thumbs/".$post[6]."')\"></div></a>".$post[2]." uploaded<br /><a href=\"".$href."\">".$post[3]."</a>",
        "type"=>"gallery"
      );
    }
  }
  foreach ($galleryClusterItems as $a) {
    array_push($items,$a);
  }
}

##phpBB FORUM ITEMS##
$forumSQL = "SELECT posts.post_id, posts.post_time, users.username, topics.topic_title, posts.topic_id
  FROM posts
  JOIN users
  ON posts.poster_id=users.user_id
  JOIN topics
  ON posts.topic_id=topics.topic_id
  ORDER BY post_time DESC";
$forumResults = dbQuery("cmubuggy_phpBB",$forumSQL);

$forumClusterItems = array();

if ($forumResults) {
  while ($post = mysqli_fetch_row($forumResults)) {
    $clusterKey = $post[4].date("md",$post[1]);
    $threadtitle = $post[3];
    if (strlen($threadtitle) > 25) { $threadtitle = substr($threadtitle, 0, 23)."..."; }
    $href = "/forum/viewtopic.php?f=3&t=".$post[4]."&p=".$post[0]."#p".$post[0];
    if (array_key_exists($clusterKey, $forumClusterItems)) {
      $forumClusterItems[$clusterKey]["count"]++;
      $forumClusterItems[$clusterKey]["content"] = "<a href=\"".$href."\"><div class=\"icon forumicon\">Forum<img src=\"/img/icon_forum.png\" /></div></a>".$forumClusterItems[$clusterKey]["count"]." new posts in the thread <br /><a href=\"".$href."\">".$threadtitle."</a>.";
      $forumClusterItems[$clusterKey]["person"] = "people";
    } else {
      $username = $post[2];
      if (strlen($username) > 16) { $username = substr($username, 0, 16)."..."; }
      $forumClusterItems[$clusterKey] = array(
        "timestamp"=>$post[1],
        "count"=>1,
        "content" => "<a href=\"".$href."\"><div class=\"icon forumicon\">Forum<img src=\"/img/icon_forum.png\" /></div></a>".$post[2]." posted in<br /><a href=\"".$href."\">".$threadtitle."</a>",
        "type"=>"forum"
      );
    }
  }
  foreach ($forumClusterItems as $a) {
    array_push($items,$a);
  }
}

##GALLERY COMMENTS##
$gcommentSQL = "SELECT comments.id,comments.created,users.name,items.relative_path_cache,comments.text,items.title,items.relative_url_cache, comments.guest_name
  FROM comments
  JOIN users
  ON comments.author_id=users.id
  JOIN items
  ON comments.item_id=items.id
  WHERE comments.state LIKE 'published'
  ORDER BY comments.created DESC";
$gcommentResults = dbQuery("cmubuggy_g3",$gcommentSQL);

$gcommentClusterItems = array();

if ($gcommentResults) {
  while ($post = mysqli_fetch_row($gcommentResults)) {
    $parent_id = $post[5];
    $commentDate = date("md",$post[1]);
    $clusterKey = $parent_id.$commentDate;
    $commenttext = $post[5];
    $username = $post[2];
    if ($username == "guest" && !is_null($post[7])) {
      $username = $post[7];
    }
    $href = "/gallery/".$post[6]."#comments";
    $thumburl = "/gallery/var/thumbs/".$post[3];
    if (strlen($commenttext) > 29) { $commenttext = substr($commenttext, 0, 26)."..."; }
    if (array_key_exists($clusterKey, $gcommentClusterItems)) {
      $gcommentClusterItems[$clusterKey]["count"]++;
      $gcommentClusterItems[$clusterKey]["content"] = "<a href=\"".$href."\"><div class=\"icon galleryicon\" style=\"background-image:url('".$thumburl."')\"><img src=\"/img/icon_comment.png\" /></div></a>".$gcommentClusterItems[$clusterKey]["count"]." new comments on <br /><a href=\"".$href."\">".$post[5]."</a>";
    } else {
      $gcommentClusterItems[$clusterKey] = array(
        "timestamp"=>$post[1],
        "count"=>1,
        "content" => "<a href=\"".$href."\"><div class=\"icon galleryicon\" style=\"background-image:url('".$thumburl."')\"><img src=\"/img/icon_comment.png\" /></div></a>".$username." commented on <br /><a href=\"".$href."\">".$commenttext."</a>",
        "type"=>"gcomment"
      );
    }
  }
  foreach ($gcommentClusterItems as $a) {
    array_push($items,$a);
  }
}


##NEWS COMMENTS##
$ncommentSQL = "SELECT wp_comments.comment_ID, wp_comments.comment_date, wp_comments.comment_author, wp_comments.comment_content, wp_comments.comment_post_ID, wp_posts.post_name, wp_posts.post_title
  FROM wp_comments
  JOIN wp_posts
  ON wp_comments.comment_post_ID=wp_posts.ID
  WHERE wp_comments.comment_approved = 1
  ORDER BY wp_comments.comment_date DESC";
$ncommentResults = dbQuery("cmubuggy_wp",$ncommentSQL);

$ncommentClusterItems = array();

if ($ncommentResults) {
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
    $commenttext = $post[3];
    if (strlen($commenttext) > 29) { $commenttext = substr($commenttext, 0, 26)."..."; }
    $title = $post[6];
    if (strlen($title) > 29) {$title = substr($title, 0, 26)."..."; }
    $commenter = $post[2];
    if (strlen($commenter) == 0) { $commenter = "Anonymous"; }
    $href = "/news/".$post[5]."#comments";
    if (array_key_exists($clusterKey, $ncommentClusterItems)) {
      $ncommentClusterItems[$clusterKey]["count"]++;
      $ncommentClusterItems[$clusterKey]["content"] = "<a href=\"".$href."\"><div class=\"icon newscommenticon\"><img class=\"commenticon\" src=\"/img/icon_comment.png\" /><img src=\"/img/icon_news.png\" /></div></a>".$ncommentClusterItems[$clusterKey]["count"]." new comments on <br /><a href=\"".$href."\">".$title."</a>";
    } else {
      $ncommentClusterItems[$clusterKey] = array(
        "timestamp"=>$timestamp,
        "count"=>1,
        "content" => "<a href=\"".$href."\"><div class=\"icon newscommenticon\"><img class=\"commenticon\" src=\"/img/icon_comment.png\" /><img src=\"/img/icon_news.png\" /></div></a>".$commenter." commented on<br /><a href=\"".$href."\">".$title."</a>",
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
  ORDER BY rev_timestamp DESC";
$referenceResults = dbQuery("cmubuggy_wiki",$referenceSQL);

$referenceClusterItems = array();

if ($referenceResults) {
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
      $referenceClusterItems[$clusterKey]["content"] = "<a href=\"".$href."\"><div class=\"icon referenceicon\">Reference<img src=\"img/icon_book.png\" /></div></a>".$referenceClusterItems[$clusterKey]["count"]." changes to<br /><a href=\"".$href."\">".str_replace("_"," ",$post[3])."</a>";
    } else {
      $referenceClusterItems[$clusterKey] = array(
        "timestamp"=>$timestamp,
        "count"=>1,
        "content"=>"<a href=\"".$href."\"><div class=\"icon referenceicon\">Reference<img src=\"img/icon_book.png\" /></div></a>".$post[2]." edited<br /><a href=\"".$href."\">".str_replace("_"," ",$post[3])."</a>",
        "type"=>"reference"
      );
    }
  }
  foreach ($referenceClusterItems as $a) {
    array_push($items,$a);
  }
}
?>
<div id="contentfeed">
  <h3>Recent News</h3>
  <div id="recentnews">
    <?php
    foreach ($newsitems as $item) {
      if ($item['type'] == "news") { $typeclass = "newsitem"; }
      echo("<div class=\"item ".$typeclass."\">".$item['content']."<div class=\"detail\">".timeago($item['timestamp'])."</div></div>");
    }
    ?>
  </div>
  <h3 id="recentactivityh3">Recent Activity</h3>
  <div id="recentactivity">
    <div class="items">
        <?php
        ##OVERALL DISPLAY##
        uasort($items, "timestamp_sort");
        $items = array_slice($items, 0, 150);
        $itemcount = 0;
        echo("<div>");
        foreach ($items as $item) {
          if ($itemcount < 8) {
            echo("<div class=\"item\">".$item['content']."<div class=\"detail\">".timeago($item['timestamp'])."</div></div>");
            $itemcount++;
          } else {
            $itemcount = 0;
            echo("</div><div>");
          }
        }
        echo("</div>");

        ?>
    </div>
  </div>
  <div class="actions">
    <a class="feedprev">&laquo; Back</a>
    <a class="feednext">More &raquo;</a>
  </div>
</div>
<script type="text/javascript">
  $(function() {
    $("#recentactivity").scrollable({ vertical: true, speed:700, next:".feednext", prev:".feedprev" });
  });
</script>
