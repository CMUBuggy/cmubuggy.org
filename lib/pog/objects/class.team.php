<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `team` (
	`teamid` int(11) NOT NULL auto_increment,
	`buggyid` int(11) NOT NULL,
	`lane` TINYINT NOT NULL,
	`heatid` int(11) NOT NULL,
	`raceclassid` int(11) NOT NULL,
	`isreroll` TINYINT NOT NULL,
	`time` FLOAT NOT NULL,
	`entryid` int(11) NOT NULL,
	`racedayid` int(11) NOT NULL,
	`dqid` int(11) NOT NULL,
	`urlkey` TINYTEXT NOT NULL,
	`broadcastnote` TEXT NOT NULL, INDEX(`buggyid`,`heatid`,`raceclassid`,`entryid`,`racedayid`,`dqid`), PRIMARY KEY  (`teamid`)) ENGINE=MyISAM;
*/

/**
* <b>team</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5&wrapper=pog&objectName=team&attributeList=array+%28%0A++0+%3D%3E+%27buggy%27%2C%0A++1+%3D%3E+%27lane%27%2C%0A++2+%3D%3E+%27heat%27%2C%0A++3+%3D%3E+%27raceclass%27%2C%0A++4+%3D%3E+%27isReroll%27%2C%0A++5+%3D%3E+%27time%27%2C%0A++6+%3D%3E+%27entry%27%2C%0A++7+%3D%3E+%27note%27%2C%0A++8+%3D%3E+%27raceday%27%2C%0A++9+%3D%3E+%27personToTeam%27%2C%0A++10+%3D%3E+%27dq%27%2C%0A++11+%3D%3E+%27urlKey%27%2C%0A++12+%3D%3E+%27broadcastnote%27%2C%0A%29&typeList=array+%28%0A++0+%3D%3E+%27BELONGSTO%27%2C%0A++1+%3D%3E+%27TINYINT%27%2C%0A++2+%3D%3E+%27BELONGSTO%27%2C%0A++3+%3D%3E+%27BELONGSTO%27%2C%0A++4+%3D%3E+%27TINYINT%27%2C%0A++5+%3D%3E+%27FLOAT%27%2C%0A++6+%3D%3E+%27BELONGSTO%27%2C%0A++7+%3D%3E+%27HASMANY%27%2C%0A++8+%3D%3E+%27BELONGSTO%27%2C%0A++9+%3D%3E+%27HASMANY%27%2C%0A++10+%3D%3E+%27BELONGSTO%27%2C%0A++11+%3D%3E+%27TINYTEXT%27%2C%0A++12+%3D%3E+%27TEXT%27%2C%0A%29
*/
include_once('class.pog_base.php');
class team extends POG_Base
{
	public $teamId = '';

	/**
	 * @var INT(11)
	 */
	public $buggyId;
	
	/**
	 * @var TINYINT
	 */
	public $lane;
	
	/**
	 * @var INT(11)
	 */
	public $heatId;
	
	/**
	 * @var INT(11)
	 */
	public $raceclassId;
	
	/**
	 * @var TINYINT
	 */
	public $isReroll;
	
	/**
	 * @var FLOAT
	 */
	public $time;
	
	/**
	 * @var INT(11)
	 */
	public $entryId;
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	/**
	 * @var INT(11)
	 */
	public $racedayId;
	
	/**
	 * @var private array of personToTeam objects
	 */
	private $_persontoteamList = array();
	
	/**
	 * @var INT(11)
	 */
	public $dqId;
	
	/**
	 * @var TINYTEXT
	 */
	public $urlKey;
	
	/**
	 * @var TEXT
	 */
	public $broadcastnote;
	
