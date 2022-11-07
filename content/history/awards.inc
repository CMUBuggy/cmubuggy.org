<?php
  $designAwardQuery = "
      SELECT a.year, a.honoree AS '1st', a.buggyid AS '1stid', a.birth AS '1stbirth',
        b.honoree AS '2nd', b.buggyid AS '2ndid', b.birth AS '2ndbirth',
			  c.honoree AS '3rd', c.buggyid AS '3rdid', c.birth AS '3rdbirth',
			  p.honoree AS 'People', p.buggyid AS 'Peopleid', p.birth AS 'Peoplebirth'
      FROM (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM hist_designawards d
		      INNER JOIN hist_buggies b ON d.buggyid = b.buggyid
		      INNER JOIN hist_orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM hist_designawards d
		      INNER JOIN hist_orgs o ON d.orgid = o.orgid) a
      LEFT JOIN (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM hist_designawards d
		      INNER JOIN hist_buggies b ON d.buggyid = b.buggyid
		      INNER JOIN hist_orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM hist_designawards d
		      INNER JOIN hist_orgs o ON d.orgid = o.orgid) b ON b.year = a.year AND b.award = 2
      LEFT JOIN (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM hist_designawards d
		      INNER JOIN hist_buggies b ON d.buggyid = b.buggyid
		      INNER JOIN hist_orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM hist_designawards d
		      INNER JOIN hist_orgs o ON d.orgid = o.orgid) c ON c.year = a.year AND c.award = 3
      LEFT JOIN (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM hist_designawards d
		      INNER JOIN hist_buggies b ON d.buggyid = b.buggyid
		      INNER JOIN hist_orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM hist_designawards d
		      INNER JOIN hist_orgs o ON d.orgid = o.orgid) p ON p.year = a.year AND p.award = 'People\'s Choice'
      WHERE a.award = 1
      ORDER BY year DESC;";
  $designAwards = dbQuery($HISTORY_DATABASE, $designAwardQuery);

  // Note: This will still render a year even if none of the selected awards are present in that year,
  // if an unnamed award (e.g. "Most Improved" _is_ present).  This doesn't seem likely enough to
  // worry about though.
  $orgAwardQuery = " 
    SELECT DISTINCT y.year AS year, occ.shortname as 'chair', occ.orgid as 'chairid',
                                    osb.shortname as 'spirit', osb.orgid as 'spiritid',
                                    ots.shortname as 'shirt', ots.orgid as 'shirtid'
	    FROM hist_orgawards y
	    LEFT JOIN hist_orgawards cc ON cc.year = y.year AND cc.award = 'Chairman\'s Choice' LEFT JOIN hist_orgs occ on cc.orgid = occ.orgid
	    LEFT JOIN hist_orgawards sb ON sb.year = y.year AND sb.award = 'Spirit of Buggy' LEFT JOIN hist_orgs osb on sb.orgid = osb.orgid
	    LEFT JOIN hist_orgawards ts ON ts.year = y.year AND ts.award = 'T-Shirt Award' LEFT JOIN hist_orgs ots on ts.orgid = ots.orgid
      ORDER BY y.year DESC;";
  $orgAwards = dbQuery($HISTORY_DATABASE, $orgAwardQuery);

  $personAwardQuery = "
      SELECT DISTINCT y.year AS year,
                      CONCAT(kperson.firstname, ' ', kperson.lastname) AS 'king',
                        CONCAT(korg.shortname, ' ', kteam.team) AS 'kingteam', king.time AS 'kingtime', king.note AS 'kingnote',
                        kperson.personid AS 'kingid', kteam.entryid AS 'kingentryid',
                      CONCAT(qperson.firstname, ' ' , qperson.lastname) AS 'queen',
                        CONCAT(qorg.shortname, ' ', qteam.team) AS 'queenteam', queen.time AS 'queentime', queen.note AS 'queennote',
                        qperson.personid AS 'queenid', qteam.entryid AS 'queenentryid',
                      chair.personid AS 'chair', chair.note AS 'chairnote'
      FROM hist_personawards y
      LEFT JOIN hist_personawards chair ON chair.year = y.year AND chair.award = 'Chair'
      LEFT JOIN hist_personawards king ON king.year = y.year AND king.award = 'King'
      LEFT JOIN hist_people kperson ON kperson.personid = king.personid
      LEFT JOIN hist_raceentries kteam ON kteam.entryid = CONCAT(king.year, '.', king.team)
      LEFT JOIN hist_orgs korg ON korg.orgid = kteam.orgid
      LEFT JOIN hist_personawards queen ON queen.year = y.year AND queen.award = 'Queen'
      LEFT JOIN hist_people qperson ON qperson.personid = queen.personid
      LEFT JOIN hist_raceentries qteam ON qteam.entryid = CONCAT(queen.year, '.', queen.team)
      LEFT JOIN hist_orgs qorg ON qorg.orgid = kteam.orgid
      ORDER BY y.year DESC;";
  $personAwards = dbQuery($HISTORY_DATABASE, $personAwardQuery);
