<?php

include "functions.php";
#$AuctionEndDate=strtotime("Wed Apr 14 21:04:00 EDT 2010");
$AuctionEndDate=strtotime("Wed Apr 13  21:00:00 EDT 2011");
$AuctionStartDate=strtotime("Mon Apr 11  09:00:00 EDT 2011");
#$AuctionStartDate=strtotime("Thu Apr 8  2:00:00 EDT 2010");
$cur_time = time();


if(isset($_GET['func'])){
    if ($_GET['func'] == "get_json_auction_end"){
       echo json_encode($AuctionEndDate-$cur_time);         
    }
    if ($_GET['func'] == "get_json_bids"){
        initAuctionDbConnection();       		      
	$bids = init_bids($_GET['auction_uid']); 
	echo json_encode(array("data"=>$bids));	
    }
    if ($_GET['func'] == "get_json_auctions"){
        initAuctionDbConnection();
	$auctions = init_auctions($_GET['gender'],$_GET['day']); 
//	$auctions = init_auctions('m','1'); 
/*	if($_GET['gender'] == "w"){
	    $temp_auctions=outputOnlyAuctionType("w",$auctions);
	} else {
	    $temp_auctions=outputOnlyAuctionType("m",$auctions);
	}*/
	echo json_encode(array("data"=>$auctions));
	return 0;
    }
    if ($_GET['func'] == "submit_json_bid"){
       if($cur_time < $AuctionStartDate){
       	 echo json_encode("<b>Auction has not yet started</b>");
	 return;	     
       }
       if($cur_time > $AuctionEndDate){
       	 echo json_encode("<b>Auction has finished</b>");
	 return;	     
       }


       if(checkSecretNum() == False){
       		echo json_encode("<b>Bid failed.  You have not logged in yet");
		return;
       }
       initAuctionDbConnection();       		      
       $status_result=add_bid($_GET['user_uid'],intval($_GET['bid_value']),$_GET['auction_uid'],True);
       echo json_encode($status_result);
    }
    if ($_GET['func'] == "submit_json_reserve_bid"){
       if($cur_time < $AuctionStartDate){
       	 echo json_encode("<b>Auction has not yet started</b>");
	 return;	     
       }
       if($cur_time > $AuctionEndDate){
       	 echo json_encode("<b>Auction has finished</b>");
	 return;	     
       }
       if(checkSecretNum() == False){
       		echo json_encode("<b>Bid failed.  You have not logged in yet");
		return;
       }
       initAuctionDbConnection();       		      
       $status_result=add_reserve_bid($_GET['user_uid'],intval($_GET['reserve_bid_value']),$_GET['auction_uid']);
       echo json_encode($status_result);
    }
    if ($_GET['func'] == "get_json_reserve_bid"){
       if(checkSecretNum() == False){
		return;
       }
       initAuctionDbConnection();       		      
       $status_result=get_reserve_bid($_GET['user_uid'],$_GET['auction_uid']);
       echo json_encode($status_result);
    }
}
