<h1>Videos</h1>

<figure class="figure float-right mb-2 ml-2">
  <figcaption class="figure-caption text-center">In partnership with</figcaption>
  <a href="http://cmutv.org" class="figure-img"><img width="125" height="125" src="/img/orglogos/cmutv.png" /></a>
</figure>

<p>Pictures are worth 1000 words, but videos are worth 30 pictures per second. Some videos in our library are taken and contributed by individuals, but the majority are the fine work of <a href="http://cmutv.org">cmuTV</a>, the student organization that covers the races.</p>

<p>We have partnered with <a href="http://cmutv.org">cmuTV</a> to put these videos online so they may reach the widest audience, but cmuTV also sells DVDs of the races each year to help defray the enormous cost of production. We don't want to undercut that, so each year's videos will be avaiable exclusively on DVD for 1 year. Each April we'll add the previous year's races here to the permanent archive.</p>

<p>If you have videos that aren't currently in our collection, contact <a href="mailto:admin@cmubuggy.org">admin@cmubuggy.org</a> to share them.</p>

<?php
  $videogroup = new videogroup();
  $videogrouplist = $videogroup->GetList(null,"displayordinal");
  $vidmode = "imagelink";
?>
<ul class="nav nav-tabs mb-2" role="tablist">
  <?php
    $tabcount = 1;
    foreach ($videogrouplist as $videogroup) {
      $videolist = $videogroup->GetVideoList(null,"videoId");
      if (count($videolist) > 0) {
        $tabname = "t".$tabcount;
        $active = $tabcount == 1;
  ?>
    <li class="nav-item">
      <a id="<?php echo $tabname; ?>-tab" href="#tab-<?php echo $tabname; ?>" class="nav-link<?php if ($active) { echo(" active"); }?>" data-toggle="tab" aria-controls="tab-<?php echo $tabname; ?>" aria-selected="<?php echo($active ? "true" : "false"); ?>"><?php echo($videogroup->description); ?></a>
    </li>
  <?php
        $tabcount++;
      }
    }
  ?>
</ul>

<div class="tab-content">
  <?php
    $tabcount = 1;
    foreach ($videogrouplist as $videogroup) {
      $videolist = $videogroup->GetVideoList(null,"videoId");
      if (count($videolist) > 0) {
        $tabname = "t".$tabcount;
        $tabclasses = $tabcount == 1 ? ' show active' : '';
        echo('<div class="tab-pane fade'.$tabclasses.'" id="tab-'.$tabname.'" role="tabpanel" aria-labelledby="'.$tabname.'-tab"><div class="video-grid d-flex flex-wrap justify-content-between">');
        foreach ($videolist as $video) {
          include("youtubevid.inc");
        }
        echo("</div></div>");
        $tabcount++;
      }
    }
  ?>
</div>
