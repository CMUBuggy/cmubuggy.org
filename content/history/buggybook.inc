<h1>Buggy Books</h1>

<div class="d-flex flex-wrap justify-content-between" style="margin: -.25em;">
<?php
for($year=1965;$year<2020;$year++){
  echo("<a href=\"/files/buggybooks/buggybook_".$year.".pdf\" class=\"m-1\"
        target=\"_blank\" onclick=\"_gaq.push(['_trackEvent','Download','PDF',this.href]);\">
      <img alt=\"".$year." buggy book\"
          title=\"Download a PDF of the ".$year." buggy book\"
          class=\"img-thumbnail\" style=\"max-height: 200px;\"
          src=\"/files/buggybooks/thumb_200/buggybook_".$year.".pdf.jpg\" />
      </a>");
}
?>
</div>
