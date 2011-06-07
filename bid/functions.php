<?php
$auctionIsLive=1;

include "functions_bb_mine.php";
include_once("../lib/pog/pog_includes.inc");
include_once("../util.inc");

$db_handle;


function initAuctionDbConnection(){
 global $db_handle;
 $db_handle = db_connect();
 global $sql;
 if (!mysql_select_db('cmubuggy_auction', $db_handle)) {
    echo 'Could not select database';
    exit;
 }
}

$number_of_auctions=13;
$lane_selections = array();

class bid {
    public $userid;
    public $bid_amount;
    public $bid_time;  
    public $user_unique_id;
    public $bid_uid; 

    function bid($userid,$bid_amount,$bid_time,$user_unique_id=null,$bid_uid){
	$this->userid=$userid;
	$this->bid_amount=$bid_amount;
	$this->bid_time=$bid_time;
	$this->user_unique_id=$user_unique_id;
	$this->bid_uid = $bid_uid;
    } 
    
}


class auction {
    public $bids;
    public $teams;
    public $heatNum;
    public $auction_num;
    public $max_bid;
    public $gender;
    public $day;
    public $auction_uid;
    public $heatImageName;

    function get_json_bid_list(){
	return json_encode($this->bids);
    }
    
    function auction($auction_uid,$auction_num,$gender="m",$teams=null,$day){
	$this->bids = array();
	$this->heatNum = $auction_num;
	$this->gender=$gender;
	$this->auction_uid = $auction_uid;
	if($teams==null){
	    $this->teams = array();
	} else {
	    $this->teams = $teams;
	}
	for($x=0;$x<count($this->teams);$x++){
	 //$this->teams[$x]=substr_replace($this->teams[$x],"",-1);
	 $this->teams[$x]=rtrim($this->teams[$x]);
	}
  	$this->day = $day;
	 $lane1=substr_replace($this->teams[2],"",-2);
	 $lane1=rtrim($lane1);
	 $lane2=substr_replace($this->teams[1],"",-2);
	 $lane2=rtrim($lane2);
	 $lane3=substr_replace($this->teams[0],"",-2);
	 $lane3=rtrim($lane3);

        $this->heatImageName = $lane1."-".$lane2."-".$lane3;
	    

    }
    
    function sanity_check($bid){
	if(is_numeric($bid) == false){
	    throw new Exception('Bad Bid : Bid is not a number.');
	    return 0;
	}
	if($max_bid >= $bid){
	    throw new Exception('Bad Bid : Bid is lower than ( or equal to ) the highest bid.');
	    return 0;
	} 
	if($bid<10){
	    throw new Exception('Bad Bid : Minimum bid is 10 dollars, you bid '.$bid);
	    return 0;
	}

	if(fmod(floatval($bid),1.0) > 0){
	    throw new Exception('Bad Bid : Bid can not include cents.');
	    return 0;
	}
	
	if ($bid > 9999){
	    throw new Exception('Bad Bid : Maximum bid allowed is 9999 dollars.');
	    return 0; 
	}
	return 1;
    }

    function sanity_check_finals($bid){
    	$bidding_users = array();      
	if(count($this->bids)>0){
	    $highest_bid_count = 0;
	    $max_bid=9999;
	    foreach($this->bids as $bid_inst){
	     if (isset($bidding_users[$bid_inst->userid])){
	      if($max_bid > $bid_inst->bid_amount){
	       $bidding_users[$bid_inst->userid]=$bid_inst->bid_amount;
	       $max_bid = $bid_inst->bid_amount;
	      } 
	     } else {
	       if($highest_bid_count < 5){
	        $bidding_users[$bid_inst->userid]=$bid_inst->bid_amount;;
	        if($max_bid > $bid_inst->bid_amount){
  	          $max_bid = $bid_inst->bid_amount;
	        } 
	        $highest_bid_count = $highest_bid_count+1;
	       }
	     }
	    }	
	    //$max_bid=$this->bids[0]->bid_amount;
	} else {
	    $max_bid = 0;
	}
	foreach($bidding_users as $bid_user => $bid_amount){
	 if($bid_user == $_COOKIE['userid'] && $max_bid < $bid_amount ){
	  $max_bid=$bid_amount;
	 }
	}
	if(is_numeric($bid) == false){
	    throw new Exception('Bad Bid : Bid is not a number'.$bid);
	    return 0;
	}
	if($max_bid >= $bid){
	    throw new Exception('Bid not above 5th highest bid or is lower than bid you already made.');
	    return 0;
	} 
	if($bid<10){
	    throw new Exception('Bad Bid : Minimum bid is 10 dollars, you bid '.$bid);
	    return 0;
	}

	if(fmod(floatval($bid),1.0) > 0){
	    throw new Exception('Bad Bid : Bid can not include cents.');
	    return 0;
	}
	
	if ($bid > 9999){
	    throw new Exception('Bad Bid : Maximum bid allowed is 9999 dollars.');
	    return 0; 
	}
	return 1;
    }
    
