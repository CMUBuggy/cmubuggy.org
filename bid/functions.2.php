<?
include_once("../lib/send_smtp.inc");

class BidResult {
  public $auctionUid;
  public $result;
  public $resultString;
  public $newBids = array();
}

class Bid {
  public $bidAmount;
  public $userId;
  public $bidUid;
  public $autoBid;
  public $auctionUid;
}

class Auction {
  public $auctionUid;
  public $startTime;
  public $org1;
  public $org2;
  public $org3;
  public $buggy1;
  public $buggy2;
  public $buggy3;
  public $heatNum;
  public $day;
  public $gender;
  public $bids = array();
  public $autoBids = array();
}

$gender = array("Mens","Womens");
$buggys = array("aether","avarice","banyan","barracuda","bedlam","blizzard","borealis","brazen","bristol","bungaruskrait","camo","celerity","chaos","chimera","envy","freyja","fuko","haraka","kamikaze","king_of_spades","knightfall","malice","nemesis09","pandora06","peregrine","perun","polaris","powder","problem_child09","problemchild","psychosis","quasar","renaissance09","rubicon","schadenfreude","seraph","skua","svengali","volos","zephyrus","zeus");

$orgs = array("cia","pika","sdc","fringe","sig ep","delta","SigNu","Spirit","AePi","SAE");

$validUserids=array("agoldman","samswift","ckline","carl","40dog","nirunuke","twood","theBoss");
$validBids = array();

$validBids[0]=0;
$validBids[1]=0;

function sendRegEmail($to,$randomNum){
	$mail = array(
	 "to" => $to,
	 "subject" => "CMUBuggy.org Auction account confirmation",
	 "body" => "Thanks for registering for the cmubuggy.org 2014 lead-truck auction!\n\nYour username is ".$to.".\n\nTo confirm your account, just click this link and you'll be on your way:\nhttp://dev.cmubuggy.org/bid/index.demo.UiComplete.4.html?randomNum=$randomNum&mode=register\n\n If you have any trouble logging in, just reply to this e-mail.");
	send($mail);											
}

//sendRegEmail("yanetut@gmail.com");

function registerConfirm($registerNum){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $users = $memcache->get("users");

  foreach($users as $userName=>$userRegisterNum){
    if(intval($registerNum) == $userRegisterNum){
      return 1;
      $users["$userName"]="";
      $memcache->set("users", $users, false, 2592000);
    }
  }
  
  return 0;
  
}

function registerUser($emailAddress){

  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $users = $memcache->get("users");
  $registerNum = $memcache->get("registerNum");
  $registerNum = $registerNum + rand(1,50);
  $memcache->set("registerNum", $registerNum, false, 2592000);
  $users["$emailAddress"]=$registerNum;  
  $memcache->set("users", $users, false, 2592000);
  sendRegEmail($emailAddress,$registerNum);
  return $registerNum;
}

