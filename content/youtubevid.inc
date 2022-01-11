<?php
// Expects $video to be an associative array with ["youtubeid"] and ["title"] set
// Also, optionally set "nothumbnail" to an alt string to display to get a link without an image thumbnail.
if($video){
  $id=$video["youtubeid"];
  $showthumbnail = empty($video["nothumbnail"]);

  // TODO: It is unclear to me why we cache these.  Youtube has way more serving capacity than we do.
  //
  // Check for cached youtube thumb, if found use, if not found get and save
  if($showthumbnail) {
    if(file_exists("content/cache/youtube/vidthumb-".$id.".jpg")){
      $thumbsrc = "/content/cache/youtube/vidthumb-".$id.".jpg";
    } else {
      $thumbsrc = "https://i4.ytimg.com/vi/".$id."/default.jpg";
      if (file_exists("content/cachce/youtube/")) {
        $thumb = file_get_contents("https://i4.ytimg.com/vi/".$id."/default.jpg");
        file_put_contents("content/cache/youtube/vidthumb-".$id.".jpg", $thumb);
      }
    }
  }

  // We always show popup-style videos, but we need to choose if the activation button is a link or an image.
  ?>
  <button type="button" class="btn btn-link p-0" data-toggle="modal" data-target="#youtube-<?php echo $id; ?>">
  <?php
  if($showthumbnail) {
  ?>
    <img alt="<?php echo($video["title"]); ?>" title="<?php echo($video["title"]); ?>" width="120px" height="90px" src="<?php echo($thumbsrc); ?>">
  <?php
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
            <div id="player-<?php echo $id; ?>" data-video-id="<?php echo $id; ?>" class="embed-responsive-item"></div>
          </div>
        </div>
      </div>
    </div>
  </div>

<?php
}
?>
