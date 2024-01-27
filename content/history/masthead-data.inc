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
    // Map subpages to titles.
    $TITLE_MAP = [
        // TODO:
        // These pages will need custom handling, as the title needs to be read from the DB.
        // "buggy" => "Stealth"
        // "org" => "Apex"
        // "person" => "Connor Hayes"
        // "raceday" => "2023"
        // "entry" => "2023 Spirit Womens A"
        // "sweepstakes" => "Sweepstakes Committee 2023"

        // TODO: Sweepstakes is special, see note above.

        "awards" => "Awards",
        "buggybook" => "Buggy Books",
        "buggylist" => "Buggies",
        "orglist" => "Organizations",
        "personlist" => "People Search",
        "racedaylist" => "Racedays",
        "sweepstakeslist" => "Sweepstakes Committees",
        "toptimes" => "Top Times"
    ];

    if (empty($_GET['p'])
        || !in_array($_GET['p'], array_keys($TITLE_MAP))) {
        // Either this is the top page, or we don't know what it is.  Default to "History"
        return "History";
    } else {
        return $TITLE_MAP[$_GET['p']];
    }
}
?>