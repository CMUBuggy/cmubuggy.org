<?php
  function getSweepstakesByYear($year){
    $sweepstakes = new sweepstakes();
    $sweepstakesCommittee = $sweepstakes->GetList(array(array("year","=",$year)));
    $committeeArr = array();
    foreach($sweepstakesCommittee as $sweepstakes){
      $sweepstakesRole = $sweepstakes->GetSweepstakesrole();
      $person = $sweepstakes->GetPerson();
      $committeeArr[$sweepstakesRole->description] = $person;
    }
    return $committeeArr;
  }

  if(!empty($_GET["year"])){
    $year = $_GET["year"];
    $sweepstakesRole = new sweepstakesRole();
    $sweepstakesRoleList = $sweepstakesRole->GetList(array(array("sweepstakesRoleId", ">", "0")));
    $committeeArr = getSweepstakesByYear($year);

    echo("<h1>Sweepstakes Committee ".$year."</h1>");
    echo("<dl class=\"row\">");
    foreach($sweepstakesRoleList as $sweepstakesRole){
      $person = new person();
      if(isset($committeeArr[$sweepstakesRole->description])){
        $person = $committeeArr[$sweepstakesRole->description];
        echo("<dt class=\"col-sm-5\">".$sweepstakesRole->description."</dt>");
        echo("<dd class=\"col-sm-7\"><a href=\"/history/person/".$person->personId."\">".$person->firstName." ".$person->lastName."</a></dd>");
      }
    }
    echo("</dl>");
  } else {
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
        </tr>
      </thead>
      <tbody>
        <?php
          for ($year = 2011; $year >= 1965; $year--) {
            $committeeArr = getSweepstakesByYear($year);
            $personC = new person();
            $personAC = new person();
            $personSC = new person();

            if (isset($committeeArr["Sweepstakes Chairman"])) {
              $personC = $committeeArr["Sweepstakes Chairman"];
            }
            if (isset($committeeArr["Assistant Chairman"])) {
              $personAC = $committeeArr["Assistant Chairman"];
            }
            if (isset($committeeArr["Safety Chairman"])) {
              $personSC = $committeeArr["Safety Chairman"];
            }
            echo "<tr>";
            echo "<td><a href=\"/history/sweepstakes/".$year."\">".$year."</a></td>";
            echo "<td><a href=\"/history/person/".$personC->personId."\">".$personC->firstName." ".$personC->lastName."</a></td>";
            echo "<td><a href=\"/history/person/".$personAC->personId."\">".$personAC->firstName." ".$personAC->lastName."</a></td>";
            echo "<td><a href=\"/history/person/".$personSC->personId."\">".$personSC->firstName." ".$personSC->lastName."</a></td>";
            echo "</tr>";
          }
        ?>
      </tbody>
    </table>
  </div>
<?php } ?>

