<h1>TV Leaderboard Index</h1>
<ul>
<script>
   function dopopup(type) {
      window.open("/content/tv/tvlb-view.html?t="+type, "leaderboardview", "popup=true,width=960,height=540");
   }
   ['womens_prelims', 'mens_prelims', 'allgender_prelims',
    'womens_finals', 'mens_finals', 'allgender_finals',
    'exhibitions'].forEach(function(type) {
        document.write("<li><a href=\"#\" onclick=\"dopopup(&quot;" + type + "&quot;)\">" + type + "</a></li>");
   });
</script>
</ul>