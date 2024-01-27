<?php
function getHistoryBreadcrumbs() {
    // If we are here, we always have at least the /history crumb.
    $ret = [["/history", "History"]];

    // The map of deeper crumbs.
    $CRUMB_MAP = [
        // Entity pages need the breadcrumb for their prior level.
        "buggy" => ['/history/buggy', "Buggies"],
        "org" => ['/history/org', "Organizations"],
        "person" => ['/history/person', "People"],
        "raceday" => ['/history/raceday', "Racedays"],
        "sweepstakes" => ['/history/sweepstakes', "Sweepstakes Committees"],

        // There isn't really a /history/entries page.
        // Going to use orgs, but could arguably be racedays too.
        "entry" => ['/history/org', "Organizations"],

        // These pages exist, but are the top level and shouldn't get a dedicated breadcrumb.
        // Instead, they just get their title and the History breadcrumb.
        //
        // "awards" => ['/history/award', "Awards"],
        // "buggybook" => ['/history/buggybook', "Buggy Books"],
        // "buggylist" => ['/history/buggy', "Buggies"],
        // "orglist" => ['/history/org', "Organizations"],
        // "personlist" => ['/history/person', "People"],
        // "racedaylist" => ['/history/raceday', "Racedays"],
        // "sweepstakeslist" => ['/history/sweepstakes', "Sweepstakes Committees"],
        // "toptimes" => ['/history/toptimes', "Top Times"]
    ];

    if (empty($_GET['p'])
        || !in_array($_GET['p'], array_keys($CRUMB_MAP))) {
        // Either this is the top page, or it is a subpage that doesn't get a crumb.
        return $ret;
    } else {
        array_push($ret, $CRUMB_MAP[$_GET['p']]);
        return $ret;
    }
}

function getHistoryPageTitle() {
    $DEFAULT_TITLE = "History";

    // Map subpages to titles.
    $TITLE_MAP = [
        "awards" => "Awards",
        "buggybook" => "Buggy Books",
        "buggylist" => "Buggies",
        "orglist" => "Organizations",
        "personlist" => "People Search",
        "racedaylist" => "Racedays",
        "sweepstakeslist" => "Sweepstakes Committees",
        "toptimes" => "Top Times"
    ];

    // PHP callbacks are just strings.  None of these callback may take a param,
    // they need to work the same way the content does by processing $_GET.
    $TITLE_CALLBACKS = [
        // TODO:
        // These pages will need custom handling, as the title
        // varies based on the query.
        //
        // "buggy" => "Stealth"
        // "org" => "Apex"
        // "person" => "Connor Hayes"
        // "entry" => "2023 Spirit Womens A"

        "raceday" => 'getRacedayTitle',
        "sweepstakes" => 'getSweepstakesTitle',
    ];

    if (empty($_GET['p'])) {
        // Top level History page.
        return $DEFAULT_TITLE;
    }

    $page = $_GET['p'];

    if (in_array($page, array_keys($TITLE_MAP))) {
        // Either this is the top page, or we don't know what it is.  Default to "History"
        return $TITLE_MAP[$page];
    } elseif (in_array($page, array_keys($TITLE_CALLBACKS))) {
        return $TITLE_CALLBACKS[$page]();
    } else {
        // Don't know what this is, use default.
        return $DEFAULT_TITLE;
    }
}

function getRacedayTitle() {
    if (empty($_GET["year"])) {
        // We should have been sent into racedaylist, not here.  What happened?
        die("Ooops, no year specified!");
    }

    $year = $_GET['year'] * 1;
    return "Raceday $year";
}

function getSweepstakesTitle() {
    if (empty($_GET["year"])) {
        // We should have been sent into sweepstakeslist, not here.  What happened?
        die("Ooops, no year specified!");
    }

    $year = $_GET["year"] * 1;
    return "Sweepstakes Committee $year";
}
?>