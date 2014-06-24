<?
include_once("../lib/send_smtp.inc");
include_once("../lib/pog/pog_includes.inc");



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
$buggys = array("aether","avarice","banyan","barracuda","bedlam","blizzard","borealis","brazen","bristol","bungaruskrait","camo","celerity","chaos","chimera","envy","freyja","fuko","haraka","kamikaze","king_of_spades","knightfall","malice","nemesis09","pandora06","barracuda","perun","polaris","powder","problem_child09","problemchild","psychosis","quasar","renaissance09","rubicon","schadenfreude","seraph","skua","svengali","volos","zephyrus","zeus","empty");

$orgBuggys = array("Aepi"=>"aether","SDC"=>"envy","Spirit"=>"seraph","Fringe"=>"blizzard","CIA"=>"freyja","SigNu"=>"bungaruskrait","SigEp"=>"perun","SAE"=>"rubicon","Pika"=>"zeus","Apex"=>"barracuda");


$buggysMens = array();
$buggyWoMens = array();
$orgsMens = array();

$orgsMens[0] = array();
$orgsMens[0][0] = "SDC C";
$orgsMens[0][1] = "Spirit B";
$orgsMens[0][2] = "Fringe D";
$buggysMens[0] = array();
$buggysMens[0][0] = "zeus";
$buggysMens[0][1] = "seraph";
$buggysMens[0][2] = "freyja";

$orgsMens[1] = array();
$orgsMens[1][0] = "CIA A";
$orgsMens[1][1] = "SigNu A";
$orgsMens[1][2] = "SigEp B";

$buggysMens[1]=array();
$buggysMens[1][0] = "barracuda";
$buggysMens[1][1] = "insite";
$buggysMens[1][2] = "rubicon";

$orgsMens[2] = array();
$orgsMens[2][0] = "Fringe B";
$orgsMens[2][1] = "SDC D";
$orgsMens[2][2] = "SigEp D";
$buggysMens[2]=array();
$buggysMens[2][0] = "blizzard";
$buggysMens[2][1] = "malice";
$buggysMens[2][2] = "barracuda";

$orgsMens[3] = array();
$orgsMens[3][0] = "Spirit A";
$orgsMens[3][1] = "SigEp C";
$orgsMens[3][2] = "CIA C";
$buggysMens[3]=array();
$buggysMens[3][0] = "seraph";
$buggysMens[3][1] = "freyja";
$buggysMens[3][2] = "empty";

$orgsMens[4] = array();
$orgsMens[4][0] = "SDC B";
$orgsMens[4][1] = "Fringe C";
$orgsMens[4][2] = "SAE B";
$buggysMens[4]=array();
$buggysMens[4][0] = "malice";
$buggysMens[4][1] = "blizzard";
$buggysMens[4][2] = "empty";

$orgsMens[5] = array();
$orgsMens[5][0] = "Pika A";
$orgsMens[5][1] = "Aepi A";
$orgsMens[5][2] = "Apex B";
$buggysMens[5]=array();
$buggysMens[5][0] = "barracuda";
$buggysMens[5][1] = "seraph";
$buggysMens[5][2] = "freyja";

$orgsMens[6] = array();
$orgsMens[6][0] = "SigEp A";
$orgsMens[6][1] = "Spirit C";
$orgsMens[6][2] = "SAE A";
$buggysMens[6]=array();
$buggysMens[6][0] = "zeus";
$buggysMens[6][1] = "rubicon";
$buggysMens[6][2] = "blizzard";

$orgsMens[7] = array();
$orgsMens[7][0] = "Fringe A";
$orgsMens[7][1] = "CIA B";
$orgsMens[7][2] = "Spirit D";
$buggysMens[7]=array();
$buggysMens[7][0] = "malice";
$buggysMens[7][1] = "barracuda";
$buggysMens[7][2] = "seraph";

$orgsMens[8] = array();
$orgsMens[8][0] = "SDC A";
$orgsMens[8][1] = "Pika B";
$orgsMens[8][2] = "Apex A";
$buggysMens[8]=array();
$buggysMens[8][0] = "blizzard";
$buggysMens[8][1] = "bungaruskrait";
$buggysMens[8][2] = "barracuda";

for($x=0;$x<9;$x++){
 for($y=0;$y<3;$y++){
  preg_match("/^(.+)\ (A|B|C|D)$/",$orgsMens[$x][$y],$result);     
  $orgName = $result[1];
//  echo $orgName."<br>";
  $buggysMens[$x][$y] = $orgBuggys[$orgName];
 }	
}

