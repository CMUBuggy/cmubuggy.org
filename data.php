<?php
include_once("dbconfig.inc");
include_once("util.inc");
include_once("lib/pog/pog_includes.inc");

if(count($_POST)>0) {
	$uservars = getuservars($_COOKIE["cmubuggy_auth"]);
	if (isset($uservars["adminlevel"])){
		if($uservars["adminlevel"] > 0){
			if(isset($_POST["type"])){
				$type = $_POST["type"];
				
				$de = new dataedit();
				$de->edittype = $type;
				$de->timestamp = time();
				$de->userId = $uservars["userid"];
				
				$id = null;
				$newval = null;
				if(isset($_POST["element_id"]))	{ $id = $_POST["element_id"]; }
				if(isset($_POST["update_value"])){ $newval = $_POST["update_value"];}
			
				switch($type) {
					case "add":
						$objType = $_POST["objtype"];
						$newobj = new $objType();
						
						$ignore = array("type","objtype",);
						$keys = array_keys($_POST);
						foreach($keys as $key){
							if(!array_key_exists($key, $ignore)){
								$newobj->$key = $_POST[$key];
								echo($_POST[$key]."<br />");
							}
						}
						$objId = $newobj->Save();
						$de->objtype = $objType;
						$de->objid = $objId;				
						
					break;
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
		}
	}
} else {
	echo("go away");	
}


?>