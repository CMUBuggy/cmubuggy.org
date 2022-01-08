<?php
  $designAwardQuery = "
      SELECT a.year, a.honoree AS '1st', a.buggyid AS '1stid', a.birth AS '1stbirth',
        b.honoree AS '2nd', b.buggyid AS '2ndid', b.birth AS '2ndbirth',
			  c.honoree AS '3rd', c.buggyid AS '3rdid', c.birth AS '3rdbirth',
			  p.honoree AS 'People', p.buggyid AS 'Peopleid', p.birth AS 'Peoplebirth'
      FROM (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM 1designawards d
		      INNER JOIN 0buggies b ON d.buggyid = b.buggyid
		      INNER JOIN 0orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM 1designawards d
		      INNER JOIN 0orgs o ON d.orgid = o.orgid) a
      LEFT JOIN (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM 1designawards d
		      INNER JOIN 0buggies b ON d.buggyid = b.buggyid
		      INNER JOIN 0orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM 1designawards d
		      INNER JOIN 0orgs o ON d.orgid = o.orgid) b ON b.year = a.year AND b.award = 2
      LEFT JOIN (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM 1designawards d
		      INNER JOIN 0buggies b ON d.buggyid = b.buggyid
		      INNER JOIN 0orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM 1designawards d
		      INNER JOIN 0orgs o ON d.orgid = o.orgid) c ON c.year = a.year AND c.award = 3
      LEFT JOIN (
	      SELECT year, award, concat(shortname, ' - ', name) AS honoree, b.buggyid AS buggyid, b.birthyear AS birth FROM 1designawards d
		      INNER JOIN 0buggies b ON d.buggyid = b.buggyid
		      INNER JOIN 0orgs o ON b.orgid = o.orgid
	      UNION SELECT year, award, shortname AS honoree, NULL AS buggyid, NULL as birth FROM 1designawards d
		      INNER JOIN 0orgs o ON d.orgid = o.orgid) p ON p.year = a.year AND p.award = 'People\'s Choice'
      WHERE a.award = 1
      ORDER BY year DESC;";
  $designAwards = dbQuery("history",$designAwardQuery);

  $orgAwardQuery = " 
    SELECT DISTINCT y.year AS year, occ.shortname as 'chair', occ.orgid as 'chairid',
                                    osb.shortname as 'spirit', osb.orgid as 'spiritid',
                                    ots.shortname as 'shirt', ots.orgid as 'shirtid'
	    FROM 1orgawards y
	    LEFT JOIN 1orgawards cc ON cc.year = y.year AND cc.award = 'Chairman\'s Choice' LEFT JOIN 0orgs occ on cc.orgid = occ.orgid
	    LEFT JOIN 1orgawards sb ON sb.year = y.year AND sb.award = 'Spirit of Buggy' LEFT JOIN 0orgs osb on sb.orgid = osb.orgid
	    LEFT JOIN 1orgawards ts ON ts.year = y.year AND ts.award = 'T-Shirt Award' LEFT JOIN 0orgs ots on ts.orgid = ots.orgid
      ORDER BY y.year desc;";
  $orgAwards = dbQuery("history",$orgAwardQuery);
?>
<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="designcomp-tab" href="#tab-designcomp" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-designcomp" aria-selected="true">Design Competition</a>
  </li>
  <li class="nav-item">
    <a id="orgawards-tab" href="#tab-orgawards" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-orgawards" aria-selected="false">Organization Awards</a>
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
            <th>Chairman's Choice</th>
            <th>Spirit of Buggy</th>
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
</div>
