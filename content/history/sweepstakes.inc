<?php
  function getSweepstakesYear($year) {
    $query = "SELECT role, concat(p.firstname, ' ', p.lastname) AS name, s.personid AS id
                FROM hist_sweepstakes s
                LEFT JOIN hist_people p ON s.personid = p.personid
                WHERE year=?
                ORDER BY role, p.lastname, p.firstname;";
                
    global $HISTORY_DATABASE;
    return dbBoundQuery($HISTORY_DATABASE, $query, "d", $year);
  }

  // Should always have a year, due to htaccess routing.
  $year = $_GET["year"] * 1;
  $sweeps = getSweepstakesYear($_GET["year"]);
?>
<?php
  if ($sweeps->num_rows > 0) {
    echo("<dl class=\"row\">");
    while($r = $sweeps->fetch_assoc()) {
      echo("<dt class=\"col-6 my-1 d-sm-flex justify-content-end\">".$r["role"]."</dt>");
      echo("<dd class=\"col-6 my-1 d-flex align-items-center\"><a href=\"/history/person/".$r["id"]."\">".$r["name"]."</a></dd>");
    }
    echo("</dl>");
  } else {
    echo("<i>Sorry, no committee data exists for this year.</i>");
  }
?>


