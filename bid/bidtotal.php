<?php

include "functions.php";

initAuctionDbConnection();

$sum = 0;

for($i=107;$i<125;$i++){
	$sql="SELECT MAX(bid_amount) FROM bids WHERE auction_uid = ".$i; 
	//echo($sql);
	$result = mysql_query($sql, $db_handle);
	$row = mysql_fetch_assoc($result);
	$sum += $row["MAX(bid_amount)"];
	//echo($sum);
}

$sql="SELECT bid_amount FROM bids WHERE auction_uid = 104 ORDER BY  `bids`.`bid_amount` DESC LIMIT 0,5";
$result = mysql_query($sql, $db_handle);
while($row = mysql_fetch_assoc($result)){
	$sum += $row["bid_amount"];
}

$sql="SELECT bid_amount FROM bids WHERE auction_uid = 105 ORDER BY  `bids`.`bid_amount` DESC LIMIT 0,5";
$result = mysql_query($sql, $db_handle);
while($row = mysql_fetch_assoc($result)){
	$sum += $row["bid_amount"];
}

$sql="SELECT bid_amount FROM bids WHERE auction_uid = 106 ORDER BY  `bids`.`bid_amount` DESC LIMIT 0,3";
$result = mysql_query($sql, $db_handle);
while($row = mysql_fetch_assoc($result)){
	$sum += $row["bid_amount"];
}

echo($sum);

?>