<?php

include "functions.php";

$userId=$_GET['userId'];
$auctionUid=$_GET['auctionUid'];
$amount=$_GET['amount'];

echo json_encode(makeAutoBid($userId,$amount,$auctionUid));

?>