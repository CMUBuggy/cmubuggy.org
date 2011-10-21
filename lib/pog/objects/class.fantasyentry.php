<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `fantasyentry` (
	`fantasyentryid` int(11) NOT NULL auto_increment,
	`username` VARCHAR(255) NOT NULL,
	`email` VARCHAR(255) NOT NULL,
	`freeroll1` VARCHAR(255) NOT NULL,
	`freeroll2` VARCHAR(255) NOT NULL,
	`freeroll3` VARCHAR(255) NOT NULL,
	`freeroll4` VARCHAR(255) NOT NULL,
	`backhills1` VARCHAR(255) NOT NULL,
	`backhills2` VARCHAR(255) NOT NULL,
	`backhills3` VARCHAR(255) NOT NULL,
	`backhills4` VARCHAR(255) NOT NULL,
	`tiebreaker` VARCHAR(255) NOT NULL,
	`name` VARCHAR(255) NOT NULL,
	`timestamp` INT NOT NULL,
	`ip` VARCHAR(255) NOT NULL,
	`key` VARCHAR(255) NOT NULL, PRIMARY KEY  (`fantasyentryid`)) ENGINE=MyISAM;
*/

/**
* <b>fantasyentry</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=fantasyentry&attributeList=array+%28%0A++0+%3D%3E+%27username%27%2C%0A++1+%3D%3E+%27email%27%2C%0A++2+%3D%3E+%27freeroll1%27%2C%0A++3+%3D%3E+%27freeroll2%27%2C%0A++4+%3D%3E+%27freeroll3%27%2C%0A++5+%3D%3E+%27freeroll4%27%2C%0A++6+%3D%3E+%27backhills1%27%2C%0A++7+%3D%3E+%27backhills2%27%2C%0A++8+%3D%3E+%27backhills3%27%2C%0A++9+%3D%3E+%27backhills4%27%2C%0A++10+%3D%3E+%27tiebreaker%27%2C%0A++11+%3D%3E+%27name%27%2C%0A++12+%3D%3E+%27timestamp%27%2C%0A++13+%3D%3E+%27ip%27%2C%0A++14+%3D%3E+%27key%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B8%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B9%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B10%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B11%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B12%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B13%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B14%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class fantasyentry extends POG_Base
{
	public $fantasyentryId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $username;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $email;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $freeroll1;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $freeroll2;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $freeroll3;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $freeroll4;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $backhills1;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $backhills2;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $backhills3;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $backhills4;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $tiebreaker;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $name;
	
	/**
	 * @var INT
	 */
	public $timestamp;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $ip;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $key;
	
	public $pog_attribute_type = array(
		"fantasyentryId" => array('db_attributes' => array("NUMERIC", "INT")),
		"username" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"email" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"freeroll1" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"freeroll2" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"freeroll3" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"freeroll4" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"backhills1" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"backhills2" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"backhills3" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"backhills4" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"tiebreaker" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"name" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"timestamp" => array('db_attributes' => array("NUMERIC", "INT")),
		"ip" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"key" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function fantasyentry($username='', $email='', $freeroll1='', $freeroll2='', $freeroll3='', $freeroll4='', $backhills1='', $backhills2='', $backhills3='', $backhills4='', $tiebreaker='', $name='', $timestamp='', $ip='', $key='')
	{
		$this->username = $username;
		$this->email = $email;
		$this->freeroll1 = $freeroll1;
		$this->freeroll2 = $freeroll2;
		$this->freeroll3 = $freeroll3;
		$this->freeroll4 = $freeroll4;
		$this->backhills1 = $backhills1;
		$this->backhills2 = $backhills2;
		$this->backhills3 = $backhills3;
		$this->backhills4 = $backhills4;
		$this->tiebreaker = $tiebreaker;
		$this->name = $name;
		$this->timestamp = $timestamp;
		$this->ip = $ip;
		$this->key = $key;
	}
	
	
	/**
	* Gets object from database
	* @param integer $fantasyentryId 
	* @return object $fantasyentry
	*/
	function Get($fantasyentryId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `fantasyentry` where `fantasyentryid`='".intval($fantasyentryId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->fantasyentryId = $row['fantasyentryid'];
			$this->username = $this->Unescape($row['username']);
			$this->email = $this->Unescape($row['email']);
			$this->freeroll1 = $this->Unescape($row['freeroll1']);
			$this->freeroll2 = $this->Unescape($row['freeroll2']);
			$this->freeroll3 = $this->Unescape($row['freeroll3']);
			$this->freeroll4 = $this->Unescape($row['freeroll4']);
			$this->backhills1 = $this->Unescape($row['backhills1']);
			$this->backhills2 = $this->Unescape($row['backhills2']);
			$this->backhills3 = $this->Unescape($row['backhills3']);
			$this->backhills4 = $this->Unescape($row['backhills4']);
			$this->tiebreaker = $this->Unescape($row['tiebreaker']);
			$this->name = $this->Unescape($row['name']);
			$this->timestamp = $this->Unescape($row['timestamp']);
			$this->ip = $this->Unescape($row['ip']);
			$this->key = $this->Unescape($row['key']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $fantasyentryList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `fantasyentry` ";
		$fantasyentryList = Array();
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
			$sortBy = "fantasyentryid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$fantasyentry = new $thisObjectName();
			$fantasyentry->fantasyentryId = $row['fantasyentryid'];
			$fantasyentry->username = $this->Unescape($row['username']);
			$fantasyentry->email = $this->Unescape($row['email']);
			$fantasyentry->freeroll1 = $this->Unescape($row['freeroll1']);
			$fantasyentry->freeroll2 = $this->Unescape($row['freeroll2']);
			$fantasyentry->freeroll3 = $this->Unescape($row['freeroll3']);
			$fantasyentry->freeroll4 = $this->Unescape($row['freeroll4']);
			$fantasyentry->backhills1 = $this->Unescape($row['backhills1']);
			$fantasyentry->backhills2 = $this->Unescape($row['backhills2']);
			$fantasyentry->backhills3 = $this->Unescape($row['backhills3']);
			$fantasyentry->backhills4 = $this->Unescape($row['backhills4']);
			$fantasyentry->tiebreaker = $this->Unescape($row['tiebreaker']);
			$fantasyentry->name = $this->Unescape($row['name']);
			$fantasyentry->timestamp = $this->Unescape($row['timestamp']);
			$fantasyentry->ip = $this->Unescape($row['ip']);
			$fantasyentry->key = $this->Unescape($row['key']);
			$fantasyentryList[] = $fantasyentry;
		}
		return $fantasyentryList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $fantasyentryId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `fantasyentryid` from `fantasyentry` where `fantasyentryid`='".$this->fantasyentryId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `fantasyentry` set 
			`username`='".$this->Escape($this->username)."', 
			`email`='".$this->Escape($this->email)."', 
			`freeroll1`='".$this->Escape($this->freeroll1)."', 
			`freeroll2`='".$this->Escape($this->freeroll2)."', 
			`freeroll3`='".$this->Escape($this->freeroll3)."', 
			`freeroll4`='".$this->Escape($this->freeroll4)."', 
			`backhills1`='".$this->Escape($this->backhills1)."', 
			`backhills2`='".$this->Escape($this->backhills2)."', 
			`backhills3`='".$this->Escape($this->backhills3)."', 
			`backhills4`='".$this->Escape($this->backhills4)."', 
			`tiebreaker`='".$this->Escape($this->tiebreaker)."', 
			`name`='".$this->Escape($this->name)."', 
			`timestamp`='".$this->Escape($this->timestamp)."', 
			`ip`='".$this->Escape($this->ip)."', 
			`key`='".$this->Escape($this->key)."' where `fantasyentryid`='".$this->fantasyentryId."'";
		}
		else
		{
			$this->pog_query = "insert into `fantasyentry` (`username`, `email`, `freeroll1`, `freeroll2`, `freeroll3`, `freeroll4`, `backhills1`, `backhills2`, `backhills3`, `backhills4`, `tiebreaker`, `name`, `timestamp`, `ip`, `key` ) values (
			'".$this->Escape($this->username)."', 
			'".$this->Escape($this->email)."', 
			'".$this->Escape($this->freeroll1)."', 
			'".$this->Escape($this->freeroll2)."', 
			'".$this->Escape($this->freeroll3)."', 
			'".$this->Escape($this->freeroll4)."', 
			'".$this->Escape($this->backhills1)."', 
			'".$this->Escape($this->backhills2)."', 
			'".$this->Escape($this->backhills3)."', 
			'".$this->Escape($this->backhills4)."', 
			'".$this->Escape($this->tiebreaker)."', 
			'".$this->Escape($this->name)."', 
			'".$this->Escape($this->timestamp)."', 
			'".$this->Escape($this->ip)."', 
			'".$this->Escape($this->key)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->fantasyentryId == "")
		{
			$this->fantasyentryId = $insertId;
		}
		return $this->fantasyentryId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $fantasyentryId
	*/
	function SaveNew()
	{
		$this->fantasyentryId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `fantasyentry` where `fantasyentryid`='".$this->fantasyentryId."'";
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
			$pog_query = "delete from `fantasyentry` where ";
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
?>