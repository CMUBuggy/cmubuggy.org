<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `entry` (
	`entryid` int(11) NOT NULL auto_increment,
	`place` SMALLINT NOT NULL,
	`abcd` CHAR(255) NOT NULL,
	`compubookieplace` SMALLINT NOT NULL,
	`raceyearid` int(11) NOT NULL,
	`raceclassid` int(11) NOT NULL,
	`orgid` int(11) NOT NULL,
	`urlkey` VARCHAR(255) NOT NULL, INDEX(`raceyearid`,`raceclassid`,`orgid`), PRIMARY KEY  (`entryid`)) ENGINE=MyISAM;
*/

/**
* <b>entry</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=entry&attributeList=array+%28%0A++0+%3D%3E+%27place%27%2C%0A++1+%3D%3E+%27abcd%27%2C%0A++2+%3D%3E+%27compubookieplace%27%2C%0A++3+%3D%3E+%27raceyear%27%2C%0A++4+%3D%3E+%27raceclass%27%2C%0A++5+%3D%3E+%27team%27%2C%0A++6+%3D%3E+%27org%27%2C%0A++7+%3D%3E+%27urlkey%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527CHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class entry extends POG_Base
{
	public $entryId = '';

	/**
	 * @var SMALLINT
	 */
	public $place;
	
	/**
	 * @var CHAR(255)
	 */
	public $abcd;
	
	/**
	 * @var SMALLINT
	 */
	public $compubookieplace;
	
	/**
	 * @var INT(11)
	 */
	public $raceyearId;
	
	/**
	 * @var INT(11)
	 */
	public $raceclassId;
	
	/**
	 * @var private array of team objects
	 */
	private $_teamList = array();
	
	/**
	 * @var INT(11)
	 */
	public $orgId;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $urlkey;
	
	public $pog_attribute_type = array(
		"entryId" => array('db_attributes' => array("NUMERIC", "INT")),
		"place" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"abcd" => array('db_attributes' => array("TEXT", "CHAR", "255")),
		"compubookieplace" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"raceyear" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"raceclass" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"team" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"org" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"urlkey" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function entry($place='', $abcd='', $compubookieplace='', $urlkey='')
	{
		$this->place = $place;
		$this->abcd = $abcd;
		$this->compubookieplace = $compubookieplace;
		$this->_teamList = array();
		$this->urlkey = $urlkey;
	}
	
	
	/**
	* Gets object from database
	* @param integer $entryId 
	* @return object $entry
	*/
	function Get($entryId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `entry` where `entryid`='".intval($entryId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->entryId = $row['entryid'];
			$this->place = $this->Unescape($row['place']);
			$this->abcd = $this->Unescape($row['abcd']);
			$this->compubookieplace = $this->Unescape($row['compubookieplace']);
			$this->raceyearId = $row['raceyearid'];
			$this->raceclassId = $row['raceclassid'];
			$this->orgId = $row['orgid'];
			$this->urlkey = $this->Unescape($row['urlkey']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $entryList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `entry` ";
		$entryList = Array();
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
			$sortBy = "entryid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$entry = new $thisObjectName();
			$entry->entryId = $row['entryid'];
			$entry->place = $this->Unescape($row['place']);
			$entry->abcd = $this->Unescape($row['abcd']);
			$entry->compubookieplace = $this->Unescape($row['compubookieplace']);
			$entry->raceyearId = $row['raceyearid'];
			$entry->raceclassId = $row['raceclassid'];
			$entry->orgId = $row['orgid'];
			$entry->urlkey = $this->Unescape($row['urlkey']);
			$entryList[] = $entry;
		}
		return $entryList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $entryId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `entryid` from `entry` where `entryid`='".$this->entryId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `entry` set 
			`place`='".$this->Escape($this->place)."', 
			`abcd`='".$this->Escape($this->abcd)."', 
			`compubookieplace`='".$this->Escape($this->compubookieplace)."', 
			`raceyearid`='".$this->raceyearId."', 
			`raceclassid`='".$this->raceclassId."', 
			`orgid`='".$this->orgId."', 
			`urlkey`='".$this->Escape($this->urlkey)."' where `entryid`='".$this->entryId."'";
		}
		else
		{
			$this->pog_query = "insert into `entry` (`place`, `abcd`, `compubookieplace`, `raceyearid`, `raceclassid`, `orgid`, `urlkey` ) values (
			'".$this->Escape($this->place)."', 
			'".$this->Escape($this->abcd)."', 
			'".$this->Escape($this->compubookieplace)."', 
			'".$this->raceyearId."', 
			'".$this->raceclassId."', 
			'".$this->orgId."', 
			'".$this->Escape($this->urlkey)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->entryId == "")
		{
			$this->entryId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_teamList as $team)
			{
				$team->entryId = $this->entryId;
				$team->Save($deep);
			}
		}
		return $this->entryId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $entryId
	*/
	function SaveNew($deep = false)
	{
		$this->entryId = '';
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
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `entry` where `entryid`='".$this->entryId."'";
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
				$pog_query = "delete from `entry` where ";
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
		$fcv_array[] = array("entryId", "=", $this->entryId);
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
			$team->entryId = '';
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
		$team->entryId = $this->entryId;
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