    function check_dup_bid($userid,$bid_amount){
	foreach ($this->bids as $bid){
	    if($bid->userid == $userid and $bid->bid_amount == $bid_amount){
		return 1;
	    }
	}
	return 0;
    }
    
    function add_bid_from_db($userid,$bid_amount,$bid_time,$user_unique_id=null,$bid_uid){
	$this->bids[count($this->bids)]=new bid($userid,$bid_amount,$bid_time,$user_unique_id,$bid_uid);
    }
    
    function add_max_bid_from_db($userid,$username,$bid_amount,$auction_num){
	$this->max_bids[count($this->max_bids)]=new max_bid($userid,$username,$bid_amount);
    }
    
    function get_max_bid($userid){
	foreach ($this->max_bids as $max_bid){
	    if ($max_bid->userid == $userid && $this->bids[0]->bid_amount < $max_bid->bid_amount){
		return $max_bid->bid_amount;			  
	    }     	    
	}
	return "none";			  
    }
    
    function add_max_bid($userid,$bid_amount){
	global $db_handle;
	try {
	    $this->sanity_check($bid_amount);
	} catch (Exception $e) {
	    throw $e; 	  
	    return 0;
	}	   
	$sql="insert into reserve_bids values (".$this->auction_num.",".$_COOKIE['secret_number'].",$bid_amount)";
	$result = mysql_query($sql, $db_handle);
	
	if (!$result) {
	    $error = mysql_error($db_handle);
	    $error_pos = stripos($error,"Duplicate entry");
	    if($error_pos === false){
		throw new Exception('SQL ERROR : '.mysql_error($db_handle));     
		return 0;
	    } else {
		$old_reserve_amount = 0;
		foreach ($this->max_bids as $max_bid){
		    if($max_bid->userid == $_COOKIE['userid']){
			$old_reserve_amount = $max_bid->reserve_amount;		   
			$max_bid->reserve_amount=$bid_amount;
		    }
		}
		$sql="update reserve_bids set auction_num=".$this->auction_num.",unique_id=".$_COOKIE['secret_number'].",reserve_amount=".$bid_amount." where auction_num=".$this->auction_num." and unique_id=".$_COOKIE['secret_number'];
		$result = mysql_query($sql, $db_handle);
		
	    }
	}
	
	if(count($this->max_bids)==0){    
	    if(count($this->bids)==0){
		$this->add_bid($userid,10);
	    } else {
		if($bid_amount - $this->bids[0]->bid_amount < 2){
		    $this->add_bid($userid,$bid_amount);
		} else {
		    if($this->bids[0]->user_unique_id == $userid){
			return 1;
		    } else {
			$this->add_bid($userid,($this->bids[0]->bid_amount)+1);
		    }
		}
	    }
	}
	if(count($this->max_bids)>0){    
	    
	    if($this->bids[0]->userid == $userid){
		return 1;
	    }
	    
	    
	    $highest_max_bid = new max_bid(1,'noone',0);
	    foreach ($this->max_bids as $max_bid){
		if ($max_bid->bid_amount > $highest_max_bid->bid_amount){
		    $highest_max_bid = $max_bid;
		}     	    
	    }
	    
	    
	    if ($highest_max_bid->bid_amount == $bid_amount){
		throw new Exception("Bad Bid : You were beat out by another max bid");
	    }
	    if ($highest_max_bid->userid == $userid){
		return 1;
	    }
	    
	    if($highest_max_bid->bid_amount < $bid_amount){    				    
		
		$this->add_bid($highest_max_bid->userid,$highest_max_bid->bid_amount);
		if($bid_amount-$highest_max_bid->bid_amount<1){
		    $this->add_bid($userid,$bid_amount);
		} else {
		    $this->add_bid($userid,($highest_max_bid->bid_amount)+1);
		}
	    }
	    
	    if($highest_max_bid->bid_amount > $bid_amount){    				    
		
		$this->add_bid($userid,$bid_amount);
		if($highest_max_bid->bid_amount-$bid_amount<1){
		    $this->add_bid($highest_max_bid->userid,$highest_bid_max->bid_amount);
		} else {
		    $this->add_bid($highest_max_bid->userid,($bid_amount)+1);
		}
	    }                
	    return 1;
	}
    }
    
