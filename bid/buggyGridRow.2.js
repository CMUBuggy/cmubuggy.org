buggyReserveRow=["<span  class='bubbleWbackgroundYellowNoPadding' style='padding-right:5px;padding-left:5px'>",
		  "<img src='https://cdn1.iconfinder.com/data/icons/softwaredemo/PNG/16x16/DrawingPin1_Blue.png'>",
		  "${0}",
		 "</span>"].join("");
buggyBlock=["<div id=\'bidBlock{0}\' class='bidBlock' style='position:relative;px;margin-left:auto;margin-right:auto;margin-left:50px;width:625px;display:block;border-width:5px;border-style:solid'>",
                 "<center>",
                 "<div  style='width:600px;position:relative;margin-left:auto;margin-right:auto;'>&nbsp",
                  "<div id='biddingControlsManual' style='padding:5px;float:left;'>",
                   "<div class='bubbleWbackground' style='width:170px'> Make Bid ",
	           "</div>",
                   "<div style='margin-top:5px;margin-left:25px;'>$<input id='manBidInput{0}' type='text' width=50px size=3 style='padding:0;margin:0;display:inline;float:none'/> <a class='bidButton' onClick='makeManualBid({0})'>Bid </a>",
                   "</div>",
                  "</div>",
                  "<div style='border-width:0px;border-style:solid;width:200px;float:left;padding-top:10px'>",
                  "<div id='addBidsHere{0}' style='display:table;'>",//this is where you start appending
                  "</div>",
                  "</div>",
                  "<div id='biddingControlsReserve' style='padding:5px;float:left'>",
                   "<div id='biddingControlsReserve{0}' class='bubbleWbackground' style='width:170px'> Make Reserve Bid",
	           "</div>",
                   "<div style='margin-top:5px;margin-left:25px'>$<input id='manAutoInput{0}' type='text' width=50px size=3 style='padding:0;margin:0;display:inline;float:none'/> <a onClick='makeAutoBid({0})' class='bidButton'>Bid </a>",
	           "</div>",
                   "<div style='float:none;clear:both;padding-bottom:7px'>",
                   "</div>",
                  "</div>",
	          "<div style='float:none;clear:both;padding-bottom:15px'></div></center>",
                 "</div>",
                 "</center>",
                "</div>"].join("");

buggyBidRow=["<div style='display:table-row;' userId='{1}' class='buggybuggybuggy'>",
	      "<div style='display:table-cell;padding-top:3px;padding-bottom:3px' class='bidRowFirstCell bidRowCell'>",
	      "${0}",
 	      "</div>",
	      "<div class='bidRowCell bidRowLastCell' style='display:table-cell;padding-right:7px'>",
	      "{1}",
	      "</div>",
	     "</div>",
	     "<div class='rowSpacer buggybuggybuggy'></div>"].join("");
