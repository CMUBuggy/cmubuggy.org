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

  // Tracks which years have _any_ individual award.
  $individualAwardYears = array();

  // We have a notes field in the table, but, we don't use it currently.
  $hillOneAwardQuery = "
      SELECT DISTINCT y.year AS year,
                      CONCAT(kperson.firstname, ' ', kperson.lastname) AS 'king',
                        CONCAT(korg.shortname, ' ', kteam.team) AS 'kingteam', king.time AS 'kingtime',
                        kperson.personid AS 'kingid', kteam.entryid AS 'kingentryid',
                      CONCAT(qperson.firstname, ' ', qperson.lastname) AS 'queen',
                        CONCAT(qorg.shortname, ' ', qteam.team) AS 'queenteam', queen.time AS 'queentime',
                        qperson.personid AS 'queenid', qteam.entryid AS 'queenentryid',
                      CONCAT(mperson.firstname, ' ', mperson.lastname) AS 'monarch',
                        CONCAT(morg.shortname, ' ', mteam.team) AS 'monarchteam', monarch.time AS 'monarchtime',
                        mperson.personid AS 'monarchid', mteam.entryid AS 'monarchentryid'
      FROM hist_personawards y
      LEFT JOIN hist_personawards king ON king.year = y.year AND king.award = 'King'
      LEFT JOIN hist_people kperson ON kperson.personid = king.personid
      LEFT JOIN hist_raceentries kteam ON kteam.entryid = CONCAT(king.year, '.', king.team)
      LEFT JOIN hist_orgs korg ON korg.orgid = kteam.orgid
      LEFT JOIN hist_personawards queen ON queen.year = y.year AND queen.award = 'Queen'
      LEFT JOIN hist_people qperson ON qperson.personid = queen.personid
      LEFT JOIN hist_raceentries qteam ON qteam.entryid = CONCAT(queen.year, '.', queen.team)
      LEFT JOIN hist_orgs qorg ON qorg.orgid = qteam.orgid
      LEFT JOIN hist_personawards monarch ON monarch.year = y.year AND monarch.award = 'Monarch'
      LEFT JOIN hist_people mperson ON mperson.personid = monarch.personid
      LEFT JOIN hist_raceentries mteam ON mteam.entryid = CONCAT(monarch.year, '.', monarch.team)
      LEFT JOIN hist_orgs morg ON morg.orgid = mteam.orgid
      ORDER BY y.year DESC;";
  $hillOneAwards = dbQuery($HISTORY_DATABASE, $hillOneAwardQuery);

  // Collapse out all the hill one awards into a per-year map, and record which years we used.
  $hillOneAwardTable = array();
  while($h = $hillOneAwards->fetch_assoc()) {
    $year = $h["year"];
    $individualAwardYears[$year] = 'x';
    if(array_key_exists($year, $hillOneAwardTable)){
      array_push($hillOneAwardTable[$year],$h);
    } else {
      $hillOneAwardTable[$year]= array($h);
    }
  }

  // For chair of the year, we need to worry about multiple concurrent winners (e.g. co-chairs),
  // so we fetch them separately and condense them down to their own lookup table.
  //
  // This query assumes that "ChairHon" sorts in the enum at a higher value than "Chair"
  // (so that it will appear after any "Chair" entries).
  //
  // TODO: chair should perhaps use its own orgid column don't overload team like this, but this
  // is workable and we'd still need to know the difference in the awards.
  $chairAwardQuery = "
      SELECT DISTINCT year, award,
                      CONCAT(cperson.firstname, ' ', cperson.lastname) AS 'chair',
                        corg.shortname AS 'chairorg',
                        cperson.personid AS 'chairid', chair.team AS 'chairorgid'
      FROM hist_personawards chair
      LEFT JOIN hist_people cperson ON cperson.personid = chair.personid
      LEFT JOIN hist_orgs corg ON chair.team = corg.orgid
      WHERE chair.award IN ('Chair', 'ChairHon')
      ORDER BY year DESC, award ASC;";
  $chairAwards = dbQuery($HISTORY_DATABASE, $chairAwardQuery);

  // Collapse every year from the chair table into a per-year map, and record which years we used.
  $chairAwardTable = array();
  while($c = $chairAwards->fetch_assoc()) {
    $year = $c["year"];
    $individualAwardYears[$year] = 'x';
    if(array_key_exists($year, $chairAwardTable)){
      array_push($chairAwardTable[$year],$c);
    } else {
      $chairAwardTable[$year]= array($c);
    }
  }
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
              echo("<ul class=\"mb-0 nobullet\"><li><a href=\"./team/".$teamId."\">".$team."</a>");
              if (!empty($time)) {
                echo(" (".$time."s)");
              }
              echo("</ul>\n");
            }

            // We need the desending set of years.  ksort gives us ascending, so we need to reverse it.
            ksort($individualAwardYears);
            $individualAwardYears = array_reverse(array_keys($individualAwardYears));
            foreach($individualAwardYears as $year) {
                echo("<tr><td>".$year."</td>");

                echo("<td>");
                foreach ($hillOneAwardTable[$year] as $h) {
                  // Ties, notably, will be messy, but they should be very rare in practice.
                  if ($h["king"]) {
                    echoHillOne("King", $h["kingid"],$h["king"],$h["kingentryid"],$h["kingteam"],$h["kingtime"]);
                  }
                  if ($h["queen"]) {
                    echoHillOne("Queen", $h["queenid"],$h["queen"],$h["queenentryid"],$h["queenteam"],$h["queentime"]);
                  }
                  if ($h["monarch"]) {
                    echoHillOne("Monarch", $h["monarchid"],$h["monarch"],$h["monarchentryid"],
                                $h["monarchteam"],$h["monarchtime"]);
                  }
                }
                echo("</td><td>");
                // NOTE: It goes without saying that this won't render a chairperson award if there is no
                // Hill 1 award (of any class) that year.  Any fix should consider what we do with
                // Hill 1 award ties as well (which currently are handled poorly anyway).
                if (array_key_exists($year, $chairAwardTable)) {
                  foreach($chairAwardTable[$year] as $c) {
                    echo("<a href=\"./person/".$c["chairid"]."\">".$c["chair"]."</a> ");
                    echo("<ul class=\"mb-0 nobullet\">");
                    echo("<li><a href=\"./org/".$c["chairorgid"]."\">".$c["chairorg"]."</a></li>");
                    if ($c["award"] == 'ChairHon') {
                      echo("<li class=\"font-italic\">Honorable Mention</li>");
                    }
                    echo("</ul>");
                  }
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
