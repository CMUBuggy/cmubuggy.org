<?php
	$pics = array(
		array("tx1930s.jpg","Theta Xi buggy and driver in 1939 submitted by another alum, his grandson"),	
		array("course.png","Arial view of the entire buggy course"),
		array("bedlam.jpg","Fringe's Bedlam rolls in the spring of 2010"),
		array("pikasigepwomen2009.jpg","PiKA and SigEp's Women's A teams in 2009"),
		array("4-5silhouette.jpg","Spring freeroll practice 2009"),
		array("ATO_Andy2_1963.jpg","ATO's \"Andy 2\" at the start in 1963"),
		array("leroystart1970.jpg","Fringe's open-air Leroy at the start around 1970"),
		array("pikakdrh2.jpg","PiKA and KDR both shove at the end of hill 2 on raceday 2002"),
		array("spirith22011.jpg","Spirit A's all-out hill 2 shove on raceday 2011"),
		array("finishline.jpg","2010 PiKA B, as captured by the new BAA-financed and operated timing system")
	);
	
	shuffle($pics);
	$pics = array_slice($pics, 0, 5);

?>

<div id="featurepic" class="scroll shadow">
	<div class="scrollitems">
		<div class="item">
			<?php include_once("twitterwidget.inc"); ?>
		</div>
		<?php
			if(file_exists("img/featurepics/promo.jpg")){
				echo("<div class=\"item\" style=\"background-image:url(/img/featurepics/promo.jpg)\"></div>");
			}
			foreach($pics as $pic){
				echo("<div class=\"item\" style=\"background-image:url(/img/featurepics/".$pic[0].")\"><div class=\"caption hidden\">".$pic[1]."</div></div>");
			}
		?>
	</div>
</div>	

<script type="text/javascript">
	$("#featurepic").scrollable({ circular: true, easing:"swing", speed:1250 }).click(function() {
		$(this).data("scrollable").next();		
	}).autoscroll({autoplay:true,interval:10000});
	
	$("#featurepic .item").hover(
      function () {
        $("#featurepic .caption").fadeIn(100);
      }, 
      function () {
        $("#featurepic .caption").fadeOut(500);
      }
    );
</script>