    function check_bid_against_max($userid,$bid_amount){
	foreach ($this->max_bids as $max_bid){
	    if($max_bid->userid == $userid){
		if($max_bid->bid_amount >= $bid_amount){
		    throw new Exception("Bad Bid : You already have a max bid greater than this bid");
		}
	    }
	}	 
    }
    function add_bid($user_uid,$bid_amount){
	global $db_handle,$sql;
	$result = mysql_query($sql, $db_handle);
	$bid_time = get_microtime()*100;
	/*
	try {
	    $this->sanity_check($bid_amount);
	} catch (Exception $e) {
	    throw $e; 	  
	    return 0;
	}*/	   
	
	$sql="insert into bids values (".$this->auction_uid.",0,".$bid_time.",".$bid_amount.",".$user_uid.")";
	$result = mysql_query($sql, $db_handle);
	
/*	if (!$result) {
	    $error = mysql_error($db_handle);
	    $sql="select * from bids where auction_num=".$this->auction_num." and unique_id=".$userid." and bid_time = $bid_time";
	    $result = mysql_query($sql, $db_handle);
	    $row = mysql_fetch_assoc($result);
	    if($row['bid_amount']<$bid_amount){
		$bid_time=$bid_time+100;
		$sql="insert into bids values (".$this->auction_num.",".$userid.",$bid_time,$bid_amount)";		
		$result = mysql_query($sql, $db_handle);
		if (!$result) {
		    $error = mysql_error($db_handle);
		    throw new Exception('THERE WAS A DATABASE ERROR - PLEASE TRY AGAIN!');     
		}

	    } else {
		throw new Exception('Bad Bid : a higher bid has already been submitted');     
	    }
	}*/
	return 1;
    }

    function add_finals_bid($userid,$bid_amount){
	//FIXME : REPLACE WITH SQL
	    global $db_handle,$sql;
	$bid_time = get_microtime()*100;
	try {
	    $this->sanity_check_finals($bid_amount);
	} catch (Exception $e) {
	    throw $e; 	  
	    return 0;
	}	   
	
	$sql="insert into bids values (".$this->auction_num.",".$userid.",$bid_time,$bid_amount)";
	$result = mysql_query($sql, $db_handle);
	if (!$result) {
	    $error = mysql_error($db_handle);
	    $sql="select * from bids where auction_num=".$this->auction_num." and unique_id=".$userid." and bid_time = $bid_time";
	    $result = mysql_query($sql, $db_handle);
	    $row = mysql_fetch_assoc($result);
	    if($row['bid_amount']<$bid_amount){
		$bid_time=$bid_time+1;
		$sql="insert into bids values (".$this->auction_num.",".$userid.",$bid_time,$bid_amount)";		
		$result = mysql_query($sql, $db_handle);
		if (!$result) {
		    $error = mysql_error($db_handle);
		    throw new Exception('THERE WAS A DATABASE ERROR - PLEASE TRY AGAIN!');     
		}

	    } else {
		throw new Exception('Bad Bid : a higher bid has already been submitted');     
	    }
	}
	return 1;
    }
    
    function remove_bid($userid,$bid_amount){
	//FIXME : REPLACE WITH SQL
	    
	    // PUT SOMETHING HERE
	    
    }
    
    function get_json_bids_since($time,$auction_number){
	$bids_to_return = array();
	foreach ($this->bids as $bid){
	    if($bid->bid_time > $time){
		array_push($bids_to_return,$bid);
	    }
	}
	return json_encode(array("data"=>$bids_to_return,"auc_num"=>$auction_number));
    }
    
}

