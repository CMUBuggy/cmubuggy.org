<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `broadcasterq` (
	`broadcasterqid` int(11) NOT NULL auto_increment,
	`timestamp` BIGINT NOT NULL,
	`name` VARCHAR(255) NOT NULL,
	`location` VARCHAR(255) NOT NULL,
	`orgyear` VARCHAR(255) NOT NULL,
	`question` TEXT NOT NULL,
	`status` SMALLINT NOT NULL, PRIMARY KEY  (`broadcasterqid`)) ENGINE=MyISAM;
*/

/**
* <b>broadcasterQ</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=broadcasterQ&attributeList=array+%28%0A++0+%3D%3E+%27timestamp%27%2C%0A++1+%3D%3E+%27name%27%2C%0A++2+%3D%3E+%27location%27%2C%0A++3+%3D%3E+%27orgyear%27%2C%0A++4+%3D%3E+%27question%27%2C%0A++5+%3D%3E+%27status%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527BIGINT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527TEXT%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class broadcasterQ extends POG_Base
{
	public $broadcasterqId = '';

	/**
	 * @var BIGINT
	 */
	public $timestamp;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $name;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $location;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $orgyear;
	
	/**
	 * @var TEXT
	 */
	public $question;
	
	/**
	 * @var SMALLINT
	 */
	public $status;
	
	public $pog_attribute_type = array(
		"broadcasterqId" => array('db_attributes' => array("NUMERIC", "INT")),
		"timestamp" => array('db_attributes' => array("NUMERIC", "BIGINT")),
		"name" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"location" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"orgyear" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"question" => array('db_attributes' => array("TEXT", "TEXT")),
		"status" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
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
	
	function broadcasterQ($timestamp='', $name='', $location='', $orgyear='', $question='', $status='')
	{
		$this->timestamp = $timestamp;
		$this->name = $name;
		$this->location = $location;
		$this->orgyear = $orgyear;
		$this->question = $question;
		$this->status = $status;
	}
	
	
	/**
	* Gets object from database
	* @param integer $broadcasterqId 
	* @return object $broadcasterQ
	*/
	function Get($broadcasterqId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `broadcasterq` where `broadcasterqid`='".intval($broadcasterqId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->broadcasterqId = $row['broadcasterqid'];
			$this->timestamp = $this->Unescape($row['timestamp']);
			$this->name = $this->Unescape($row['name']);
			$this->location = $this->Unescape($row['location']);
			$this->orgyear = $this->Unescape($row['orgyear']);
			$this->question = $this->Unescape($row['question']);
			$this->status = $this->Unescape($row['status']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $broadcasterqList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `broadcasterq` ";
		$broadcasterqList = Array();
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
			$sortBy = "broadcasterqid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$broadcasterq = new $thisObjectName();
			$broadcasterq->broadcasterqId = $row['broadcasterqid'];
			$broadcasterq->timestamp = $this->Unescape($row['timestamp']);
			$broadcasterq->name = $this->Unescape($row['name']);
			$broadcasterq->location = $this->Unescape($row['location']);
			$broadcasterq->orgyear = $this->Unescape($row['orgyear']);
			$broadcasterq->question = $this->Unescape($row['question']);
			$broadcasterq->status = $this->Unescape($row['status']);
			$broadcasterqList[] = $broadcasterq;
		}
		return $broadcasterqList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $broadcasterqId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `broadcasterqid` from `broadcasterq` where `broadcasterqid`='".$this->broadcasterqId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `broadcasterq` set 
			`timestamp`='".$this->Escape($this->timestamp)."', 
			`name`='".$this->Escape($this->name)."', 
			`location`='".$this->Escape($this->location)."', 
			`orgyear`='".$this->Escape($this->orgyear)."', 
			`question`='".$this->Escape($this->question)."', 
			`status`='".$this->Escape($this->status)."' where `broadcasterqid`='".$this->broadcasterqId."'";
		}
		else
		{
			$this->pog_query = "insert into `broadcasterq` (`timestamp`, `name`, `location`, `orgyear`, `question`, `status` ) values (
			'".$this->Escape($this->timestamp)."', 
			'".$this->Escape($this->name)."', 
			'".$this->Escape($this->location)."', 
			'".$this->Escape($this->orgyear)."', 
			'".$this->Escape($this->question)."', 
			'".$this->Escape($this->status)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->broadcasterqId == "")
		{
			$this->broadcasterqId = $insertId;
		}
		return $this->broadcasterqId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $broadcasterqId
	*/
	function SaveNew()
	{
		$this->broadcasterqId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `broadcasterq` where `broadcasterqid`='".$this->broadcasterqId."'";
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
			$pog_query = "delete from `broadcasterq` where ";
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