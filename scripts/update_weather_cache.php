<?php
	//also consider google weather API, but they don't have hourly forecasts
	//http://www.google.com/ig/api?weather=15213


	//wunderground.com API key = e834497e61773017
	//http://www.wunderground.com/weather/api/d/documentation.html
	
	$json_string = file_get_contents("http://api.wunderground.com/api/e834497e61773017/hourly7day/q/15213.json");
	$parsed_json = json_decode($json_string);
	$hours = $parsed_json->hourly_forecast;
	foreach($hours as $hour){
		echo($hour->FCTTIME->pretty." : feels like:".$hour->feelslike->english."<br />");
	}
?>