?>
<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="designcomp-tab" href="#tab-designcomp" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-designcomp" aria-selected="true">Design Competition</a>
  </li>
  <li class="nav-item">
    <a id="orgawards-tab" href="#tab-orgawards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-orgawards" aria-selected="false">Organization Awards</a>
  </li>
  <li class="nav-item">
    <a id="personawards-tab" href="#tab-personawards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-personawards" aria-selected="false">Individual Awards</a>
  </li>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-designcomp" role="tabpanel" aria-labelledby="designcomp-tab">
    <h1>Design Competition</h1>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Year</th>
            <th>1st Place</th>
            <th>2nd Place</th>
            <th>3rd Place</th>
            <th>People's Choice</th>
          </tr>
        </thead>
        <tbody>
          <?php
            // Format a cell for 1st, 2nd, 3rd, peoples, etc.
            function echoDesignCompCell($d, $prefix) {
              if ($d[$prefix."id"]) {
                $tooltip = $d[$prefix."birth"] ? "title=\"Built ".$d[$prefix."birth"]."\" " : "";
                echo("<td><a ".$tooltip."href=\"./buggy/".$d[$prefix."id"]."\">".$d[$prefix]."</a></td>");
              } else {
                echo("<td>".$d[$prefix]."</td>");
              }

            }

            while ($d = $designAwards->fetch_assoc()) {
              // TODO: Expand query to link to org and buggy id separately.  For now, follow existing behavior
              // to link to buggy only.
              //
              // Thus, no link at all for now if no buggy data available.
              //
              // Show birth year in tooltip if available.
              echo("<tr><td>".$d["year"]."</td>");
              echoDesignCompCell($d, "1st");
              echoDesignCompCell($d, "2nd");
              echoDesignCompCell($d, "3rd");
              echoDesignCompCell($d, "People");
              echo("</tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
    <span class="small">Note: Years where there are ties will show multiple lines in the table.</span>
  </div>

  <div class="tab-pane fade" id="tab-orgawards" role="tabpanel" aria-labelledby="orgawards-tab">
    <h1>Organization Awards</h1>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Year</th>
            <th>Anne Witchner<br>Chairman's Choice</th>
            <th>Tom Wood<br>Spirit of Buggy</th>
            <th>T-Shirt Award</th>
          </tr>
        </thead>
        <tbody>
          <?php
            while ($o = $orgAwards->fetch_assoc()) {
                echo("<tr><td>".$o["year"]."</td>");
                echo("<td><a href=\"./org/".$o["chairid"]."\">".$o["chair"]."</a></td>");
                echo("<td><a href=\"./org/".$o["spiritid"]."\">".$o["spirit"]."</a></td>");
                echo("<td><a href=\"./org/".$o["shirtid"]."\">".$o["shirt"]."</a></td>");
                echo("</tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
    <span class="small">Note: Years where there are ties will show multiple lines in the table.</span>
  </div>

  <div class="tab-pane fade" id="tab-personawards" role="tabpanel" aria-labelledby="personawards-tab">
    <h1>Individual Awards</h1>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Year</th>
            <th>King of The Hill</th><th>Time (sec)</th>
            <th>Queen Of The Hill</th><th>Time (sec)</th>
            <!-- TODO: Chairperson of the year -->
          </tr>
        </thead>
        <tbody>
          <?php
            while ($p = $personAwards->fetch_assoc()) {
                echo("<tr><td>".$p["year"]."</td>");
                if ($p["king"]) {
                  $note = "";
                  if ($p["kingnote"]) {
                    $note = "<br><i>".$p["kingnote"]."</i>";
                  }
                  echo("<td><a href=\"./person/".$p["kingid"]."\">".$p["king"]."</a> (<a href=\"./team/".$p["kingentryid"]."\">".$p["kingteam"]."</a>)".$note."</td>");
                  echo("<td>".$p["kingtime"]."</td>");
                } else {
                  echo("<td colspan=2></td>");
                }
                if ($p["queen"]) {
                  $note = "";
                  if ($p["queennote"]) {
                    $note = "<br><i>".$p["kingnote"]."</i>";
                  }
                  echo("<td><a href=\"./person/".$p["queenid"]."\">".$p["queen"]."</a> (<a href=\"./team/".$p["queenentryid"]."\">".$p["queenteam"]."</a>)".$note."</td>");
                  echo("<td>".$p["queentime"]."</td>");
                } else {
                  echo("<td colspan=2></td>");
                }
                echo("</tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>
</div>
