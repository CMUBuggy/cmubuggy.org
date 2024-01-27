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
    $query = "SELECT role, concat(p.firstname, ' ', p.lastname) AS name, s.personid AS id
                FROM hist_sweepstakes s
                LEFT JOIN hist_people p ON s.personid = p.personid
                WHERE year=?
                ORDER BY role, p.lastname, p.firstname;";
                
    global $HISTORY_DATABASE;
    return dbBoundQuery($HISTORY_DATABASE, $query, "d", $year);
  }

  // If "year" parameter is supplied, show all known positions for that year.
  if(!empty($_GET["year"])){
    $year = $_GET["year"];
    $sweeps = getSweepstakesYear($_GET["year"]);

?>
    <div class="row align-items-center mb-4">
      <div class="col col-sm-8 col-md-9">
        <h1 class="text-center">Sweepstakes Committee <?php echo($year);?></h1>
      </div>
      <div class="d-none d-sm-flex col justify-content-end">
        <img class="img-fluid" style="max-height:150px" src="/img/logos/sweepstakes_logo_notext.svg">
      </div>
    </div>
<?php

    echo("<dl class=\"row\">");
    while($r = $sweeps->fetch_assoc()) {
      echo("<dt class=\"col-6 my-1 d-sm-flex justify-content-end\">".$r["role"]."</dt>");
      echo("<dd class=\"col-6 my-1 d-flex align-items-center\"><a href=\"/history/person/".$r["id"]."\">".$r["name"]."</a></dd>");
    }
  } else {
    // Show all years, but only 4 roles.
    $sweeps = getAllSweepstakes();
?>
  <p class="font-italic">To see the full committee, click on the year.</p>
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

