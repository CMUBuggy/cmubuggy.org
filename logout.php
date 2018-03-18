<?php

setcookie("cmubuggy_auth",				"", time()-3600,"/");
setcookie('cmubuggy_wikiToken', 		"", time()-3600,"/");
setcookie('cmubuggy_wikiUserID', 	"", time()-3600,"/");
setcookie('cmubuggy_wikiUserName', 	"", time()-3600,"/");
setcookie('cmubuggy_wiki_session', 	"", time()-3600,"/");
setcookie('phpbb3_3ecw2_u',			"", time()-3600,"/");
setcookie('phpbb3_3ecw2_k',			"", time()-3600,"/");
setcookie('phpbb3_3ecw2_sid',			"", time()-3600,"/");
setcookie('g3sid', 						"", time()-3600,"/");

unset($_COOKIE["cmubuggy_auth"]);
unset($_COOKIE["phpbb3_3ecw2_u"]);
unset($_COOKIE["phpbb3_3ecw2_k"]);
unset($_COOKIE["phpbb3_3ecw2_sid"]);



header("Location: /");

?>
