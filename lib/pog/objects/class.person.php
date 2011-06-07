<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `person` (
	`personid` int(11) NOT NULL auto_increment,
	`firstname` VARCHAR(255) NOT NULL,
	`lastname` VARCHAR(255) NOT NULL,
	`gradyear` SMALLINT NOT NULL,
	`email` VARCHAR(255) NOT NULL,
	`gender` TINYINT NOT NULL,
	`userid` int(11) NOT NULL, INDEX(`userid`), PRIMARY KEY  (`personid`)) ENGINE=MyISAM;
*/

/**
* <b>person</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=person&attributeList=array+%28%0A++0+%3D%3E+%27firstName%27%2C%0A++1+%3D%3E+%27lastName%27%2C%0A++2+%3D%3E+%27gradYear%27%2C%0A++3+%3D%3E+%27email%27%2C%0A++4+%3D%3E+%27gender%27%2C%0A++5+%3D%3E+%27personToOrg%27%2C%0A++6+%3D%3E+%27personToTeam%27%2C%0A++7+%3D%3E+%27buggyToPerson%27%2C%0A++8+%3D%3E+%27sweepstakes%27%2C%0A++9+%3D%3E+%27user%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B8%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B9%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class person extends POG_Base
{
	public $personId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $firstName;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $lastName;
	
	/**
	 * @var SMALLINT
	 */
	public $gradYear;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $email;
	
	/**
	 * @var TINYINT
	 */
	public $gender;
	
	/**
	 * @var private array of personToOrg objects
	 */
	private $_persontoorgList = array();
	
	/**
	 * @var private array of personToTeam objects
	 */
	private $_persontoteamList = array();
	
	/**
	 * @var private array of buggyToPerson objects
	 */
	private $_buggytopersonList = array();
	
	/**
	 * @var private array of sweepstakes objects
	 */
	private $_sweepstakesList = array();
	
	/**
	 * @var INT(11)
	 */
	public $userId;
	
	public $pog_attribute_type = array(
		"personId" => array('db_attributes' => array("NUMERIC", "INT")),
		"firstName" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"lastName" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"gradYear" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"email" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"gender" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"personToOrg" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"personToTeam" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"buggyToPerson" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"sweepstakes" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"user" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
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
	
	function person($firstName='', $lastName='', $gradYear='', $email='', $gender='')
	{
		$this->firstName = $firstName;
		$this->lastName = $lastName;
		$this->gradYear = $gradYear;
		$this->email = $email;
		$this->gender = $gender;
		$this->_persontoorgList = array();
		$this->_persontoteamList = array();
		$this->_buggytopersonList = array();
		$this->_sweepstakesList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $personId 
	* @return object $person
	*/
	function Get($personId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `person` where `personid`='".intval($personId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->personId = $row['personid'];
			$this->firstName = $this->Unescape($row['firstname']);
			$this->lastName = $this->Unescape($row['lastname']);
			$this->gradYear = $this->Unescape($row['gradyear']);
			$this->email = $this->Unescape($row['email']);
			$this->gender = $this->Unescape($row['gender']);
			$this->userId = $row['userid'];
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $personList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `person` ";
		$personList = Array();
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
			$sortBy = "personid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$person = new $thisObjectName();
			$person->personId = $row['personid'];
			$person->firstName = $this->Unescape($row['firstname']);
			$person->lastName = $this->Unescape($row['lastname']);
			$person->gradYear = $this->Unescape($row['gradyear']);
			$person->email = $this->Unescape($row['email']);
			$person->gender = $this->Unescape($row['gender']);
			$person->userId = $row['userid'];
			$personList[] = $person;
		}
		return $personList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $personId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `personid` from `person` where `personid`='".$this->personId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `person` set 
			`firstname`='".$this->Escape($this->firstName)."', 
			`lastname`='".$this->Escape($this->lastName)."', 
			`gradyear`='".$this->Escape($this->gradYear)."', 
			`email`='".$this->Escape($this->email)."', 
			`gender`='".$this->Escape($this->gender)."', 
			`userid`='".$this->userId."' where `personid`='".$this->personId."'";
		}
		else
		{
			$this->pog_query = "insert into `person` (`firstname`, `lastname`, `gradyear`, `email`, `gender`, `userid` ) values (
			'".$this->Escape($this->firstName)."', 
			'".$this->Escape($this->lastName)."', 
			'".$this->Escape($this->gradYear)."', 
			'".$this->Escape($this->email)."', 
			'".$this->Escape($this->gender)."', 
			'".$this->userId."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->personId == "")
		{
			$this->personId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_persontoorgList as $persontoorg)
			{
				$persontoorg->personId = $this->personId;
				$persontoorg->Save($deep);
			}
			foreach ($this->_persontoteamList as $persontoteam)
			{
				$persontoteam->personId = $this->personId;
				$persontoteam->Save($deep);
			}
			foreach ($this->_buggytopersonList as $buggytoperson)
			{
				$buggytoperson->personId = $this->personId;
				$buggytoperson->Save($deep);
			}
			foreach ($this->_sweepstakesList as $sweepstakes)
			{
				$sweepstakes->personId = $this->personId;
				$sweepstakes->Save($deep);
			}
		}
		return $this->personId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $personId
	*/
	function SaveNew($deep = false)
	{
		$this->personId = '';
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
			$persontoorgList = $this->GetPersontoorgList();
			foreach ($persontoorgList as $persontoorg)
			{
				$persontoorg->Delete($deep, $across);
			}
			$persontoteamList = $this->GetPersontoteamList();
			foreach ($persontoteamList as $persontoteam)
			{
				$persontoteam->Delete($deep, $across);
			}
			$buggytopersonList = $this->GetBuggytopersonList();
			foreach ($buggytopersonList as $buggytoperson)
			{
				$buggytoperson->Delete($deep, $across);
			}
			$sweepstakesList = $this->GetSweepstakesList();
			foreach ($sweepstakesList as $sweepstakes)
			{
				$sweepstakes->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `person` where `personid`='".$this->personId."'";
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
				$pog_query = "delete from `person` where ";
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
	* Gets a list of personToOrg objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of personToOrg objects
	*/
	function GetPersontoorgList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$persontoorg = new personToOrg();
		$fcv_array[] = array("personId", "=", $this->personId);
		$dbObjects = $persontoorg->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all personToOrg objects in the personToOrg List array. Any existing personToOrg will become orphan(s)
	* @return null
	*/
	function SetPersontoorgList(&$list)
	{
		$this->_persontoorgList = array();
		$existingPersontoorgList = $this->GetPersontoorgList();
		foreach ($existingPersontoorgList as $persontoorg)
		{
			$persontoorg->personId = '';
			$persontoorg->Save(false);
		}
		$this->_persontoorgList = $list;
	}
	
	
	/**
	* Associates the personToOrg object to this one
	* @return 
	*/
	function AddPersontoorg(&$persontoorg)
	{
		$persontoorg->personId = $this->personId;
		$found = false;
		foreach($this->_persontoorgList as $persontoorg2)
		{
			if ($persontoorg->persontoorgId > 0 && $persontoorg->persontoorgId == $persontoorg2->persontoorgId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_persontoorgList[] = $persontoorg;
		}
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
		$fcv_array[] = array("personId", "=", $this->personId);
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
			$persontoteam->personId = '';
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
		$persontoteam->personId = $this->personId;
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
		$fcv_array[] = array("personId", "=", $this->personId);
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
			$buggytoperson->personId = '';
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
		$buggytoperson->personId = $this->personId;
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
	* Gets a list of sweepstakes objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of sweepstakes objects
	*/
	function GetSweepstakesList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$sweepstakes = new sweepstakes();
		$fcv_array[] = array("personId", "=", $this->personId);
		$dbObjects = $sweepstakes->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all sweepstakes objects in the sweepstakes List array. Any existing sweepstakes will become orphan(s)
	* @return null
	*/
	function SetSweepstakesList(&$list)
	{
		$this->_sweepstakesList = array();
		$existingSweepstakesList = $this->GetSweepstakesList();
		foreach ($existingSweepstakesList as $sweepstakes)
		{
			$sweepstakes->personId = '';
			$sweepstakes->Save(false);
		}
		$this->_sweepstakesList = $list;
	}
	
	
	/**
	* Associates the sweepstakes object to this one
	* @return 
	*/
	function AddSweepstakes(&$sweepstakes)
	{
		$sweepstakes->personId = $this->personId;
		$found = false;
		foreach($this->_sweepstakesList as $sweepstakes2)
		{
			if ($sweepstakes->sweepstakesId > 0 && $sweepstakes->sweepstakesId == $sweepstakes2->sweepstakesId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_sweepstakesList[] = $sweepstakes;
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
}
?>