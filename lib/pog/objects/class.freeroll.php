<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `freeroll` (
	`freerollid` int(11) NOT NULL auto_increment,
	`date` DATE NOT NULL,
	`firstroll` TIME NOT NULL,
	`status` VARCHAR(255) NOT NULL, PRIMARY KEY  (`freerollid`)) ENGINE=MyISAM;
*/

/**
* <b>freeroll</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=freeroll&attributeList=array+%28%0A++0+%3D%3E+%27date%27%2C%0A++1+%3D%3E+%27firstroll%27%2C%0A++2+%3D%3E+%27status%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527DATE%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527TIME%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class freeroll extends POG_Base
{
	public $freerollId = '';

	/**
	 * @var DATE
	 */
	public $date;
	
	/**
	 * @var TIME
	 */
	public $firstroll;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $status;
	
	public $pog_attribute_type = array(
		"freerollId" => array('db_attributes' => array("NUMERIC", "INT")),
		"date" => array('db_attributes' => array("NUMERIC", "DATE")),
		"firstroll" => array('db_attributes' => array("NUMERIC", "TIME")),
		"status" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function freeroll($date='', $firstroll='', $status='')
	{
		$this->date = $date;
		$this->firstroll = $firstroll;
		$this->status = $status;
	}
	
	
	/**
	* Gets object from database
	* @param integer $freerollId 
	* @return object $freeroll
	*/
	function Get($freerollId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `freeroll` where `freerollid`='".intval($freerollId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->freerollId = $row['freerollid'];
			$this->date = $row['date'];
			$this->firstroll = $row['firstroll'];
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
	* @return array $freerollList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `freeroll` ";
		$freerollList = Array();
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
			$sortBy = "freerollid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$freeroll = new $thisObjectName();
			$freeroll->freerollId = $row['freerollid'];
			$freeroll->date = $row['date'];
			$freeroll->firstroll = $row['firstroll'];
			$freeroll->status = $this->Unescape($row['status']);
			$freerollList[] = $freeroll;
		}
		return $freerollList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $freerollId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `freerollid` from `freeroll` where `freerollid`='".$this->freerollId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `freeroll` set 
			`date`='".$this->date."', 
			`firstroll`='".$this->firstroll."', 
			`status`='".$this->Escape($this->status)."' where `freerollid`='".$this->freerollId."'";
		}
		else
		{
			$this->pog_query = "insert into `freeroll` (`date`, `firstroll`, `status` ) values (
			'".$this->date."', 
			'".$this->firstroll."', 
			'".$this->Escape($this->status)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->freerollId == "")
		{
			$this->freerollId = $insertId;
		}
		return $this->freerollId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $freerollId
	*/
	function SaveNew()
	{
		$this->freerollId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `freeroll` where `freerollid`='".$this->freerollId."'";
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
			$pog_query = "delete from `freeroll` where ";
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