<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `raceclass` (
	`raceclassid` int(11) NOT NULL auto_increment,
	`description` VARCHAR(255) NOT NULL, PRIMARY KEY  (`raceclassid`)) ENGINE=MyISAM;
*/

/**
* <b>raceclass</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=raceclass&attributeList=array+%28%0A++0+%3D%3E+%27description%27%2C%0A++1+%3D%3E+%27team%27%2C%0A++2+%3D%3E+%27entry%27%2C%0A++3+%3D%3E+%27heat%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class raceclass extends POG_Base
{
	public $raceclassId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $description;
	
	/**
	 * @var private array of team objects
	 */
	private $_teamList = array();
	
	/**
	 * @var private array of entry objects
	 */
	private $_entryList = array();
	
	/**
	 * @var private array of heat objects
	 */
	private $_heatList = array();
	
	public $pog_attribute_type = array(
		"raceclassId" => array('db_attributes' => array("NUMERIC", "INT")),
		"description" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"team" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"entry" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"heat" => array('db_attributes' => array("OBJECT", "HASMANY")),
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
	
	function raceclass($description='')
	{
		$this->description = $description;
		$this->_teamList = array();
		$this->_entryList = array();
		$this->_heatList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $raceclassId 
	* @return object $raceclass
	*/
	function Get($raceclassId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `raceclass` where `raceclassid`='".intval($raceclassId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->raceclassId = $row['raceclassid'];
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
	* @return array $raceclassList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `raceclass` ";
		$raceclassList = Array();
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
			$sortBy = "raceclassid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$raceclass = new $thisObjectName();
			$raceclass->raceclassId = $row['raceclassid'];
			$raceclass->description = $this->Unescape($row['description']);
			$raceclassList[] = $raceclass;
		}
		return $raceclassList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $raceclassId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `raceclassid` from `raceclass` where `raceclassid`='".$this->raceclassId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `raceclass` set 
			`description`='".$this->Escape($this->description)."'where `raceclassid`='".$this->raceclassId."'";
		}
		else
		{
			$this->pog_query = "insert into `raceclass` (`description`) values (
			'".$this->Escape($this->description)."')";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->raceclassId == "")
		{
			$this->raceclassId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_teamList as $team)
			{
				$team->raceclassId = $this->raceclassId;
				$team->Save($deep);
			}
			foreach ($this->_entryList as $entry)
			{
				$entry->raceclassId = $this->raceclassId;
				$entry->Save($deep);
			}
			foreach ($this->_heatList as $heat)
			{
				$heat->raceclassId = $this->raceclassId;
				$heat->Save($deep);
			}
		}
		return $this->raceclassId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $raceclassId
	*/
	function SaveNew($deep = false)
	{
		$this->raceclassId = '';
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
			$teamList = $this->GetTeamList();
			foreach ($teamList as $team)
			{
				$team->Delete($deep, $across);
			}
			$entryList = $this->GetEntryList();
			foreach ($entryList as $entry)
			{
				$entry->Delete($deep, $across);
			}
			$heatList = $this->GetHeatList();
			foreach ($heatList as $heat)
			{
				$heat->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `raceclass` where `raceclassid`='".$this->raceclassId."'";
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
				$pog_query = "delete from `raceclass` where ";
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
	* Gets a list of team objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of team objects
	*/
	function GetTeamList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$team = new team();
		$fcv_array[] = array("raceclassId", "=", $this->raceclassId);
		$dbObjects = $team->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all team objects in the team List array. Any existing team will become orphan(s)
	* @return null
	*/
	function SetTeamList(&$list)
	{
		$this->_teamList = array();
		$existingTeamList = $this->GetTeamList();
		foreach ($existingTeamList as $team)
		{
			$team->raceclassId = '';
			$team->Save(false);
		}
		$this->_teamList = $list;
	}
	
	
	/**
	* Associates the team object to this one
	* @return 
	*/
	function AddTeam(&$team)
	{
		$team->raceclassId = $this->raceclassId;
		$found = false;
		foreach($this->_teamList as $team2)
		{
			if ($team->teamId > 0 && $team->teamId == $team2->teamId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_teamList[] = $team;
		}
	}
	
	
	/**
	* Gets a list of entry objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of entry objects
	*/
	function GetEntryList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$entry = new entry();
		$fcv_array[] = array("raceclassId", "=", $this->raceclassId);
		$dbObjects = $entry->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all entry objects in the entry List array. Any existing entry will become orphan(s)
	* @return null
	*/
	function SetEntryList(&$list)
	{
		$this->_entryList = array();
		$existingEntryList = $this->GetEntryList();
		foreach ($existingEntryList as $entry)
		{
			$entry->raceclassId = '';
			$entry->Save(false);
		}
		$this->_entryList = $list;
	}
	
	
	/**
	* Associates the entry object to this one
	* @return 
	*/
	function AddEntry(&$entry)
	{
		$entry->raceclassId = $this->raceclassId;
		$found = false;
		foreach($this->_entryList as $entry2)
		{
			if ($entry->entryId > 0 && $entry->entryId == $entry2->entryId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_entryList[] = $entry;
		}
	}
	
	
	/**
	* Gets a list of heat objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of heat objects
	*/
	function GetHeatList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$heat = new heat();
		$fcv_array[] = array("raceclassId", "=", $this->raceclassId);
		$dbObjects = $heat->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all heat objects in the heat List array. Any existing heat will become orphan(s)
	* @return null
	*/
	function SetHeatList(&$list)
	{
		$this->_heatList = array();
		$existingHeatList = $this->GetHeatList();
		foreach ($existingHeatList as $heat)
		{
			$heat->raceclassId = '';
			$heat->Save(false);
		}
		$this->_heatList = $list;
	}
	
	
	/**
	* Associates the heat object to this one
	* @return 
	*/
	function AddHeat(&$heat)
	{
		$heat->raceclassId = $this->raceclassId;
		$found = false;
		foreach($this->_heatList as $heat2)
		{
			if ($heat->heatId > 0 && $heat->heatId == $heat2->heatId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_heatList[] = $heat;
		}
	}
}
?>