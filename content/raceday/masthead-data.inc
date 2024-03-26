<?php
function getRacedayBreadcrumbs() {
    global $RACEDAY_WORD, $RACEDAY_URL_PART;

    $ret = [["/".$RACEDAY_URL_PART, $RACEDAY_WORD]];
    if (empty($_GET['p'])) {
        // Top Page, no crumb.
        return [];
    } else if ($_GET['p'] == 'rostersorg') {
        // Org specific rosters are a sub heading of Rosters
        array_push($ret, ["/raceday/rosters", "Rosters"]);
        return $ret;
    } else {
        // Most raceday pages don't get their own crumb.
        return $ret;
    }
}

function getRacedayPageTitle() {
    global $RACEDAY_WORD;
    $DEFAULT_TITLE = $RACEDAY_WORD;

    // Map subpages to titles.
    $TITLE_MAP = [
        "leaderboard" => "Leaderboard",
    ];

    // Titles where we need to process the URL and/or do a DB query.  Requires
    // us to do a callback.
    //
    // PHP callbacks are just strings.  None of these callback may take a param,
    // they need to work the same way the content does by processing $_GET.
    $TITLE_CALLBACKS = [
        "rosters" => 'getRostersTitle',
        "rostersorg" => 'getRostersOrgTitle'
    ];

    if (empty($_GET['p'])) {
        // Top level Raceday page.
        return $DEFAULT_TITLE;
    }

    $page = $_GET['p'];

    if (in_array($page, array_keys($TITLE_MAP))) {
        return $TITLE_MAP[$page];
    } elseif (in_array($page, array_keys($TITLE_CALLBACKS))) {
        return $TITLE_CALLBACKS[$page]();
    } else {
        // Don't know what this is, use default.
        return $DEFAULT_TITLE;
    }
}

function getRostersTitle() {
    $year = safeGetYear();
    return "$year Team Rosters";
}

function safeGetYear() {
    $year = getDefaultRacedayYear();
    if (!empty($_GET["year"])) {
        $year = $_GET['year'] * 1;
    }
    return $year;
}

function getRostersOrgTitle() {
    // getOrgShortname is defined in content/raceday/opengraph/opengraphdata.inc,
    // and should have a cached result for us at this point, so no database hit required.
    $year = safeGetYear();
    $orgshortname = getOrgShortname(dieOrGetParam("org"));
    return $year." ".$orgshortname." Rosters";
}
?>
