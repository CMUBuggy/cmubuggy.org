<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `video` (
	`videoid` int(11) NOT NULL auto_increment,
	`title` VARCHAR(255) NOT NULL,
	`youtubeid` VARCHAR(255) NOT NULL,
	`heatid` int(11) NOT NULL,
	`videogroupid` int(11) NOT NULL,
	`urlkey` VARCHAR(255) NOT NULL, INDEX(`heatid`,`videogroupid`), PRIMARY KEY  (`videoid`)) ENGINE=MyISAM;
*/

/**
* <b>video</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.0f / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=video&attributeList=array+%28%0A++0+%3D%3E+%27title%27%2C%0A++1+%3D%3E+%27youtubeID%27%2C%0A++2+%3D%3E+%27heat%27%2C%0A++3+%3D%3E+%27note%27%2C%0A++4+%3D%3E+%27videogroup%27%2C%0A++5+%3D%3E+%27urlkey%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527HASMANY%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527BELONGSTO%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2529
*/
include_once('class.pog_base.php');
class video extends POG_Base
{
	public $videoId = '';

	/**
	 * @var VARCHAR(255)
	 */
	public $title;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $youtubeID;
	
	/**
	 * @var INT(11)
	 */
	public $heatId;
	
	/**
	 * @var private array of note objects
	 */
	private $_noteList = array();
	
	/**
	 * @var INT(11)
	 */
	public $videogroupId;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $urlkey;
	
	public $pog_attribute_type = array(
		"videoId" => array('db_attributes' => array("NUMERIC", "INT")),
		"title" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"youtubeID" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"heat" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"note" => array('db_attributes' => array("OBJECT", "HASMANY")),
		"videogroup" => array('db_attributes' => array("OBJECT", "BELONGSTO")),
		"urlkey" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
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
	
	function video($title='', $youtubeID='', $urlkey='')
	{
		$this->title = $title;
		$this->youtubeID = $youtubeID;
		$this->_noteList = array();
		$this->urlkey = $urlkey;
	}
	
	
	/**
	* Gets object from database
	* @param integer $videoId 
	* @return object $video
	*/
	function Get($videoId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `video` where `videoid`='".intval($videoId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->videoId = $row['videoid'];
			$this->title = $this->Unescape($row['title']);
			$this->youtubeID = $this->Unescape($row['youtubeid']);
			$this->heatId = $row['heatid'];
			$this->videogroupId = $row['videogroupid'];
			$this->urlkey = $this->Unescape($row['urlkey']);
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $videoList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `video` ";
		$videoList = Array();
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
			$sortBy = "videoid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$video = new $thisObjectName();
			$video->videoId = $row['videoid'];
			$video->title = $this->Unescape($row['title']);
			$video->youtubeID = $this->Unescape($row['youtubeid']);
			$video->heatId = $row['heatid'];
			$video->videogroupId = $row['videogroupid'];
			$video->urlkey = $this->Unescape($row['urlkey']);
			$videoList[] = $video;
		}
		return $videoList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $videoId
	*/
	function Save($deep = true)
	{
		$connection = Database::Connect();
		$this->pog_query = "select `videoid` from `video` where `videoid`='".$this->videoId."' LIMIT 1";
		$rows = Database::Query($this->pog_query, $connection);
		if ($rows > 0)
		{
			$this->pog_query = "update `video` set 
			`title`='".$this->Escape($this->title)."', 
			`youtubeid`='".$this->Escape($this->youtubeID)."', 
			`heatid`='".$this->heatId."', 
			`videogroupid`='".$this->videogroupId."', 
			`urlkey`='".$this->Escape($this->urlkey)."' where `videoid`='".$this->videoId."'";
		}
		else
		{
			$this->pog_query = "insert into `video` (`title`, `youtubeid`, `heatid`, `videogroupid`, `urlkey` ) values (
			'".$this->Escape($this->title)."', 
			'".$this->Escape($this->youtubeID)."', 
			'".$this->heatId."', 
			'".$this->videogroupId."', 
			'".$this->Escape($this->urlkey)."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->videoId == "")
		{
			$this->videoId = $insertId;
		}
		if ($deep)
		{
			foreach ($this->_noteList as $note)
			{
				$note->videoId = $this->videoId;
				$note->Save($deep);
			}
		}
		return $this->videoId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $videoId
	*/
	function SaveNew($deep = false)
	{
		$this->videoId = '';
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
			$noteList = $this->GetNoteList();
			foreach ($noteList as $note)
			{
				$note->Delete($deep, $across);
			}
		}
		$connection = Database::Connect();
		$this->pog_query = "delete from `video` where `videoid`='".$this->videoId."'";
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
				$pog_query = "delete from `video` where ";
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
	* Associates the heat object to this one
	* @return boolean
	*/
	function GetHeat()
	{
		$heat = new heat();
		return $heat->Get($this->heatId);
	}
	
	
	/**
	* Associates the heat object to this one
	* @return 
	*/
	function SetHeat(&$heat)
	{
		$this->heatId = $heat->heatId;
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
		$fcv_array[] = array("videoId", "=", $this->videoId);
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
			$note->videoId = '';
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
		$note->videoId = $this->videoId;
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
	* Associates the videogroup object to this one
	* @return boolean
	*/
	function GetVideogroup()
	{
		$videogroup = new videogroup();
		return $videogroup->Get($this->videogroupId);
	}
	
	
	/**
	* Associates the videogroup object to this one
	* @return 
	*/
	function SetVideogroup(&$videogroup)
	{
		$this->videogroupId = $videogroup->videogroupId;
	}
}
?>