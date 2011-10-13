<?php

	#This script is designed to be run periodically via a cron job to check for new content from reddit.com/r/cmubuggy
	#These cached files in /content/cache/reddit/ are used by /content/contendfeed.inc
	#If running properly, contentfeed.inc should never have to request the source files from reddit which can really slow down page loads
	
	#initial cronjob settings are:
	#*/10 * * * * php /var/www/cmubuggy.org/scripts/update_reddit_cache.php



	$posts = file_get_contents("http://www.reddit.com/r/cmubuggy/new.json?sort=new");
	file_put_contents(dirname(__file__)."/../content/cache/reddit/reddit.json",$posts);
	
	$comments = file_get_contents("http://www.reddit.com/r/cmubuggy/comments.json");
	file_put_contents(dirname(__file__)."/../content/cache/reddit/reddit.comments.json",$comments);
	
?>