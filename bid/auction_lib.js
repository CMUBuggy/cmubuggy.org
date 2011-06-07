lane_1_deltax=0;
lane_1_deltay=20;
lane_2_deltax=0;
lane_2_deltay=20;
lane_3_deltax=0;
lane_3_deltay=20;

lane_1_x_coord=93+lane_1_deltax;
lane_1_y_coord=160+lane_1_deltay;
lane_2_x_coord=192+lane_2_deltax;
lane_2_y_coord=185+lane_2_deltay;
lane_3_x_coord=310+lane_3_deltax;
lane_3_y_coord=235+lane_3_deltay;
shadow_distance=25;

skipLoad = 1;
timeTillEndOfAuction=0;

function getCgiVars(){
     cgiVars = location.search.substring(1).split("&");
     cgiVarsToReturn = []
     for(i in cgiVars){
	 tempValue = cgiVars[i].split("=");
	 cgiVarsToReturn[tempValue[0]]=tempValue[1];
     }
     return cgiVarsToReturn;
}

function clearErrorBox(){
    //         $('#errorbox').css('visibility','hidden');	       
}

function process_json_bid_status(data,status) {
     $('#errorbox').css('visibility','visible');	       
     $('#errorbox').html(data);
     //     window.setTimeout(clearErrorBox,10000);
     skipLoad=-1;
     displayBidListAfter();
     getAuctionAjax("get_json_reserve_bid",{"user_uid":readCookie("user_uid"),"auction_uid":cgiVars['auc_num']},displayReserveBidCallback);     
}


function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
	var c = ca[i];
	while (c.charAt(0)==' ') c = c.substring(1,c.length);
	if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}


function json_submit_bid(){
      //fixme : deal with multiple auctions
    cgiVars = getCgiVars();
    tempargs={'user_uid':readCookie("user_uid"),'secret_number':readCookie("secret_number"),'bid_value':$('#bid_value').val(),'auction_uid':cgiVars['auc_num']}; 
      $('#errorbox').css('visibility','hidden');	       
      getAuctionAjax("submit_json_bid",tempargs,process_json_bid_status);
}

function json_submit_max_bid(){
      //fixme : deal with multiple auctions
    cgiVars = getCgiVars();
    tempargs={'user_uid':readCookie("user_uid"),'secret_number':readCookie("secret_number"),'reserve_bid_value':$('#bid_value2').val(),'auction_uid':cgiVars['auc_num']}; 
      $('#errorbox').css('visibility','hidden');	       
      getAuctionAjax("submit_json_reserve_bid",tempargs,process_json_bid_status);
}



function getAuctionAjax(func,args,callback){
    args_string = "";
    for(i in args){
	args_string = args_string + i + "=" + args[i]+"&";    
    }
    if(args.length == 0){
	$.getJSON("http://www.cmubuggy.org/bid2011/ajax_auction.php?func="+func,callback);      
    } else { 
	$.getJSON("http://www.cmubuggy.org/bid2011/ajax_auction.php?func="+func,args,callback);
    }
}

     function reloadBids(){
    if(skipLoad==1){
      cgiVars = getCgiVars();
      $('#thebids').empty();
      displayBidList(cgiVars['auc_num']);
     } else {
	skipLoad=skipLoad*-1;	
    }
     window.setTimeout ( "reloadBids()", 5000 ); 	


    }

function displayBidListAfter(){
     cgiVars = getCgiVars();
     $('#thebids').empty();
     getAuctionAjax("get_json_bids",{"auction_uid":cgiVars['auc_num']},displayBidsCallback);
}

function displayAuctionList(gender,day){
    getAuctionAjax("get_json_auctions",{"gender":gender,"day":day},displayAuctionsCallback);
}

function displayBidList(auction_uid){
        getAuctionAjax("get_json_bids",{"auction_uid":auction_uid},displayBidsCallback);
}

