<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `videogroup` (
	`videogroupid` int(11) NOT NULL auto_increment,
	`description` VARCHAR(255) NOT NULL,
	`displayordinal` SMALLINT NOT NULL, PRIMARY KEY  (`videogroupid`)) ENGINE=MyISAM;
*/

/**
* <b>videogroup</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=videogroup&attributeList=array+%28%0A++0+%3D%3E+%27description%27%2C%0A++1+%3D%3E+%27video%27%2C%0A++2+%3D%3E+%27displayordinal%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527SMALLINT%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class videogroup extends POG_Base
{
	public $videogroupId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $description;
	
	/**
	 * @var private array of video objects
	 */
	private $_videoList = array();
	
	/**
	 * @var SMALLINT
	 */
	public $displayordinal;
	
	public $pog_attribute_type = array(
		"videogroupId" => array('db_attributes' => array("NUMERIC", "INT")),
		"description" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"video" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"displayordinal" => array('db_attributes' => array("NUMERIC", "SMALLINT")),
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
	
	function videogroup($description='', $displayordinal='')
	{
		$this->description = $description;
		$this->_videoList = array();
		$this->displayordinal = $displayordinal;
	}
	
	
	/**
	* Gets object from database
	* @param integer $videogroupId 
	* @return object $videogroup
	*/
	function Get($videogroupId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `videogroup` where `videogroupid`='".intval($videogroupId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->videogroupId = $row['videogroupid'];
			$this->description = $this->Unescape($row['description']);
			$this->displayordinal = $this->Unescape($row['displayordinal']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $videogroupList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `videogroup` ";
		$videogroupList = Array();
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
			$sortBy = "videogroupid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$videogroup = new $thisObjectName();
			$videogroup->videogroupId = $row['videogroupid'];
			$videogroup->description = $this->Unescape($row['description']);
			$videogroup->displayordinal = $this->Unescape($row['displayordinal']);
			$videogroupList[] = $videogroup;
		}
		return $videogroupList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $videogroupId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `videogroupid` from `videogroup` where `videogroupid`='".$this->videogroupId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `videogroup` set 
			`description`='".$this->Escape($this->description)."', 
			`displayordinal`='".$this->Escape($this->displayordinal)."' where `videogroupid`='".$this->videogroupId."'";
		}
		else
		{
			$this->pog_query = "insert into `videogroup` (`description`, `displayordinal` ) values (
			'".$this->Escape($this->description)."', 
			'".$this->Escape($this->displayordinal)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->videogroupId == "")
		{
			$this->videogroupId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_videoList as $video)
			{
				$video->videogroupId = $this->videogroupId;
				$video->Save($deep);
			}
		}
		return $this->videogroupId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $videogroupId
	*/
	function SaveNew($deep = false)
	{
		$this->videogroupId = '';
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
			$videoList = $this->GetVideoList();
			foreach ($videoList as $video)
			{
				$video->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `videogroup` where `videogroupid`='".$this->videogroupId."'";
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
				$pog_query = "delete from `videogroup` where ";
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
	* Gets a list of video objects associated to this one
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array of video objects
	*/
	function GetVideoList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$video = new video();
		$fcv_array[] = array("videogroupId", "=", $this->videogroupId);
		$dbObjects = $video->GetList($fcv_array, $sortBy, $ascending, $limit);
		return $dbObjects;
	}
	
	
	/**
	* Makes this the parent of all video objects in the video List array. Any existing video will become orphan(s)
	* @return null
	*/
	function SetVideoList(&$list)
	{
		$this->_videoList = array();
		$existingVideoList = $this->GetVideoList();
		foreach ($existingVideoList as $video)
		{
			$video->videogroupId = '';
			$video->Save(false);
		}
		$this->_videoList = $list;
	}
	
	
	/**
	* Associates the video object to this one
	* @return 
	*/
	function AddVideo(&$video)
	{
		$video->videogroupId = $this->videogroupId;
		$found = false;
		foreach($this->_videoList as $video2)
		{
			if ($video->videoId > 0 && $video->videoId == $video2->videoId)
			{
				$found = true;
				break;
			}
		}
		if (!$found)
		{
			$this->_videoList[] = $video;
		}
	}
}
?>