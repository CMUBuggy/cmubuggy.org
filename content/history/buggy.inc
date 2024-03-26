<?php

if (empty($_GET["urlkey"])) {
  // We should have been redirected into buggylist.inc, not here.  What happened?
  die("Ooops, no buggy specified!");
}

$buggyUrlKey = $_GET["urlkey"];

#(/buggy) metadata (existance, build year, org, notes)
$metaDataQuery = "SELECT b.name, b.birthyear, o.shortname AS org, b.orgid,
                         b.note, b.smugmug_slug, b.suppress_gallery,
                         b.formerly AS formerid, fb.name AS fname,
                         fo.orgid AS forgid, fo.shortname AS forg
                    FROM hist_buggies b
                    LEFT JOIN hist_orgs o ON b.orgid=o.orgid
                    LEFT JOIN hist_buggies fb ON fb.buggyid=b.formerly
                    LEFT JOIN hist_orgs fo ON fb.orgid=fo.orgid
                    WHERE b.buggyid=?;";

$metaData = dbBoundQuery($HISTORY_DATABASE, $metaDataQuery, "s", $buggyUrlKey);

if ($metaData->num_rows == 1) {
  $buggy = $metaData->fetch_assoc();
} else if ($metaData->num_rows == 0) {
  echo("I'm sorry, I don't know about buggy: " . $buggyUrlKey);
  exit(0);
} else {
  echo("I'm sorry, I seem to be confused and think there are more than one buggy called: " . $buggyUrlKey);
  exit(0);
}

//
// Fetching the link to the videos is a bit gross, since we need to join against every lane of the heats table
// for each of the 4 heats, and fetch up to 4 different blocks of youtube data.  Apologies for the shorthand naming.
//
$raceQuery = "SELECT e.year,
                     case when e.orgid <> b.orgid then borrower.shortname else NULL end AS borrowerorg,
                     CONCAT(case when e.class = 'W' then 'Women\'s'
                                 when e.class = 'M' then 'Men\'s'
                                 when e.class = 'N' then 'All Gender'
                                 when e.class = 'R' then 'Robotic'
                                 else 'Unknown' end, ' ', team) AS Team,
                     case when e.class = 'W' then '#womens'
                          when e.class = 'M' then '#mens'
                          when e.class = 'N' then '#allgender'
                          when e.class = 'R' then '#robotic'
                          else '' end AS classanchor,
                     entryid AS TeamID,
                     nullif(place,0) AS Place,
                     Prelim, Reroll, Final, FinalReroll,
                     case when DQ <> '0' then DQ else null end AS DQ,
                     vp.youtubeid AS pyoutubeid, vp.title AS ptitle,
                     vr.youtubeid AS ryoutubeid, vr.title AS rtitle,
                     vf.youtubeid AS fyoutubeid, vf.title AS ftitle,
                     vfr.youtubeid AS fryoutubeid, vfr.title AS frtitle,
                     e.note
                FROM hist_raceentries e
                LEFT JOIN hist_orgs borrower ON borrower.orgid=e.orgid
                LEFT JOIN hist_buggies b ON e.buggyid = b.buggyid
                LEFT JOIN hist_heats hp ON hp.isfinals = 0 AND hp.isreroll = 0
                                           AND (CONCAT(hp.year,'.',hp.lane1)=e.entryid
                                                OR CONCAT(hp.year,'.',hp.lane2)=e.entryid
                                                OR CONCAT(hp.year,'.',hp.lane3)=e.entryid)
                LEFT JOIN video vp ON vp.heatid = hp.heatid
                LEFT JOIN hist_heats hr ON hr.isfinals = 0 AND hr.isreroll = 1
                                           AND (CONCAT(hr.year,'.',hr.lane1)=e.entryid
                                                OR CONCAT(hr.year,'.',hr.lane2)=e.entryid
                                                OR CONCAT(hr.year,'.',hr.lane3)=e.entryid)
                LEFT JOIN video vr ON vr.heatid = hr.heatid
                LEFT JOIN hist_heats hf ON hf.isfinals = 1 AND hf.isreroll = 0
                                           AND (CONCAT(hf.year,'.',hf.lane1)=e.entryid
                                                OR CONCAT(hf.year,'.',hf.lane2)=e.entryid
                                                OR CONCAT(hf.year,'.',hf.lane3)=e.entryid)
                LEFT JOIN video vf ON vf.heatid = hf.heatid
                LEFT JOIN hist_heats hfr ON hfr.isfinals = 1 AND hfr.isreroll = 1
                                           AND (CONCAT(hfr.year,'.',hfr.lane1)=e.entryid
                                                OR CONCAT(hfr.year,'.',hfr.lane2)=e.entryid
                                                OR CONCAT(hfr.year,'.',hfr.lane3)=e.entryid)
                LEFT JOIN video vfr ON vfr.heatid = hfr.heatid
                WHERE e.buggyid = ?
                ORDER BY year DESC, Team ASC;";