function initMemoryStuff(){
  global $buggys,$orgs,$gender,$validBids,$validUserids;
  
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $memcache->set("totalCollected", 0, false, 2592000);
 
  $auctions = array();
  $users = array();

  $memcache->set("users", $users, false, 2592000);  
  $memcache->set("registerNum", 0, false, 2592000);  

  $y=0; 
  $yy=0;

  
  for($x=0;$x<10;$x++){
    $temp = new Auction();
    $temp->auctionUid=$y;
    $temp->startTime="10:00am";
    $temp->org1=$orgs[rand(0,count($orgs)-1)];
    $temp->org2=$orgs[rand(0,count($orgs)-1)];
    $temp->org3=$orgs[rand(0,count($orgs)-1)];
    $temp->buggy1=$buggys[rand(0,count($buggys)-1)];
    $temp->buggy2=$buggys[rand(0,count($buggys)-1)];
    $temp->buggy3=$buggys[rand(0,count($buggys)-1)];
    $temp->heatNum=$x+1;
    $temp->day="Prelims";
    $temp->gender="Mens";  
    $numBids=0;
    $curBidIndex=0;
    for($xx=0;$xx<$numBids;$xx++){
      $tempBid= new Bid();
      $tempBid->bidAmount = $validBids[$curBidIndex];
      $curBidIndex++;
      $tempBid->userId = $validUserids[rand(0,count($validUserids)-1)];
      $tempBid->bidUid = $yy;
      $yy++;
      $tempBid->autoBid = 0;
      $tempBid->auctionUid = $y;
      array_unshift($temp->bids,$tempBid);    
    }
    $auctions[$y]=$temp;  
    $y++;
  }

  for($x=0;$x<10;$x++){
    $temp = new Auction();
    $temp->auctionUid=$y;
    $temp->startTime="10:00am";
    $temp->org1=$orgs[rand(0,count($orgs)-1)];
    $temp->org2=$orgs[rand(0,count($orgs)-1)];
    $temp->org3=$orgs[rand(0,count($orgs)-1)];
    $temp->buggy1=$buggys[rand(0,count($buggys)-1)];
    $temp->buggy2=$buggys[rand(0,count($buggys)-1)];
    $temp->buggy3=$buggys[rand(0,count($buggys)-1)];
    $temp->heatNum=$x+1;
    $temp->gender="Womens";    
    $temp->day="Prelims";
    $curBidIndex=0;
    for($xx=0;$xx<$numBids;$xx++){
      $tempBid= new Bid();
      $tempBid->bidAmount = $validBids[$curBidIndex];
      $curBidIndex++;
      $tempBid->userId = $validUserids[rand(0,count($validUserids)-1)];
      $tempBid->bidUid = $yy;
      $yy++;
      $tempBid->autoBid = 0;
      $tempBid->auctionUid = $y;
      array_unshift($temp->bids,$tempBid);    
    }
    $auctions[$y]=$temp;  
    $y++;
  }
  
  $temp = new Auction();
  $temp->auctionUid=$y;
  $temp->startTime=microtime();
  $temp->org1=$orgs[rand(0,count($orgs)-1)];
  $temp->org2=$orgs[rand(0,count($orgs)-1)];
  $temp->org3=$orgs[rand(0,count($orgs)-1)];
  $temp->buggy1=$buggys[rand(0,count($buggys)-1)];
  $temp->buggy2=$buggys[rand(0,count($buggys)-1)];
  $temp->buggy3=$buggys[rand(0,count($buggys)-1)];
  $temp->heatNum=1;
  $temp->gender="Womens";    
  $temp->day="Finals";

  for($xx=0;$xx<$numBids;$xx++){
    $tempBid= new Bid();
    $tempBid->bidAmount = $validBids[0];
    $tempBid->userId = $validUserids[rand(0,count($validUserids)-1)];
    $tempBid->bidUid = $yy;
    $yy++;
    $tempBid->autoBid = 0;
    $tempBid->auctionUid = $y;
    array_unshift($temp->bids,$tempBid);    
  }
  $auctions[$y]=$temp;  
  $y++;

  $temp = new Auction();
  $temp->auctionUid=$y;
  $temp->startTime=microtime();
  $temp->org1=$orgs[rand(0,count($orgs)-1)];
  $temp->org2=$orgs[rand(0,count($orgs)-1)];
  $temp->org3=$orgs[rand(0,count($orgs)-1)];
  $temp->buggy1=$buggys[rand(0,count($buggys)-1)];
  $temp->buggy2=$buggys[rand(0,count($buggys)-1)];
  $temp->buggy3=$buggys[rand(0,count($buggys)-1)];
  $temp->heatNum=1;
  $temp->gender="Mens";    
  $temp->day="Finals";

  for($xx=0;$xx<$numBids;$xx++){
    $tempBid= new Bid();
    $tempBid->bidAmount = $validBids[0];
    $tempBid->userId = $validUserids[rand(0,count($validUserids)-1)];
    $tempBid->bidUid = $yy;
    $yy++;
    $tempBid->autoBid = 0;
    $tempBid->auctionUid = $y;
    array_unshift($temp->bids,$tempBid);    
  }
  $auctions[$y]=$temp;  
  $y++;
  

  //  $imageToReturn=$memcache->get($uid."-".intval($page));
  $memcache->set("auctions", $auctions, false, 2592000);
  $memcache->set("mostRecentBid", $y, false, 2592000);
}

function getAuctionsWithChanges($clientAuctionBids){
  
  // expecting an array (keys are auctionUids), with values being the most recent bidUid;
  
  $auctions = getAllAuctions();

  $changedBids = array();
  $changedBidsIndex=0;
  for($x=0;$x<count($auctions);$x++){

    $auctionUid=$auctions[$x]->auctionUid;
    if(count($auctions[$x]->bids)>0){
	$mostRecentBidUidServer=$auctions[$x]->bids[0]->bidUid;
    }
    if (isset($clientAuctionBids[$auctionUid])){
      $clientBid=$clientAuctionBids[$auctionUid];
    } else {
      $clientBid=-1;
    }

    if($clientBid != $mostRecentBidUidServer){
      //      $changedBids[$auctionUid]=getChangedBids($clientBid,$auctions[$x]->bids);
      $changedBids[$changedBidsIndex]=getChangedBids($clientBid,$auctions[$x]->bids);
      $changedBidsIndex++;
    }
    
  }
  return $changedBids;
}

