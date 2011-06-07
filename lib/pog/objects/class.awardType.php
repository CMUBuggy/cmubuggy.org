<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `awardtype` (
	`awardtypeid` int(11) NOT NULL auto_increment,
	`forbuggy` TINYINT NOT NULL,
	`description` VARCHAR(255) NOT NULL, PRIMARY KEY  (`awardtypeid`)) ENGINE=MyISAM;
*/

/**
* <b>awardType</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=awardType&attributeList=array+%28%0A++0+%3D%3E+%27orgAward%27%2C%0A++1+%3D%3E+%27buggyAward%27%2C%0A++2+%3D%3E+%27forBuggy%27%2C%0A++3+%3D%3E+%27description%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class awardType extends POG_Base
{
	public $awardtypeId = '';

	/**
	 * @var private array of orgAward objects
	 */
	private $_orgawardList = array();
	
	/**
	 * @var private array of buggyAward objects
	 */
	private $_buggyawardList = array();
	
	/**
	 * @var TINYINT
	 */
	public $forBuggy;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $description;
	
	public $pog_attribute_type = array(
		"awardtypeId" => array('db_attributes' => array("NUMERIC", "INT")),
		"orgAward" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"buggyAward" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"forBuggy" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"description" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function awardType($forBuggy='', $description='')
	{
		$this->_orgawardList = array();
		$this->_buggyawardList = array();
		$this->forBuggy = $forBuggy;
		$this->description = $description;
	}
	
	
	/**
	* Gets object from database
	* @param integer $awardtypeId 
	* @return object $awardType
	*/
	function Get($awardtypeId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `awardtype` where `awardtypeid`='".intval($awardtypeId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->awardtypeId = $row['awardtypeid'];
			$this->forBuggy = $this->Unescape($row['forbuggy']);
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
	* @return array $awardtypeList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `awardtype` ";
		$awardtypeList = Array();
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
			$sortBy = "awardtypeid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$awardtype = new $thisObjectName();
			$awardtype->awardtypeId = $row['awardtypeid'];
			$awardtype->forBuggy = $this->Unescape($row['forbuggy']);
			$awardtype->description = $this->Unescape($row['description']);
			$awardtypeList[] = $awardtype;
		}
		return $awardtypeList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $awardtypeId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `awardtypeid` from `awardtype` where `awardtypeid`='".$this->awardtypeId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `awardtype` set 
			`forbuggy`='".$this->Escape($this->forBuggy)."', 
			`description`='".$this->Escape($this->description)."' where `awardtypeid`='".$this->awardtypeId."'";
		}
		else
		{
			$this->pog_query = "insert into `awardtype` (`forbuggy`, `description` ) values (
			'".$this->Escape($this->forBuggy)."', 
			'".$this->Escape($this->description)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->awardtypeId == "")
		{
			$this->awardtypeId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_orgawardList as $orgaward)
			{
				$orgaward->awardtypeId = $this->awardtypeId;
				$orgaward->Save($deep);
			}
			foreach ($this->_buggyawardList as $buggyaward)
			{
				$buggyaward->awardtypeId = $this->awardtypeId;
				$buggyaward->Save($deep);
			}
		}
		return $this->awardtypeId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $awardtypeId
	*/
	function SaveNew($deep = false)
	{
		$this->awardtypeId = '';
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
			$orgawardList = $this->GetOrgawardList();
			foreach ($orgawardList as $orgaward)
			{
				$orgaward->Delete($deep, $across);
			}
			$buggyawardList = $this->GetBuggyawardList();
			foreach ($buggyawardList as $buggyaward)
			{
				$buggyaward->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `awardtype` where `awardtypeid`='".$this->awardtypeId."'";
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
				$pog_query = "delete from `awardtype` where ";
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
	* Gets a list of orgAward objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of orgAward objects
	*/
	function GetOrgawardList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$orgaward = new orgAward();
		$fcv_array[] = array("awardtypeId", "=", $this->awardtypeId);
		$dbObjects = $orgaward->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all orgAward objects in the orgAward List array. Any existing orgAward will become orphan(s)
	* @return null
	*/
	function SetOrgawardList(&$list)
	{
		$this->_orgawardList = array();
		$existingOrgawardList = $this->GetOrgawardList();
		foreach ($existingOrgawardList as $orgaward)
		{
			$orgaward->awardtypeId = '';
			$orgaward->Save(false);
		}
		$this->_orgawardList = $list;
	}
	
	
	/**
	* Associates the orgAward object to this one
	* @return 
	*/
	function AddOrgaward(&$orgaward)
	{
		$orgaward->awardtypeId = $this->awardtypeId;
		$found = false;
		foreach($this->_orgawardList as $orgaward2)
		{
			if ($orgaward->orgawardId > 0 && $orgaward->orgawardId == $orgaward2->orgawardId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_orgawardList[] = $orgaward;
		}
	}
	
	
	/**
	* Gets a list of buggyAward objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of buggyAward objects
	*/
	function GetBuggyawardList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$buggyaward = new buggyAward();
		$fcv_array[] = array("awardtypeId", "=", $this->awardtypeId);
		$dbObjects = $buggyaward->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all buggyAward objects in the buggyAward List array. Any existing buggyAward will become orphan(s)
	* @return null
	*/
	function SetBuggyawardList(&$list)
	{
		$this->_buggyawardList = array();
		$existingBuggyawardList = $this->GetBuggyawardList();
		foreach ($existingBuggyawardList as $buggyaward)
		{
			$buggyaward->awardtypeId = '';
			$buggyaward->Save(false);
		}
		$this->_buggyawardList = $list;
	}
	
	
	/**
	* Associates the buggyAward object to this one
	* @return 
	*/
	function AddBuggyaward(&$buggyaward)
	{
		$buggyaward->awardtypeId = $this->awardtypeId;
		$found = false;
		foreach($this->_buggyawardList as $buggyaward2)
		{
			if ($buggyaward->buggyawardId > 0 && $buggyaward->buggyawardId == $buggyaward2->buggyawardId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_buggyawardList[] = $buggyaward;
		}
	}
}
?>