$orgsWoMens = array();
$orgsWoMens[0] = array();
$orgsWoMens[0][0] = "SDC C";
$orgsWoMens[0][1] = "Apex A";
$orgsWoMens[0][2] = "CIA C";
$buggysWoMens[0]=array();
$buggysWoMens[0][0] = "zeus";
$buggysWoMens[0][1] = "barracuda";
$buggysWoMens[0][2] = "freyja";

$orgsWoMens[1] = array();
$orgsWoMens[1][0] = "Spirit A";
$orgsWoMens[1][1] = "SigEp C";
$orgsWoMens[1][2] = "Fringe D";
$buggysWoMens[1]=array();
$buggysWoMens[1][0] = "seraph";
$buggysWoMens[1][1] = "malice";
$buggysWoMens[1][2] = "freyja";

$orgsWoMens[2] = array();
$orgsWoMens[2][0] = "CIA A";
$orgsWoMens[2][1] = "Pika A";
$orgsWoMens[2][2] = "SDC D";
$buggysWoMens[2]=array();
$buggysWoMens[2][0] = "malice";
$buggysWoMens[2][1] = "rubicon";
$buggysWoMens[2][2] = "empty";


$orgsWoMens[3] = array();
$orgsWoMens[3][0] = "SigEp A";
$orgsWoMens[3][1] = "Spirit C";
$orgsWoMens[3][2] = "Fringe B";
$buggysWoMens[3]=array();
$buggysWoMens[3][0] = "barracuda";
$buggysWoMens[3][1] = "blizzard";
$buggysWoMens[3][2] = "empty";


$orgsWoMens[4] = array();
$orgsWoMens[4][0] = "SDC B";
$orgsWoMens[4][1] = "Spirit B";
$orgsWoMens[4][2] = "Apex B";
$buggysWoMens[4]=array();
$buggysWoMens[4][0] = "malice";
$buggysWoMens[4][1] = "freyja";
$buggysWoMens[4][2] = "blizzard";


$orgsWoMens[5] = array();
$orgsWoMens[5][0] = "Fringe A";
$orgsWoMens[5][1] = "SigEp B";
$orgsWoMens[5][2] = "Aepi A";
$buggysWoMens[5]=array();
$buggysWoMens[5][0] = "blizzard";
$buggysWoMens[5][1] = "seraph";
$buggysWoMens[5][2] = "insite";

$orgsWoMens[6] = array();
$orgsWoMens[6][0] = "SDC A";
$orgsWoMens[6][1] = "CIA B";
$orgsWoMens[6][2] = "Fringe C";
$buggysWoMens[6]=array();
$buggysWoMens[6][0] = "malice";
$buggysWoMens[6][1] = "freyja";
$buggysWoMens[6][2] = "kamikaze";

for($x=0;$x<7;$x++){
 for($y=0;$y<3;$y++){
  preg_match("/^(.+)\ (A|B|C|D)$/",$orgsMens[$x][$y],$result);     
  $orgName = $result[1];
//  echo $orgName."<br>";
  $buggysWoMens[$x][$y] = $orgBuggys[$orgName];
 }	
}



$orgs = array("CIA A","CIA B","CIA C","CIA D","Fringe A","Fringe B","Fringe C", "SigEp A", "SigEp B", "SigEp C", "SigEp D","Spirit A","Spirit B","Spirit C","Spirit D","Pika A", "Pika B", "Pika C", "Pika D", "SDC A", "SDC B", "SDC C", "SDC D", "SigNu A", "SigNu B", "Apex A", "SAE A", "SAE B", "DF A","Aepi A","Aepi B","Aepi C","ROTC A","Empty");

$validUserids=array("agoldman","samswift","ckline","carl","40dog","nirunuke","twood","theBoss");
$validBids = array();

$validBids[0]=0;
$validBids[1]=0;

function sendRegEmail($to,$randomNum){
	$mail = array(
	 "to" => $to,
	 "subject" => "CMUBuggy.org Auction account confirmation",
	 "body" => "Thanks for registering for the cmubuggy.org 2014 lead-truck auction!\n\nYour username is ".$to.".\n\nTo confirm your account, just click this link and you'll be on your way:\nhttp://www.cmubuggy.org/bid/index.html?randomNum=$randomNum&mode=register&userId=$to\n\n If you have any trouble logging in, send email to admin@cmubuggy.org.");
	send($mail);											
}

//sendRegEmail("yanetut@gmail.com");

function registerConfirm($registerNum){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $users = $memcache->get("users");

  foreach($users as $userName=>$userRegisterNum){
    if(intval($registerNum) == $userRegisterNum){
      $users["$userName"]="good";
      $memcache->set("users", $users, false, 2592000);
      return 1;
    }
  }
  
  return 0;
  
}