function get_secret_number($userid){
    //FIXME : THIS SHOULD ACTUALLY GENERATE A SECRET NUMBER
	return 10;
}


// changing user db to unified login db
// verify_user()
// init_bids()
// init_auctions()
// no get_email_address()
// no check_for_email_address()
// maybe no check_secret_number()

function login(){
    //FIXME : usernames can not have spaces in them ( due to using them for div ids )
	$secret_number = 0;
    try {
	$secret_number = verify_user($_POST['userid'],$_POST['password']);
    } catch (Exception $e) {
	return -1;
    }
    $_COOKIE['secret_number']=$secret_number;
    $_COOKIE['user_uid']=$secret_number;
    $_COOKIE['userid']=$_POST['userid'];
    setcookie('secret_number',$secret_number);

    setcookie('userid',$_POST['userid']);

    setcookie('user_uid',$secret_number);
/*    if(check_for_email_address($secret_number)==0){
	ask_for_email_address($secret_number);
    }*/
    if(check_for_phone_number($secret_number)==0){
	ask_for_phone_number();
    }
    return $secret_number;
}

/*
function verify_user($userid,$password){
    global $db_handle;
    $sql    = "SELECT user_id,username,user_password FROM cmubuggy_phpBB.users WHERE LOWER(username) = LOWER('$userid')";
    $result = mysql_query($sql, $db_handle);
    $row = mysql_fetch_array($result);
    if ($row == false){
	throw new Exception('badlogin_user');
    } else {
	if (phpbb_check_hash($password,$row[2])){
	    return $row[0];
	} else {
	    throw new Exception('badlogin_pass');
	}
    }
}

*/

function verify_user($userid,$password){

	 $authenticated = FALSE;
	 $user = new user();
	 $userList = $user->GetList(array(array("username", "=", $userid)));
	 if(count($userList)>0){ 
	 	$user = $userList[0];
		$authenticated = checkpassword($password,$user->salt,$user->password);
		if($authenticated){
		  //return array("user_id" => $user->userId, "username" => $user->username, "user_password" => $user->password);
		  return $user->userId;
		} else {
		  throw new Exception('badlogin_pass');
		}
	 } else {
	   	throw new Exception('badlogin_user');
	 }
}


function ask_for_email_address(){
    header( 'Location: get_email.php?error=needemail');	 
    exit();
}

function ask_for_phone_number(){
    header( 'Location: get_phone.php');	 
    exit();
}

function get_email_address($secret_number){
    global $db_handle;
    $sql    = "SELECT user_email FROM cmubuggy_phpBB.users WHERE user_id = $secret_number";
    $result = mysql_query($sql, $db_handle);
    return $row[0];
}

function check_for_email_address($secret_number){
    global $db_handle;
    $sql    = "SELECT user_email FROM cmubuggy_phpBB.users WHERE user_id = $secret_number";
    $result = mysql_query($sql, $db_handle);
    if ($row == false){
	$sql    = "SELECT emailaddress FROM user_info WHERE unique_id = $secret_number";
	$row = mysql_fetch_array($result);
	if ($row == false){
	    return 0;
	} else {
	    return 1;
	}
    } else {
	return 1;
    }
}

function store_phone_number(){
    global $db_handle;
    $sql    = "insert into user_info (phonenumber,unique_id) values('".$_POST['phone_number']."',".$_COOKIE['secret_number'].")";
    $result = mysql_query($sql, $db_handle);
}

function check_for_phone_number($secret_number){
    global $db_handle;
    $sql    = "SELECT phonenumber FROM user_info WHERE unique_id = $secret_number";
    $result = mysql_query($sql, $db_handle);
    $row = mysql_fetch_array($result);
    if ($row == false){
	return 0;
    } else {
	return 1;
    }
}

function check_secret_number($userid,$secret_number){
    global $db_handle;
    $sql    = "SELECT user_id FROM cmubuggy_phpBB.users WHERE username = '$userid' and user_id = $secret_number";
    $result = mysql_query($sql, $db_handle);
    $row = mysql_fetch_array($result);
    if ($row == false){
	return -1;
    } else {
	return 1;
    }
}

