<?php
// Helper to generate open graph metadata for raceday pages.
// $ogMap is a map of open graph <meta> parameters (e.g. og:type, og:title, etc).
// we return an updated copy of this map.
function getRacedayOpenGraphContent($ogMap) {
  if (empty($_GET['p']) ||
      !in_array($_GET['p'], ['rosters', 'rostersorg', 'leaderboard'])) {
    // If it isn't one of these three, we don't know what to do.  No changes.
    return $ogMap;
  }

  $racedayPage = $_GET['p'];
  $year = getDefaultRacedayYear();

  if(in_array($racedayPage, ['rosters', 'rostersorg'])) {
    if(!empty($_GET['year'])) {
      $year = $_GET['year'] * 1;
    }
    if ($racedayPage == "rostersorg") {
      if (!empty($_GET['org'])) {
        $orgUrlKey = $_GET['org'];
      } else {
        // If we don't have an org parameter, for OpenGraph purposes, act like this is just the regular roster page.
        // Our rewrite code should prevent this for normal users though.
        $racedayPage = 'rosters';
      }
    }
  }

  switch($racedayPage) {
    case "rosters":
      $ogMap["og:title"] = "Raceday $year: All Entries";
      $ogMap["og:url"] = "https://cmubuggy.org/raceday/rosters/$year/";
      break;
    case "rostersorg":
      // Fast DB query to confirm org existance and get shortname.
      $shortName = getOrgShortname($orgUrlKey);
      if (empty($shortName)) {
        // Don't know what this org is, so $orgUrlKey isn't safe, so we can't use it.
        // Default to just the year in the URL.
        $ogMap["og:title"] = "Raceday $year: Unknown Org";
        $ogMap["og:url"] = "https://cmubuggy.org/raceday/rosters/$year/";
      } else {
        $ogMap["og:title"] = "Raceday $year: $shortName Rosters";
        $ogMap["og:url"] = "https://cmubuggy.org/raceday/rosters/$year/$orgUrlKey/";
      }
      break;
    case "leaderboard":
      $ogMap["og:title"] = "Raceday: Leaderboard";
      $ogMap["og:url"] = "https://cmubuggy.org/raceday/leaderboard/";
      break;
    default:
      die("unknown page for opengraph"); // er. what?  we checked for this above.
  };

  return $ogMap;
}

// Just does the query to get the proper shortname for an org and return it (or an empty string)
//
// Doesn't check to see if they're actually valid entered for this year or not, since this is only for
// opengraph purposes.
function getOrgShortname($orgUrlKey) {
  global $HISTORY_DATABASE;

  $metaDataQuery = "SELECT shortname FROM hist_orgs o WHERE o.orgid=?;";
  $metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $orgUrlKey);

  if ($metaData->num_rows == 1) {
    $org = $metaData->fetch_assoc();
    return $org["shortname"];

    // We could obviously also fetch the logo here, unfortuinately OpenGraph is pretentious and does not
    // accept SVG as a valid image format.  Thus, most of our orgs would get no image anyway (since we
    // prefer SVGs for logos), and therefore we chose to skip it.
  } else {
    return "";
  }
}
?>