<h1>TV Leaderboard Index</h1>
<ul>
<script>
   ['womens_prelims', 'mens_prelims', 'allgender_prelims',
    'womens_finals', 'mens_finals', 'allgender_finals',
    'exhibitions'].forEach(function(type) {
        document.write("<li><a href=\"/content/tv/tvlb-view.html?t=" + type + "\">" + type + "</a></li>");
   });
</script>
</ul>