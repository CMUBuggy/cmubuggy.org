<?php

	require_once "Mail.php";

	function send($mail){
		$host = "ssl://smtp.gmail.com";
      $port = "465";
		$username = "mailer@cmubuggy.org";
		$password = "2r6taFru";

		$from = "CMU Buggy Alumni Association <admin@cmubuggy.org>";
		if(isset($mail["from"])){
			$from = $mail["from"];	
		}

		$to = $mail["to"];
		$headers = array ('From' => $from, 'To' => $mail["to"], 'Subject' => $mail["subject"]);
		$body = $mail["body"];
        
      $smtp = Mail::factory('smtp',
          array ('host' => $host,
            'port' => $port,
            'auth' => true,
            'username' => $username,
            'password' => $password));

		$mail = $smtp->send($to, $headers, $body);
		if (PEAR::isError($mail)) {
			return FALSE;
		} else {
			return TRUE;
		}
	}

?>