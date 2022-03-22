<?php
// Helper to generate open graph metadata for certain history pages.

function getHistoryOpenGraphContent() {
  $historyPage = $_GET['p'];

  if (!in_array($historyPage, ['buggy', 'org']) || empty($_GET["urlkey"])) {
    // Either we don't know how to handle this page, or we don't have a paremeter.
    // Either way, No OG data.
    return "";
  }

  $urlKey = $_GET["urlkey"];
  $url = "https://cmubuggy.org/history/".$historyPage."/".$urlKey."/";

  $OUTPUT = "<!-- OpenGraph Metadata -->\n"
          . "<meta property=\"og:type\" content= \"website\" />\n"
          . "<meta property=\"og:site_name\" content=\"CMU Buggy Alumni Association\" />\n"
          . "<meta property=\"og:url\" content=\"".$url."\" />\n";

  return $OUTPUT;
}

//<meta property="og:type" content= "website" />
//<meta property="og:site_name" content="Stack Overflow" />
//<meta property="og:url" content="https://stackoverflow.com/questions/59100553/link-description-of-wordpress-site-on-discord"/>

//<meta property="og:image" itemprop="image primaryImageOfPage" content="https://cdn.sstatic.net/Sites/stackoverflow/Img/apple-touch-icon@2.png?v=73d79a89bded" />

?>