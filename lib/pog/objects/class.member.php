<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `member` (
	`memberid` int(11) NOT NULL auto_increment,
	`firstname` VARCHAR(255) NOT NULL,
	`lastname` VARCHAR(255) NOT NULL,
	`email` VARCHAR(255) NOT NULL,
	`gradyear` VARCHAR(255) NOT NULL,
	`school` VARCHAR(255) NOT NULL,
	`mem2009` VARCHAR(255) NOT NULL,
	`mem2010` VARCHAR(255) NOT NULL,
	`mem2011` VARCHAR(255) NOT NULL,
	`mem2012` VARCHAR(255) NOT NULL,
	`userid` int(11) NOT NULL,
	`mem2013` VARCHAR(255) NOT NULL, INDEX(`userid`), PRIMARY KEY  (`memberid`)) ENGINE=MyISAM;
*/

/**
* <b>member</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5&wrapper=pog&objectName=member&attributeList=array+%28%0A++0+%3D%3E+%27firstname%27%2C%0A++1+%3D%3E+%27lastname%27%2C%0A++2+%3D%3E+%27email%27%2C%0A++3+%3D%3E+%27gradyear%27%2C%0A++4+%3D%3E+%27org%27%2C%0A++5+%3D%3E+%27school%27%2C%0A++6+%3D%3E+%27mem2009%27%2C%0A++7+%3D%3E+%27mem2010%27%2C%0A++8+%3D%3E+%27mem2011%27%2C%0A++9+%3D%3E+%27mem2012%27%2C%0A++10+%3D%3E+%27user%27%2C%0A++11+%3D%3E+%27mem2013%27%2C%0A%29&typeList=array+%28%0A++0+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++1+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++2+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++3+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++4+%3D%3E+%27JOIN%27%2C%0A++5+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++6+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++7+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++8+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++9+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++10+%3D%3E+%27BELONGSTO%27%2C%0A++11+%3D%3E+%27VARCHAR%28255%29%27%2C%0A%29
*/
include_once('class.pog_base.php');
include_once('class.memberorgmap.php');
class member extends POG_Base
{
	public $memberId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $firstname;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $lastname;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $email;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $gradyear;
	
	/**
	 * @var private array of org objects
	 */
	private $_orgList = array();
	
	/**
	 * @var VARCHAR(255)
	 */
	public $school;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $mem2009;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $mem2010;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $mem2011;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $mem2012;
	
	/**
	 * @var INT(11)
	 */
	public $userId;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $mem2013;
	
