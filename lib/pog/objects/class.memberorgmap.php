<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `memberorgmap` (
	`memberid` int(11) NOT NULL,
	`orgid` int(11) NOT NULL,INDEX(`memberid`, `orgid`)) ENGINE=MyISAM;
*/

/**
* <b>memberorgMap</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5
* @copyright Free for personal & commercial use. (Offered under the BSD license)
*/
class memberorgMap
{
	public $memberId = '';

	public $orgId = '';

	public $pog_attribute_type = array(
		"memberId" => array('db_attributes' => array("NUMERIC", "INT")),
		"orgId" => array('db_attributes' => array("NUMERIC", "INT")));
		public $pog_query;
	
	
	/**
	* Creates a mapping between the two objects
	* @param member $object 
	* @param org $otherObject 
	* @return 
	*/
	function AddMapping($object, $otherObject)
	{
		if ($object instanceof member && $object->memberId != '')
		{
			$this->memberId = $object->memberId;
			$this->orgId = $otherObject->orgId;
			return $this->Save();
		}
		else if ($object instanceof org && $object->orgId != '')
		{
			$this->orgId = $object->orgId;
			$this->memberId = $otherObject->memberId;
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
		if ($object instanceof member)
		{
			$this->pog_query = "delete from `memberorgmap` where `memberid` = '".$object->memberId."'";
			if ($otherObject != null && $otherObject instanceof org)
			{
				$this->pog_query .= " and `orgid` = '".$otherObject->orgId."'";
			}
		}
		else if ($object instanceof org)
		{
			$this->pog_query = "delete from `memberorgmap` where `orgid` = '".$object->orgId."'";
			if ($otherObject != null && $otherObject instanceof member)
			{
				$this->pog_query .= " and `memberid` = '".$otherObject->memberId."'";
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
		$this->pog_query = "select `memberid` from `memberorgmap` where `memberid`='".$this->memberId."' AND `orgid`='".$this->orgId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows == 0)
		{
			$this->pog_query = "insert into `memberorgmap` (`memberid`, `orgid`) values ('".$this->memberId."', '".$this->orgId."')";
		}
		return Database::InsertOrUpdate($this->pog_query, $connection);
	}
}
?>