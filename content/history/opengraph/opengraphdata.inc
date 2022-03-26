<?php
// Helper to generate open graph metadata for certain history pages.
// $ogMap is a map of open graph <meta> parameters (e.g. og:type, og:title, etc).
// we return an updated copy of this map.
function getHistoryOpenGraphContent($ogMap) {
  // Early bailout with no/minimal new data
  if (empty($_GET['p'])
      || !in_array($_GET['p'], ['buggy', 'entry', 'org', 'person', 'personlist'])) {
    // We don't know what page this is.
    return $ogMap;
  } else if ($_GET['p'] == "personlist") {
    // no parameter expected, personlist
    $ogMap["og:url"] = "https://cmubuggy.org/history/person/";
    $ogMap["og:title"] = "History | Person Search";
    return $ogMap;
  } else if ((in_array($_GET['p'], ['buggy', 'entry', 'org'])
              && empty($_GET["urlkey"]))
             || ($_GET['p'] == "person" && empty($_GET["id"]))) {
    // missing required parameter
    return $ogMap;
  }

  $historyPage = $_GET['p'];
  $visiblePage = $historyPage;

  // Special cases for nonstandard URL rewrites/parameters
  // person page uses "id" not "urlkey"
  if ($historyPage == "person") {
    $urlKey = $_GET["id"];
  } else {
    $urlKey = $_GET["urlkey"];
  }

  // "entry" is the internal parameter, "team" is the visible url.
  if ($visiblePage == "entry") {
    $visiblePage = "team";
  }

  $url = "https://cmubuggy.org/history/".$visiblePage."/".$urlKey."/";
  $ogMap["og:url"] = $url;

  // TODO: Several of these extra bits require a database query, which sucks, since when the history code
  // itself runs we'll likely be grabbing the same information again.  For now, keep the queries simple and
  // just be sad about it.  Long term, it'd be good to be able to know we're about to render a history page and
  // gather this stuff as we go.

  switch($historyPage) {
    case "buggy":
      getBuggyExtraData($urlKey, $ogMap);
      break;
    case "entry":
      getEntryExtraData($urlKey, $ogMap);
      break;
    case "person":
      getPersonExtraData($urlKey, $ogMap);
      break;
    case "org":
      getOrgExtraData($urlKey, $ogMap);
      break;
    default:
      die("unknown page for opengraph"); // er. what?  we checked for this above.
  };

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

function getEntryExtraData($entryUrlKey, &$ogMap) {
  global $HISTORY_DATABASE;

  $metaDataQuery = "SELECT e.year, o.shortname AS shortname,
                           case when e.Class = 'M' then 'Men\'s'
                             when e.Class = 'W' then 'Women\'s'
                             else 'Unknown' end AS class,
                           Team AS team
                      FROM hist_raceentries e
                      LEFT JOIN hist_orgs o ON e.orgid = o.orgid
                      WHERE entryid = ?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $entryUrlKey);

  if ($metaData->num_rows == 1) {
    $e = $metaData->fetch_assoc();
    $ogMap["og:title"] = "History | Entry: ".$e["year"]." ".$e["shortname"]." ".$e["class"]." ".$e["team"];
  } else {
    // Provide a reasonable title if we couldn't find the org.
    $ogMap["og:title"] = "History | Unknown Entry";
  }

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

function getPersonExtraData($personUrlKey, &$ogMap) {
  global $HISTORY_DATABASE;

  // Check existance & get name.
  $metaDataQuery = "SELECT concat(firstname, ' ', lastname) AS name FROM hist_people WHERE personid=?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $personUrlKey);

  if ($metaData->num_rows == 1) {
    $org = $metaData->fetch_assoc();
    $ogMap["og:title"] = "History | Person: ".$org["name"];
  } else {
    // Provide a reasonable title if we couldn't find the org.
    $ogMap["og:title"] = "History | Unknown Person";
  }
}
?>
