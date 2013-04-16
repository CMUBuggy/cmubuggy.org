<?
include "functions.php";

/*function calculateTotalRaised(){

  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $auctions = $memcache->get("auctions");  

  $mensWinners = array();
  $womensWinners = array();
  $totalMensBids=0;
  $totalWomensBids=0;

  $totalCollected=0;

  for($za=0;$za<count($auctions);$za++){
    if($auctions[$za]->day=="Prelims"){
      if(count($auctions[$za]->bids)>0){
       $totalCollected=$totalCollected+$auctions[$za]->bids[0]->bidAmount;
      }
    } else {
      if($auctions[$za]->gender == "Mens"){
	for($zb=0;$zb<count($auctions[$za]->bids);$zb++){
	  $bidUser=$auctions[$za]->bids[$zb]->userId;
	  if(count($auctions[$za]->bids)>0 && !isset($mensWinners["$bidUser"]) && $totalMensBids<6){
	    $totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	    $mensWinners["$bidUser"]="bid";
	    $totalMensBids++;
	  }
	}
      } else {
	for($zb=0;$zb<count($auctions[$za]->bids);$zb++){
	  $bidUser=$auctions[$za]->bids[$zb]->userId;
	  if(count($auctions[$za]->bids)>0 && !isset($womensWinners["$bidUser"]) && $totalWomensBids<4){
	    $totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	    $totalWomensBids++;
	    $womensWinners["$bidUser"]="bid";
	  }
	}
      }
    }
  }
 return $totalCollected;
}*/


 echo calculateTotalRaised();
?>