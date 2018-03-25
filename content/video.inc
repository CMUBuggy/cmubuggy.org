<?php
  $video = new video();
  if (!empty($_GET["urlkey"])) {
    $videoList = $video->GetList(array(array("urlkey","=",$_GET["urlkey"])));
    if ($videoList) {
      $video = $videoList[0];
    }
  }

  if ($video) {
    echo("<h1>".$video->title."</h1>");
    $vidmode = "embed";
    include("youtubevid.inc");
  } else {
    echo("No video found");
  }
?>