	public $pog_attribute_type = array(
		"teamId" => array('db_attributes' => array("NUMERIC", "INT")),
		"buggy" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"lane" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"heat" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"raceclass" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"isReroll" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"time" => array('db_attributes' => array("NUMERIC", "FLOAT")),
		"entry" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"raceday" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"personToTeam" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"dq" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"urlKey" => array('db_attributes' => array("TEXT", "TINYTEXT")),
		"broadcastnote" => array('db_attributes' => array("TEXT", "TEXT")),
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
	
	function team($lane='', $isReroll='', $time='', $urlKey='', $broadcastnote='')
	{
		$this->lane = $lane;
		$this->isReroll = $isReroll;
		$this->time = $time;
		$this->_noteList = array();
		$this->_persontoteamList = array();
		$this->urlKey = $urlKey;
		$this->broadcastnote = $broadcastnote;
	}
	
	
	/**
	* Gets object from database
	* @param integer $teamId 
	* @return object $team
	*/
	function Get($teamId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `team` where `teamid`='".intval($teamId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->teamId = $row['teamid'];
			$this->buggyId = $row['buggyid'];
			$this->lane = $this->Unescape($row['lane']);
			$this->heatId = $row['heatid'];
			$this->raceclassId = $row['raceclassid'];
			$this->isReroll = $this->Unescape($row['isreroll']);
			$this->time = $this->Unescape($row['time']);
			$this->entryId = $row['entryid'];
			$this->racedayId = $row['racedayid'];
			$this->dqId = $row['dqid'];
			$this->urlKey = $this->Unescape($row['urlkey']);
			$this->broadcastnote = $this->Unescape($row['broadcastnote']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $teamList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `team` ";
		$teamList = Array();
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
			$sortBy = "teamid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$team = new $thisObjectName();
			$team->teamId = $row['teamid'];
			$team->buggyId = $row['buggyid'];
			$team->lane = $this->Unescape($row['lane']);
			$team->heatId = $row['heatid'];
			$team->raceclassId = $row['raceclassid'];
			$team->isReroll = $this->Unescape($row['isreroll']);
			$team->time = $this->Unescape($row['time']);
			$team->entryId = $row['entryid'];
			$team->racedayId = $row['racedayid'];
			$team->dqId = $row['dqid'];
			$team->urlKey = $this->Unescape($row['urlkey']);
			$team->broadcastnote = $this->Unescape($row['broadcastnote']);
			$teamList[] = $team;
		}
		return $teamList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $teamId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `teamid` from `team` where `teamid`='".$this->teamId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `team` set 
			`buggyid`='".$this->buggyId."', 
			`lane`='".$this->Escape($this->lane)."', 
			`heatid`='".$this->heatId."', 
			`raceclassid`='".$this->raceclassId."', 
			`isreroll`='".$this->Escape($this->isReroll)."', 
			`time`='".$this->Escape($this->time)."', 
			`entryid`='".$this->entryId."', 
			`racedayid`='".$this->racedayId."', 
			`dqid`='".$this->dqId."', 
			`urlkey`='".$this->Escape($this->urlKey)."', 
			`broadcastnote`='".$this->Escape($this->broadcastnote)."' where `teamid`='".$this->teamId."'";
		}
		else
		{
			$this->pog_query = "insert into `team` (`buggyid`, `lane`, `heatid`, `raceclassid`, `isreroll`, `time`, `entryid`, `racedayid`, `dqid`, `urlkey`, `broadcastnote` ) values (
			'".$this->buggyId."', 
			'".$this->Escape($this->lane)."', 
			'".$this->heatId."', 
			'".$this->raceclassId."', 
			'".$this->Escape($this->isReroll)."', 
			'".$this->Escape($this->time)."', 
			'".$this->entryId."', 
			'".$this->racedayId."', 
			'".$this->dqId."', 
			'".$this->Escape($this->urlKey)."', 
			'".$this->Escape($this->broadcastnote)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->teamId == "")
		{
			$this->teamId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_noteList as $note)
			{
				$note->teamId = $this->teamId;
				$note->Save($deep);
			}
			foreach ($this->_persontoteamList as $persontoteam)
			{
				$persontoteam->teamId = $this->teamId;
				$persontoteam->Save($deep);
			}
		}
		return $this->teamId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $teamId
	*/
	function SaveNew($deep = false)
	{
		$this->teamId = '';
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
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
			$persontoteamList = $this->GetPersontoteamList();
			foreach ($persontoteamList as $persontoteam)
			{
				$persontoteam->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `team` where `teamid`='".$this->teamId."'";
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
				$pog_query = "delete from `team` where ";
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
	
	
	/**
	* Associates the heat object to this one
	* @return boolean
	*/
	function GetHeat()
	{
		$heat = new heat();
		return $heat->Get($this->heatId);
	}
	
	
	/**
	* Associates the heat object to this one
	* @return 
	*/
	function SetHeat(&$heat)
	{
		$this->heatId = $heat->heatId;
	}
	
	
	/**
	* Associates the raceclass object to this one
	* @return boolean
	*/
	function GetRaceclass()
	{
		$raceclass = new raceclass();
		return $raceclass->Get($this->raceclassId);
	}
	
	
	/**
	* Associates the raceclass object to this one
	* @return 
	*/
	function SetRaceclass(&$raceclass)
	{
		$this->raceclassId = $raceclass->raceclassId;
	}
	
	
	/**
	* Associates the entry object to this one
	* @return boolean
	*/
	function GetEntry()
	{
		$entry = new entry();
		return $entry->Get($this->entryId);
	}
	
	
	/**
	* Associates the entry object to this one
	* @return 
	*/
	function SetEntry(&$entry)
	{
		$this->entryId = $entry->entryId;
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
		$fcv_array[] = array("teamId", "=", $this->teamId);
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
			$note->teamId = '';
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
		$note->teamId = $this->teamId;
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
	* Associates the raceday object to this one
	* @return boolean
	*/
	function GetRaceday()
	{
		$raceday = new raceday();
		return $raceday->Get($this->racedayId);
	}
	
	
	/**
	* Associates the raceday object to this one
	* @return 
	*/
	function SetRaceday(&$raceday)
	{
		$this->racedayId = $raceday->racedayId;
	}
	
	
	/**
	* Gets a list of personToTeam objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of personToTeam objects
	*/
	function GetPersontoteamList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$persontoteam = new personToTeam();
		$fcv_array[] = array("teamId", "=", $this->teamId);
		$dbObjects = $persontoteam->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all personToTeam objects in the personToTeam List array. Any existing personToTeam will become orphan(s)
	* @return null
	*/
	function SetPersontoteamList(&$list)
	{
		$this->_persontoteamList = array();
		$existingPersontoteamList = $this->GetPersontoteamList();
		foreach ($existingPersontoteamList as $persontoteam)
		{
			$persontoteam->teamId = '';
			$persontoteam->Save(false);
		}
		$this->_persontoteamList = $list;
	}
	
	
	/**
	* Associates the personToTeam object to this one
	* @return 
	*/
	function AddPersontoteam(&$persontoteam)
	{
		$persontoteam->teamId = $this->teamId;
		$found = false;
		foreach($this->_persontoteamList as $persontoteam2)
		{
			if ($persontoteam->persontoteamId > 0 && $persontoteam->persontoteamId == $persontoteam2->persontoteamId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_persontoteamList[] = $persontoteam;
		}
	}
	
	
	/**
	* Associates the dq object to this one
	* @return boolean
	*/
	function GetDq()
	{
		$dq = new dq();
		return $dq->Get($this->dqId);
	}
	
	
	/**
	* Associates the dq object to this one
	* @return 
	*/
	function SetDq(&$dq)
	{
		$this->dqId = $dq->dqId;
	}
}
?>