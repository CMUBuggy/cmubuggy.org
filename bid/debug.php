<?php

include "functions.php";

  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $auctions = $memcache->get("cheapestPrelimHeat");

  echo json_encode($auctions);
?>