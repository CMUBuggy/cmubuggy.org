<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `orgaward` (
	`orgawardid` int(11) NOT NULL auto_increment,
	`awardtypeid` int(11) NOT NULL,
	`orgid` int(11) NOT NULL,
	`year` SMALLINT NOT NULL, INDEX(`awardtypeid`,`orgid`), PRIMARY KEY  (`orgawardid`)) ENGINE=MyISAM;
*/

/**
* <b>orgAward</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0e / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=orgAward&attributeList=array+%28%0A++0+%3D%3E+%27awardType%27%2C%0A++1+%3D%3E+%27org%27%2C%0A++2+%3D%3E+%27year%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class orgAward extends POG_Base
{
	public $orgawardId = '';

	/**
	 * @var INT(11)
	 */
	public $awardtypeId;
	
	/**
	 * @var INT(11)
	 */
	public $orgId;
	
	/**
	 * @var SMALLINT
	 */
	public $year;
	
	public $pog_attribute_type = array(
		"orgawardId" => array('db_attributes' => array("NUMERIC", "INT")),
		"awardType" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"org" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"year" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
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
	
	function orgAward($year='')
	{
		$this->year = $year;
	}
	
	
	/**
	* Gets object from database
	* @param integer $orgawardId 
	* @return object $orgAward
	*/
	function Get($orgawardId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `orgaward` where `orgawardid`='".intval($orgawardId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->orgawardId = $row['orgawardid'];
			$this->awardtypeId = $row['awardtypeid'];
			$this->orgId = $row['orgid'];
			$this->year = $this->Unescape($row['year']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $orgawardList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `orgaward` ";
		$orgawardList = Array();
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
			$sortBy = "orgawardid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$orgaward = new $thisObjectName();
			$orgaward->orgawardId = $row['orgawardid'];
			$orgaward->awardtypeId = $row['awardtypeid'];
			$orgaward->orgId = $row['orgid'];
			$orgaward->year = $this->Unescape($row['year']);
			$orgawardList[] = $orgaward;
		}
		return $orgawardList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $orgawardId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$this->pog_query = "select `orgawardid` from `orgaward` where `orgawardid`='".$this->orgawardId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `orgaward` set 
			`awardtypeid`='".$this->awardtypeId."', 
			`orgid`='".$this->orgId."', 
			`year`='".$this->Escape($this->year)."' where `orgawardid`='".$this->orgawardId."'";
		}
		else
		{
			$this->pog_query = "insert into `orgaward` (`awardtypeid`, `orgid`, `year` ) values (
			'".$this->awardtypeId."', 
			'".$this->orgId."', 
			'".$this->Escape($this->year)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->orgawardId == "")
		{
			$this->orgawardId = $insertId;
		}
		return $this->orgawardId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $orgawardId
	*/
	function SaveNew()
	{
		$this->orgawardId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `orgaward` where `orgawardid`='".$this->orgawardId."'";
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
			$pog_query = "delete from `orgaward` where ";
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
	* Associates the awardType object to this one
	* @return boolean
	*/
	function GetAwardtype()
	{
		$awardtype = new awardType();
		return $awardtype->Get($this->awardtypeId);
	}
	
	
	/**
	* Associates the awardType object to this one
	* @return 
	*/
	function SetAwardtype(&$awardtype)
	{
		$this->awardtypeId = $awardtype->awardtypeId;
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