function json_process_bid($auctions,$auction_num,$userid,$bid_amount){
    //FIXME : NUMERIC CHECK SHOULD BE IN THE JAVASCRIPT
	////  $add_error = $auctions[$auction_num]->add_bid($userid,$bid_amount);
    try{
	$auctions[$auction_num]->check_bid_against_max($_COOKIE['secret_number'],$bid_amount);
    } catch (Exception $e){
	throw $e;
    }    
    try{          
	$auctions[$auction_num]->add_bid($_COOKIE['secret_number'],$bid_amount);
    } catch (Exception $e){
	throw $e;
    }
    $highest_max_bid = new max_bid(1,"noone",0);
    
    foreach ($auctions[$auction_num]->max_bids as $max_bid){
	if ($max_bid->bid_amount > $highest_max_bid->bid_amount){
	    $highest_max_bid = $max_bid;
	} else {
	}     	    
    }
    if ($highest_max_bid->bid_amount - $bid_amount >=1){     
	$auctions[$auction_num]->add_bid($highest_max_bid->userid,$bid_amount+1);
	
    } else {
        if($highest_max_bid->bid_amount != 0){
	  	try {					
		    $auctions[$auction_num]->add_bid($highest_max_bid->userid,$highest_max_bid->bid_amount);        
		    } catch (Exception $e){

		    }
	}
    }
    
    return 1;  
}

function json_process_finals_bid($auctions,$auction_num,$userid,$bid_amount){
    //FIXME : NUMERIC CHECK SHOULD BE IN THE JAVASCRIPT
    try{
	$auctions[$auction_num]->check_bid_against_max($_COOKIE['secret_number'],$bid_amount);
    } catch (Exception $e){
	throw $e;
    }    
    try{          
	$auctions[$auction_num]->add_finals_bid($_COOKIE['secret_number'],$bid_amount);
    } catch (Exception $e){
	throw $e;
    }
    $highest_max_bid = new max_bid(1,"noone",0);
    
    foreach ($auctions[$auction_num]->max_bids as $max_bid){
	if ($max_bid->bid_amount > $highest_max_bid->bid_amount){
	    $highest_max_bid = $max_bid;
	} else {
	}     	    
    }
    if ($highest_max_bid->bid_amount - $bid_amount >=1){
        try {
	  $auctions[$auction_num]->add_bid($highest_max_bid->userid,$bid_amount+1);
	} catch (Exception $e) {

	}
	
    } else {
        if($highest_max_bid->bid_amount != 0){
	  try { 
	  $auctions[$auction_num]->add_bid($highest_max_bid->userid,$highest_max_bid->bid_amount);        
          } catch (Exception $e){

	  }
	}
    }
    
    return 1;  
}

function json_process_max_bid($auctions,$auction_num,$userid,$bid_amount){
    //FIXME : NUMERIC CHECK SHOULD BE IN THE JAVASCRIPT
	try {
    } catch (Exception $e) {
	throw $e; 	  
    }
    try {
	$auctions[$auction_num]->add_max_bid($_COOKIE['secret_number'],$bid_amount);
    } catch (Exception $e) {
	throw $e;
    }   
    
    return 1;  
}

function json_process_max_bid_finals($auctions,$auction_num,$userid,$bid_amount){
    //FIXME : NUMERIC CHECK SHOULD BE IN THE JAVASCRIPT
	try {
    } catch (Exception $e) {
	throw $e; 	  
    }
    try {
	$auctions[$auction_num]->add_max_bid($_COOKIE['secret_number'],$bid_amount);
    } catch (Exception $e) {
    	if($e.getMessage() == "Bad Bid : Bid is lower than ( or equal to ) the highest bid"){
	 throw new Exception("uh oh");
	}
    }   
    
    return 1;  
}


//no longer use process_bid
    function process_bid($auctions,$auction_num,$userid,$bid_amount){
	$userid=$_COOKIE['userid'];
	$secret_number=$_COOKIE['secret_number'];
	if(is_numeric($bid_amount) == false){
	    return 0;
	}
	if (check_secret_number($userid,$secret_number)==0){
	    return -1;
	} else {
	    
	    if($auctions[$auction_num]->add_bid($userid,$bid_amount)>0){
		//$file = '/usr0/wwwsrv/htdocs/DurandAuction/auctions.data' or die('Could not open file!');
		//$fh = fopen($file, 'w') or die('Could not open file!');    
		//fwrite($fh,serialize($auctions));
		//fclose($fh);
	    } else {
		return -2;
		//FIXME : BAD ADD!!
	    }
	}
	return 1;
}

