<h1>Racedays</h1>

<?php
// This query only works for years in one of 3 cases:
// - No results at all, and there is an entry in the database. (e.g. COVID and War Years)
//   - These are in the database as mens with a null entry and a note (or, in the case of 2020, 1 each for mens and womens)
// - Only a mens result. (e.g. 1978 and prior)
// - Both a mens and a women's result (Years 1979 onward)
//
// - Notably, I don't expect this to return results when there is _only_ a women's result but no mens result.
//   It is possible to fix this by using the MySQL workaround for a full outer join, but that makes this query
//   significantly more complex, and this case seems unlikely at this point so I will leave it to the future
//   to fix it when it actually happens.
//
// - We only fetch ma.note (as "note") to be used for the years where nothing happened, so we have a reason to display.
$query = "SELECT ma.Year AS year,
  concat(oma.shortname, case when ma.team = 'A' then '' else concat(' ', ma.team) end) AS Mens1, ma.entryid AS Mens1ID,
	case when ma.finalreroll > 0 then ma.finalreroll
       when ma.final > 0 then ma.final
       when ma.reroll > 0 then ma.reroll
		   when ma.prelim > 0 then ma.prelim
       else NULL
	end AS MensTime,
  concat(omb.shortname, case when mb.team = 'A' then '' else concat(' ', mb.team) end) AS Mens2, mb.entryid AS Mens2ID,
  concat(omc.shortname, case when mc.team = 'A' then '' else concat(' ', mc.team) end) AS Mens3, mc.entryid AS Mens3ID,
  concat(owa.shortname, case when wa.team = 'A' then '' else concat(' ', wa.team) end) AS Womens1, wa.entryid AS Womens1ID,
	case when wa.finalreroll > 0 then wa.finalreroll
       when wa.final > 0 then wa.final
       when wa.reroll > 0 then wa.reroll
		   when wa.prelim > 0 then wa.prelim
       else NULL
	end AS WomensTime,
  concat(owb.shortname, case when wb.team = 'A' then '' else concat(' ', wb.team) end) AS Womens2, wb.entryid AS Womens2ID,
  concat(owc.shortname, case when wc.team = 'A' then '' else concat(' ', wc.team) end) AS Womens3, wc.entryid AS Womens3ID,
  concat(ona.shortname, case when na.team = 'A' then '' else concat(' ', na.team) end) AS AllGender1, na.entryid AS AllGender1ID,
	case when na.finalreroll > 0 then na.finalreroll
       when na.final > 0 then na.final
       when na.reroll > 0 then na.reroll
		   when na.prelim > 0 then na.prelim
       else NULL
	end AS AllGenderTime,
  concat(onb.shortname, case when nb.team = 'A' then '' else concat(' ', nb.team) end) AS AllGender2, nb.entryid AS AllGender2ID,
  concat(onc.shortname, case when nc.team = 'A' then '' else concat(' ', nc.team) end) AS AllGender3, nc.entryid AS AllGender3ID,
  ma.note AS note
  FROM hist_raceentries ma LEFT JOIN hist_orgs oma ON ma.orgid = oma.orgid
  LEFT JOIN hist_raceentries mb ON ma.year=mb.year AND ma.class = mb.class AND mb.place = 2 LEFT JOIN hist_orgs omb ON mb.orgid = omb.orgid
  LEFT JOIN hist_raceentries mc ON ma.year=mc.year AND ma.class = mc.class AND mc.place = 3 LEFT JOIN hist_orgs omc ON mc.orgid = omc.orgid
  LEFT JOIN hist_raceentries wa ON ma.year=wa.year AND wa.class = 'W' AND wa.place = 1 LEFT JOIN hist_orgs owa ON wa.orgid = owa.orgid
  LEFT JOIN hist_raceentries wb ON wa.year=wb.year AND wa.class = wb.class AND wb.place = 2 LEFT JOIN hist_orgs owb ON wb.orgid = owb.orgid
  LEFT JOIN hist_raceentries wc ON wa.year=wc.year AND wa.class = wc.class AND wc.place = 3 LEFT JOIN hist_orgs owc ON wc.orgid = owc.orgid
  LEFT JOIN hist_raceentries na ON ma.year=na.year AND na.class = 'N' AND na.place = 1 LEFT JOIN hist_orgs ona ON na.orgid = ona.orgid
  LEFT JOIN hist_raceentries nb ON na.year=nb.year AND na.class = nb.class AND nb.place = 2 LEFT JOIN hist_orgs onb ON nb.orgid = onb.orgid
  LEFT JOIN hist_raceentries nc ON na.year=nc.year AND na.class = nc.class AND nc.place = 3 LEFT JOIN hist_orgs onc ON nc.orgid = onc.orgid
  WHERE ((ma.place = 1 AND ma.class = 'M') OR (ma.team IS NULL AND ma.class = 'M'))
  ORDER BY Year DESC;";

