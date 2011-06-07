<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `user` (
	`userid` int(11) NOT NULL auto_increment,
	`username` VARCHAR(255) NOT NULL,
	`password` VARCHAR(255) NOT NULL,
	`email` VARCHAR(255) NOT NULL,
	`realname` VARCHAR(255) NOT NULL,
	`membersince` INT NOT NULL,
	`gradyear` SMALLINT NOT NULL,
	`salt` VARCHAR(255) NOT NULL,
	`urlkey` VARCHAR(255) NOT NULL,
	`emailvalidatekey` VARCHAR(255) NOT NULL,
	`registerip` VARCHAR(255) NOT NULL,
	`lastloginip` VARCHAR(255) NOT NULL,
	`lastlogintime` INT NOT NULL,
	`registerhumantest` VARCHAR(255) NOT NULL, PRIMARY KEY  (`userid`)) ENGINE=MyISAM;
*/

/**
* <b>user</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=user&attributeList=array+%28%0A++0+%3D%3E+%27username%27%2C%0A++1+%3D%3E+%27password%27%2C%0A++2+%3D%3E+%27email%27%2C%0A++3+%3D%3E+%27realname%27%2C%0A++4+%3D%3E+%27membersince%27%2C%0A++5+%3D%3E+%27gradyear%27%2C%0A++6+%3D%3E+%27org%27%2C%0A++7+%3D%3E+%27person%27%2C%0A++8+%3D%3E+%27note%27%2C%0A++9+%3D%3E+%27salt%27%2C%0A++10+%3D%3E+%27urlkey%27%2C%0A++11+%3D%3E+%27emailvalidatekey%27%2C%0A++12+%3D%3E+%27member%27%2C%0A++13+%3D%3E+%27registerip%27%2C%0A++14+%3D%3E+%27lastloginip%27%2C%0A++15+%3D%3E+%27lastlogintime%27%2C%0A++16+%3D%3E+%27registerhumantest%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527JOIN%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B8%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B9%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B10%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B11%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B12%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B13%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B14%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B15%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B16%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
include_once('class.orgusermap.php');
class user extends POG_Base
{
	public $userId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $username;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $password;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $email;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $realname;
	
	/**
	 * @var INT
	 */
	public $membersince;
	
	/**
	 * @var SMALLINT
	 */
	public $gradyear;
	
	/**
	 * @var private array of org objects
	 */
	private $_orgList = array();
	
	/**
	 * @var private array of person objects
	 */
	private $_personList = array();
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	/**
	 * @var VARCHAR(255)
	 */
	public $salt;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $urlkey;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $emailvalidatekey;
	
	/**
	 * @var private array of member objects
	 */
	private $_memberList = array();
	
	/**
	 * @var VARCHAR(255)
	 */
	public $registerip;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $lastloginip;
	
	/**
	 * @var INT
	 */
	public $lastlogintime;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $registerhumantest;
	
	public $pog_attribute_type = array(
		"userId" => array('db_attributes' => array("NUMERIC", "INT")),
		"username" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"password" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"email" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"realname" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"membersince" => array('db_attributes' => array("NUMERIC", "INT")),
		"gradyear" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"org" => array('db_attributes' => array("OBJECT", "JOIN")),
		"person" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"salt" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"urlkey" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"emailvalidatekey" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"member" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"registerip" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"lastloginip" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"lastlogintime" => array('db_attributes' => array("NUMERIC", "INT")),
		"registerhumantest" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function user($username='', $password='', $email='', $realname='', $membersince='', $gradyear='', $salt='', $urlkey='', $emailvalidatekey='', $registerip='', $lastloginip='', $lastlogintime='', $registerhumantest='')
	{
		$this->username = $username;
		$this->password = $password;
		$this->email = $email;
		$this->realname = $realname;
		$this->membersince = $membersince;
		$this->gradyear = $gradyear;
		$this->_orgList = array();
		$this->_personList = array();
		$this->_noteList = array();
		$this->salt = $salt;
		$this->urlkey = $urlkey;
		$this->emailvalidatekey = $emailvalidatekey;
		$this->_memberList = array();
		$this->registerip = $registerip;
		$this->lastloginip = $lastloginip;
		$this->lastlogintime = $lastlogintime;
		$this->registerhumantest = $registerhumantest;
	}
	
	
	/**
	* Gets object from database
	* @param integer $userId 
	* @return object $user
	*/
	function Get($userId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `user` where `userid`='".intval($userId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->userId = $row['userid'];
			$this->username = $this->Unescape($row['username']);
			$this->password = $this->Unescape($row['password']);
			$this->email = $this->Unescape($row['email']);
			$this->realname = $this->Unescape($row['realname']);
			$this->membersince = $this->Unescape($row['membersince']);
			$this->gradyear = $this->Unescape($row['gradyear']);
			$this->salt = $this->Unescape($row['salt']);
			$this->urlkey = $this->Unescape($row['urlkey']);
			$this->emailvalidatekey = $this->Unescape($row['emailvalidatekey']);
			$this->registerip = $this->Unescape($row['registerip']);
			$this->lastloginip = $this->Unescape($row['lastloginip']);
			$this->lastlogintime = $this->Unescape($row['lastlogintime']);
			$this->registerhumantest = $this->Unescape($row['registerhumantest']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $userList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `user` ";
		$userList = Array();
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
			$sortBy = "userid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$user = new $thisObjectName();
			$user->userId = $row['userid'];
			$user->username = $this->Unescape($row['username']);
			$user->password = $this->Unescape($row['password']);
			$user->email = $this->Unescape($row['email']);
			$user->realname = $this->Unescape($row['realname']);
			$user->membersince = $this->Unescape($row['membersince']);
			$user->gradyear = $this->Unescape($row['gradyear']);
			$user->salt = $this->Unescape($row['salt']);
			$user->urlkey = $this->Unescape($row['urlkey']);
			$user->emailvalidatekey = $this->Unescape($row['emailvalidatekey']);
			$user->registerip = $this->Unescape($row['registerip']);
			$user->lastloginip = $this->Unescape($row['lastloginip']);
			$user->lastlogintime = $this->Unescape($row['lastlogintime']);
			$user->registerhumantest = $this->Unescape($row['registerhumantest']);
			$userList[] = $user;
		}
		return $userList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $userId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `userid` from `user` where `userid`='".$this->userId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `user` set 
			`username`='".$this->Escape($this->username)."', 
			`password`='".$this->Escape($this->password)."', 
			`email`='".$this->Escape($this->email)."', 
			`realname`='".$this->Escape($this->realname)."', 
			`membersince`='".$this->Escape($this->membersince)."', 
			`gradyear`='".$this->Escape($this->gradyear)."', 
			`salt`='".$this->Escape($this->salt)."', 
			`urlkey`='".$this->Escape($this->urlkey)."', 
			`emailvalidatekey`='".$this->Escape($this->emailvalidatekey)."', 
			`registerip`='".$this->Escape($this->registerip)."', 
			`lastloginip`='".$this->Escape($this->lastloginip)."', 
			`lastlogintime`='".$this->Escape($this->lastlogintime)."', 
			`registerhumantest`='".$this->Escape($this->registerhumantest)."' where `userid`='".$this->userId."'";
		}
		else
		{
			$this->pog_query = "insert into `user` (`username`, `password`, `email`, `realname`, `membersince`, `gradyear`, `salt`, `urlkey`, `emailvalidatekey`, `registerip`, `lastloginip`, `lastlogintime`, `registerhumantest` ) values (
			'".$this->Escape($this->username)."', 
			'".$this->Escape($this->password)."', 
			'".$this->Escape($this->email)."', 
			'".$this->Escape($this->realname)."', 
			'".$this->Escape($this->membersince)."', 
			'".$this->Escape($this->gradyear)."', 
			'".$this->Escape($this->salt)."', 
			'".$this->Escape($this->urlkey)."', 
			'".$this->Escape($this->emailvalidatekey)."', 
			'".$this->Escape($this->registerip)."', 
			'".$this->Escape($this->lastloginip)."', 
			'".$this->Escape($this->lastlogintime)."', 
			'".$this->Escape($this->registerhumantest)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->userId == "")
		{
			$this->userId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_orgList as $org)
			{
				$org->Save();
				$map = new orguserMap();
				$map->AddMapping($this, $org);
			}
			foreach ($this->_personList as $person)
			{
				$person->userId = $this->userId;
				$person->Save($deep);
			}
			foreach ($this->_noteList as $note)
			{
				$note->userId = $this->userId;
				$note->Save($deep);
			}
			foreach ($this->_memberList as $member)
			{
				$member->userId = $this->userId;
				$member->Save($deep);
			}
		}
		return $this->userId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $userId
	*/
	function SaveNew($deep = false)
	{
		$this->userId = '';
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
			$personList = $this->GetPersonList();
			foreach ($personList as $person)
			{
				$person->Delete($deep, $across);
			}
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
			$memberList = $this->GetMemberList();
			foreach ($memberList as $member)
			{
				$member->Delete($deep, $across);
			}
		}
		if ($across)
		{
			$orgList = $this->GetOrgList();
			$map = new orguserMap();
			$map->RemoveMapping($this);
			foreach ($orgList as $org)
			{
				$org->Delete($deep, $across);
			}
		}
		else
		{
			$map = new orguserMap();
			$map->RemoveMapping($this);
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `user` where `userid`='".$this->userId."'";
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
				$pog_query = "delete from `user` where ";
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
		$map = new orguserMap();
		$map->RemoveMapping($this);
		$this->_orgList = $orgList;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $userList
	*/
	function GetOrgList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$connection = Database::Connect();
		$org = new org();
		$orgList = Array();
		$this->pog_query = "select distinct * from `org` a INNER JOIN `orgusermap` m ON m.orgid = a.orgid where m.userid = '$this->userId' ";
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
			if (in_array($this, $org->userList, true))
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
	* Gets a list of person objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of person objects
	*/
	function GetPersonList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$person = new person();
		$fcv_array[] = array("userId", "=", $this->userId);
		$dbObjects = $person->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all person objects in the person List array. Any existing person will become orphan(s)
	* @return null
	*/
	function SetPersonList(&$list)
	{
		$this->_personList = array();
		$existingPersonList = $this->GetPersonList();
		foreach ($existingPersonList as $person)
		{
			$person->userId = '';
			$person->Save(false);
		}
		$this->_personList = $list;
	}
	
	
	/**
	* Associates the person object to this one
	* @return 
	*/
	function AddPerson(&$person)
	{
		$person->userId = $this->userId;
		$found = false;
		foreach($this->_personList as $person2)
		{
			if ($person->personId > 0 && $person->personId == $person2->personId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_personList[] = $person;
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
		$fcv_array[] = array("userId", "=", $this->userId);
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
			$note->userId = '';
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
		$note->userId = $this->userId;
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
	* Gets a list of member objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of member objects
	*/
	function GetMemberList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$member = new member();
		$fcv_array[] = array("userId", "=", $this->userId);
		$dbObjects = $member->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all member objects in the member List array. Any existing member will become orphan(s)
	* @return null
	*/
	function SetMemberList(&$list)
	{
		$this->_memberList = array();
		$existingMemberList = $this->GetMemberList();
		foreach ($existingMemberList as $member)
		{
			$member->userId = '';
			$member->Save(false);
		}
		$this->_memberList = $list;
	}
	
	
	/**
	* Associates the member object to this one
	* @return 
	*/
	function AddMember(&$member)
	{
		$member->userId = $this->userId;
		$found = false;
		foreach($this->_memberList as $member2)
		{
			if ($member->memberId > 0 && $member->memberId == $member2->memberId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_memberList[] = $member;
		}
	}
}
?>