function calc_days_from_time($time){
	 $days=$time/(60*60*24);
	 $hours=($time%(60*60*24))/(60*60);
	 $mins=(($time%(60*60*24))%(60*60))/(60);
	 $secs=((($time%(60*60*24))%(60*60))%(60));
	 return array(intval($days),intval($hours),intval($mins),intval($secs),$time);
}

function get_microtime(){
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
}

function get_json_time_till_auction_end(){
    //  return json_encode(array(time()*1000));
    return json_encode(array(get_microtime()*100));
}

function init_auction_list(){
    
}
function init_bids($auction_uid){
	 global $db_handle;
	 $bids = array();
	 //$sql    = "select cmubuggy_phpBB.users.user_id,username,bid_amount,bid_time,username,bid_uid FROM cmubuggy_phpBB.users,cmubuggy_auction.bids where cmubuggy_phpBB.users.user_id=bids.user_uid and auction_uid=".$auction_uid." order by bid_amount desc limit 12";
	 $sql    = "select cmubuggy.user.userId as user_id ,cmubuggy.user.username,bid_amount,bid_time,username,bid_uid FROM cmubuggy.user,cmubuggy_auction.bids where cmubuggy.user.userId=bids.user_uid and auction_uid=".$auction_uid." order by bid_amount desc limit 12";
	 $result = mysql_query($sql, $db_handle);
	 if ($result == NULL){
	   return $bids;
	 }

         while ($row = mysql_fetch_assoc($result)) {
		array_unshift($bids,new bid($row['username'],$row['bid_amount'],$row['bid_time'],$row['user_id'],$row['bid_uid']));    
		
	 }	 	 
	 return $bids;
}

function init_auctions($gender,$day){  
    $auctions = array();
    global $number_of_auctions,$lane_selections,$db_handle;
    $sql    = "SELECT * FROM auctions where day='".$day."' and gender='".$gender."' order by auction_uid";

    $result = mysql_query($sql, $db_handle);
    while ($row = mysql_fetch_assoc($result)) {
        $teams = array($row['lane1'],$row['lane2'],$row['lane3']);
	array_push($auctions,new auction($row['auction_uid'],$row['auction_num'],$row['gender'],$teams,$row['day']));    
    }
    
    foreach($auctions as $auction){
     $sql = "SELECT * FROM bids,cmubuggy_dev.user where user.userId = bids.user_uid and auction_uid = ".$auction->auction_uid." order by bid_amount" ;    
     $result = mysql_query($sql, $db_handle);

     if($result == NULL){
      return $auctions;
     }
     while ($row = mysql_fetch_assoc($result)) {
	    array_push($auction->bids,new Bid($row['username'],$row['bid_amount'],$row['bid_time'],$row['user_uid'],$row['bid_uid']));   
	}
    }    
    return $auctions;
}


function check_valid_function($func){
    //FIXME
	return 1;
}

function db_connect(){
    return mysql_connect("localhost","cmubuggy","vRXHXxKYUcYzCsE8");
}

function db_connect_beta(){
    return mysql_connect("localhost","cmubuggy","vRXHXxKYUcYzCsE8");
}

function outputOnlyAuctionType($type,$auctions){
    $temp_auction = array();
    foreach($auctions as $auction){
	if($auction->type == $type){
	    $temp_auction[count($temp_auction)]=$auction;
	}
    }
    return $temp_auction;
}