function displayBidsCallback(data,status){
    typeOfBid=1;
    $('#thbids').empty();
    $.each(data['data'],function(i,item){
	    var bidDate = new Date();
	    bidDate.setTime(parseInt(item.bid_time)*10);	    
	    $('<div class="bid_item'+typeOfBid+'"><b class="bidamount">$'+item.bid_amount+'</b> was bid by <b class="bidamount">'+item.userid+'</b> on '+bidDate.toLocaleDateString()+' '+bidDate.toLocaleTimeString()+'</div>').prependTo('#thebids');
	    typeOfBid=typeOfBid*-1;
	})
	if(data['data'].length > 0 ){
	     lastBid = data['data'].pop();
	     lastBidAmount =lastBid.bid_amount;
	 } else {
		 lastBidAmount = "0";
	 }
          $("#highest_bid").html("Highest bid is $"+lastBidAmount);
}

function get_cookie ( cookie_name )
{
    var results = document.cookie.match ( '(^|;) ?' + cookie_name + '=([^;]*)(;|$)' );

    if ( results )
	return ( unescape ( results[2] ) );
    else
	return null;
}

onlyOnce=0;

function displayAuctionsCallback(data,status){
     $.each(data['data'],function(i,item){
	     if (item.bids.length > 0){
		 lastBid = item.bids.pop();
		 lastBidAmount =lastBid.bid_amount;
	     } else {
		 lastBidAmount = "0";
	     }
	     if (item.gender == "w"){
		 gender = "Womens";
	     } else {
		 gender = "Mens";
	     }
	     if (onlyOnce<2){
		 //		 alert(item.heatNum);
	      onlyOnce=onlyOnce+1;
	     }
	     auctionSummaryHtml = '<a href="auction.html?auc_num='+item.auction_uid+'&auction_type='+gender+'&heat_num='+item.heatNum+'&lane1='+item.teams[0]+'&lane2='+item.teams[1]+'&lane3='+item.teams[2]+'">';
	     auctionSummaryHtml = auctionSummaryHtml + '<div class="auc_box_wrapper"><div class="auc_box_spacer_2"><span ';
	     if(item.heatNum < 0){
		 auctionSummaryHtml = auctionSummaryHtml + ' style="color:white" '; 
	     }
	     auctionSummaryHtml = auctionSummaryHtml + 'class="auc_box_span">';
	     auctionSummaryHtml = auctionSummaryHtml + item.teams[0]+' &diams; '+item.teams[1]+' &diams; '+item.teams[2]+'</span>';
	     if (item.heatNum >= 0){
		 heatNum = item.heatNum;
	     } else {
		 if (item.gender == "m"){
		     heatNum = "1-5";
		 } else {
		     heatNum = "1-3";
		 }
	     }
	     auctionSummaryHtml = auctionSummaryHtml + '<span class="auc_box_span_heat">Heat '+heatNum+'</span></div>';
	     if(item.heatImageName == '?-?-?'){
		 item.heatImageName = "follow";
	     }

	     auctionSummaryHtml = auctionSummaryHtml + '<div class="auc_box" style="background-image:url(http://www.cmubuggy.org/bid2011/images/'+item.heatImageName+'.png);background-repeat:no-repeat" id="auc'+item.heatNum+'">';
	     auctionSummaryHtml = auctionSummaryHtml + '<div class="auc_box_spacer_1"><span class="auc_box_span_status">Highest bid : <b>$'+lastBidAmount+'</b></span></div></div></div></a>';
	     $(auctionSummaryHtml).appendTo("#auctions");
	     //$('.auc_box').corners();
	     //$('.auc_box_span_status').corners();
	     //$('.auc_box_span_heat').corners();
	     //$('.auc_box_span').corners();
	 }
	 ) 
}
function center_lane_labels(){
    lane1_y=(lane_1_y_coord-$('#lane1_span').height());
    $('#lane1_span').css("top",lane1_y+"px");    
    lane1_x=(lane_1_x_coord-($('#lane1_span').width()/2));
    $('#lane1_span').css("left",lane1_x+"px");

    lane2_y=(lane_2_y_coord-$('#lane2_span').height()-$('#lane1_span').height());
    $('#lane2_span').css("top",lane2_y+"px");    
    lane2_x=(lane_2_x_coord-($('#lane2_span').width()/2));
    $('#lane2_span').css("left",lane2_x+"px");

    lane3_y=(lane_3_y_coord-$('#lane3_span').height()-$('#lane2_span').height()-$('#lane1_span').height());
    $('#lane3_span').css("top",lane3_y+"px");    
    lane3_x=(lane_3_x_coord-($('#lane3_span').width()/2));
    $('#lane3_span').css("left",lane3_x+"px");

    ydistance = $('#lane1_span').position()['top']-$('#shadow1').position()['top'];
    xdistance = ($('#lane1_span').position()['left']+($('#lane1_span').width()/2))-($('#shadow1').position()['left']+($('#shadow1').width()/2));
    xdistance = xdistance + 10;
    $('#shadow1').css("top",(ydistance+shadow_distance)+"px");
    $('#shadow1').css("left",(xdistance)+"px");

    ydistance = $('#lane2_span').position()['top']-$('#shadow2').position()['top'];
    xdistance = ($('#lane2_span').position()['left']+($('#lane2_span').width()/2))-($('#shadow2').position()['left']+($('#shadow2').width()/2));
    xdistance = xdistance + 10;
    $('#shadow2').css("top",(ydistance+shadow_distance)+"px");
    $('#shadow2').css("left",(xdistance)+"px");

    ydistance = $('#lane3_span').position()['top']-$('#shadow3').position()['top'];
    xdistance = ($('#lane3_span').position()['left']+($('#lane3_span').width()/2))-($('#shadow3').position()['left']+($('#shadow3').width()/2));
    xdistance = xdistance + 10;
    $('#shadow3').css("top",(ydistance+shadow_distance)+"px");
    $('#shadow3').css("left",(xdistance)+"px");
}

     function calcTimeTill(timeOfEvent){    
      var localtime = (new Date()).getTime();
      var carnivaltime = timeOfEvent;
      var days = 60000*60*24;
      var hours = 60000*60;
      var mins = 60000;
      var seconds = 1000;
      //var days = 60*60*24;
      //var hours = 60*60;
      //var mins = 60;
      //var seconds = 1;
      var diff = carnivaltime*1000;
      var days_left = Math.floor((diff)/(days));
      var hours_left = diff-(days_left*days);
      hours_left = Math.floor(hours_left/hours);
      var minutes_left = diff-(days_left*days)-(hours_left*hours);
      minutes_left = Math.floor(minutes_left/mins);
      var seconds_left = diff-(days_left*days)-(hours_left*hours) - (minutes_left * mins);
      seconds_left = Math.floor(seconds_left/seconds);
      return new Array(days_left,hours_left,minutes_left,seconds_left);
     }

     

     function displayTimeTillEndOfAuctionCallback(data,status){    
	 timeTillEndOfAuction=data;
	 displayTimeTillEndOfAuction(); 
     }

     function displayReserveBidCallback(data,status){    
	 $("#bid_value3").val(data);
     }

     function outputCountdownClockHtml(days_left,hours_left,minutes_left,seconds_left){
days_left="<td class='menu_countdown_field'>"+days_left+"</td><td class='menu_countdown_desc'> days </td></td>";
      hours_left="<td class='menu_countdown_field'>"+hours_left+"</td><td class='menu_countdown_desc'> hours </td>";
      minutes_left="<td class='menu_countdown_field'>"+minutes_left+"</td><td class='menu_countdown_desc'> minutes </td>";
      seconds_left="<td class='menu_countdown_field'>"+seconds_left+"</td><td class='menu_countdown_desc'> seconds </td>";

      $('#countdown').html("<center><table class='countdowntable'><tr><td style='text-align:center' colspan=2>The auctions will end in</td>"+days_left+hours_left+minutes_left+seconds_left+"</table></center>");
} 
     function displayTimeTillEndOfAuction(){
      //fixme : take into account differential 
      //var carnivaltime = (new Date("April 14 2010 22:00:00")).getTime();
      timeLeft=calcTimeTill(timeTillEndOfAuction);
      days_left=timeLeft[0];
      hours_left=timeLeft[1];
      minutes_left=timeLeft[2];
      seconds_left=timeLeft[3];     
      outputCountdownClockHtml(days_left,hours_left,minutes_left,seconds_left);
      timeTillEndOfAuction=timeTillEndOfAuction-1;
      window.setTimeout(displayTimeTillEndOfAuction,1000);
     }
