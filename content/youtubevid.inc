<?php
if($video){
	$id=$video->youtubeID;

	//Check for cached youtube thumb, if found use, if not found get and save
	if(file_exists("content/cache/youtube/vidthumb-".$id.".jpg")){
		$thumbsrc = "/content/cache/youtube/vidthumb-".$id.".jpg";
	} else {
		$thumbsrc = "https://i4.ytimg.com/vi/".$id."/default.jpg";
		$thumb = file_get_contents("https://i4.ytimg.com/vi/".$id."/default.jpg");
		file_put_contents("content/cache/youtube/vidthumb-".$id.".jpg", $thumb);
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
			<img class=\"vidthumb\" alt="<? echo($video->title); ?>" title="<? echo($video->title); ?>" width="120px" height="90px" src="<?php echo($thumbsrc); ?>" rel="#<?php echo($id); ?>"/>
			<div class="overlay" id="<?php echo($id); ?>">
				<object style="height: 390px; width: 640px">
					<param name="movie" value="https://www.youtube.com/v/u1zgFlCw8Aw?version=3">
					<param name="allowFullScreen" value="true">
					<param name="allowScriptAccess" value="always">
					<embed src="https://www.youtube.com/v/<?php echo($id); ?>?version=3&enablejsapi=1" type="application/x-shockwave-flash" allowfullscreen="true" allowScriptAccess="always" width="750" height="525">
				</object>
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
