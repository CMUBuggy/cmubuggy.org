<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `raceday` (
	`racedayid` int(11) NOT NULL auto_increment,
	`date` DATE NOT NULL,
	`isfinals` TINYINT NOT NULL,
	`temperature` FLOAT NOT NULL,
	`weather` VARCHAR(255) NOT NULL,
	`raceyearid` int(11) NOT NULL, INDEX(`raceyearid`), PRIMARY KEY  (`racedayid`)) ENGINE=MyISAM;
*/

/**
* <b>raceday</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=raceday&attributeList=array+%28%0A++0+%3D%3E+%27date%27%2C%0A++1+%3D%3E+%27isFinals%27%2C%0A++2+%3D%3E+%27temperature%27%2C%0A++3+%3D%3E+%27weather%27%2C%0A++4+%3D%3E+%27raceyear%27%2C%0A++5+%3D%3E+%27team%27%2C%0A++6+%3D%3E+%27note%27%2C%0A++7+%3D%3E+%27heat%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527DATE%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527FLOAT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class raceday extends POG_Base
{
	public $racedayId = '';

	/**
	 * @var DATE
	 */
	public $date;
	
	/**
	 * @var TINYINT
	 */
	public $isFinals;
	
	/**
	 * @var FLOAT
	 */
	public $temperature;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $weather;
	
	/**
	 * @var INT(11)
	 */
	public $raceyearId;
	
	/**
	 * @var private array of team objects
	 */
	private $_teamList = array();
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	/**
	 * @var private array of heat objects
	 */
	private $_heatList = array();
	
	public $pog_attribute_type = array(
		"racedayId" => array('db_attributes' => array("NUMERIC", "INT")),
		"date" => array('db_attributes' => array("NUMERIC", "DATE")),
		"isFinals" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"temperature" => array('db_attributes' => array("NUMERIC", "FLOAT")),
		"weather" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"raceyear" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"team" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
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
	
	function raceday($date='', $isFinals='', $temperature='', $weather='')
	{
		$this->date = $date;
		$this->isFinals = $isFinals;
		$this->temperature = $temperature;
		$this->weather = $weather;
		$this->_teamList = array();
		$this->_noteList = array();
		$this->_heatList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $racedayId 
	* @return object $raceday
	*/
	function Get($racedayId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `raceday` where `racedayid`='".intval($racedayId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->racedayId = $row['racedayid'];
			$this->date = $row['date'];
			$this->isFinals = $this->Unescape($row['isfinals']);
			$this->temperature = $this->Unescape($row['temperature']);
			$this->weather = $this->Unescape($row['weather']);
			$this->raceyearId = $row['raceyearid'];
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $racedayList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `raceday` ";
		$racedayList = Array();
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
			$sortBy = "racedayid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$raceday = new $thisObjectName();
			$raceday->racedayId = $row['racedayid'];
			$raceday->date = $row['date'];
			$raceday->isFinals = $this->Unescape($row['isfinals']);
			$raceday->temperature = $this->Unescape($row['temperature']);
			$raceday->weather = $this->Unescape($row['weather']);
			$raceday->raceyearId = $row['raceyearid'];
			$racedayList[] = $raceday;
		}
		return $racedayList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $racedayId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `racedayid` from `raceday` where `racedayid`='".$this->racedayId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `raceday` set 
			`date`='".$this->date."', 
			`isfinals`='".$this->Escape($this->isFinals)."', 
			`temperature`='".$this->Escape($this->temperature)."', 
			`weather`='".$this->Escape($this->weather)."', 
			`raceyearid`='".$this->raceyearId."'where `racedayid`='".$this->racedayId."'";
		}
		else
		{
			$this->pog_query = "insert into `raceday` (`date`, `isfinals`, `temperature`, `weather`, `raceyearid`) values (
			'".$this->date."', 
			'".$this->Escape($this->isFinals)."', 
			'".$this->Escape($this->temperature)."', 
			'".$this->Escape($this->weather)."', 
			'".$this->raceyearId."')";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->racedayId == "")
		{
			$this->racedayId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_teamList as $team)
			{
				$team->racedayId = $this->racedayId;
				$team->Save($deep);
			}
			foreach ($this->_noteList as $note)
			{
				$note->racedayId = $this->racedayId;
				$note->Save($deep);
			}
			foreach ($this->_heatList as $heat)
			{
				$heat->racedayId = $this->racedayId;
				$heat->Save($deep);
			}
		}
		return $this->racedayId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $racedayId
	*/
	function SaveNew($deep = false)
	{
		$this->racedayId = '';
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
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
			$heatList = $this->GetHeatList();
			foreach ($heatList as $heat)
			{
				$heat->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `raceday` where `racedayid`='".$this->racedayId."'";
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
				$pog_query = "delete from `raceday` where ";
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
	* Associates the raceyear object to this one
	* @return boolean
	*/
	function GetRaceyear()
	{
		$raceyear = new raceyear();
		return $raceyear->Get($this->raceyearId);
	}
	
	
	/**
	* Associates the raceyear object to this one
	* @return 
	*/
	function SetRaceyear(&$raceyear)
	{
		$this->raceyearId = $raceyear->raceyearId;
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
		$fcv_array[] = array("racedayId", "=", $this->racedayId);
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
			$team->racedayId = '';
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
		$team->racedayId = $this->racedayId;
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
	* Gets a list of note objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of note objects
	*/
	function GetNoteList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$note = new note();
		$fcv_array[] = array("racedayId", "=", $this->racedayId);
		$dbObjects = $note->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all note objects in the note List array. Any existing note will become orphan(s)
	* @return null
	*/
	function SetNoteList(&$list)
	{
		$this->_noteList = array();
		$existingNoteList = $this->GetNoteList();
		foreach ($existingNoteList as $note)
		{
			$note->racedayId = '';
			$note->Save(false);
		}
		$this->_noteList = $list;
	}
	
	
	/**
	* Associates the note object to this one
	* @return 
	*/
	function AddNote(&$note)
	{
		$note->racedayId = $this->racedayId;
		$found = false;
		foreach($this->_noteList as $note2)
		{
			if ($note->noteId > 0 && $note->noteId == $note2->noteId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_noteList[] = $note;
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
		$fcv_array[] = array("racedayId", "=", $this->racedayId);
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
			$heat->racedayId = '';
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
		$heat->racedayId = $this->racedayId;
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