function check_reserve_bid($auction_uid,$topBid,$topUser){
	 global $db_handle,$sql;
	 $error = "";
	 $reserveBids = array();
	 $reserveBidUsers = array();
	 $sql="select * from reserve_bids where auction_num=".$auction_uid." and reserve_amount > ".$topBid." order by reserve_amount";
	 $result = mysql_query($sql, $db_handle);
	 if($result){
	        $error = $error." found reserves;";
		while ($row = mysql_fetch_assoc($result)){
		   array_push($reserveBids,$row['reserve_amount']);   	      
		   array_push($reserveBidUsers,$row['user_uid']);   	      
 	           $error = $error.$row['user_uid'];
		}
		$x=0;
		if(count($reserveBids)>1){
			$error = $error." found multiple reserves;";
			for ($x=0;$x<count($reserveBids)-1;$x++){
		   	    add_bid($reserveBidUsers[$x],$reserveBids[$x],$auction_uid,False); 		          	
			}
		   	add_bid($reserveBidUsers[$x],$reserveBids[$x-1]+1,$auction_uid,False); 		          
		} else {
		       if($topBid<10){
		        $newBid = 10;
		       } else {
		        $newBid=$topBid+1;
		       }
		       $error=$error." and ".$newBid;
		       if($topUser!=$reserveBidUsers[0]){		       
		       		add_bid($reserveBidUsers[0],intval($newBid),$auction_uid,False);
				$error = $error." and we are adding!";
		       }
		}
	 }
	 return $error;
}

function get_reserve_bid($user_uid,$auction_uid){
	 global $db_handle,$sql;
	 $sql="select * from reserve_bids where auction_num=".$auction_uid." and user_uid=".$user_uid." order by reserve_amount desc";
	 $result = mysql_query($sql, $db_handle);
	 if($result){
	    $row = mysql_fetch_assoc($result);
	    return $row['reserve_amount'];
	 } else {
	    return 0;
	 }
}
function add_reserve_bid($user_uid,$reserve_amount,$auction_uid){
	 global $db_handle,$sql;
	 $rowFound = 0;
	 $topBid = 0;
	 $topUser = "noOne";
	 $reserveBids = array();
	 $reserveBidUsers = array();
	 $reserve_amount = intval($reserve_amount);
	 if($reserve_amount < 10){
          return "<b style='color:red'>MAX BID REJECTED : Bid is less than 10 dollars</b> ";	  		    
	 }
	 if($reserve_amount > 3500){
          return "<b style='color:red'>MAX BID REJECTED : Max bid is greater than 3500 dollars</b> ";	  		    
	 }
	 $sql="lock tables cmubuggy_auction.bids,cmubuggy_auction.reserve_bids write"; 
	 $result = mysql_query($sql, $db_handle);
	 $sql="select * from bids where auction_uid=".$auction_uid." order by bid_amount desc";
	 $result = mysql_query($sql, $db_handle);
	 if($result){
	    $row = mysql_fetch_assoc($result);
	    if($row){
		    $topBid = $row['bid_amount'];
	    	    $topUser = $row['user_uid'];
	    }
	 }
	 $sql="select * from reserve_bids where auction_num=".$auction_uid." and user_uid=".$user_uid." order by reserve_amount desc";
	 $result = mysql_query($sql, $db_handle);
	 if($result){
	    $row = mysql_fetch_assoc($result);
	    if(intval($row['reserve_amount'])>=intval($reserve_amount)){
	    	 $sql="unlock tables";
	 	 $result = mysql_query($sql, $db_handle);	
		 return "<b style='color:red'>MAX BID REJECTED : Bid is less than your current max bid</b> ";
	    } 
	    if ($topBid > intval($reserve_amount)){
	    	 $sql="unlock tables";
	 	 $result = mysql_query($sql, $db_handle);	
		 return "<b style='color:red'>MAX BID REJECTED : Max Bid is less than the current max bid</b> ";
	    }
	    $rowFound = intval($row['reserve_amount']);
	 }
	 $sql="select * from reserve_bids where auction_num=".$auction_uid." and reserve_amount=".$reserve_amount." order by reserve_amount desc";
	 $result = mysql_query($sql, $db_handle);
	 if($result){
	    $row = mysql_fetch_assoc($result);
	    if($row){
	     $sql="unlock tables";
	     $result = mysql_query($sql, $db_handle);	
             return "<b style='color:red'>MAX BID REJECTED : someone else already made that reserve bid</b> ".$sql2;		
	    }
	 }
	 $bid_time = get_microtime()*100;
 	 $sql="delete from reserve_bids where auction_num = ".$auction_uid." and user_uid = ".$user_uid;
	 $result = mysql_query($sql, $db_handle);
 	 $sql="insert into reserve_bids values (".$auction_uid.",".$user_uid.",".$reserve_amount.")";
	 $result = mysql_query($sql, $db_handle);
	 check_reserve_bid($auction_uid,$topBid,$topUser);

	 $sql2="unlock tables";
	 $result = mysql_query($sql2, $db_handle);	
	 return "<b>MAX BID ACCECPTED</b> ";
}

