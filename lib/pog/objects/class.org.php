<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `org` (
	`orgid` int(11) NOT NULL auto_increment,
	`longname` VARCHAR(255) NOT NULL,
	`shortname` VARCHAR(255) NOT NULL,
	`isgreek` TINYINT NOT NULL,
	`yearfounded` SMALLINT NOT NULL,
	`orgurl` VARCHAR(255) NOT NULL,
	`isactive` TINYINT NOT NULL,
	`isracingorg` TINYINT NOT NULL,
	`urlkey` TINYTEXT NOT NULL,
	`greekname` VARCHAR(255) NOT NULL, PRIMARY KEY  (`orgid`)) ENGINE=MyISAM;
*/

/**
* <b>org</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=org&attributeList=array+%28%0A++0+%3D%3E+%27longname%27%2C%0A++1+%3D%3E+%27shortname%27%2C%0A++2+%3D%3E+%27isgreek%27%2C%0A++3+%3D%3E+%27yearfounded%27%2C%0A++4+%3D%3E+%27orgurl%27%2C%0A++5+%3D%3E+%27isactive%27%2C%0A++6+%3D%3E+%27buggy%27%2C%0A++7+%3D%3E+%27personToOrg%27%2C%0A++8+%3D%3E+%27entry%27%2C%0A++9+%3D%3E+%27orgAward%27%2C%0A++10+%3D%3E+%27isracingorg%27%2C%0A++11+%3D%3E+%27urlkey%27%2C%0A++12+%3D%3E+%27user%27%2C%0A++13+%3D%3E+%27greekname%27%2C%0A++14+%3D%3E+%27member%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B8%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B9%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B10%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B11%2B%253D%253E%2B%2527TINYTEXT%2527%252C%250A%2B%2B12%2B%253D%253E%2B%2527JOIN%2527%252C%250A%2B%2B13%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B14%2B%253D%253E%2B%2527JOIN%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
include_once('class.orgusermap.php');
include_once('class.memberorgmap.php');
class org extends POG_Base
{
	public $orgId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $longname;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $shortname;
	
	/**
	 * @var TINYINT
	 */
	public $isgreek;
	
	/**
	 * @var SMALLINT
	 */
	public $yearfounded;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $orgurl;
	
	/**
	 * @var TINYINT
	 */
	public $isactive;
	
	/**
	 * @var private array of buggy objects
	 */
	private $_buggyList = array();
	
	/**
	 * @var private array of personToOrg objects
	 */
	private $_persontoorgList = array();
	
	/**
	 * @var private array of entry objects
	 */
	private $_entryList = array();
	
	/**
	 * @var private array of orgAward objects
	 */
	private $_orgawardList = array();
	
	/**
	 * @var TINYINT
	 */
	public $isracingorg;
	
	/**
	 * @var TINYTEXT
	 */
	public $urlkey;
	
	/**
	 * @var private array of user objects
	 */
	private $_userList = array();
	
	/**
	 * @var VARCHAR(255)
	 */
	public $greekname;
	
	/**
	 * @var private array of member objects
	 */
	private $_memberList = array();
	
	public $pog_attribute_type = array(
		"orgId" => array('db_attributes' => array("NUMERIC", "INT")),
		"longname" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"shortname" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"isgreek" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"yearfounded" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
		"orgurl" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"isactive" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"buggy" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"personToOrg" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"entry" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"orgAward" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"isracingorg" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"urlkey" => array('db_attributes' => array("TEXT", "TINYTEXT")),
		"user" => array('db_attributes' => array("OBJECT", "JOIN")),
		"greekname" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"member" => array('db_attributes' => array("OBJECT", "JOIN")),
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
	
	function org($longname='', $shortname='', $isgreek='', $yearfounded='', $orgurl='', $isactive='', $isracingorg='', $urlkey='', $greekname='')
	{
		$this->longname = $longname;
		$this->shortname = $shortname;
		$this->isgreek = $isgreek;
		$this->yearfounded = $yearfounded;
		$this->orgurl = $orgurl;
		$this->isactive = $isactive;
		$this->_buggyList = array();
		$this->_persontoorgList = array();
		$this->_entryList = array();
		$this->_orgawardList = array();
		$this->isracingorg = $isracingorg;
		$this->urlkey = $urlkey;
		$this->_userList = array();
		$this->greekname = $greekname;
		$this->_memberList = array();
	}
	
	
	/**
	* Gets object from database
	* @param integer $orgId 
	* @return object $org
	*/
	function Get($orgId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `org` where `orgid`='".intval($orgId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->orgId = $row['orgid'];
			$this->longname = $this->Unescape($row['longname']);
			$this->shortname = $this->Unescape($row['shortname']);
			$this->isgreek = $this->Unescape($row['isgreek']);
			$this->yearfounded = $this->Unescape($row['yearfounded']);
			$this->orgurl = $this->Unescape($row['orgurl']);
			$this->isactive = $this->Unescape($row['isactive']);
			$this->isracingorg = $this->Unescape($row['isracingorg']);
			$this->urlkey = $this->Unescape($row['urlkey']);
			$this->greekname = $this->Unescape($row['greekname']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $orgList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `org` ";
		$orgList = Array();
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
			$sortBy = "orgid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$org = new $thisObjectName();
			$org->orgId = $row['orgid'];
			$org->longname = $this->Unescape($row['longname']);
			$org->shortname = $this->Unescape($row['shortname']);
			$org->isgreek = $this->Unescape($row['isgreek']);
			$org->yearfounded = $this->Unescape($row['yearfounded']);
			$org->orgurl = $this->Unescape($row['orgurl']);
			$org->isactive = $this->Unescape($row['isactive']);
			$org->isracingorg = $this->Unescape($row['isracingorg']);
			$org->urlkey = $this->Unescape($row['urlkey']);
			$org->greekname = $this->Unescape($row['greekname']);
			$orgList[] = $org;
		}
		return $orgList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $orgId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `orgid` from `org` where `orgid`='".$this->orgId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `org` set 
			`longname`='".$this->Escape($this->longname)."', 
			`shortname`='".$this->Escape($this->shortname)."', 
			`isgreek`='".$this->Escape($this->isgreek)."', 
			`yearfounded`='".$this->Escape($this->yearfounded)."', 
			`orgurl`='".$this->Escape($this->orgurl)."', 
			`isactive`='".$this->Escape($this->isactive)."', 
			`isracingorg`='".$this->Escape($this->isracingorg)."', 
			`urlkey`='".$this->Escape($this->urlkey)."', 
			`greekname`='".$this->Escape($this->greekname)."'where `orgid`='".$this->orgId."'";
		}
		else
		{
			$this->pog_query = "insert into `org` (`longname`, `shortname`, `isgreek`, `yearfounded`, `orgurl`, `isactive`, `isracingorg`, `urlkey`, `greekname`) values (
			'".$this->Escape($this->longname)."', 
			'".$this->Escape($this->shortname)."', 
			'".$this->Escape($this->isgreek)."', 
			'".$this->Escape($this->yearfounded)."', 
			'".$this->Escape($this->orgurl)."', 
			'".$this->Escape($this->isactive)."', 
			'".$this->Escape($this->isracingorg)."', 
			'".$this->Escape($this->urlkey)."', 
			'".$this->Escape($this->greekname)."')";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->orgId == "")
		{
			$this->orgId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_buggyList as $buggy)
			{
				$buggy->orgId = $this->orgId;
				$buggy->Save($deep);
			}
			foreach ($this->_persontoorgList as $persontoorg)
			{
				$persontoorg->orgId = $this->orgId;
				$persontoorg->Save($deep);
			}
			foreach ($this->_entryList as $entry)
			{
				$entry->orgId = $this->orgId;
				$entry->Save($deep);
			}
			foreach ($this->_orgawardList as $orgaward)
			{
				$orgaward->orgId = $this->orgId;
				$orgaward->Save($deep);
			}
			foreach ($this->_userList as $user)
			{
				$user->Save();
				$map = new orguserMap();
				$map->AddMapping($this, $user);
			}
			foreach ($this->_memberList as $member)
			{
				$member->Save();
				$map = new memberorgMap();
				$map->AddMapping($this, $member);
			}
		}
		return $this->orgId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $orgId
	*/
	function SaveNew($deep = false)
	{
		$this->orgId = '';
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
			$buggyList = $this->GetBuggyList();
			foreach ($buggyList as $buggy)
			{
				$buggy->Delete($deep, $across);
			}
			$persontoorgList = $this->GetPersontoorgList();
			foreach ($persontoorgList as $persontoorg)
			{
				$persontoorg->Delete($deep, $across);
			}
			$entryList = $this->GetEntryList();
			foreach ($entryList as $entry)
			{
				$entry->Delete($deep, $across);
			}
			$orgawardList = $this->GetOrgawardList();
			foreach ($orgawardList as $orgaward)
			{
				$orgaward->Delete($deep, $across);
			}
		}
		if ($across)
		{
			$userList = $this->GetUserList();
			$map = new orguserMap();
			$map->RemoveMapping($this);
			foreach ($userList as $user)
			{
				$user->Delete($deep, $across);
			}
			$memberList = $this->GetMemberList();
			$map = new memberorgMap();
			$map->RemoveMapping($this);
			foreach ($memberList as $member)
			{
				$member->Delete($deep, $across);
			}
		}
		else
		{
			$map = new orguserMap();
			$map->RemoveMapping($this);
			$map = new memberorgMap();
			$map->RemoveMapping($this);
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `org` where `orgid`='".$this->orgId."'";
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
				$pog_query = "delete from `org` where ";
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
	* Gets a list of buggy objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of buggy objects
	*/
	function GetBuggyList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$buggy = new buggy();
		$fcv_array[] = array("orgId", "=", $this->orgId);
		$dbObjects = $buggy->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all buggy objects in the buggy List array. Any existing buggy will become orphan(s)
	* @return null
	*/
	function SetBuggyList(&$list)
	{
		$this->_buggyList = array();
		$existingBuggyList = $this->GetBuggyList();
		foreach ($existingBuggyList as $buggy)
		{
			$buggy->orgId = '';
			$buggy->Save(false);
		}
		$this->_buggyList = $list;
	}
	
	
	/**
	* Associates the buggy object to this one
	* @return 
	*/
	function AddBuggy(&$buggy)
	{
		$buggy->orgId = $this->orgId;
		$found = false;
		foreach($this->_buggyList as $buggy2)
		{
			if ($buggy->buggyId > 0 && $buggy->buggyId == $buggy2->buggyId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_buggyList[] = $buggy;
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
		$fcv_array[] = array("orgId", "=", $this->orgId);
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
			$persontoorg->orgId = '';
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
		$persontoorg->orgId = $this->orgId;
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
		$fcv_array[] = array("orgId", "=", $this->orgId);
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
			$entry->orgId = '';
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
		$entry->orgId = $this->orgId;
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
	* Gets a list of orgAward objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of orgAward objects
	*/
	function GetOrgawardList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$orgaward = new orgAward();
		$fcv_array[] = array("orgId", "=", $this->orgId);
		$dbObjects = $orgaward->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all orgAward objects in the orgAward List array. Any existing orgAward will become orphan(s)
	* @return null
	*/
	function SetOrgawardList(&$list)
	{
		$this->_orgawardList = array();
		$existingOrgawardList = $this->GetOrgawardList();
		foreach ($existingOrgawardList as $orgaward)
		{
			$orgaward->orgId = '';
			$orgaward->Save(false);
		}
		$this->_orgawardList = $list;
	}
	
	
	/**
	* Associates the orgAward object to this one
	* @return 
	*/
	function AddOrgaward(&$orgaward)
	{
		$orgaward->orgId = $this->orgId;
		$found = false;
		foreach($this->_orgawardList as $orgaward2)
		{
			if ($orgaward->orgawardId > 0 && $orgaward->orgawardId == $orgaward2->orgawardId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_orgawardList[] = $orgaward;
		}
	}
	
	
	/**
	* Creates mappings between this and all objects in the user List array. Any existing mapping will become orphan(s)
	* @return null
	*/
	function SetUserList(&$userList)
	{
		$map = new orguserMap();
		$map->RemoveMapping($this);
		$this->_userList = $userList;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $orgList
	*/
	function GetUserList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$connection = Database::Connect();
		$user = new user();
		$userList = Array();
		$this->pog_query = "select distinct * from `user` a INNER JOIN `orgusermap` m ON m.userid = a.userid where m.orgid = '$this->orgId' ";
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
					if (isset($user->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $user->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $user->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
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
			if (isset($user->pog_attribute_type[$sortBy]['db_attributes']) && $user->pog_attribute_type[$sortBy]['db_attributes'][0] != 'NUMERIC' && $user->pog_attribute_type[$sortBy]['db_attributes'][0] != 'SET')
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
			$sortBy = "a.userid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$cursor = Database::Reader($this->pog_query, $connection);
		while($rows = Database::Read($cursor))
		{
			$user = new user();
			foreach ($user->pog_attribute_type as $attribute_name => $attrubute_type)
			{
				if ($attrubute_type['db_attributes'][1] != "HASMANY" && $attrubute_type['db_attributes'][1] != "JOIN")
				{
					if ($attrubute_type['db_attributes'][1] == "BELONGSTO")
					{
						$user->{strtolower($attribute_name).'Id'} = $rows[strtolower($attribute_name).'id'];
						continue;
					}
					$user->{$attribute_name} = $this->Unescape($rows[strtolower($attribute_name)]);
				}
			}
			$userList[] = $user;
		}
		return $userList;
	}
	
	
	/**
	* Associates the user object to this one
	* @return 
	*/
	function AddUser(&$user)
	{
		if ($user instanceof user)
		{
			if (in_array($this, $user->orgList, true))
			{
				return false;
			}
			else
			{
				$found = false;
				foreach ($this->_userList as $user2)
				{
					if ($user->userId > 0 && $user->userId == $user2->userId)
					{
						$found = true;
						break;
					}
				}
				if (!$found)
				{
					$this->_userList[] = $user;
				}
			}
		}
	}
	
	
	/**
	* Creates mappings between this and all objects in the member List array. Any existing mapping will become orphan(s)
	* @return null
	*/
	function SetMemberList(&$memberList)
	{
		$map = new memberorgMap();
		$map->RemoveMapping($this);
		$this->_memberList = $memberList;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $orgList
	*/
	function GetMemberList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$connection = Database::Connect();
		$member = new member();
		$memberList = Array();
		$this->pog_query = "select distinct * from `member` a INNER JOIN `memberorgmap` m ON m.memberid = a.memberid where m.orgid = '$this->orgId' ";
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
					if (isset($member->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $member->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $member->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
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
			if (isset($member->pog_attribute_type[$sortBy]['db_attributes']) && $member->pog_attribute_type[$sortBy]['db_attributes'][0] != 'NUMERIC' && $member->pog_attribute_type[$sortBy]['db_attributes'][0] != 'SET')
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
			$sortBy = "a.memberid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$cursor = Database::Reader($this->pog_query, $connection);
		while($rows = Database::Read($cursor))
		{
			$member = new member();
			foreach ($member->pog_attribute_type as $attribute_name => $attrubute_type)
			{
				if ($attrubute_type['db_attributes'][1] != "HASMANY" && $attrubute_type['db_attributes'][1] != "JOIN")
				{
					if ($attrubute_type['db_attributes'][1] == "BELONGSTO")
					{
						$member->{strtolower($attribute_name).'Id'} = $rows[strtolower($attribute_name).'id'];
						continue;
					}
					$member->{$attribute_name} = $this->Unescape($rows[strtolower($attribute_name)]);
				}
			}
			$memberList[] = $member;
		}
		return $memberList;
	}
	
	
	/**
	* Associates the member object to this one
	* @return 
	*/
	function AddMember(&$member)
	{
		if ($member instanceof member)
		{
			if (in_array($this, $member->orgList, true))
			{
				return false;
			}
			else
			{
				$found = false;
				foreach ($this->_memberList as $member2)
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
	}
}
?>