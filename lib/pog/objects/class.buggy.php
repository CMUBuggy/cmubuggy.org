<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `buggy` (
	`buggyid` int(11) NOT NULL auto_increment,
	`yearbuilt` SMALLINT NOT NULL,
	`name` VARCHAR(255) NOT NULL,
	`orgid` int(11) NOT NULL,
	`urlkey` TINYTEXT NOT NULL, INDEX(`orgid`), PRIMARY KEY  (`buggyid`)) ENGINE=MyISAM;
*/

/**
* <b>buggy</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=buggy&attributeList=array+%28%0A++0+%3D%3E+%27yearBuilt%27%2C%0A++1+%3D%3E+%27name%27%2C%0A++2+%3D%3E+%27org%27%2C%0A++3+%3D%3E+%27team%27%2C%0A++4+%3D%3E+%27buggyToPerson%27%2C%0A++5+%3D%3E+%27buggyAward%27%2C%0A++6+%3D%3E+%27note%27%2C%0A++7+%3D%3E+%27urlKey%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527TINYTEXT%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class buggy extends POG_Base
{
	public $buggyId = '';

	/**
	 * @var SMALLINT
	 */
	public $yearBuilt;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $name;
	
	/**
	 * @var INT(11)
	 */
	public $orgId;
	
	/**
	 * @var private array of team objects
	 */
	private $_teamList = array();
	
	/**
	 * @var private array of buggyToPerson objects
	 */
	private $_buggytopersonList = array();
	
	/**
	 * @var private array of buggyAward objects
	 */
	private $_buggyawardList = array();
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	/**
	 * @var TINYTEXT
	 */
	public $urlKey;
	
	public $pog_attribute_type = array(
		"buggyId" => array('db_attributes' => array("NUMERIC", "INT")),
		"yearBuilt" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"name" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"org" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"team" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"buggyToPerson" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"buggyAward" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"urlKey" => array('db_attributes' => array("TEXT", "TINYTEXT")),
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
	
	function buggy($yearBuilt='', $name='', $urlKey='')
	{
		$this->yearBuilt = $yearBuilt;
		$this->name = $name;
		$this->_teamList = array();
		$this->_buggytopersonList = array();
		$this->_buggyawardList = array();
		$this->_noteList = array();
		$this->urlKey = $urlKey;
	}
	
	
	/**
	* Gets object from database
	* @param integer $buggyId 
	* @return object $buggy
	*/
	function Get($buggyId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `buggy` where `buggyid`='".intval($buggyId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->buggyId = $row['buggyid'];
			$this->yearBuilt = $this->Unescape($row['yearbuilt']);
			$this->name = $this->Unescape($row['name']);
			$this->orgId = $row['orgid'];
			$this->urlKey = $this->Unescape($row['urlkey']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $buggyList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `buggy` ";
		$buggyList = Array();
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
			$sortBy = "buggyid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$buggy = new $thisObjectName();
			$buggy->buggyId = $row['buggyid'];
			$buggy->yearBuilt = $this->Unescape($row['yearbuilt']);
			$buggy->name = $this->Unescape($row['name']);
			$buggy->orgId = $row['orgid'];
			$buggy->urlKey = $this->Unescape($row['urlkey']);
			$buggyList[] = $buggy;
		}
		return $buggyList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $buggyId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `buggyid` from `buggy` where `buggyid`='".$this->buggyId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `buggy` set 
			`yearbuilt`='".$this->Escape($this->yearBuilt)."', 
			`name`='".$this->Escape($this->name)."', 
			`orgid`='".$this->orgId."', 
			`urlkey`='".$this->Escape($this->urlKey)."' where `buggyid`='".$this->buggyId."'";
		}
		else
		{
			$this->pog_query = "insert into `buggy` (`yearbuilt`, `name`, `orgid`, `urlkey` ) values (
			'".$this->Escape($this->yearBuilt)."', 
			'".$this->Escape($this->name)."', 
			'".$this->orgId."', 
			'".$this->Escape($this->urlKey)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->buggyId == "")
		{
			$this->buggyId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_teamList as $team)
			{
				$team->buggyId = $this->buggyId;
				$team->Save($deep);
			}
			foreach ($this->_buggytopersonList as $buggytoperson)
			{
				$buggytoperson->buggyId = $this->buggyId;
				$buggytoperson->Save($deep);
			}
			foreach ($this->_buggyawardList as $buggyaward)
			{
				$buggyaward->buggyId = $this->buggyId;
				$buggyaward->Save($deep);
			}
			foreach ($this->_noteList as $note)
			{
				$note->buggyId = $this->buggyId;
				$note->Save($deep);
			}
		}
		return $this->buggyId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $buggyId
	*/
	function SaveNew($deep = false)
	{
		$this->buggyId = '';
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
			$buggytopersonList = $this->GetBuggytopersonList();
			foreach ($buggytopersonList as $buggytoperson)
			{
				$buggytoperson->Delete($deep, $across);
			}
			$buggyawardList = $this->GetBuggyawardList();
			foreach ($buggyawardList as $buggyaward)
			{
				$buggyaward->Delete($deep, $across);
			}
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `buggy` where `buggyid`='".$this->buggyId."'";
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
				$pog_query = "delete from `buggy` where ";
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
		$fcv_array[] = array("buggyId", "=", $this->buggyId);
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
			$team->buggyId = '';
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
		$team->buggyId = $this->buggyId;
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
	* Gets a list of buggyToPerson objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of buggyToPerson objects
	*/
	function GetBuggytopersonList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$buggytoperson = new buggyToPerson();
		$fcv_array[] = array("buggyId", "=", $this->buggyId);
		$dbObjects = $buggytoperson->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all buggyToPerson objects in the buggyToPerson List array. Any existing buggyToPerson will become orphan(s)
	* @return null
	*/
	function SetBuggytopersonList(&$list)
	{
		$this->_buggytopersonList = array();
		$existingBuggytopersonList = $this->GetBuggytopersonList();
		foreach ($existingBuggytopersonList as $buggytoperson)
		{
			$buggytoperson->buggyId = '';
			$buggytoperson->Save(false);
		}
		$this->_buggytopersonList = $list;
	}
	
	
	/**
	* Associates the buggyToPerson object to this one
	* @return 
	*/
	function AddBuggytoperson(&$buggytoperson)
	{
		$buggytoperson->buggyId = $this->buggyId;
		$found = false;
		foreach($this->_buggytopersonList as $buggytoperson2)
		{
			if ($buggytoperson->buggytopersonId > 0 && $buggytoperson->buggytopersonId == $buggytoperson2->buggytopersonId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_buggytopersonList[] = $buggytoperson;
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
		$fcv_array[] = array("buggyId", "=", $this->buggyId);
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
			$buggyaward->buggyId = '';
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
		$buggyaward->buggyId = $this->buggyId;
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
		$fcv_array[] = array("buggyId", "=", $this->buggyId);
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
			$note->buggyId = '';
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
		$note->buggyId = $this->buggyId;
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