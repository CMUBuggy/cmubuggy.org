<?php
  // This is about as dirt simple a person search as we can do.
  //
  // Basically we are providing a minimum functionality to find someone by name, but there's a lot of room for improvement.

  $doSearch = !empty($_GET['term']);

  $MAX_RESULTS = 25;
  $personList = array();
  $searchError = "";
  if ($doSearch) {
    $term = $_GET['term'];

    if (strlen($term) < 3) {
      $searchError = "Please specifiy at least 3 characters.";
    } else {
      $personQuery = "SELECT personid, concat(firstname, ' ', lastname) AS name
                        FROM hist_people
                        WHERE firstname LIKE concat('%', ?, '%') OR lastname LIKE concat('%', ?, '%')
                        LIMIT ".$MAX_RESULTS.";";
      $personData = dbBoundQuery($HISTORY_DATABASE, $personQuery, "ss", $term, $term);
      $personList = $personData->fetch_all(MYSQLI_ASSOC);

      if (count($personList) == 0) {
        $searchError = "No results!";
      }
    }
  }
?>

<h1>People Search</h1>

<p>The history database currently includes people that we have records for as raceday pushers, drivers, and members of the sweepstakes committee.</p>
<form method="get" action="/history/person">
<div class="form-inline my-2">
  <div class="form-group">
    <label for="term">Give us a few characters:</label>
    <input type="text" id="term" name="term" class="form-control mx-sm-3">
  </div>
  <div class="form-group">
    <input type="submit">
  </div>
</div>
</form>
<hr>

<?php
if ($doSearch) {
  if (empty($searchError)) {
    echo "<table>";
    foreach($personList as $p) {
      echo "<tr><td><a href=\"/history/person/".$p["personid"]."\">".$p["name"]."</a></td></tr>";
    }
    //print_r($personList);
    echo "</table>";
    
    if (count($personList) == $MAX_RESULTS) {
      echo("<span class=\"small\">We got a lot of results that time, try a more narrow query.</span>");
    }
  } else {
    echo($searchError);
  }
}
?>