	public $pog_attribute_type = array(
		"memberId" => array('db_attributes' => array("NUMERIC", "INT")),
		"firstname" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"lastname" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"email" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"gradyear" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"org" => array('db_attributes' => array("OBJECT", "JOIN")),
		"school" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"mem2009" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"mem2010" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"mem2011" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"mem2012" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"user" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"mem2013" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function member($firstname='', $lastname='', $email='', $gradyear='', $school='', $mem2009='', $mem2010='', $mem2011='', $mem2012='', $mem2013='')
	{
		$this->firstname = $firstname;
		$this->lastname = $lastname;
		$this->email = $email;
		$this->gradyear = $gradyear;
		$this->_orgList = array();
		$this->school = $school;
		$this->mem2009 = $mem2009;
		$this->mem2010 = $mem2010;
		$this->mem2011 = $mem2011;
		$this->mem2012 = $mem2012;
		$this->mem2013 = $mem2013;
	}
	
	
	/**
	* Gets object from database
	* @param integer $memberId 
	* @return object $member
	*/
	function Get($memberId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `member` where `memberid`='".intval($memberId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->memberId = $row['memberid'];
			$this->firstname = $this->Unescape($row['firstname']);
			$this->lastname = $this->Unescape($row['lastname']);
			$this->email = $this->Unescape($row['email']);
			$this->gradyear = $this->Unescape($row['gradyear']);
			$this->school = $this->Unescape($row['school']);
			$this->mem2009 = $this->Unescape($row['mem2009']);
			$this->mem2010 = $this->Unescape($row['mem2010']);
			$this->mem2011 = $this->Unescape($row['mem2011']);
			$this->mem2012 = $this->Unescape($row['mem2012']);
			$this->userId = $row['userid'];
			$this->mem2013 = $this->Unescape($row['mem2013']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $memberList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `member` ";
		$memberList = Array();
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
			$sortBy = "memberid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$member = new $thisObjectName();
			$member->memberId = $row['memberid'];
			$member->firstname = $this->Unescape($row['firstname']);
			$member->lastname = $this->Unescape($row['lastname']);
			$member->email = $this->Unescape($row['email']);
			$member->gradyear = $this->Unescape($row['gradyear']);
			$member->school = $this->Unescape($row['school']);
			$member->mem2009 = $this->Unescape($row['mem2009']);
			$member->mem2010 = $this->Unescape($row['mem2010']);
			$member->mem2011 = $this->Unescape($row['mem2011']);
			$member->mem2012 = $this->Unescape($row['mem2012']);
			$member->userId = $row['userid'];
			$member->mem2013 = $this->Unescape($row['mem2013']);
			$memberList[] = $member;
		}
		return $memberList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $memberId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `memberid` from `member` where `memberid`='".$this->memberId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `member` set 
			`firstname`='".$this->Escape($this->firstname)."', 
			`lastname`='".$this->Escape($this->lastname)."', 
			`email`='".$this->Escape($this->email)."', 
			`gradyear`='".$this->Escape($this->gradyear)."', 
			`school`='".$this->Escape($this->school)."', 
			`mem2009`='".$this->Escape($this->mem2009)."', 
			`mem2010`='".$this->Escape($this->mem2010)."', 
			`mem2011`='".$this->Escape($this->mem2011)."', 
			`mem2012`='".$this->Escape($this->mem2012)."', 
			`userid`='".$this->userId."', 
			`mem2013`='".$this->Escape($this->mem2013)."' where `memberid`='".$this->memberId."'";
		}
		else
		{
			$this->pog_query = "insert into `member` (`firstname`, `lastname`, `email`, `gradyear`, `school`, `mem2009`, `mem2010`, `mem2011`, `mem2012`, `userid`, `mem2013` ) values (
			'".$this->Escape($this->firstname)."', 
			'".$this->Escape($this->lastname)."', 
			'".$this->Escape($this->email)."', 
			'".$this->Escape($this->gradyear)."', 
			'".$this->Escape($this->school)."', 
			'".$this->Escape($this->mem2009)."', 
			'".$this->Escape($this->mem2010)."', 
			'".$this->Escape($this->mem2011)."', 
			'".$this->Escape($this->mem2012)."', 
			'".$this->userId."', 
			'".$this->Escape($this->mem2013)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->memberId == "")
		{
			$this->memberId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_orgList as $org)
			{
				$org->Save();
				$map = new memberorgMap();
				$map->AddMapping($this, $org);
			}
		}
		return $this->memberId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $memberId
	*/
	function SaveNew($deep = false)
	{
		$this->memberId = '';
		return $this->Save($deep);
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete($deep = false, $across = false)
	{
		if ($across)
		{
			$orgList = $this->GetOrgList();
			$map = new memberorgMap();
			$map->RemoveMapping($this);
			foreach ($orgList as $org)
			{
				$org->Delete($deep, $across);
			}
		}
		else
		{
			$map = new memberorgMap();
			$map->RemoveMapping($this);
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `member` where `memberid`='".$this->memberId."'";
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
				$pog_query = "delete from `member` where ";
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
	* Creates mappings between this and all objects in the org List array. Any existing mapping will become orphan(s)
	* @return null
	*/
	function SetOrgList(&$orgList)
	{
		$map = new memberorgMap();
		$map->RemoveMapping($this);
		$this->_orgList = $orgList;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $memberList
	*/
	function GetOrgList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$connection = Database::Connect();
		$org = new org();
		$orgList = Array();
		$this->pog_query = "select distinct * from `org` a INNER JOIN `memberorgmap` m ON m.orgid = a.orgid where m.memberid = '$this->memberId' ";
		if (sizeof($fcv_array) > 0)
		{
			$this->pog_query .= " AND ";
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
					if (isset($org->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $org->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $org->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
					{
						if ($GLOBALS['configuration']['db_encoding'] == 1)
						{
							$value = POG_Base::IsColumn($fcv_array[$i][2]) ? "BASE64_DECODE(".$fcv_array[$i][2].")" : "'".$fcv_array[$i][2]."'";
							$this->pog_query .= "BASE64_DECODE(`".$fcv_array[$i][0]."`) ".$fcv_array[$i][1]." ".$value;
						}
						else
						{
							$value =  POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$this->Escape($fcv_array[$i][2])."'";
							$this->pog_query .= "a.`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
						}
					}
					else
					{
						$value = POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$fcv_array[$i][2]."'";
						$this->pog_query .= "a.`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
					}
				}
			}
		}
		if ($sortBy != '')
		{
			if (isset($org->pog_attribute_type[$sortBy]['db_attributes']) && $org->pog_attribute_type[$sortBy]['db_attributes'][0] != 'NUMERIC' && $org->pog_attribute_type[$sortBy]['db_attributes'][0] != 'SET')
			{
				if ($GLOBALS['configuration']['db_encoding'] == 1)
				{
					$sortBy = "BASE64_DECODE(a.$sortBy) ";
				}
				else
				{
					$sortBy = "a.$sortBy ";
				}
			}
			else
			{
				$sortBy = "a.$sortBy ";
			}
		}
		else
		{
			$sortBy = "a.orgid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$cursor = Database::Reader($this->pog_query, $connection);
		while($rows = Database::Read($cursor))
		{
			$org = new org();
			foreach ($org->pog_attribute_type as $attribute_name => $attrubute_type)
			{
				if ($attrubute_type['db_attributes'][1] != "HASMANY" && $attrubute_type['db_attributes'][1] != "JOIN")
				{
					if ($attrubute_type['db_attributes'][1] == "BELONGSTO")
					{
						$org->{strtolower($attribute_name).'Id'} = $rows[strtolower($attribute_name).'id'];
						continue;
					}
					$org->{$attribute_name} = $this->Unescape($rows[strtolower($attribute_name)]);
				}
			}
			$orgList[] = $org;
		}
		return $orgList;
	}
	
	
	/**
	* Associates the org object to this one
	* @return 
	*/
	function AddOrg(&$org)
	{
		if ($org instanceof org)
		{
			if (in_array($this, $org->memberList, true))
			{
				return false;
			}
			else
			{
				$found = false;
				foreach ($this->_orgList as $org2)
				{
					if ($org->orgId > 0 && $org->orgId == $org2->orgId)
					{
						$found = true;
						break;
					}
				}
				if (!$found)
				{
					$this->_orgList[] = $org;
				}
			}
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