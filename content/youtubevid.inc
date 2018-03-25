<?php
if($video){
  $id=$video->youtubeID;

  //Check for cached youtube thumb, if found use, if not found get and save
  if(file_exists("content/cache/youtube/vidthumb-".$id.".jpg")){
    $thumbsrc = "/content/cache/youtube/vidthumb-".$id.".jpg";
  } else {
    $thumbsrc = "https://i4.ytimg.com/vi/".$id."/default.jpg";
    if (file_exists("content/cachce/youtube/")) {
      $thumb = file_get_contents("https://i4.ytimg.com/vi/".$id."/default.jpg");
      file_put_contents("content/cache/youtube/vidthumb-".$id.".jpg", $thumb);
    }
  }

  if(!isset($vidmode)){ $vidmode = "popup"; }

  switch($vidmode) {
    case "imagelink":
      echo("<div class=\"vidlink\">");
      echo("<a href=\"/video/".$video->urlkey."\"><img class=\"vidthumb\" alt=\"".$video->title."\" width=\"120px\" height=\"90px\" src=\"".$thumbsrc."\"/></a>");
      echo($video->title."</div>");
      break;
    case "popup":
    ?>
      <button type="button" class="btn btn-link p-0" data-toggle="modal" data-target="#youtube-<?php echo $id; ?>"><img alt="<?php echo($video->title); ?>" title="<?php echo($video->title); ?>" width="120px" height="90px" src="<?php echo($thumbsrc); ?>"></button>
      <div id="youtube-<?php echo $id; ?>" class="modal fade" tabindex="-1" role="dialog" aria-labelledby="#title-<?php echo $id; ?>" aria-hidden="true">
        <div class="modal-dialog modal-dialog-centered" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="title-<?php echo $id; ?>"><?php echo $video->title; ?></h5>
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
      break;
    case "embed":
    ?>
      <object style="height: 390px; width: 640px">
        <param name="movie" value="https://www.youtube.com/v/u1zgFlCw8Aw?version=3">
        <param name="allowFullScreen" value="true">
        <param name="allowScriptAccess" value="always">
        <embed src="https://www.youtube.com/v/<?php echo($id); ?>?version=3&enablejsapi=1" type="application/x-shockwave-flash" allowfullscreen="true" allowScriptAccess="always" width="750" height="525">
      </object>
    <?php
    break;
  }
}

?>
