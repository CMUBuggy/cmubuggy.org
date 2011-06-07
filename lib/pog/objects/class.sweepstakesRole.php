<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `sweepstakesrole` (
	`sweepstakesroleid` int(11) NOT NULL auto_increment,
	`description` VARCHAR(255) NOT NULL, PRIMARY KEY  (`sweepstakesroleid`)) ENGINE=MyISAM;
*/

/**
* <b>sweepstakesRole</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=sweepstakesRole&attributeList=array+%28%0A++0+%3D%3E+%27description%27%2C%0A++1+%3D%3E+%27sweepstakes%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class sweepstakesRole extends POG_Base
{
	public $sweepstakesroleId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $description;
	
	/**
	 * @var private array of sweepstakes objects
	 */
	private $_sweepstakesList = array();
	
	public $pog_attribute_type = array(
		"sweepstakesroleId" => array('db_attributes' => array("NUMERIC", "INT")),
		"description" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"sweepstakes" => array('db_attributes' => array("OBJECT", "HASMANY")),
		);
	public $pog_query;
	
	
	/**
	* Getter for some private attributes
	* @return mixed $attribute
	*/
	public function __get($attribute)
	{
		if (isset($this->{"_".$attribute}))
		{
			return $this->{"_".$attribute};
		}
		else
		{
			return false;
		}
	}
	
	function sweepstakesRole($description='')
	{
		$this->description = $description;
		$this->_sweepstakesList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $sweepstakesroleId 
	* @return object $sweepstakesRole
	*/
	function Get($sweepstakesroleId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `sweepstakesrole` where `sweepstakesroleid`='".intval($sweepstakesroleId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->sweepstakesroleId = $row['sweepstakesroleid'];
			$this->description = $this->Unescape($row['description']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $sweepstakesroleList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `sweepstakesrole` ";
		$sweepstakesroleList = Array();
		if (sizeof($fcv_array) > 0)
		{
			$this->pog_query .= " where ";
			for ($i=0, $c=sizeof($fcv_array); $i<$c; $i++)
			{
				if (sizeof($fcv_array[$i]) == 1)
				{
					$this->pog_query .= " ".$fcv_array[$i][0]." ";
					continue;
				}
				else
				{
					if ($i > 0 && sizeof($fcv_array[$i-1]) != 1)
					{
						$this->pog_query .= " AND ";
					}
					if (isset($this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
					{
						if ($GLOBALS['configuration']['db_encoding'] == 1)
						{
							$value = POG_Base::IsColumn($fcv_array[$i][2]) ? "BASE64_DECODE(".$fcv_array[$i][2].")" : "'".$fcv_array[$i][2]."'";
							$this->pog_query .= "BASE64_DECODE(`".$fcv_array[$i][0]."`) ".$fcv_array[$i][1]." ".$value;
						}
						else
						{
							$value =  POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$this->Escape($fcv_array[$i][2])."'";
							$this->pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
						}
					}
					else
					{
						$value = POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$fcv_array[$i][2]."'";
						$this->pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
					}
				}
			}
		}
		if ($sortBy != '')
		{
			if (isset($this->pog_attribute_type[$sortBy]['db_attributes']) && $this->pog_attribute_type[$sortBy]['db_attributes'][0] != 'NUMERIC' && $this->pog_attribute_type[$sortBy]['db_attributes'][0] != 'SET')
			{
				if ($GLOBALS['configuration']['db_encoding'] == 1)
				{
					$sortBy = "BASE64_DECODE($sortBy) ";
				}
				else
				{
					$sortBy = "$sortBy ";
				}
			}
			else
			{
				$sortBy = "$sortBy ";
			}
		}
		else
		{
			$sortBy = "sweepstakesroleid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$sweepstakesrole = new $thisObjectName();
			$sweepstakesrole->sweepstakesroleId = $row['sweepstakesroleid'];
			$sweepstakesrole->description = $this->Unescape($row['description']);
			$sweepstakesroleList[] = $sweepstakesrole;
		}
		return $sweepstakesroleList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $sweepstakesroleId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `sweepstakesroleid` from `sweepstakesrole` where `sweepstakesroleid`='".$this->sweepstakesroleId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `sweepstakesrole` set 
			`description`='".$this->Escape($this->description)."'where `sweepstakesroleid`='".$this->sweepstakesroleId."'";
		}
		else
		{
			$this->pog_query = "insert into `sweepstakesrole` (`description`) values (
			'".$this->Escape($this->description)."')";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->sweepstakesroleId == "")
		{
			$this->sweepstakesroleId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_sweepstakesList as $sweepstakes)
			{
				$sweepstakes->sweepstakesroleId = $this->sweepstakesroleId;
				$sweepstakes->Save($deep);
			}
		}
		return $this->sweepstakesroleId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $sweepstakesroleId
	*/
	function SaveNew($deep = false)
	{
		$this->sweepstakesroleId = '';
		return $this->Save($deep);
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete($deep = false, $across = false)
	{
		if ($deep)
		{
			$sweepstakesList = $this->GetSweepstakesList();
			foreach ($sweepstakesList as $sweepstakes)
			{
				$sweepstakes->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `sweepstakesrole` where `sweepstakesroleid`='".$this->sweepstakesroleId."'";
		return Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	* Deletes a list of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param bool $deep 
	* @return 
	*/
	function DeleteList($fcv_array, $deep = false, $across = false)
	{
		if (sizeof($fcv_array) > 0)
		{
			if ($deep || $across)
			{
				$objectList = $this->GetList($fcv_array);
				foreach ($objectList as $object)
				{
					$object->Delete($deep, $across);
				}
			}
			else
			{
				$connection = Database::Connect();
				$pog_query = "delete from `sweepstakesrole` where ";
				for ($i=0, $c=sizeof($fcv_array); $i<$c; $i++)
				{
					if (sizeof($fcv_array[$i]) == 1)
					{
						$pog_query .= " ".$fcv_array[$i][0]." ";
						continue;
					}
					else
					{
						if ($i > 0 && sizeof($fcv_array[$i-1]) !== 1)
						{
							$pog_query .= " AND ";
						}
						if (isset($this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
						{
							$pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." '".$this->Escape($fcv_array[$i][2])."'";
						}
						else
						{
							$pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." '".$fcv_array[$i][2]."'";
						}
					}
				}
				return Database::NonQuery($pog_query, $connection);
			}
		}
	}
	
	
	/**
	* Gets a list of sweepstakes objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of sweepstakes objects
	*/
	function GetSweepstakesList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$sweepstakes = new sweepstakes();
		$fcv_array[] = array("sweepstakesroleId", "=", $this->sweepstakesroleId);
		$dbObjects = $sweepstakes->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all sweepstakes objects in the sweepstakes List array. Any existing sweepstakes will become orphan(s)
	* @return null
	*/
	function SetSweepstakesList(&$list)
	{
		$this->_sweepstakesList = array();
		$existingSweepstakesList = $this->GetSweepstakesList();
		foreach ($existingSweepstakesList as $sweepstakes)
		{
			$sweepstakes->sweepstakesroleId = '';
			$sweepstakes->Save(false);
		}
		$this->_sweepstakesList = $list;
	}
	
	
	/**
	* Associates the sweepstakes object to this one
	* @return 
	*/
	function AddSweepstakes(&$sweepstakes)
	{
		$sweepstakes->sweepstakesroleId = $this->sweepstakesroleId;
		$found = false;
		foreach($this->_sweepstakesList as $sweepstakes2)
		{
			if ($sweepstakes->sweepstakesId > 0 && $sweepstakes->sweepstakesId == $sweepstakes2->sweepstakesId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_sweepstakesList[] = $sweepstakes;
		}
	}
}
?>