	<!--CSS-->
	<link rel="stylesheet" type="text/css" href="/css/yui3.3-reset-fronts-grids.css" />	
	<link rel="stylesheet" type="text/css" href="/css/cmubuggy.css" />
	<link rel="stylesheet" type="text/css" href="/css/superfish-menu.css" />
	<link  href="http://fonts.googleapis.com/css?family=Lobster:regular" rel="stylesheet" type="text/css" >
	<!--<link  href="http://fonts.googleapis.com/css?family=Permanent+Marker:regular" rel="stylesheet" type="text/css" >-->



	<!--JS-->
	<!--<script type="text/javascript" src="/js/jquery.autocomplete.min.js" ></script>-->
	<!--<script type="text/javascript" src="/js/jquery.infieldlabel.min.js" ></script>-->
	<script type="text/javascript" src="/js/jquery.tools.min.js" ></script>
	<script type="text/javascript" src="/js/superfish-menu.js" ></script>
	<script type="text/javascript" src="http://www.google.com/recaptcha/api/js/recaptcha_ajax.js"></script>
	<script type="text/javascript">
		$(document).ready(function() {
			//superfish drop down menus		
			jQuery(function(){
				jQuery('ul.sf-menu').superfish();
			});
			
			//jquerytools overlays
			$("img[rel]").overlay({onClose: function(){}});

			//jquerytools tabs
			$(".tabs").tabs(".panes > div", {history:true});
			
			//jquerytools accordion
			//$("#accordion").tabs("#accordion div.pane", {tabs: 'h2', effect: 'slide', initialIndex: null});
		});
	</script>
	
	<!--Google analytics -->
	<script type="text/javascript">
	  var _gaq = _gaq || [];
	  _gaq.push(['_setAccount', 'UA-345857-14']);
	  _gaq.push(['_trackPageview']);
	
	  (function() {
	    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
	  })();
	</script>
