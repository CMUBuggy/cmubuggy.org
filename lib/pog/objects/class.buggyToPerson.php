<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `buggytoperson` (
	`buggytopersonid` int(11) NOT NULL auto_increment,
	`islead` TINYINT NOT NULL,
	`personid` int(11) NOT NULL,
	`buggyid` int(11) NOT NULL, INDEX(`personid`,`buggyid`), PRIMARY KEY  (`buggytopersonid`)) ENGINE=MyISAM;
*/

/**
* <b>buggyToPerson</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=buggyToPerson&attributeList=array+%28%0A++0+%3D%3E+%27isLead%27%2C%0A++1+%3D%3E+%27person%27%2C%0A++2+%3D%3E+%27buggy%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class buggyToPerson extends POG_Base
{
	public $buggytopersonId = '';

	/**
	 * @var TINYINT
	 */
	public $isLead;
	
	/**
	 * @var INT(11)
	 */
	public $personId;
	
	/**
	 * @var INT(11)
	 */
	public $buggyId;
	
	public $pog_attribute_type = array(
		"buggytopersonId" => array('db_attributes' => array("NUMERIC", "INT")),
		"isLead" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"person" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"buggy" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
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
	
	function buggyToPerson($isLead='')
	{
		$this->isLead = $isLead;
	}
	
	
	/**
	* Gets object from database
	* @param integer $buggytopersonId 
	* @return object $buggyToPerson
	*/
	function Get($buggytopersonId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `buggytoperson` where `buggytopersonid`='".intval($buggytopersonId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->buggytopersonId = $row['buggytopersonid'];
			$this->isLead = $this->Unescape($row['islead']);
			$this->personId = $row['personid'];
			$this->buggyId = $row['buggyid'];
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $buggytopersonList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `buggytoperson` ";
		$buggytopersonList = Array();
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
			$sortBy = "buggytopersonid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$buggytoperson = new $thisObjectName();
			$buggytoperson->buggytopersonId = $row['buggytopersonid'];
			$buggytoperson->isLead = $this->Unescape($row['islead']);
			$buggytoperson->personId = $row['personid'];
			$buggytoperson->buggyId = $row['buggyid'];
			$buggytopersonList[] = $buggytoperson;
		}
		return $buggytopersonList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $buggytopersonId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `buggytopersonid` from `buggytoperson` where `buggytopersonid`='".$this->buggytopersonId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `buggytoperson` set 
			`islead`='".$this->Escape($this->isLead)."', 
			`personid`='".$this->personId."', 
			`buggyid`='".$this->buggyId."' where `buggytopersonid`='".$this->buggytopersonId."'";
		}
		else
		{
			$this->pog_query = "insert into `buggytoperson` (`islead`, `personid`, `buggyid` ) values (
			'".$this->Escape($this->isLead)."', 
			'".$this->personId."', 
			'".$this->buggyId."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->buggytopersonId == "")
		{
			$this->buggytopersonId = $insertId;
		}
		return $this->buggytopersonId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $buggytopersonId
	*/
	function SaveNew()
	{
		$this->buggytopersonId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `buggytoperson` where `buggytopersonid`='".$this->buggytopersonId."'";
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
			$pog_query = "delete from `buggytoperson` where ";
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
	* Associates the buggy object to this one
	* @return boolean
	*/
	function GetBuggy()
	{
		$buggy = new buggy();
		return $buggy->Get($this->buggyId);
	}
	
	
	/**
	* Associates the buggy object to this one
	* @return 
	*/
	function SetBuggy(&$buggy)
	{
		$this->buggyId = $buggy->buggyId;
	}
}
?>