function registerUserOptional($userId,$firstName,$lastName,$phoneNum){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $usersOptional = $memcache->get("usersOptional");
  $usersOptional["$userId"]="$firstName,$lastName,$phoneNum";
  $memcache->set("usersOptional", $usersOptional, false, 2592000);
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

function initHeatsMemoryStuff(){
  global $orgs,$buggys,$buggysMens,$buggysWoMens,$orgsMens,$orgsWoMens,$gender,$validBids,$validUserids;
  
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $auctions = array();

  $y=0; 
  $yy=0;

  for($x=0;$x<9;$x++){
    $temp = new Auction();
    $temp->auctionUid=$y;
    $temp->startTime="10:00am";
    $temp->org1=$orgsMens[$x][0];//rand(0,count($orgs)-1)];
    $temp->org2=$orgsMens[$x][1];//rand(0,count($orgs)-1)];
    $temp->org3=$orgsMens[$x][2];//rand(0,count($orgs)-1)];
    $temp->buggy1=$buggysMens[$x][0];//[rand(0,count($buggys)-1)];
    $temp->buggy2=$buggysMens[$x][1];//rand(0,count($buggys)-1)];
    $temp->buggy3=$buggysMens[$x][2];//rand(0,count($buggys)-1)];
    $temp->heatNum=$x+1;
    $temp->day="Prelims";
    $temp->gender="Mens";  
    $numBids=0;
    $curBidIndex=0;
    $auctions[$y]=$temp;  
    $y++;
  }

  for($x=0;$x<7;$x++){
    $temp = new Auction();
    $temp->auctionUid=$y;
    $temp->startTime="10:00am";
    $temp->org1=$orgsWoMens[$x][0];//rand(0,count($orgs)-1)];
    $temp->org2=$orgsWoMens[$x][1];//rand(0,count($orgs)-1)];
    $temp->org3=$orgsWoMens[$x][2];//rand(0,count($orgs)-1)];
    $temp->buggy1=$buggysWoMens[$x][0];//[rand(0,count($buggys)-1)];
    $temp->buggy2=$buggysWoMens[$x][1];//rand(0,count($buggys)-1)];
    $temp->buggy3=$buggysWoMens[$x][2];//rand(0,count($buggys)-1)];
    $temp->heatNum=$x+1;
    $temp->gender="Womens";    
    $temp->day="Prelims";
    $curBidIndex=0;
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

  $auctions[$y]=$temp;  
  $y++;

  $memcache->set("auctions", $auctions, false, 2592000);
}

function initMemoryStuff(){
  global $orgs,$buggys,$buggysMens,$buggysWoMens,$orgsMens,$orgsWoMens,$gender,$validBids,$validUserids;
  
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");

  $memcache->set("totalCollected", 0, false, 2592000);
 
  $auctions = array();
  $users = array();
  $usersOptional = array();

  $memcache->set("users", $users, false, 2592000);  
  $memcache->set("usersOptional", $usersOptional, false, 2592000);  
  $memcache->set("registerNum", 0, false, 2592000);  

  $y=0; 
  $yy=0;

  
  for($x=0;$x<9;$x++){
    $temp = new Auction();
    $temp->auctionUid=$y;
    $temp->startTime="10:00am";
    $temp->org1=$orgsMens[$x][0];//rand(0,count($orgs)-1)];
    $temp->org2=$orgsMens[$x][1];//rand(0,count($orgs)-1)];
    $temp->org3=$orgsMens[$x][2];//rand(0,count($orgs)-1)];
    $temp->buggy1=$buggysMens[$x][0];//[rand(0,count($buggys)-1)];
    $temp->buggy2=$buggysMens[$x][1];//rand(0,count($buggys)-1)];
    $temp->buggy3=$buggysMens[$x][2];//rand(0,count($buggys)-1)];
    $temp->heatNum=$x+1;
    $temp->day="Prelims";
    $temp->gender="Mens";  
    $numBids=0;
    $curBidIndex=0;
    $auctions[$y]=$temp;  
    $y++;
  }

  for($x=0;$x<7;$x++){
    $temp = new Auction();
    $temp->auctionUid=$y;
    $temp->startTime="10:00am";
    $temp->org1=$orgsWoMens[$x][0];//rand(0,count($orgs)-1)];
    $temp->org2=$orgsWoMens[$x][1];//rand(0,count($orgs)-1)];
    $temp->org3=$orgsWoMens[$x][2];//rand(0,count($orgs)-1)];
    $temp->buggy1=$buggysWoMens[$x][0];//[rand(0,count($buggys)-1)];
    $temp->buggy2=$buggysWoMens[$x][1];//rand(0,count($buggys)-1)];
    $temp->buggy3=$buggysWoMens[$x][2];//rand(0,count($buggys)-1)];
    $temp->heatNum=$x+1;
    $temp->gender="Womens";    
    $temp->day="Prelims";
    $curBidIndex=0;
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
    if($auctions[$x]->day=="Finals"){
       $changedBids[$changedBidsIndex]=$auctions[$x]->bids;
       $changedBidsIndex++;
    } 
    if($auctions[$x]->day=="Prelims"){    
     if($clientBid != $mostRecentBidUidServer){
       $changedBids[$changedBidsIndex]=getChangedBids($clientBid,$auctions[$x]->bids);
       $changedBidsIndex++;

     }
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


function calculateTotalRaised(){

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
	  if(count($auctions[$za]->bids)>0 && !isset($womensWinners["$bidUser"]) && $totalWomensBids<5){
	    $totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	    $totalWomensBids++;
	    $womensWinners["$bidUser"]="bid";
	  }
	}
      }
    }
  }
 return $totalCollected;
}

function getMostRecentBid(){
  $memcache = new Memcache;
  $memcache->connect('localhost', 11211) or die ("Could not connect");
  $auctionEnd = date_create('2014-04-6 21:00:00');
  $currentDate = date_create();
  $timeTillRaces=date_diff($auctionEnd, $currentDate); 
  $timeTillRaces->format("%d days");
  $totalRaised=$memcache->get("totalCollected");
  $cheapestPrelimHeat=$memcache->get("cheapestPrelimHeat");
  //  $timeLeft=$timeTillRaces->m." months, ".$timeTillRaces->d." days, ".$timeTillRaces->h." hours, ".$timeTillRaces->i." minutes, ".$timeTillRaces->s." seconds" ;
  $timeLeft = $timeTillRaces->format("%a days %h hours %i minutes left");
  return array('mostRecentBid'=>$memcache->get("mostRecentBid"),'timeLeft'=>$timeLeft,'totalRaised'=>$totalRaised,'cheapestHeat'=>$cheapestPrelimHeat,'curTime'=>$currentDate->getTimestamp()); 
}

function loadMemcacheFromFile(){
	 $auctions = unserialize(file_get_contents("auctions.txt"));
	 $users = unserialize(file_get_contents("users.txt"));
	 $usersoptional = unserialize(file_get_contents("usersoptional.txt"));
	 $recent = unserialize(file_get_contents("mostrecentbid.txt"));

	 $memcache = new Memcache;
         $memcache->connect('localhost', 11211) or die ("Could not connect");

         $memcache->set("auctions", $auctions, false, 2592000);
         $memcache->set("users", $users, false, 2592000);
         $memcache->set("usersOptional", $usersoptional, false, 2592000);
         $memcache->set("mostRecentBid", $recent, false, 2592000);
}

function getMemcacheKeys() { 

    $memcache = new Memcache; 
    $memcache->connect('localhost', 11211) or die ("Could not connect to memcache server"); 

    $auctions = $memcache->get("auctions"); 
    $users = $memcache->get("users"); 
    $usersoptional = $memcache->get("usersOptional"); 
    $mostRecentBid = $memcache->get("mostRecentBid"); 

    file_put_contents("auctions.txt", serialize($auctions));
    file_put_contents("users.txt", serialize($users));
    file_put_contents("usersoptional.txt", serialize($usersoptional));
    file_put_contents("mostrecentbid.txt", serialize($mostRecentBid));

    
    foreach($auctions as $keys => $auction){
    // echo "$keys --  ".serialize($auction)."<br>";
    }

    $list = array(); 
    $allSlabs = $memcache->getExtendedStats('slabs'); 
    $items = $memcache->getExtendedStats('items'); 
    foreach($allSlabs as $server => $slabs) { 
        foreach($slabs AS $slabId => $slabMeta) { 
           $cdump = $memcache->getExtendedStats('cachedump',(int)$slabId); 
            foreach($cdump AS $keys => $arrVal) { 
	        if($arrVal){
                    foreach($arrVal AS $k => $v) {                    
		    	foreach($v as $newKey => $newVal){	    
                          //echo "$k : ".serialize($v).'<br>';	
			  //echo "$k $newKey ".serialize($newVal)."<br>";
			}
                    } 
	        }
           } 
        } 
    }    
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
	    //$totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	  }
	}
      } else {
	for($zb=0;$zb<count($auctions[$za]->bids) && $zb<5;$zb++){
	  if(count($auctions[$za]->bids)>0){
	    //$totalCollected=$totalCollected+$auctions[$za]->bids[$zb]->bidAmount;
	  }
	}
      }
    }
  }

  if($auctions[$auctionUid]->day!="Prelims"){
   usort($auctions[$auctionUid]->bids,"cmpBidsRev");  
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

function cmpBidsRev($a,$b){
  if($a->bidAmount == $b->bidAmount){
    return 0;
  }
  return ($a->bidAmount > $b->bidAmount) ? -1 : 1;
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