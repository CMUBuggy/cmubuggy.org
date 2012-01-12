<?php
include_once("dbconfig.inc");
include_once("lib/pog/pog_includes.inc");

if(count($_POST)>0) {
	if(isset($_POST["type"])){
		$type = $_POST["type"];
		
		$de = new dataedit();
		$de->edittype = $type;
		$de->timestamp = time();
		
		$id = null;
		$newval = null;
		if(isset($_POST["element_id"]))	{ $id = $_POST["element_id"]; }
		if(isset($_POST["update_value"])){ $newval = $_POST["update_value"];}
	
		switch($type) {
			case "update":
				$idvals = explode("-",$id);
				$objType = $idvals[0];
				$objId = $idvals[1];
				$objAttr = $idvals[2];
			
				$de->objtype = $objType;
				$de->objid = $objId;
				$de->objattr = $objAttr;
				$de->newvalue = $newval;
				
				$object = new $objType();
				$object->Get($objId);
				$de->oldvalue = $object->$objAttr;
				$object->$objAttr = $newval;
				$object->Save();
				echo($object->$objAttr);
				break;
			default: echo("no default data handler");	
		}
		$de->Save();
	}
} else {
	echo("go away");	
}


?>