function add_bid($user_uid,$bid_amount,$auction_uid,$lock){
	 $bid_amount = intval($bid_amount);
	 if($bid_amount < 10){
 	  return "<b style='color:red'>BID REJECTED : Bid is less than 10 dollars</b> ";
	} 
	 if($bid_amount > 3500){
          return "<b style='color:red'>BID REJECTED : bid is greater than 3500 dollars</b> ";	  		    
	 }
	 global $db_handle,$sql;
	 $topBid=$bid_amount;
	 $mensfinals = False;
	 $womensfinals = False;
	 $sql="select * from auctions where auction_uid=".$auction_uid;
	 $result = mysql_query($sql, $db_handle);
	 if($result){
	    $row = mysql_fetch_assoc($result);
	    if ($row['day'] == 2 && $row['gender'] == 'm'){	       
	       $mensfinals = True;
	    }
	    if ($row['day'] == 2 && $row['gender'] == 'w'){	       
	       $womensfinals = True;
	    }
	 }
	 if($lock == True){
	 	  $sql="lock tables cmubuggy_auction.bids,cmubuggy_auction.reserve_bids write"; 
	 	  $result = mysql_query($sql, $db_handle);
	 }
//	 $sql="select * from bids where auction_uid=".$auction_uid." order by bid_time desc";
	 $sql="select * from bids where auction_uid=".$auction_uid." order by bid_amount desc";
	 $result = mysql_query($sql, $db_handle);
	 $bid_amount_1=0;
	 $bid_amount_2=0;
	 $bid_amount_3=0;
	 $bid_amount_4=0;

	 if($result){
	    if($mensfinals == True){
	     $row = mysql_fetch_assoc($result);
	     $bid_amount_1=$row['bid_amount'];
	     $row = mysql_fetch_assoc($result);
	     $bid_amount_2=$row['bid_amount'];
	     $row = mysql_fetch_assoc($result);
	     $bid_amount_3=$row['bid_amount'];
	     $row = mysql_fetch_assoc($result);	    	       	       
	     $bid_amount_4=$row['bid_amount'];
	    }
	    if($womensfinals == True){
	     $row = mysql_fetch_assoc($result);
	     $bid_amount_1=$row['bid_amount'];
	     $row = mysql_fetch_assoc($result);
	     $bid_amount_2=$row['bid_amount'];
	    }
	    $row = mysql_fetch_assoc($result);
	    $topBid=$row['bid_amount'];
	    if(intval($row['bid_amount'])>=intval($bid_amount)){
	    	 if($lock == True){
		 	$sql="unlock tables";
	 		$result = mysql_query($sql, $db_handle);	
		 }
		  return "<b style='color:red'>BID REJECTED : Bid is less than the highest bid</b> ";		 
	    } else {
	       if($bid_amount_1==$bid_amount or $bid_amount_2==$bid_amount or $bid_amount_3==$bid_amount or $bid_amount_4==$bid_amount){
		  return "<b style='color:red'>BID REJECTED : Bid is equal to a current bid</b> ";		 		 
	       }	       
	       $rowFound = $row['bid_amount'];
	    }
	 }
	 $bid_time = get_microtime()*100;
	
 	 $sql="insert into bids values (".$auction_uid.",0,".$bid_time.",".$bid_amount.",".$user_uid.")";
	 $result = mysql_query($sql, $db_handle);
	 if($lock==True){
	 	 $sql2="unlock tables";
		 $result = mysql_query($sql2, $db_handle);
		 $checkresults = check_reserve_bid($auction_uid,intval($bid_amount),$user_uid);		 
	 }	
	 return "<b>BID ACCECPTED </b> ";
    }

function checkSecretNum(){
	 if($_COOKIE['secret_number']==$_COOKIE['user_uid'] and intval($_COOKIE['secret_number']) > 0 and intval($_COOKIE['user_uid']) > 0){
		return True;
	 } 
	 return False;

	 
}
?>