$raceData = dbBoundQuery($HISTORY_DATABASE, $raceQuery, "s", $buggyUrlKey);

// Combine all buggy awards (design)
//
// Note: we need to postfilter using checkTrophyYear() which is why we separately
// pull class and place (and need to null them out on the design side of the union)
$awardQuery = "SELECT year,
                      case when award = 1 then '1st Place Design'
                           when award = 2 then '2nd Place Design'
                           when award = 3 then '3rd Place Design'
                           else concat('Design ', award) end as award,
                      NULL AS place, NULL as class,
                      note
                      FROM hist_designawards
                      WHERE buggyid = ?
               UNION SELECT year,
                      concat(case when place = 1 then '1st Place'
                                  when place = 2 then '2nd Place'
                                  when place = 3 then '3rd Place'
                                  else concat(place, 'th Place') end,
                             case when class = 'M' then ' Men\'s'
                                  when class = 'W' then ' Women\'s'
                                  when class = 'N' then ' All Gender'
                                  else ' Unknown' end)
                      AS award, place, class, note
                      FROM hist_raceentries
                      WHERE buggyid = ?
                            AND place >= 1 AND place <= 6
                            AND dq = '0'
               ORDER BY year DESC, award ASC;";

$awardData = dbBoundQuery($HISTORY_DATABASE, $awardQuery, "ss", $buggyUrlKey, $buggyUrlKey);

$filteredAwards = array();

while ($a = $awardData->fetch_assoc()) {
  // if place and class are null, this is a design award and
  // checkTrophyYear should be included regardless.  Otherwise, we need
  // to confirm the place award existed in that year.
  if ((!isset($a["place"]) && !isset($a["class"]))
      || checkTrophyYear($a["class"], $a["year"], $a["place"])) {
    array_push($filteredAwards, $a);
  }
}

// Compute a URL for any image we might have.
$image_url = "";
$smart_gallery_url = "";
$image_column_class = "d-flex col align-items-center justify-content-end";
if(!empty($buggy["smugmug_slug"])) {
  $image_url = makeSmugmugUrl($buggy["smugmug_slug"], "S");
}
if(empty($image_url)) {
  // We hide the column entirely on smaller break points to avoid strange word wrapping of long
  // buggy names if we have no image, but it keeps the formatting of the metadata roughtly the same
  // on the larger breakpoints where we probably have enough space anyway.
  //
  // If we _have_ an image, though, we want to preserve it for spotting purposes on mobile.
  //
  // At sm and xs, of course, the columns for the metadata become line breaks...
  $image_column_class = "col d-none d-md-flex";
}
?>

<div class="row mb-3">
  <div class="col">
  <dl class="row">
    <dt class="col-sm-5">Built</dt>
    <dd class="col-sm-7"><?php echo($buggy["birthyear"]); ?></dd>

    <dt class="col-sm-5">Organization</dt>
    <dd class="col-sm-7"><?php echo("<a href=\"/history/org/".$buggy["orgid"]."\">".$buggy["org"]. "</a>"); ?></dd>

    <?php if (!empty($buggy["fname"])) {
            $formertext = "<a href=\"/history/buggy/".$buggy["formerid"]."\">".$buggy["fname"]."</a>";
            if (!empty($buggy["forg"])) {
              $formertext .=" (<a href=\"/history/org/".$buggy["forgid"]."\">".$buggy["forg"]."</a>)";
            }
    ?>
      <dt class="col-sm-5">Formerly</dt>
      <dd class="col-sm-7"><?php echo($formertext); ?></dd>

    <?php }

          if (!empty($buggy["note"])) { ?>

      <dt class="col-sm-5">Notes</dt>
      <dd class="col-sm-7"><?php echo($buggy["note"]); ?></dd>
    <?php }

          // We host "smart galleries" on smugmug at /Buggies/[buggyid]/
          // But they don't always exist, so we rely on the database to tell is what to try.
          if (!$buggy["suppress_gallery"]) {
            $smugmug_smart_gallery = ucfirst(strtolower($buggyUrlKey));
            $smart_gallery_url = "https://cmubuggy.smugmug.com/Buggies/".$smugmug_smart_gallery."/";
    ?>
      <div class="col-sm-12 text-align-center"><a class="btn btn-info" href="<?php echo($smart_gallery_url); ?>">View Photo Gallery</a></dd>
    <?php } ?>
  </dl>
  </div>
  <div class="<?php echo($image_column_class);?>"><div class="row">
  <?php
    // Note we want to keep this column around, even if there is no image, because it keeps the rendering
    // consistent for the metadata.  However, this might do strange things in the event of very long
    // buggy names.
    if (!empty($smart_gallery_url)) {
      echo("<a href=\"".$smart_gallery_url."\">");
    }
    if (!empty($image_url)) {
      echo("<img alt=\"Picture of Buggy\" class=\"img-fluid img-thumbnail\" src=\"".$image_url."\" />");
    }
    if (!empty($smart_gallery_url)) {
      echo("</a>");
    }
  ?>
  </div></div>
