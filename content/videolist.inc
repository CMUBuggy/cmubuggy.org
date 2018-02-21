<div class="pane">
	<div style="float:right; text-align:center; margin-left:10px; font-style: italic;">In partnership with<br/><a href="http://cmutv.org"><img width="125" height="125" src="/img/orglogos/cmutv.png" /></a></div>
	Pictures are worth 1000 words, but videos are worth 30 pictures per second.  Some videos in our library are taken and contributed by individuals, but the majority are the fine work of <a href="http://cmutv.org">cmuTV</a>, the student organization that covers the races.<br />
	<br />
	We have partnered with <a href="http://cmutv.org">cmuTV</a> to put these videos online so they may reach the widest audience, but cmuTV also sells DVDs of the races each year to help defray the enormous cost of production.  We don't want to undercut that, so each year's videos will be avaiable exclusively on DVD for 1 year.  Each April we'll add the previous year's races here to the permanent archive.<br />
	<br />
	If you have videos that aren't currently in our collection, contact admin@cmubuggy.org to share them.
</div>
<div id="accordion">

<?php
$videogroup = new videogroup();
$videogrouplist = $videogroup->GetList(null,"displayordinal");
$vidmode = "imagelink";

$tabcount = 1;
echo("<ul class=\"tabs\">");
foreach($videogrouplist as $videogroup){
	$videolist = $videogroup->GetVideoList(null,"videoId");
	if(count($videolist)>0){
		echo("<li><a id=\"t".$tabcount."\" href=\"#".$videogroup->description."\">".$videogroup->description."</a></li>");
		$tabcount++;
	}
}

echo("</ul>");
echo("<div class=\"panes\">");
foreach($videogrouplist as $videogroup){
	$videolist = $videogroup->GetVideoList(null,"videoId");
	if(count($videolist)>0){
		echo("<div class=\"pane\">");
		foreach($videolist as $video){
			include("youtubevid.inc");
		}
		echo("</div>");
	}
}
echo("</div>");

?>
</div>
