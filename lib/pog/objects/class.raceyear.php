<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `raceyear` (
	`raceyearid` int(11) NOT NULL auto_increment,
	`year` YEAR NOT NULL, PRIMARY KEY  (`raceyearid`)) ENGINE=MyISAM;
*/

/**
* <b>raceyear</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=raceyear&attributeList=array+%28%0A++0+%3D%3E+%27year%27%2C%0A++1+%3D%3E+%27entry%27%2C%0A++2+%3D%3E+%27raceday%27%2C%0A++3+%3D%3E+%27note%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527YEAR%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class raceyear extends POG_Base
{
	public $raceyearId = '';

	/**
	 * @var YEAR
	 */
	public $year;
	
	/**
	 * @var private array of entry objects
	 */
	private $_entryList = array();
	
	/**
	 * @var private array of raceday objects
	 */
	private $_racedayList = array();
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	public $pog_attribute_type = array(
		"raceyearId" => array('db_attributes' => array("NUMERIC", "INT")),
		"year" => array('db_attributes' => array("NUMERIC", "YEAR")),
		"entry" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"raceday" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
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
	
	function raceyear($year='')
	{
		$this->year = $year;
		$this->_entryList = array();
		$this->_racedayList = array();
		$this->_noteList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $raceyearId 
	* @return object $raceyear
	*/
	function Get($raceyearId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `raceyear` where `raceyearid`='".intval($raceyearId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->raceyearId = $row['raceyearid'];
			$this->year = $this->Unescape($row['year']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $raceyearList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `raceyear` ";
		$raceyearList = Array();
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
			$sortBy = "raceyearid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$raceyear = new $thisObjectName();
			$raceyear->raceyearId = $row['raceyearid'];
			$raceyear->year = $this->Unescape($row['year']);
			$raceyearList[] = $raceyear;
		}
		return $raceyearList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $raceyearId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `raceyearid` from `raceyear` where `raceyearid`='".$this->raceyearId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `raceyear` set 
			`year`='".$this->Escape($this->year)."'where `raceyearid`='".$this->raceyearId."'";
		}
		else
		{
			$this->pog_query = "insert into `raceyear` (`year`) values (
			'".$this->Escape($this->year)."')";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->raceyearId == "")
		{
			$this->raceyearId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_entryList as $entry)
			{
				$entry->raceyearId = $this->raceyearId;
				$entry->Save($deep);
			}
			foreach ($this->_racedayList as $raceday)
			{
				$raceday->raceyearId = $this->raceyearId;
				$raceday->Save($deep);
			}
			foreach ($this->_noteList as $note)
			{
				$note->raceyearId = $this->raceyearId;
				$note->Save($deep);
			}
		}
		return $this->raceyearId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $raceyearId
	*/
	function SaveNew($deep = false)
	{
		$this->raceyearId = '';
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
			$entryList = $this->GetEntryList();
			foreach ($entryList as $entry)
			{
				$entry->Delete($deep, $across);
			}
			$racedayList = $this->GetRacedayList();
			foreach ($racedayList as $raceday)
			{
				$raceday->Delete($deep, $across);
			}
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `raceyear` where `raceyearid`='".$this->raceyearId."'";
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
				$pog_query = "delete from `raceyear` where ";
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
		$fcv_array[] = array("raceyearId", "=", $this->raceyearId);
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
			$entry->raceyearId = '';
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
		$entry->raceyearId = $this->raceyearId;
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
	* Gets a list of raceday objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of raceday objects
	*/
	function GetRacedayList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$raceday = new raceday();
		$fcv_array[] = array("raceyearId", "=", $this->raceyearId);
		$dbObjects = $raceday->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all raceday objects in the raceday List array. Any existing raceday will become orphan(s)
	* @return null
	*/
	function SetRacedayList(&$list)
	{
		$this->_racedayList = array();
		$existingRacedayList = $this->GetRacedayList();
		foreach ($existingRacedayList as $raceday)
		{
			$raceday->raceyearId = '';
			$raceday->Save(false);
		}
		$this->_racedayList = $list;
	}
	
	
	/**
	* Associates the raceday object to this one
	* @return 
	*/
	function AddRaceday(&$raceday)
	{
		$raceday->raceyearId = $this->raceyearId;
		$found = false;
		foreach($this->_racedayList as $raceday2)
		{
			if ($raceday->racedayId > 0 && $raceday->racedayId == $raceday2->racedayId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_racedayList[] = $raceday;
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
		$fcv_array[] = array("raceyearId", "=", $this->raceyearId);
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
			$note->raceyearId = '';
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
		$note->raceyearId = $this->raceyearId;
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