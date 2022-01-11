<?php
  function getAllSweepstakes() {
    $query = "SELECT DISTINCT y.year,
                              concat(pch.firstname, ' ', pch.lastname) AS chair, pch.personid AS chairid,
	                            concat(pac.firstname, ' ', pac.lastname) AS asst, pac.personid AS asstid,
	                            concat(psf.firstname, ' ', psf.lastname) AS safety, psf.personid AS safetyid,
	                            concat(phj.firstname, ' ', phj.lastname) AS judge, phj.personid AS judgeid
                  FROM hist_sweepstakes y
                    LEFT JOIN hist_sweepstakes ch ON ch.year = y.year AND ch.role = 'Sweepstakes Chairman'
                      LEFT JOIN hist_people pch ON ch.personid = pch.personid
	                  LEFT JOIN hist_sweepstakes ac ON ac.year = y.year AND ac.role = 'Assistant Chairman'
                      LEFT JOIN hist_people pac ON ac.personid = pac.personid
	                  LEFT JOIN hist_sweepstakes sf ON sf.year = y.year AND sf.role = 'Safety Chairman'
                      LEFT JOIN hist_people psf ON sf.personid = psf.personid
	                  LEFT JOIN hist_sweepstakes hj ON hj.year = y.year AND hj.role = 'Head Judge'
                      LEFT JOIN hist_people phj ON hj.personid = phj.personid
                  ORDER BY y.year DESC;";

    global $HISTORY_DATABASE;
    return dbQuery($HISTORY_DATABASE, $query);
  }

  function getSweepstakesYear($year) {
    // We are cheating a bit by using ORDER BY field here.  We do 10 - FIELD() to put unknown roles at the bottom and
    // ensure that Chair, Asst Chair, and Safety are at the top.
    $query = "SELECT role, concat(p.firstname, ' ', p.lastname) AS name, s.personid AS id
                FROM hist_sweepstakes s
                LEFT JOIN hist_people p ON s.personid = p.personid
                WHERE year=?
                ORDER BY 10 - FIELD(role,
                                    'Sweepstakes Advisor', 'Buggy Book Chairman', 'Design Comp Chairman',
                                    'Head Judge', 'Safety Chairman', 'Assistant Chairman', 'Sweepstakes Chairman');";

    global $HISTORY_DATABASE;
    return dbBoundQuery($HISTORY_DATABASE, $query, "d", $year);
  }

  // If "year" parameter is supplied, show all known positions for that year.
  if(!empty($_GET["year"])){
    $year = $_GET["year"];
    $sweeps = getSweepstakesYear($_GET["year"]);

    echo("<h1>Sweepstakes Committee ".$year."</h1>");
    echo("<dl class=\"row\">");
    while($r = $sweeps->fetch_assoc()) {
      echo("<dt class=\"col-sm-5\">".$r["role"]."</dt>");
      echo("<dd class=\"col-sm-7\"><a href=\"/history/person/".$r["id"]."\">".$r["name"]."</a></dd>");
    }
  } else {
    // Show all years, but only 4 roles.
    $sweeps = getAllSweepstakes();
?>
  <h1>Sweepstakes Committees</h1>
  <div class="table-responsive">
    <table class="table">
      <thead>
        <tr>
          <th>Year</th>
          <th>Sweepstakes Chair</th>
          <th>Assistant Chair</th>
          <th>Safety Chair</th>
          <th>Head Judge</th>
        </tr>
      </thead>
      <tbody>
        <?php
          while($s = $sweeps->fetch_assoc()) {
            echo "<tr>";
            echo "<td><a href=\"/history/sweepstakes/".$s["year"]."\">".$s["year"]."</a></td>";
            echo "<td><a href=\"/history/person/".$s["chairid"]."\">".$s["chair"]."</a></td>";
            echo "<td><a href=\"/history/person/".$s["asstid"]."\">".$s["asst"]."</a></td>";
            echo "<td><a href=\"/history/person/".$s["safetyid"]."\">".$s["safety"]."</a></td>";
            echo "<td><a href=\"/history/person/".$s["judgeid"]."\">".$s["judge"]."</a></td>";
            echo "</tr>";
          }
        ?>
      </tbody>
    </table>
  </div>
<?php } ?>

