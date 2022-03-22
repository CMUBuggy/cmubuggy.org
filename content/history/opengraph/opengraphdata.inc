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

  // TODO: Several of these extra bits require a database query, which sucks, since when the history code
  // itself runs we'll likely be grabbing the same information again.  For now, keep the queries simple and
  // just be sad about it.  Long term, it'd be good to be able to know we're about to render a history page and
  // gather this stuff as we go.

  switch($historyPage) {
    case "buggy":
      $OUTPUT .= getBuggyExtraData($urlKey);
      break;
    case "org":
      $OUTPUT .= getOrgExtraData($urlKey);
      break;
    default:
      die("unknown page for opengraph"); // er. what?  we checked for this above.
  };

  return $OUTPUT;
}

function getOrgExtraData($orgUrlKey) {
  global $HISTORY_DATABASE;

  $metaDataQuery = "SELECT shortname, orglogos.image_url AS image_url
                    FROM hist_orgs o
                    LEFT JOIN orglogos ON o.orgid = orglogos.orgid
                    WHERE o.orgid=?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $orgUrlKey);

  if ($metaData->num_rows == 1) {
    $org = $metaData->fetch_assoc();
    $ret = "<meta property=\"og:title\" content=\"History | Org: ".$org["shortname"]."\" />\n";
    if(!empty($org["image_url"])) {
      // So, OpenGraph requires absolute URLs, but we tend to use relative URLs in this table.
      // If the url starts with a slash, append https://cmubuggy.org to the front.
      //
      // Gross.
      $image_url = $org["image_url"];
      if ($image_url[0] == "/") {
          $image_url = "https://cmubuggy.org" . $image_url;
      }
      $ret .= "<meta property=\"og:image\" content=\"".$image_url."\" />\n";
    }
    return $ret;
  }

  // If we do not have this org, we actually don't care that much, but we should be reasonable if we can.
  return "<meta property=\"og:title\" content=\"History | Unknown Buggy\" />\n";
}

function getBuggyExtraData($buggyUrlKey) {
  global $HISTORY_DATABASE;

  $metaDataQuery = "SELECT name, smugmug_slug FROM hist_buggies WHERE buggyid=?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $buggyUrlKey);

  if ($metaData->num_rows == 1) {
    $buggy = $metaData->fetch_assoc();
    $ret = "<meta property=\"og:title\" content=\"History | Buggy: ".$buggy["name"]."\" />\n";
    if(!empty($buggy["smugmug_slug"])) {
      $image_url = makeSmugmugUrl($buggy["smugmug_slug"], "S");
      $ret .= "<meta property=\"og:image\" content=\"".$image_url."\" />\n";
    }
    return $ret;
  }

  // If we do not have this buggy, we actually don't care that much, but we should be reasonable if we can.
  return "<meta property=\"og:title\" content=\"History | Unknown Buggy\" />\n";
}

//<meta property="og:type" content= "website" />
//<meta property="og:site_name" content="Stack Overflow" />
//<meta property="og:url" content="https://stackoverflow.com/questions/59100553/link-description-of-wordpress-site-on-discord"/>

//<meta property="og:title" content="History | Buggy: Aurora" />
//<meta property="og:image" content="https://photos.smugmug.com/photos/i-QpzjK6T/0/S/i-QpzjK6T-S.jpg" /><!--Favicon-->

//<meta property="og:image" itemprop="image primaryImageOfPage" content="https://cdn.sstatic.net/Sites/stackoverflow/Img/apple-touch-icon@2.png?v=73d79a89bded" />

?>