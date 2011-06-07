<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `role` (
	`roleid` int(11) NOT NULL auto_increment,
	`description` VARCHAR(255) NOT NULL, PRIMARY KEY  (`roleid`)) ENGINE=MyISAM;
*/

/**
* <b>role</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=role&attributeList=array+%28%0A++0+%3D%3E+%27description%27%2C%0A++1+%3D%3E+%27personToOrg%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class role extends POG_Base
{
	public $roleId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $description;
	
	/**
	 * @var private array of personToOrg objects
	 */
	private $_persontoorgList = array();
	
	public $pog_attribute_type = array(
		"roleId" => array('db_attributes' => array("NUMERIC", "INT")),
		"description" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"personToOrg" => array('db_attributes' => array("OBJECT", "HASMANY")),
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
	
	function role($description='')
	{
		$this->description = $description;
		$this->_persontoorgList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $roleId 
	* @return object $role
	*/
	function Get($roleId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `role` where `roleid`='".intval($roleId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->roleId = $row['roleid'];
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
	* @return array $roleList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `role` ";
		$roleList = Array();
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
			$sortBy = "roleid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$role = new $thisObjectName();
			$role->roleId = $row['roleid'];
			$role->description = $this->Unescape($row['description']);
			$roleList[] = $role;
		}
		return $roleList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $roleId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `roleid` from `role` where `roleid`='".$this->roleId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `role` set 
			`description`='".$this->Escape($this->description)."'where `roleid`='".$this->roleId."'";
		}
		else
		{
			$this->pog_query = "insert into `role` (`description`) values (
			'".$this->Escape($this->description)."')";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->roleId == "")
		{
			$this->roleId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_persontoorgList as $persontoorg)
			{
				$persontoorg->roleId = $this->roleId;
				$persontoorg->Save($deep);
			}
		}
		return $this->roleId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $roleId
	*/
	function SaveNew($deep = false)
	{
		$this->roleId = '';
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
			$persontoorgList = $this->GetPersontoorgList();
			foreach ($persontoorgList as $persontoorg)
			{
				$persontoorg->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `role` where `roleid`='".$this->roleId."'";
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
				$pog_query = "delete from `role` where ";
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
	* Gets a list of personToOrg objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of personToOrg objects
	*/
	function GetPersontoorgList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$persontoorg = new personToOrg();
		$fcv_array[] = array("roleId", "=", $this->roleId);
		$dbObjects = $persontoorg->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all personToOrg objects in the personToOrg List array. Any existing personToOrg will become orphan(s)
	* @return null
	*/
	function SetPersontoorgList(&$list)
	{
		$this->_persontoorgList = array();
		$existingPersontoorgList = $this->GetPersontoorgList();
		foreach ($existingPersontoorgList as $persontoorg)
		{
			$persontoorg->roleId = '';
			$persontoorg->Save(false);
		}
		$this->_persontoorgList = $list;
	}
	
	
	/**
	* Associates the personToOrg object to this one
	* @return 
	*/
	function AddPersontoorg(&$persontoorg)
	{
		$persontoorg->roleId = $this->roleId;
		$found = false;
		foreach($this->_persontoorgList as $persontoorg2)
		{
			if ($persontoorg->persontoorgId > 0 && $persontoorg->persontoorgId == $persontoorg2->persontoorgId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_persontoorgList[] = $persontoorg;
		}
	}
}
?>