function getChangedBids($mostRecentClientsBid,$serverBids){
  if($mostRecentClientsBid==-1){
    return array_slice($serverBids,0,count($serverBids));
  }

  for($xx=0;$xx<count($serverBids);$xx++){
    //    echo "$mostRecentClientsBid $serverBids[$xx]<br>";

    if($serverBids[$xx]->bidUid == $mostRecentClientsBid && $xx != 0){
      return array_slice($serverBids,0,$xx);
    }
  }
  return array();
}

function dummyAddBid(){
  $time=localtime();
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $auctions = $memcache->get("auctions");

  $newId=$memcache->get("mostRecentBid");

  $newId++;

  $tempBid= new Bid();
  $tempBid->bidAmount = ($auctions[0]->bids[0]->bidAmount)+5;
  $curBidIndex=$curBidIndex+rand(1,10);
  $tempBid->userId = "agoldman";
  $tempBid->bidUid = $newId;
  $tempBid->autoBid = 0;
  $tempBid->auctionUid = 0;
  echo "<br>".$newId."<br>";
  echo $tempBid->bidAmount."<br>"; 
  array_unshift($auctions[0]->bids,$tempBid);    
  $memcache->set("mostRecentBid", $newId, false, 2592000);
  $memcache->set("auctions", $auctions, false, 2592000);
  $time2= localtime();
  echo "$time[0] $time2[0]<br>";
}

function getMostRecentBid(){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $auctionEnd = date_create('2012-04-20');
  $currentDate = date_create();
  $timeTillRaces=date_diff($auctionEnd, $currentDate); 
  $timeTillRaces->format("%d days");
  $totalRaised=$memcache->get("totalCollected");
  $cheapestPrelimHeat=$memcache->get("cheapestPrelimHeat");
  //  $timeLeft=$timeTillRaces->m." months, ".$timeTillRaces->d." days, ".$timeTillRaces->h." hours, ".$timeTillRaces->i." minutes, ".$timeTillRaces->s." seconds" ;
  $timeLeft = $timeTillRaces->format("%a days %h hours %i minutes left");
  return array('mostRecentBid'=>$memcache->get("mostRecentBid"),'timeLeft'=>$timeLeft,'totalRaised'=>$totalRaised,'cheapestHeat'=>$cheapestPrelimHeat); 
}

function getAllAuctions(){

  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");


  return $memcache->get("auctions");

}

function getAuction($auctionId){
  global $buggys,$orgs,$gender;

  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $auctions = $memcache->get("auctions");

  return   $auctions[$auctionId];
}

/*
  
  makeManualBid()
  fireAutoBids()
  makeAutoBid()


 */

function makeManualBid($userId,$amount,$auctionUid,$fireAuto){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $bidResult = new BidResult();  
  $bidResult->$auctionUid=$auctionUid;

  $auctions = $memcache->get("auctions");  

  $totalCollected = 0;
  $cheapestHeatAmount = 9999;
  $cheapestHeat = "";

  
  $curHighBid=$auctions[$auctionUid]->bids[0];

  if(intval($amount)<=$curHighBid->bidAmount){
   if($auctions[$auctionUid]->day=="Prelims"){
    $bidResult->result=0;
    $bidResult->resultString="Higher bid has already <br>been entered";
    return $bidResult;
   }
  }

  $tempBid= new Bid();
  $tempBid->bidAmount = $amount;
  $tempBid->userId = $userId;
  $tempBid->bidUid = ($memcache->get("mostRecentBid"))+1;
  $tempBid->autoBid = 0;
  $tempBid->auctionUid = $auctionUid;  
  array_unshift($auctions[$auctionUid]->bids,$tempBid);      
  $memcache->set("mostRecentBid", $tempBid->bidUid, false, 2592000);
  $memcache->set("auctions", $auctions, false, 2592000);

  if($fireAuto==0){
    fireAutoBids($auctionUid);
  }

  $bidResult->result=1;
  $bidResult->resultString="bid succesfully entered";

  for($za=0;$za<count($auctions);$za++){
    if($auctions[$za]->day=="Prelims"){
      if(count($auctions[$za]->bids)>0){
       $totalCollected=$totalCollected+$auctions[$za]->bids[0]->bidAmount;
       if($cheapestHeatAmount>$auctions[$za]->bids[0]->bidAmount){
	 $cheapestHeatAmount=$auctions[$za]->bids[0]->bidAmount;
	 $cheapestHeat=$auctions[$za]->gender." Heat #".$auctions[$za]->heatNum." / $".$cheapestHeatAmount;
       }
      } else {
  	 $cheapestHeatAmount=0;
	 $cheapestHeat=$auctions[$za]->gender." Heat #".$auctions[$za]->heatNum." / $".$cheapestHeatAmount;
      }
    } else {
      if($auctions[$za]->gender == "Mens"){
	for($zb=0;$zb<count($auctions[$za]->bids) && $zb<10;$zb++){
	  if(count($auctions[$za]->bids)>0){
	    $totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	  }
	}
      } else {
	for($zb=0;$zb<count($auctions[$za]->bids) && $zb<5;$zb++){
	  if(count($auctions[$za]->bids)>0){
	    $totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	  }
	}
      }
    }
  }

  if($auctions[$auctionUid]->day!="Prelims"){
   usort($auctions[$auctionUid]->bids,"cmpBids");  
   $memcache->set("auctions", $auctions, false, 2592000);
  }
  $memcache->set("totalCollected", $totalCollected, false, 2592000);
  if($cheapestHeatAmount<1000){
  $memcache->set("cheapestPrelimHeat",$cheapestHeat, false, 2592000);
  }

  return $bidResult;
}