</div>

<ul class="nav nav-tabs" role="tablist">
  <li class="nav-item">
    <a id="races-tab" href="#tab-races" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-races" aria-selected="true">Races <span class="badge badge-primary"><?php echo($raceData->num_rows); ?></span></a>
  </li>
  <li class="nav-item">
    <a id="awards-tab" href="#tab-awards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-awards" aria-selected="false">Awards <span class="badge badge-primary"><?php echo(count($filteredAwards)); ?></span></a>
  </li>
</ul>
<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-races" role="tabpanel" aria-labelledby="races-tab">
    <div class="table-responsive"><table class="table">
      <thead>
        <tr class="text-nowrap">
          <th>Year</th>
          <th>Team</th>
          <th>Place</th>
          <th>Prelim</th>
          <th>Prelim Reroll</th>
          <th>Final</th>
          <th>Final Reroll</th>
          <th>DQ / Notes</th>
        </tr>
      </thead>
      <tbody>
        <?php
          while ($r = $raceData->fetch_assoc()) {
            $heatorder = array('Prelim', 'Reroll', 'Final', 'FinalReroll');
            $heattypes = array('Prelim' => 'p','Reroll' => 'r','Final' => 'f', 'FinalReroll' => 'fr');

            $videomap = array();
            foreach ($heattypes as $type => $vp) {
              if (!empty($r[$vp."youtubeid"])) {
                $videomap[$type] = array(
                  "youtubeid" => $r[$vp."youtubeid"],
                  "title" => $r[$vp."title"],
                  "nothumbnail" => "Video" // there just isn't enough room for thumbnails on this page.
                );
              }
            }

            // Because the heats table treats "finals reroll" as "reroll on finals day", we need to
            // fudge videos that are labeled as "finals reroll" but are likely to be prelims rerolls.
            //
            // So, if we have a final reroll video, and no prelim reroll video, and there is
            // no final reroll time, relabel that video.
            //
            // Example buggy that has a lot of these cases: shakazulu
            //
            // This is a hack that might break if the final reroll _acutally_ had no time (e.g. crash)
            // and there is no prelim reroll.
            if (isset($videomap["FinalReroll"])
                && !isset($videomap["Reroll"])
                && empty($r["FinalReroll"])) {
              $videomap["Reroll"] = $videomap["FinalReroll"];
              unset($videomap["FinalReroll"]);
            }

            $year = $r["year"];
            echo("<tr><td><a href=\"/history/".$RACEDAY_URL_PART."/".$year.$r["classanchor"]."\">".$year."</a></td>");

            echo("<td style=\"white-space: nowrap\">");
            // If the entry org doesn't match the owner org for this buggy,
            // we should label that in this entry specifically.
            //
            // Example buggies: perun, thirtyfourninetyfive
            echo("<a href=\"/history/team/".$r["TeamID"]."\">");
            if (!empty($r["borrowerorg"])) {
              echo($r["borrowerorg"]."<br>");
            }
            echo($r["Team"]."</a>");
            echo("</td>");

            echo("<td>".$r["Place"]."</td>");
            foreach ($heatorder as $type) {
              echo("<td>");
              echo(displayTime($r[$type]));
              if (isset($videomap[$type])) {
                echo ("<br>");
                $video = $videomap[$type];
                include("content/youtubevid.inc");
              }
              echo("</td>");
            }
            echo("<td>".$r["DQ"]." ".$r["note"]."</td></tr>");
          }
        ?>
      </tbody>
    </table></div>
  </div>
  <div class="tab-pane fade" id="tab-awards" role="tabpanel" aria-labelledby="awards-tab">
    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr class="text-nowrap">
            <th>Year</th>
            <th>Awards</th>
          </tr>
        </thead>
        <tbody>
          <?php
            foreach ($filteredAwards as $a) {
              echo("<tr><td>".$a["year"]."</td>");
              echo("<td>".$a["award"]."</td>");
              echo("<td>".$a["note"]."</td></tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>
</div>
