<?
include "functions.php";

$clientAuctionBids = json_decode($_GET['clientAuctionHighBids']); 
echo json_encode(getAuctionsWithChanges($clientAuctionBids));

?>