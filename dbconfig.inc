<?php
  $config_json_str = file_get_contents($_SERVER['DOCUMENT_ROOT'].'/dbconfig.json');
  $config = json_decode($config_json_str);

  $dbhost = $config->DB_HOST;
  $dbuser = $config->DB_USER;
  $dbpass = $config->DB_PASSWORD;

  $HISTORY_DATABASE = $config->DB_NAME;  // '[database name for history data]'

  $ENABLE_GA_TAG = $config->GA_TAG;  // false or unset will prevent GA tag from showing

  // If false or unset, disable the static components of the allgender UI.
  //
  // This is only a aunch flag for the static components, if there is data present, it should generally
  // be displayed even if it cannot be filtered because the static component is missing.
  //
  // In other words, this is expected to be a relatively short-lived flag.
  //
  // TODO: remove this code after raceday 2023.
  $ALLGENDER_UI_ENABLED = isset($config->ALLGENDER_UI_ENABLED) && $config->ALLGENDER_UI_ENABLED;
?>
