<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `persontoteam` (
	`persontoteamid` int(11) NOT NULL auto_increment,
	`teamid` int(11) NOT NULL,
	`personid` int(11) NOT NULL,
	`teamroleid` int(11) NOT NULL,
	`void` VARCHAR(255) NOT NULL, INDEX(`teamid`,`personid`,`teamroleid`), PRIMARY KEY  (`persontoteamid`)) ENGINE=MyISAM;
*/

/**
* <b>personToTeam</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=personToTeam&attributeList=array+%28%0A++0+%3D%3E+%27team%27%2C%0A++1+%3D%3E+%27person%27%2C%0A++2+%3D%3E+%27teamRole%27%2C%0A++3+%3D%3E+%27void%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class personToTeam extends POG_Base
{
	public $persontoteamId = '';

	/**
	 * @var INT(11)
	 */
	public $teamId;
	
	/**
	 * @var INT(11)
	 */
	public $personId;
	
	/**
	 * @var INT(11)
	 */
	public $teamroleId;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $void;
	
	public $pog_attribute_type = array(
		"persontoteamId" => array('db_attributes' => array("NUMERIC", "INT")),
		"team" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"person" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"teamRole" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"void" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function personToTeam($void='')
	{
		$this->void = $void;
	}
	
	
	/**
	* Gets object from database
	* @param integer $persontoteamId 
	* @return object $personToTeam
	*/
	function Get($persontoteamId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `persontoteam` where `persontoteamid`='".intval($persontoteamId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->persontoteamId = $row['persontoteamid'];
			$this->teamId = $row['teamid'];
			$this->personId = $row['personid'];
			$this->teamroleId = $row['teamroleid'];
			$this->void = $this->Unescape($row['void']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $persontoteamList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `persontoteam` ";
		$persontoteamList = Array();
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
			$sortBy = "persontoteamid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$persontoteam = new $thisObjectName();
			$persontoteam->persontoteamId = $row['persontoteamid'];
			$persontoteam->teamId = $row['teamid'];
			$persontoteam->personId = $row['personid'];
			$persontoteam->teamroleId = $row['teamroleid'];
			$persontoteam->void = $this->Unescape($row['void']);
			$persontoteamList[] = $persontoteam;
		}
		return $persontoteamList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $persontoteamId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `persontoteamid` from `persontoteam` where `persontoteamid`='".$this->persontoteamId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `persontoteam` set 
			`teamid`='".$this->teamId."', 
			`personid`='".$this->personId."', 
			`teamroleid`='".$this->teamroleId."', 
			`void`='".$this->Escape($this->void)."' where `persontoteamid`='".$this->persontoteamId."'";
		}
		else
		{
			$this->pog_query = "insert into `persontoteam` (`teamid`, `personid`, `teamroleid`, `void` ) values (
			'".$this->teamId."', 
			'".$this->personId."', 
			'".$this->teamroleId."', 
			'".$this->Escape($this->void)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->persontoteamId == "")
		{
			$this->persontoteamId = $insertId;
		}
		return $this->persontoteamId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $persontoteamId
	*/
	function SaveNew()
	{
		$this->persontoteamId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `persontoteam` where `persontoteamid`='".$this->persontoteamId."'";
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
			$pog_query = "delete from `persontoteam` where ";
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
	* Associates the teamRole object to this one
	* @return boolean
	*/
	function GetTeamrole()
	{
		$teamrole = new teamRole();
		return $teamrole->Get($this->teamroleId);
	}
	
	
	/**
	* Associates the teamRole object to this one
	* @return 
	*/
	function SetTeamrole(&$teamrole)
	{
		$this->teamroleId = $teamrole->teamroleId;
	}
}
?>