<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `orgusermap` (
	`orgid` int(11) NOT NULL,
	`userid` int(11) NOT NULL,INDEX(`orgid`, `userid`)) ENGINE=MyISAM;
*/

/**
* <b>orguserMap</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @copyright Free for personal & commercial use. (Offered under the BSD license)
*/
class orguserMap
{
	public $orgId = '';

	public $userId = '';

	public $pog_attribute_type = array(
		"orgId" => array('db_attributes' => array("NUMERIC", "INT")),
		"userId" => array('db_attributes' => array("NUMERIC", "INT")));
		public $pog_query;
	
	
	/**
	* Creates a mapping between the two objects
	* @param org $object 
	* @param user $otherObject 
	* @return 
	*/
	function AddMapping($object, $otherObject)
	{
		if ($object instanceof org && $object->orgId != '')
		{
			$this->orgId = $object->orgId;
			$this->userId = $otherObject->userId;
			return $this->Save();
		}
		else if ($object instanceof user && $object->userId != '')
		{
			$this->userId = $object->userId;
			$this->orgId = $otherObject->orgId;
			return $this->Save();
		}
		else
		{
			return false;
		}
	}
	
	
	/**
	* Removes the mapping between the two objects
	* @param Object $object 
	* @param Object $object2 
	* @return 
	*/
	function RemoveMapping($object, $otherObject = null)
	{
		$connection = Database::Connect();
		if ($object instanceof org)
		{
			$this->pog_query = "delete from `orgusermap` where `orgid` = '".$object->orgId."'";
			if ($otherObject != null && $otherObject instanceof user)
			{
				$this->pog_query .= " and `userid` = '".$otherObject->userId."'";
			}
		}
		else if ($object instanceof user)
		{
			$this->pog_query = "delete from `orgusermap` where `userid` = '".$object->userId."'";
			if ($otherObject != null && $otherObject instanceof org)
			{
				$this->pog_query .= " and `orgid` = '".$otherObject->orgId."'";
			}
		}
		Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	* Physically saves the mapping to the database
	* @return 
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `orgid` from `orgusermap` where `orgid`='".$this->orgId."' AND `userid`='".$this->userId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows == 0)
		{
			$this->pog_query = "insert into `orgusermap` (`orgid`, `userid`) values ('".$this->orgId."', '".$this->userId."')";
		}
		return Database::InsertOrUpdate($this->pog_query, $connection);
	}
}
?>