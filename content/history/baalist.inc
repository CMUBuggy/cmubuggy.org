<?php
  // TODO: Maybe re-merge this with sweepstakeslist.inc, it is basically identical except
  // for the table name, headline roles, "committee" vs "board", and yearly detail url.
  function getAllBAA() {
    $query = "SELECT DISTINCT y.year,
                              concat(pp.firstname, ' ', pp.lastname) AS pres, pp.personid AS presid,
	                            concat(pvp.firstname, ' ', pvp.lastname) AS vp, pvp.personid AS vpid,
	                            concat(ps.firstname, ' ', ps.lastname) AS sec, ps.personid AS secid,
	                            concat(pt.firstname, ' ', pt.lastname) AS tres, pt.personid AS tresid
                  FROM hist_baa y
                    LEFT JOIN hist_baa p ON p.year = y.year AND p.role = 'President'
                      LEFT JOIN hist_people pp ON p.personid = pp.personid
	                  LEFT JOIN hist_baa vp ON vp.year = y.year AND vp.role = 'Vice President'
                      LEFT JOIN hist_people pvp ON vp.personid = pvp.personid
	                  LEFT JOIN hist_baa s ON s.year = y.year AND s.role = 'Secretary'
                      LEFT JOIN hist_people ps ON s.personid = ps.personid
	                  LEFT JOIN hist_baa t ON t.year = y.year AND t.role = 'Treasurer'
                      LEFT JOIN hist_people pt ON t.personid = pt.personid
                  ORDER BY y.year DESC;";

    global $HISTORY_DATABASE;
    return dbQuery($HISTORY_DATABASE, $query);
  }

  // Show all years, but only 4 roles.
  $sweeps = getAllBAA();
?>
<p class="font-italic">To see the full board, click on the year.</p>
<div class="table-responsive">
  <table class="table">
    <thead>
      <tr>
        <th>Year</th>
        <th>President</th>
        <th>Vice President</th>
        <th>Secretary</th>
        <th>Treasurer</th>
      </tr>
    </thead>
    <tbody>
      <?php
        while($s = $sweeps->fetch_assoc()) {
          echo "<tr>";
          echo "<td><a href=\"/history/baa/".$s["year"]."\">".$s["year"]."</a></td>";
          echo "<td><a href=\"/history/person/".$s["presid"]."\">".$s["pres"]."</a></td>";
          echo "<td><a href=\"/history/person/".$s["vpid"]."\">".$s["vp"]."</a></td>";
          echo "<td><a href=\"/history/person/".$s["secid"]."\">".$s["sec"]."</a></td>";
          echo "<td><a href=\"/history/person/".$s["tresid"]."\">".$s["tres"]."</a></td>";
          echo "</tr>";
        }
      ?>
    </tbody>
  </table>
</div>

