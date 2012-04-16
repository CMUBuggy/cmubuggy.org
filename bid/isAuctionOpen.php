<?
 $auctionEnd = date_create('2012-04-18 21:00:00');
// $auctionStart = date_create('2012-04-17 9:00:00');
 $auctionStart = date_create('2012-04-15 17:00:00');
 $currentDate = date_create();
 $timeTillAuctionStart=date_diff($auctionStart, $currentDate, false); 
 $timeTillAuctionEnd=date_diff($auctionEnd, $currentDate); 
 if($timeTillAuctionStart->invert == 1 || $timeTillAuctionEnd->invert == 0){
  echo json_encode(array("auctionGo"=>"0"));
 } else {
  echo json_encode(array("auctionGo"=>"1"));
 }


?>
