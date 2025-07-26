<?php

// Note: Constant Query, dbQuery() is safe.
$motdQuery = "SELECT option_value FROM wp_options where option_name='cmubuggy-motd'";

$motdResult = false;
try {
  $motdResult = dbQuery("cmubuggy_wp", $motdQuery);
} catch (Exception $e) {
  // If there's an error (e.g. no wordpress database on this instance), just act as if there are
  // no results.  Its fine.
}

if ($motdResult) {
  if ($motdResult->num_rows > 1) {
    // option_name should be a unique index.  What has wordpress done if we get here?
    //
    // Debatable if we should die or fail silently here, I'll choose to die for now, so we notice when they
    // break it (and it seems unlikely to break).
    die ("unexpected number of rows for motd query");
  }
  if ($motdResult->num_rows == 1) {
    $motd = $motdResult->fetch_assoc()['option_value'];

    // Attention: We trust this field, since it is assumed to have come from an admin.  Not really worse than
    // what we do elsewhere for wordpress though.
?>

<div class="card mb-3">
    <h5 class="card-header">Important Message</h5>
    <div class="card-body">
      <?php echo($motd); ?>
    </div>
</div>

<?php
  }
}
?>
