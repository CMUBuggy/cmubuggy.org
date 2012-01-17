<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `dataedit` (
	`dataeditid` int(11) NOT NULL auto_increment,
	`edittype` VARCHAR(255) NOT NULL,
	`objtype` VARCHAR(255) NOT NULL,
	`objid` VARCHAR(255) NOT NULL,
	`oldvalue` VARCHAR(255) NOT NULL,
	`newvalue` VARCHAR(255) NOT NULL,
	`timestamp` VARCHAR(255) NOT NULL,
	`userid` int(11) NOT NULL,
	`objattr` VARCHAR(255) NOT NULL, INDEX(`userid`), PRIMARY KEY  (`dataeditid`)) ENGINE=MyISAM;
*/

/**
* <b>dataedit</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5&wrapper=pog&objectName=dataedit&attributeList=array+%28%0A++0+%3D%3E+%27edittype%27%2C%0A++1+%3D%3E+%27objtype%27%2C%0A++2+%3D%3E+%27objid%27%2C%0A++3+%3D%3E+%27oldvalue%27%2C%0A++4+%3D%3E+%27newvalue%27%2C%0A++5+%3D%3E+%27timestamp%27%2C%0A++6+%3D%3E+%27user%27%2C%0A++7+%3D%3E+%27objattr%27%2C%0A%29&typeList=array+%28%0A++0+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++1+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++2+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++3+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++4+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++5+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++6+%3D%3E+%27BELONGSTO%27%2C%0A++7+%3D%3E+%27VARCHAR%28255%29%27%2C%0A%29
*/
include_once('class.pog_base.php');
class dataedit extends POG_Base
{
	public $dataeditId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $edittype;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $objtype;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $objid;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $oldvalue;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $newvalue;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $timestamp;
	
	/**
	 * @var INT(11)
	 */
	public $userId;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $objattr;
	
	public $pog_attribute_type = array(
		"dataeditId" => array('db_attributes' => array("NUMERIC", "INT")),
		"edittype" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"objtype" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"objid" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"oldvalue" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"newvalue" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"timestamp" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"user" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"objattr" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function dataedit($edittype='', $objtype='', $objid='', $oldvalue='', $newvalue='', $timestamp='', $objattr='')
	{
		$this->edittype = $edittype;
		$this->objtype = $objtype;
		$this->objid = $objid;
		$this->oldvalue = $oldvalue;
		$this->newvalue = $newvalue;
		$this->timestamp = $timestamp;
		$this->objattr = $objattr;
	}
	
	
	/**
	* Gets object from database
	* @param integer $dataeditId 
	* @return object $dataedit
	*/
	function Get($dataeditId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `dataedit` where `dataeditid`='".intval($dataeditId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->dataeditId = $row['dataeditid'];
			$this->edittype = $this->Unescape($row['edittype']);
			$this->objtype = $this->Unescape($row['objtype']);
			$this->objid = $this->Unescape($row['objid']);
			$this->oldvalue = $this->Unescape($row['oldvalue']);
			$this->newvalue = $this->Unescape($row['newvalue']);
			$this->timestamp = $this->Unescape($row['timestamp']);
			$this->userId = $row['userid'];
			$this->objattr = $this->Unescape($row['objattr']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $dataeditList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `dataedit` ";
		$dataeditList = Array();
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
			$sortBy = "dataeditid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$dataedit = new $thisObjectName();
			$dataedit->dataeditId = $row['dataeditid'];
			$dataedit->edittype = $this->Unescape($row['edittype']);
			$dataedit->objtype = $this->Unescape($row['objtype']);
			$dataedit->objid = $this->Unescape($row['objid']);
			$dataedit->oldvalue = $this->Unescape($row['oldvalue']);
			$dataedit->newvalue = $this->Unescape($row['newvalue']);
			$dataedit->timestamp = $this->Unescape($row['timestamp']);
			$dataedit->userId = $row['userid'];
			$dataedit->objattr = $this->Unescape($row['objattr']);
			$dataeditList[] = $dataedit;
		}
		return $dataeditList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $dataeditId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `dataeditid` from `dataedit` where `dataeditid`='".$this->dataeditId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `dataedit` set 
			`edittype`='".$this->Escape($this->edittype)."', 
			`objtype`='".$this->Escape($this->objtype)."', 
			`objid`='".$this->Escape($this->objid)."', 
			`oldvalue`='".$this->Escape($this->oldvalue)."', 
			`newvalue`='".$this->Escape($this->newvalue)."', 
			`timestamp`='".$this->Escape($this->timestamp)."', 
			`userid`='".$this->userId."', 
			`objattr`='".$this->Escape($this->objattr)."' where `dataeditid`='".$this->dataeditId."'";
		}
		else
		{
			$this->pog_query = "insert into `dataedit` (`edittype`, `objtype`, `objid`, `oldvalue`, `newvalue`, `timestamp`, `userid`, `objattr` ) values (
			'".$this->Escape($this->edittype)."', 
			'".$this->Escape($this->objtype)."', 
			'".$this->Escape($this->objid)."', 
			'".$this->Escape($this->oldvalue)."', 
			'".$this->Escape($this->newvalue)."', 
			'".$this->Escape($this->timestamp)."', 
			'".$this->userId."', 
			'".$this->Escape($this->objattr)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->dataeditId == "")
		{
			$this->dataeditId = $insertId;
		}
		return $this->dataeditId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $dataeditId
	*/
	function SaveNew()
	{
		$this->dataeditId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `dataedit` where `dataeditid`='".$this->dataeditId."'";
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
			$pog_query = "delete from `dataedit` where ";
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
}
?>