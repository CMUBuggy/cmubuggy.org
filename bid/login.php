<?php

  //NEED TO ADD COOKIE FUNCTIONALITY TO MAINTAIN USER INFO
include "functions.php";

if ($_POST['userid']){
 initAuctionDbConnection();
 $secretNumber = login();  
 if($secretNumber != -1){
//  header( 'Location: auctions.html?gender=m&day=1');
  header( 'Location: auctions.html?gender=m&day=1');
 } else {
   echo "Could not log you in.  Make sure you have the correct user name and password.  If you are not registered, return to the main cmubuggy.org page and register there";
 }
} else {
 if ($_POST['phone_number']){
  initAuctionDbConnection();  
  store_phone_number();
//  header( 'Location: auctions.html?gender=m&day=1');
  header( 'Location: auctions.html?gender=m&day=1');
 } 
}
?>


