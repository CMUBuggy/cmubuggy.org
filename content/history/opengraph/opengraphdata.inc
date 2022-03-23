<?php
// Helper to generate open graph metadata for certain history pages.
// $ogMap is a map of open graph <meta> parameters (e.g. og:type, og:title, etc).
// we return an updated copy of this map.
function getHistoryOpenGraphContent($ogMap) {
  if (empty($_GET['p']) ||
      !in_array($_GET['p'], ['buggy', 'org'])
      || empty($_GET["urlkey"])) {
    // Either we don't know how to handle this page, or we don't have a paremeter.
    // Either way, No new OG data.
    return $ogMap;
  }

  $historyPage = $_GET['p'];
  $urlKey = $_GET["urlkey"];

  $url = "https://cmubuggy.org/history/".$historyPage."/".$urlKey."/";
  $ogMap["og:url"] = $url;

  // TODO: Several of these extra bits require a database query, which sucks, since when the history code
  // itself runs we'll likely be grabbing the same information again.  For now, keep the queries simple and
  // just be sad about it.  Long term, it'd be good to be able to know we're about to render a history page and
  // gather this stuff as we go.

  switch($historyPage) {
    case "buggy":
      getBuggyExtraData($urlKey, $ogMap);
      break;
    case "org":
      getOrgExtraData($urlKey, $ogMap);
      break;
    default:
      die("unknown page for opengraph"); // er. what?  we checked for this above.
  };

  return $ogMap;
}

function getOrgExtraData($orgUrlKey, &$ogMap) {
  global $HISTORY_DATABASE;

  $metaDataQuery = "SELECT shortname FROM hist_orgs o WHERE o.orgid=?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $orgUrlKey);

  if ($metaData->num_rows == 1) {
    $org = $metaData->fetch_assoc();
    $ogMap["og:title"] = "History | Org: ".$org["shortname"];

    // We could obviously also fetch the logo here, unfortuinately OpenGraph is pretentious and does not
    // accept SVG as a valid image format.  Thus, most of our orgs would get no image anyway (since we
    // prefer SVGs for logos), and therefore we chose to skip it.
  } else {
    // Provide a reasonable title if we couldn't find the org.
    $ogMap["og:title"] = "History | Unknown Org";
  }

  return $ogMap;
}

function getBuggyExtraData($buggyUrlKey, &$ogMap) {
  global $HISTORY_DATABASE;

  $metaDataQuery = "SELECT name, smugmug_slug FROM hist_buggies WHERE buggyid=?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $buggyUrlKey);

  if ($metaData->num_rows == 1) {
    $buggy = $metaData->fetch_assoc();
    $ogMap["og:title"] = "History | Buggy: ".$buggy["name"];

    if(!empty($buggy["smugmug_slug"])) {
      $ogMap["og:image"] = makeSmugmugUrl($buggy["smugmug_slug"], "S");
    }
  } else {
    // If we do not have this buggy, we actually don't care that much, but we should be reasonable if we can.
    $ogMap["og:title"] = "History | Unknown Buggy";
  }
}
?>