$raceyearlist = dbQuery($HISTORY_DATABASE, $query);

function echoTeamCell($teamkey, $teamname) {
  echo("<td><a href=\"/history/team/".$teamkey."\">".$teamname."</td>");
}
?>

<script defer type="text/javascript" src="/js/cmubuggy-classfilter.js?ver=2023012000"></script>

<b>Class To Show:</b>
All <input type="radio" id="enableAll" name="classFilter" value="ALL" checked>
Men's <input type="radio" id="enableM" name="classFilter" value="mensRow">
Women's <input type="radio" id="enableW" name="classFilter" value="womensRow">
All Gender <input type="radio" id="enableN" name="classFilter" value="allgenderRow">

<div class="table-responsive">
  <table class="table classFilterTable">
    <thead>
      <tr>
        <th>Year</th>
        <th class="classCol">Class</th>
        <th>Champ</th>
        <th>Time</th>
        <th>2nd Place</th>
        <th>3rd Place</th>
      </tr>
    </thead>
    <tbody>
      <?php

        $yearParity = false;
        while ($r = $raceyearlist->fetch_assoc()) {
          $yearCell = "<td><a href=\"/history/raceday/".$r["year"]."\">".$r["year"]."</a></td>";

          // How many rows does this year need?  [1 per class]
          $rowspan = 0;
          if (!empty($r["Mens1"])) {
            $rowspan++;
          }
          if (!empty($r["Womens1"])) {
            $rowspan++;
          }
          if (!empty($r["AllGender1"])) {
            $rowspan++;
          }

          // Stripe the table so years are the same background color when multiple classes are shown
          $yearParityClass = "";
          if ($yearParity) {
            $yearParityClass = " table-parity-color year-parity";
          }
          $yearParity = !$yearParity;

          if ($rowspan == 0) {
            // Skipped Years (War, Covid)
            echo("<tr class=\"classRow skippedYearRow".$yearParityClass."\">".$yearCell);
            echo("<td colspan=\"5\" class=\"text-center\">".$r["note"]."</td>");
            echo("</tr>\n");
          } else {
            if (!empty($r["Mens1"])) {
              echo("<tr class=\"classRow mensRow".$yearParityClass."\">".$yearCell);

              echo("<td class=\"classCol\">Men's</td>");
              echoTeamCell($r["Mens1ID"],$r["Mens1"]);
              echo("<td>".displayTime($r["MensTime"])."</td>");
              echoTeamCell($r["Mens2ID"],$r["Mens2"]);
              echoTeamCell($r["Mens3ID"],$r["Mens3"]);
              echo("</tr>\n");
            }
            if (!empty($r["Womens1"])) {
              echo("<tr class=\"classRow womensRow".$yearParityClass."\">".$yearCell);
              echo("<td class=\"classCol\">Women's</td>");
              echoTeamCell($r["Womens1ID"],$r["Womens1"]);
              echo("<td>".displayTime($r["WomensTime"])."</td>");
              echoTeamCell($r["Womens2ID"],$r["Womens2"]);
              echoTeamCell($r["Womens3ID"],$r["Womens3"]);
              echo("</tr>\n");
            }
            if (!empty($r["AllGender1"])) {
              echo("<tr class=\"classRow allgenderRow".$yearParityClass."\">".$yearCell);
              echo("<td class=\"classCol\">All Gender</td>");
              echoTeamCell($r["AllGender1ID"],$r["AllGender1"]);
              echo("<td>".displayTime($r["AllGenderTime"])."</td>");
              echoTeamCell($r["AllGender2ID"],$r["AllGender2"]);
              echoTeamCell($r["AllGender3ID"],$r["AllGender3"]);
              echo("</tr>\n");
            }
          }
        }
      ?>
    </tbody>
  </table>
  <span class="small">Note: Years where there are ties (e.g. 1922), will show multiple lines in the table.</span>
</div>
