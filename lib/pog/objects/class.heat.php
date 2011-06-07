<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `heat` (
	`heatid` int(11) NOT NULL auto_increment,
	`number` SMALLINT NOT NULL,
	`racedayid` int(11) NOT NULL,
	`raceclassid` int(11) NOT NULL,
	`isreroll` TINYINT NOT NULL, INDEX(`racedayid`,`raceclassid`), PRIMARY KEY  (`heatid`)) ENGINE=MyISAM;
*/

/**
* <b>heat</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=heat&attributeList=array+%28%0A++0+%3D%3E+%27number%27%2C%0A++1+%3D%3E+%27raceday%27%2C%0A++2+%3D%3E+%27raceclass%27%2C%0A++3+%3D%3E+%27team%27%2C%0A++4+%3D%3E+%27video%27%2C%0A++5+%3D%3E+%27note%27%2C%0A++6+%3D%3E+%27isreroll%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class heat extends POG_Base
{
	public $heatId = '';

	/**
	 * @var SMALLINT
	 */
	public $number;
	
	/**
	 * @var INT(11)
	 */
	public $racedayId;
	
	/**
	 * @var INT(11)
	 */
	public $raceclassId;
	
	/**
	 * @var private array of team objects
	 */
	private $_teamList = array();
	
	/**
	 * @var private array of video objects
	 */
	private $_videoList = array();
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	/**
	 * @var TINYINT
	 */
	public $isreroll;
	
	public $pog_attribute_type = array(
		"heatId" => array('db_attributes' => array("NUMERIC", "INT")),
		"number" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"raceday" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"raceclass" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"team" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"video" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"isreroll" => array('db_attributes' => array("NUMERIC", "TINYINT")),
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
	
	function heat($number='', $isreroll='')
	{
		$this->number = $number;
		$this->_teamList = array();
		$this->_videoList = array();
		$this->_noteList = array();
		$this->isreroll = $isreroll;
	}
	
	
	/**
	* Gets object from database
	* @param integer $heatId 
	* @return object $heat
	*/
	function Get($heatId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `heat` where `heatid`='".intval($heatId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->heatId = $row['heatid'];
			$this->number = $this->Unescape($row['number']);
			$this->racedayId = $row['racedayid'];
			$this->raceclassId = $row['raceclassid'];
			$this->isreroll = $this->Unescape($row['isreroll']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $heatList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `heat` ";
		$heatList = Array();
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
			$sortBy = "heatid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$heat = new $thisObjectName();
			$heat->heatId = $row['heatid'];
			$heat->number = $this->Unescape($row['number']);
			$heat->racedayId = $row['racedayid'];
			$heat->raceclassId = $row['raceclassid'];
			$heat->isreroll = $this->Unescape($row['isreroll']);
			$heatList[] = $heat;
		}
		return $heatList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $heatId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `heatid` from `heat` where `heatid`='".$this->heatId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `heat` set 
			`number`='".$this->Escape($this->number)."', 
			`racedayid`='".$this->racedayId."', 
			`raceclassid`='".$this->raceclassId."', 
			`isreroll`='".$this->Escape($this->isreroll)."' where `heatid`='".$this->heatId."'";
		}
		else
		{
			$this->pog_query = "insert into `heat` (`number`, `racedayid`, `raceclassid`, `isreroll` ) values (
			'".$this->Escape($this->number)."', 
			'".$this->racedayId."', 
			'".$this->raceclassId."', 
			'".$this->Escape($this->isreroll)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->heatId == "")
		{
			$this->heatId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_teamList as $team)
			{
				$team->heatId = $this->heatId;
				$team->Save($deep);
			}
			foreach ($this->_videoList as $video)
			{
				$video->heatId = $this->heatId;
				$video->Save($deep);
			}
			foreach ($this->_noteList as $note)
			{
				$note->heatId = $this->heatId;
				$note->Save($deep);
			}
		}
		return $this->heatId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $heatId
	*/
	function SaveNew($deep = false)
	{
		$this->heatId = '';
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
			$videoList = $this->GetVideoList();
			foreach ($videoList as $video)
			{
				$video->Delete($deep, $across);
			}
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `heat` where `heatid`='".$this->heatId."'";
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
				$pog_query = "delete from `heat` where ";
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
		$fcv_array[] = array("heatId", "=", $this->heatId);
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
			$team->heatId = '';
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
		$team->heatId = $this->heatId;
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
	* Gets a list of video objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of video objects
	*/
	function GetVideoList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$video = new video();
		$fcv_array[] = array("heatId", "=", $this->heatId);
		$dbObjects = $video->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all video objects in the video List array. Any existing video will become orphan(s)
	* @return null
	*/
	function SetVideoList(&$list)
	{
		$this->_videoList = array();
		$existingVideoList = $this->GetVideoList();
		foreach ($existingVideoList as $video)
		{
			$video->heatId = '';
			$video->Save(false);
		}
		$this->_videoList = $list;
	}
	
	
	/**
	* Associates the video object to this one
	* @return 
	*/
	function AddVideo(&$video)
	{
		$video->heatId = $this->heatId;
		$found = false;
		foreach($this->_videoList as $video2)
		{
			if ($video->videoId > 0 && $video->videoId == $video2->videoId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_videoList[] = $video;
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
		$fcv_array[] = array("heatId", "=", $this->heatId);
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
			$note->heatId = '';
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
		$note->heatId = $this->heatId;
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
}
?>