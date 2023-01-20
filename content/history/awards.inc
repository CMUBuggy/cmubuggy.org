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

  // TODO: chair should use its own orgid column don't overload team like this.
  // We have notes, but, we don't use them currently.
  $personAwardQuery = "
      SELECT DISTINCT y.year AS year,
                      CONCAT(kperson.firstname, ' ', kperson.lastname) AS 'king',
                        CONCAT(korg.shortname, ' ', kteam.team) AS 'kingteam', king.time AS 'kingtime',
                        kperson.personid AS 'kingid', kteam.entryid AS 'kingentryid',
                      CONCAT(qperson.firstname, ' ', qperson.lastname) AS 'queen',
                        CONCAT(qorg.shortname, ' ', qteam.team) AS 'queenteam', queen.time AS 'queentime',
                        qperson.personid AS 'queenid', qteam.entryid AS 'queenentryid',
                      CONCAT(cperson.firstname, ' ', cperson.lastname) AS 'chair',
                        corg.shortname AS 'chairorg',
                        cperson.personid AS 'chairid', chair.team AS 'chairorgid'
      FROM hist_personawards y
      LEFT JOIN hist_personawards chair ON chair.year = y.year AND chair.award = 'Chair'
      LEFT JOIN hist_people cperson ON cperson.personid = chair.personid
      LEFT JOIN hist_orgs corg ON chair.team = corg.orgid
      LEFT JOIN hist_personawards king ON king.year = y.year AND king.award = 'King'
      LEFT JOIN hist_people kperson ON kperson.personid = king.personid
      LEFT JOIN hist_raceentries kteam ON kteam.entryid = CONCAT(king.year, '.', king.team)
      LEFT JOIN hist_orgs korg ON korg.orgid = kteam.orgid
      LEFT JOIN hist_personawards queen ON queen.year = y.year AND queen.award = 'Queen'
      LEFT JOIN hist_people qperson ON qperson.personid = queen.personid
      LEFT JOIN hist_raceentries qteam ON qteam.entryid = CONCAT(queen.year, '.', queen.team)
      LEFT JOIN hist_orgs qorg ON qorg.orgid = qteam.orgid
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
  </div>

  <div class="tab-pane fade" id="tab-personawards" role="tabpanel" aria-labelledby="personawards-tab">
    <h1>Individual Awards</h1>

    <p class="font-italic">"Hill 1 Awards" refers to the "Blinn/Brewer King of the Hill" and "Queen of the Hill" awards.</p>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Year</th>
            <th>Hill 1 Awards</th>
            <th><span class="d-none d-sm-inline">Chairperson</span><span class="d-inline d-sm-none">Chair</span> of the Year</th>
          </tr>
        </thead>
        <tbody>
          <?php
            // Format one line of hill 1 awards.
            // at the XS breakpoint, we only use the first character of "prefix";
            function echoHillOne($prefix, $personId, $name, $teamId, $team, $time) {
              echo("<span class=\"d-none d-sm-inline\">".$prefix."</span>");
              echo("<span class=\"d-inline d-sm-none\">".$prefix[0]."</span>");
              echo(": <a href=\"./person/".$personId."\">".$name."</a><br>");
              echo("<ul class=\"mb-0\"><li><a href=\"./team/".$teamId."\">".$team."</a>");
              if (!empty($time)) {
                echo(" (".$time."s)");
              }
              echo("</ul>\n");
            }

            while ($p = $personAwards->fetch_assoc()) {
                echo("<tr><td>".$p["year"]."</td>");
                echo("<td>");
                $firstHillOne = true;
                if ($p["king"]) {
                  echoHillOne("King", $p["kingid"],$p["king"],$p["kingentryid"],$p["kingteam"],$p["kingtime"]);
                  $firstHillOne = false;
                }
                if ($p["queen"]) {
                  echoHillOne("Queen", $p["queenid"],$p["queen"],$p["queenentryid"],$p["queenteam"],$p["queentime"]);
                  $firstHillOne = false;
                }
                echo("</td><td>");
                if ($p["chair"]) {
                  echo("<a href=\"./person/".$p["chairid"]."\">".$p["chair"]."</a> ");
                  echo("<ul class=\"mb-0\"><li><a href=\"./org/".$p["chairorgid"]."\">".$p["chairorg"]."</a></li></ul>");
                }
                echo("</td>");
                echo("</tr>");
            }
          ?>
        </tbody>
      </table>
    </div>
  </div>
  <span class="small">Some hill 1 times may be estimated or unofficial.</span><br>
  <span class="small">Note: Years where there are ties will show multiple lines in the table.</span>
</div>
