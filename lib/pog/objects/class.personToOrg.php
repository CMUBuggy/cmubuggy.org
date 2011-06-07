<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `persontoorg` (
	`persontoorgid` int(11) NOT NULL auto_increment,
	`year` SMALLINT NOT NULL,
	`personid` int(11) NOT NULL,
	`roleid` int(11) NOT NULL,
	`orgid` int(11) NOT NULL, INDEX(`personid`,`roleid`,`orgid`), PRIMARY KEY  (`persontoorgid`)) ENGINE=MyISAM;
*/

/**
* <b>personToOrg</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=personToOrg&attributeList=array+%28%0A++0+%3D%3E+%27year%27%2C%0A++1+%3D%3E+%27person%27%2C%0A++2+%3D%3E+%27role%27%2C%0A++3+%3D%3E+%27org%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class personToOrg extends POG_Base
{
	public $persontoorgId = '';

	/**
	 * @var SMALLINT
	 */
	public $year;
	
	/**
	 * @var INT(11)
	 */
	public $personId;
	
	/**
	 * @var INT(11)
	 */
	public $roleId;
	
	/**
	 * @var INT(11)
	 */
	public $orgId;
	
	public $pog_attribute_type = array(
		"persontoorgId" => array('db_attributes' => array("NUMERIC", "INT")),
		"year" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"person" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"role" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"org" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
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
	
	function personToOrg($year='')
	{
		$this->year = $year;
	}
	
	
	/**
	* Gets object from database
	* @param integer $persontoorgId 
	* @return object $personToOrg
	*/
	function Get($persontoorgId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `persontoorg` where `persontoorgid`='".intval($persontoorgId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->persontoorgId = $row['persontoorgid'];
			$this->year = $this->Unescape($row['year']);
			$this->personId = $row['personid'];
			$this->roleId = $row['roleid'];
			$this->orgId = $row['orgid'];
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $persontoorgList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `persontoorg` ";
		$persontoorgList = Array();
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
			$sortBy = "persontoorgid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$persontoorg = new $thisObjectName();
			$persontoorg->persontoorgId = $row['persontoorgid'];
			$persontoorg->year = $this->Unescape($row['year']);
			$persontoorg->personId = $row['personid'];
			$persontoorg->roleId = $row['roleid'];
			$persontoorg->orgId = $row['orgid'];
			$persontoorgList[] = $persontoorg;
		}
		return $persontoorgList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $persontoorgId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `persontoorgid` from `persontoorg` where `persontoorgid`='".$this->persontoorgId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `persontoorg` set 
			`year`='".$this->Escape($this->year)."', 
			`personid`='".$this->personId."', 
			`roleid`='".$this->roleId."', 
			`orgid`='".$this->orgId."' where `persontoorgid`='".$this->persontoorgId."'";
		}
		else
		{
			$this->pog_query = "insert into `persontoorg` (`year`, `personid`, `roleid`, `orgid` ) values (
			'".$this->Escape($this->year)."', 
			'".$this->personId."', 
			'".$this->roleId."', 
			'".$this->orgId."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->persontoorgId == "")
		{
			$this->persontoorgId = $insertId;
		}
		return $this->persontoorgId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $persontoorgId
	*/
	function SaveNew()
	{
		$this->persontoorgId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `persontoorg` where `persontoorgid`='".$this->persontoorgId."'";
		return Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	* Deletes a list of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param bool $deep 
	* @return 
	*/
	function DeleteList($fcv_array)
	{
		if (sizeof($fcv_array) > 0)
		{
			$connection = Database::Connect();
			$pog_query = "delete from `persontoorg` where ";
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
	
	
	/**
	* Associates the person object to this one
	* @return boolean
	*/
	function GetPerson()
	{
		$person = new person();
		return $person->Get($this->personId);
	}
	
	
	/**
	* Associates the person object to this one
	* @return 
	*/
	function SetPerson(&$person)
	{
		$this->personId = $person->personId;
	}
	
	
	/**
	* Associates the role object to this one
	* @return boolean
	*/
	function GetRole()
	{
		$role = new role();
		return $role->Get($this->roleId);
	}
	
	
	/**
	* Associates the role object to this one
	* @return 
	*/
	function SetRole(&$role)
	{
		$this->roleId = $role->roleId;
	}
	
	
	/**
	* Associates the org object to this one
	* @return boolean
	*/
	function GetOrg()
	{
		$org = new org();
		return $org->Get($this->orgId);
	}
	
	
	/**
	* Associates the org object to this one
	* @return 
	*/
	function SetOrg(&$org)
	{
		$this->orgId = $org->orgId;
	}
}
?>