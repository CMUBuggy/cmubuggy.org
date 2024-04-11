<?php
  // Time out around the time races would have ended.
  // (default timezone already set in pre-content.inc)
  $rainoutenddate = mktime(12, 59, 0, 4, 12, 2024);

  // Why?
  $rainoutreason = "inclement weather.";

  // Where will we see you next?
  $seeyouat = "the Finals Races, tomorrow 7:30am!";
  //$seeyouat = "the Awards Ceremony.";

  if (time() < $rainoutenddate) {
?>
    <div class="card mb-3">
      <h5 class="card-header">Races Canceled Today</h5>
      <div class="card-body">
        <p>Races have been canceled for today due to <?php echo($rainoutreason); ?></p>
        <p>See you at <?php echo($seeyouat); ?></p>
      </div>
    </div>
<?php } ?>
    
