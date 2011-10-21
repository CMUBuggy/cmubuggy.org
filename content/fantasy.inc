<div id="topnav">
	<ul class="sf-menu">
		<li><a href="/fantasy">Instructions</a></li>
		<li><a href="/fantasy/stats">Stats / Background Info</a></li>
		<li><a href="/fantasy/enter">Submit an Entry</a></li>
		<li><a href="/fantasy/results">Results</a></li>
	</ul>
</div>

<div class="pane">
	<table summary="">
		<tr>
			<td><img src="/img/fantasy_buggy_promo.png" alt="" height="175px" ></td>
			<td style="vertical-align:center; padding-left:10px;">
				<a href="http://numberfire.com"  target="_blank" onclick="_gaq.push(['_trackEvent','Outbound','numberFire',this.href]);" style="float:left;" >
					<img src="/img/nF_sponsor.png" alt="" height="155px" style="margin:0 18px;" >
				</a>
				numberFire is a CMU-style, stats-driven fantasy football oracle founded by buggy alum and cmubuggy.org regular Nik Bonaddio. nF is sponsoring the prize in our first ever fantasy buggy game. Check them out, the numbers are good.				
			</td>
		</tr>
	</table>

<?php
	$page = "default";
	if(isset($_GET['p'])){
  		$page = $_GET['p'];
  	}
  	include_once("content/fantasy/".$page.".inc");
?>
</div>