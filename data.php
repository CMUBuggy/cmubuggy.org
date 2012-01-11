<?php
include_once("dbconfig.inc");
include_once("lib/pog/pog_includes.inc");

if(count($_POST)>0) {
	if(isset($_POST["type"])){
		switch($_POST["type"]) {
			case "admin":
				$id = $_POST["id"];
				$idvals = explode("-",$id);
				$newval = $_POST["newval"];
				
				$object = new $idvals[0]();
				$object->Get($idvals[1]);
				$object->$idvals[2] = $newval;
				$object->Save();
				break;
			default: echo("no default data handler");	
		}			
	}
} else {
	echo("go away");	
}


?>