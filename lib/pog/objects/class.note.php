<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `note` (
	`noteid` int(11) NOT NULL auto_increment,
	`userid` int(11) NOT NULL,
	`text` TEXT NOT NULL,
	`buggyid` int(11) NOT NULL,
	`teamid` int(11) NOT NULL,
	`heatid` int(11) NOT NULL,
	`racedayid` int(11) NOT NULL,
	`raceyearid` int(11) NOT NULL,
	`videoid` int(11) NOT NULL, INDEX(`userid`,`buggyid`,`teamid`,`heatid`,`racedayid`,`raceyearid`,`videoid`), PRIMARY KEY  (`noteid`)) ENGINE=MyISAM;
*/

/**
* <b>note</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=note&attributeList=array+%28%0A++0+%3D%3E+%27user%27%2C%0A++1+%3D%3E+%27text%27%2C%0A++2+%3D%3E+%27buggy%27%2C%0A++3+%3D%3E+%27team%27%2C%0A++4+%3D%3E+%27heat%27%2C%0A++5+%3D%3E+%27raceday%27%2C%0A++6+%3D%3E+%27raceyear%27%2C%0A++7+%3D%3E+%27video%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527TEXT%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class note extends POG_Base
{
	public $noteId = '';

	/**
	 * @var INT(11)
	 */
	public $userId;
	
	/**
	 * @var TEXT
	 */
	public $text;
	
	/**
	 * @var INT(11)
	 */
	public $buggyId;
	
	/**
	 * @var INT(11)
	 */
	public $teamId;
	
	/**
	 * @var INT(11)
	 */
	public $heatId;
	
	/**
	 * @var INT(11)
	 */
	public $racedayId;
	
	/**
	 * @var INT(11)
	 */
	public $raceyearId;
	
	/**
	 * @var INT(11)
	 */
	public $videoId;
	
	public $pog_attribute_type = array(
		"noteId" => array('db_attributes' => array("NUMERIC", "INT")),
		"user" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"text" => array('db_attributes' => array("TEXT", "TEXT")),
		"buggy" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"team" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"heat" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"raceday" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"raceyear" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"video" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
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
	
	function note($text='')
	{
		$this->text = $text;
	}
	
	
	/**
	* Gets object from database
	* @param integer $noteId 
	* @return object $note
	*/
	function Get($noteId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `note` where `noteid`='".intval($noteId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->noteId = $row['noteid'];
			$this->userId = $row['userid'];
			$this->text = $this->Unescape($row['text']);
			$this->buggyId = $row['buggyid'];
			$this->teamId = $row['teamid'];
			$this->heatId = $row['heatid'];
			$this->racedayId = $row['racedayid'];
			$this->raceyearId = $row['raceyearid'];
			$this->videoId = $row['videoid'];
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $noteList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `note` ";
		$noteList = Array();
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
			$sortBy = "noteid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$note = new $thisObjectName();
			$note->noteId = $row['noteid'];
			$note->userId = $row['userid'];
			$note->text = $this->Unescape($row['text']);
			$note->buggyId = $row['buggyid'];
			$note->teamId = $row['teamid'];
			$note->heatId = $row['heatid'];
			$note->racedayId = $row['racedayid'];
			$note->raceyearId = $row['raceyearid'];
			$note->videoId = $row['videoid'];
			$noteList[] = $note;
		}
		return $noteList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $noteId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `noteid` from `note` where `noteid`='".$this->noteId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `note` set 
			`userid`='".$this->userId."', 
			`text`='".$this->Escape($this->text)."', 
			`buggyid`='".$this->buggyId."', 
			`teamid`='".$this->teamId."', 
			`heatid`='".$this->heatId."', 
			`racedayid`='".$this->racedayId."', 
			`raceyearid`='".$this->raceyearId."', 
			`videoid`='".$this->videoId."' where `noteid`='".$this->noteId."'";
		}
		else
		{
			$this->pog_query = "insert into `note` (`userid`, `text`, `buggyid`, `teamid`, `heatid`, `racedayid`, `raceyearid`, `videoid` ) values (
			'".$this->userId."', 
			'".$this->Escape($this->text)."', 
			'".$this->buggyId."', 
			'".$this->teamId."', 
			'".$this->heatId."', 
			'".$this->racedayId."', 
			'".$this->raceyearId."', 
			'".$this->videoId."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->noteId == "")
		{
			$this->noteId = $insertId;
		}
		return $this->noteId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $noteId
	*/
	function SaveNew()
	{
		$this->noteId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `note` where `noteid`='".$this->noteId."'";
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
			$pog_query = "delete from `note` where ";
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
	* Associates the user object to this one
	* @return boolean
	*/
	function GetUser()
	{
		$user = new user();
		return $user->Get($this->userId);
	}
	
	
	/**
	* Associates the user object to this one
	* @return 
	*/
	function SetUser(&$user)
	{
		$this->userId = $user->userId;
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
	* Associates the team object to this one
	* @return boolean
	*/
	function GetTeam()
	{
		$team = new team();
		return $team->Get($this->teamId);
	}
	
	
	/**
	* Associates the team object to this one
	* @return 
	*/
	function SetTeam(&$team)
	{
		$this->teamId = $team->teamId;
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
	* Associates the video object to this one
	* @return boolean
	*/
	function GetVideo()
	{
		$video = new video();
		return $video->Get($this->videoId);
	}
	
	
	/**
	* Associates the video object to this one
	* @return 
	*/
	function SetVideo(&$video)
	{
		$this->videoId = $video->videoId;
	}
}
?>