<?php

  $chartData->setAxisName(0,"Time (seconds)");
  $chartData->setAbscissa("Year");

  /* Create the pChart object */
  $myPicture = new pImage(800,400,$chartData);

  /* Turn of Antialiasing */
  $myPicture->Antialias = FALSE;

  /* Add a border to the picture */
  $myPicture->drawRectangle(0,0,799,399,array("R"=>0,"G"=>0,"B"=>0));

  /* Write the chart title */
  $myPicture->setFontProperties(array("FontName"=>"lib/pChart/fonts/calibri.ttf","FontSize"=>9));
  $myPicture->drawText(150,35,$chartTitle,array("FontSize"=>18,"Align"=>TEXT_ALIGN_BOTTOMMIDDLE));

  /* Set the default font */
  $myPicture->setFontProperties(array("FontName"=>"lib/pChart/fonts/verdana.ttf","FontSize"=>9));

  /* Define the chart area */
  $myPicture->setGraphArea(60,40,750,350);

  /* Draw the scale */
  $scaleSettings = array("XMargin"=>10,"YMargin"=>10,"Floating"=>FALSE,"GridR"=>200,"GridG"=>200,"GridB"=>200,"DrawSubTicks"=>FALSE,"CycleBackground"=>TRUE);
  $myPicture->drawScale($scaleSettings);

  /* Turn on Antialiasing */
  $myPicture->Antialias = TRUE;

  /* Draw the line chart */
  $lineChartSettings = array("BreakVoid"=>FALSE);
  $myPicture->drawLineChart($lineChartSettings);

  /* Write the chart legend */
  $myPicture->drawLegend(400,20,array("Style"=>LEGEND_NOBORDER,"Mode"=>LEGEND_HORIZONTAL));


  /* Build the PNG file and send it to the web browser */
  $myPicture->Render("content/cache/graph/".$filename.".png");

  echo("<img src=\"/content/cache/graph/".$filename.".png\" alt=\"\" class=\"img-fluid my-2\">");
?>
