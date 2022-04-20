<?php
// Expects $video to be an associative array with ["youtubeid"] and ["title"] set
// Also, optionally set "nothumbnail" to an alt string to display to get a link without an image thumbnail.
// Also, optionally set "start" and "end" with the number of seconds from start of video to start and
//       end at.
if($video){
  $id=$video["youtubeid"];
  $showthumbnail = empty($video["nothumbnail"]);

  $dataVideoStart = "";
  if (!empty($video["start"])) {
    $dataVideoStart = " data-video-start=\"".$video["start"]."\"";
  }
  $dataVideoEnd = "";
  if (!empty($video["end"])) {
    $dataVideoEnd = " data-video-end=\"".$video["end"]."\"";
  }
?>

  <button type="button" class="btn btn-link p-0" data-toggle="modal" data-target="#youtube-<?php echo $id; ?>">
  <?php
    if($showthumbnail) {
      $title = $video["title"];
      $thumbsrc = "https://i4.ytimg.com/vi/".$id."/default.jpg";
      echo("<img alt=\"".$title."\" title=\"".$title."\" width=\"120px\" height=\"90px\" src=\"".$thumbsrc."\">");
    } else {
      echo($video["nothumbnail"]);
    }
  ?>
  </button>

  <div id="youtube-<?php echo $id; ?>" class="modal fade" tabindex="-1" role="dialog" aria-labelledby="#title-<?php echo $id; ?>" aria-hidden="true">
    <div class="modal-dialog modal-dialog-centered modal-lg" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <h5 class="modal-title" id="title-<?php echo $id; ?>"><?php echo $video["title"]; ?></h5>
          <button type="button" class="close" data-dismiss="modal" aria-label="close"><span aria-hidden="true">&times;</span></button>
        </div>
        <div class="modal-body">
          <div class="embed-responsive embed-responsive-16by9">
            <div id="player-<?php echo $id; ?>" data-video-id="<?php echo $id; ?>"<?php echo $dataVideoStart.$dataVideoEnd; ?> class="embed-responsive-item"></div>
          </div>
        </div>
      </div>
    </div>
  </div>

<?php
}
?>
