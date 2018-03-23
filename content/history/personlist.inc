<?php
  $person = new person();
  $personListLast = $person->GetList(array(array("personId", ">", "0")),"lastName");
?>

<h1>Search</h1>

<p>The history database currently includes people that we have records for as raceday pushers, drivers, and members of the sweepstakes committee (<?php echo(count($personListLast)); ?> people at the moment). We plan to include mechanics and organization leaders soon.</p>

<div class="form-inline my-2">
  <div class="form-group">
    <label for="personinput2">First Name</label>
    <input type="text" id="personinput2" class="form-control mx-sm-3">
  </div>
  <div class="form-group">
    <label for="personinput">Last Name</label>
    <input type="text" id="personinput" class="form-control mx-sm-3">
  </div>
</div>