function fireAutoBids($auctionUid){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $bidResult = new BidResult();  
  $bidResult->$auctionUid=$auctionUid;

  $auctions = $memcache->get("auctions");

  $auction=$auctions[$auctionUid];
  $autoBids = $auction->autoBids;
  $topBid = $auction->bids[0]->bidAmount;
  
  for($x=0;$x<count($autoBids);$x++){
    if($autoBids[$x]->bidAmount > $topBid){
      if($x<count($autoBids)-1){
	for($y=$x;$y<count($autoBids)-1;$y++){
	  makeManualBid($autoBids[$y]->userId,$autoBids[$y]->bidAmount,$auctionUid,1);	  
	  $userId=$autoBids[$y]->userId;
	  echo "made bid ".$autoBids[$y]->userId."-- ".$autoBids[$y]->bidAmount." $y<br>"; 
	}
	makeManualBid($autoBids[$y]->userId,($autoBids[$y-1]->bidAmount)+1,$auctionUid,1);	  
	//	echo "made bid "+$autoBids[$y]->userId+"-- "+($autoBids[$y-1]->bidAmount+1)+" "+($y-1)+"<br>"; 
	return;
      } else {
	makeManualBid($autoBids[$x]->userId,$topBid+1,$auctionUid,1);
	return;
      }
    }
  }
}

function cmpBids($a,$b){
  if($a->bidAmount == $b->bidAmount){
    return 0;
  }
  return ($a->bidAmount < $b->bidAmount) ? -1 : 1;
}


function makeAutoBid($userId,$amount,$auctionUid){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $bidResult = new BidResult();  
  $bidResult->$auctionUid=$auctionUid;

  $auctions = $memcache->get("auctions");

  
  /*  if(intval($amount)<=$curHighBid->bidAmount){
    $bidResult->result=0;
    $bidResult->resultString="a higher bid as already been entered - $amount";
    return $bidResult;
 }*/

  if($auctions[$auctionUid]->bids[0]->bidAmount>=$amount){
    $bidResult->result=0;
    $bidResult->resultString="autobid is lower than current high bid";
    return $bidResult;
  }
  $tempBid= new Bid();
  $tempBid->bidAmount = $amount;
  $tempBid->userId = $userId;
  $tempBid->autoBid = 1;
  $tempBid->auctionUid = $auctionUid;  


  $existingAutobid=0;

  for($xa=0;$xa<count($auctions[$auctionUid]->autoBids);$xa++){
    if($auctions[$auctionUid]->autoBids[$xa]->userId == $userId){
      $auctions[$auctionUid]->autoBids[$xa]=$tempBid;
      $existingAutobid=1;
    } 
  }
  if($existingAutobid==0){
    $tempBid->bidUid = ($memcache->get("mostRecentBid"))+1;
    array_unshift($auctions[$auctionUid]->autoBids,$tempBid);      
    $memcache->set("mostRecentBid", $tempBid->bidUid, false, 2592000);
  }
  usort($auctions[$auctionUid]->autoBids,"cmpBids");  

  $memcache->set("auctions", $auctions, false, 2592000);
  if($auctions[$auctionUid]->bids[0]->userId!=$userId){
    fireAutoBids($auctionUid);    
  }
  $bidResult->result=1;
  $bidResult->resultString="autobid succesfully entered";

  
  
  return $bidResult;
}

?>