buggyGridRow=["<div class='rowSpacer'></div>",
               "<!--<div style='position:relative;top:{10}px;z-index:900'>-->", //{10} = relative amount to move div up ( -33 * x )
//{0} = auctionUid
	         "<div id='bidRowHeatNum' class='heatCircleNew' style='position:relative;top:{10}px;{11}'>",
	          "&nbsp;{1}&nbsp",//{1} = heat num
	         "</div>",
	          "<span id='auctionContainer{0}amount' style='position:relative;top:{10}px' class='bidRowCell bidRowAmountCell'>",
	           "${2}",//{2} = bid amount
	          "</span>",
	          "<span  style='position:relative;top:{10}px' class='bidRowCell bidRowMakeBidCell'>",
	           "<a id='makeBidLink{0}' onClick='showBids({0})' style='cursor:default'> Make Bid </a>",
	          "</span>",
	          "<span  id='Org1{0}' style='position:relative;top:{10}px' class='bidRowCell bidRowOrg1' >",
	           "{3}",//{3} = org 1 name
	          "</span>",
	          "<span  style='position:relative;top:{10}px' class='bidRowCell bidRowOrg1' >",
	           "<img  class='buggyImg' width=125 height=48 src='buggy/{4}.png'>",
	          // {4} buggy 1 png name
   	          "</span>",
	          "<span   id='Org2{0}'  style='position:relative;top:{10}px' class='bidRowCell bidRowOrg2'>",
 	            "{5}",//org 2 name
	           "</span>",
	           "<span  style='position:relative;top:{10}px' class='bidRowCell bidRowOrg2'>",
	            "<img class='buggyImg' width=125 height=48 src='buggy/{6}.png'>",
	           //{6} = org 2 png name
	           "</span>",
	           "<span   id='Org3{0}'  style='position:relative;top:{10}px' class='bidRowCell bidRowOrg2'>",
	            "{7}",//{7} = org 3 name
	           "</span>",
	           "<span style='position:relative;top:{10}px'  class='bidRowCell bidRowOrg3'>",
	            "<img class='buggyImg' width=125 height=48 src='buggy/{8}.png'>",
	            //{8} = buggy 3 png name
 	            "&nbsp;",
	           "</span>",
                "<div style='float:none;clear:both'></div>",// new
	        "<div id=\'bidBlock{0}\' class='bidBlock' style='position:relative;top:{10}px;margin-left:auto;margin-right:auto;margin-left:50px;width:625px;'>",
                 "<center>",
                 "<div  style='width:600px;position:relative;margin-left:auto;margin-right:auto;'>&nbsp",
                  "<div id='biddingControlsManual' style='padding:5px;float:left;'>",
                   "<div class='bubbleWbackground' style='width:170px'> Make Bid ",
	           "</div>",
                   "<div style='margin-top:5px;margin-left:25px;'>$<input id='manBidInput{0}' type='text' width=50px size=3 style='padding:0;margin:0;display:inline;float:none'/> <a class='bidButton' onClick='makeManualBid({0})'>Bid </a>",
                   "</div>",
//                  "</div>",
                  "</div>",
                  "<div style='border-width:0px;border-style:solid;width:200px;float:left;padding-top:10px'>",
                  "<div id='addBidsHere{0}' style='display:table;'>",//this is where you start appending
                 /*  "<div id='addBidsHere{0}' style='display:table-row;'>",
                    "<div style='display:table-cell' class='bidRowFirstCell bidRowCell'>",
	             "BID AMOUNT",
	            "</div>",
	            "<div class='bidRowCell bidRowLastCell' style='display:table-cell'>",
	             "BID USER ID",
	            "</div>",
	           "</div>",
	           "<div class='rowSpacer'></div>",*/
                  "</div>",
                  "</div>",
/*	          "<div id='biddingControlsStatus' style='float:left;padding:5px;width:200px'>",
	           "{9}", // {9} = heat description
	           "<br><span id='auctionDescription{0}'>High Bid : ${2}</span>",
	          "</div>",*/
                  "<div id='biddingControlsReserve' style='padding:5px;float:left;'>",
                   "<div id='biddingControlsReserve{0}' class='bubbleWbackground' style='width:170px;'> Make Reserve Bid",
	           "</div>",
                   "<div style='margin-top:5px;margin-left:25px'>$<input id='manAutoInput{0}' type='text' width=50px size=3 style='padding:0;margin:0;display:inline;float:none'/> <a onClick='makeAutoBid({0})' class='bidButton'>Bid </a>",
	           "</div>",
                   "<div style='float:none;clear:both;padding-bottom:7px'>",
                  "</div>",//                   "</div>",
                  "</div>",
/*	          "<div id='biddingControlsStatus' style='display:block;margin:auto;padding:5px;width:500px'>",
	           "{9}", // {9} = heat description
	           "<br><span id='auctionDescription{0}'>High Bid : ${2}</span>",
	          "</div>",*/
	          "<div style='float:none;clear:both;padding-bottom:15px'></div></center>",
                 "</div>",
                 "</center>",
                "</div>"].join("");
