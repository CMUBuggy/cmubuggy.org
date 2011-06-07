<?php
/**
* <b>FindLikeMe</b> 
* plugin class to do Query-By-Example from the S.O.D.A. - Simple Object Database Access 
* Fill in a portion or all of the object and call FindLikeMe() 
* and it will return a list of objects that contain the same 
* data that is filled in.
* 
* @author Mark Slemko
* @version 0.2
* @copyright Free for personal & commercial use. (Offered under the BSD license)
*/
class FindLikeMe
{
	private $sourceObject;
	private $argv;
	public $version = '0.1';

	function Version()
	{
		return $this->version;
	}

	function FindLikeMe($sourceObject,$argv)
	{
		$this->sourceObject = $sourceObject;
		$this->argv = $argv;
	}

	function Execute()
	{
		$objectName = get_class($this->sourceObject);
		$query = array();
		
		foreach($this->sourceObject->pog_attribute_type as $attributeName=>$attribute)
		{
			// include the parent as something to be "like me"
			if ($attribute["db_attributes"][0] == "OBJECT" && $attribute["db_attributes"][1] == "BELONGSTO")
			{
				$attributeName = strtolower($attributeName)."Id";
			}
			
			if (isset($this->sourceObject->$attributeName) && $this->sourceObject->$attributeName != '')
			{
				$value = $this->sourceObject->$attributeName;
				$query[] = array($attributeName,"=",$value);
			}
		}
		return $this->sourceObject->GetList($query);
	}

	function SetupRender()
	{
		echo ' This Plugin returns a list of objects that have similar data.<br>';
		if ($this->PerformUnitTest() === false)
		{
			echo get_class($this).' failed unit test';
		}
		else
		{
			echo get_class($this).' passed unit test';
		}
	}

	function AuthorPage()
	{
		return null;
	}

	function PerformUnitTest()
	{
		//test w/o arguments
		//any object
		$objectNames = unserialize($_SESSION['objectNameList']);

		//try getting a count
		if (sizeof($objectNames) > 0)
		{
			$anyObject = $objectNames[0];
			echo "using class.".strtolower($anyObject).".php <br>";
			
			include_once("../objects/class.".strtolower($anyObject).".php");
			$anyObjectInstance = new $anyObject();
			
			$anyOjbectList = $anyObjectInstance->getList(array(),'',true,1);
			if (count($anyOjbectList) > 0)
			{
				echo "found some objects...<br>";
				$list = $anyOjbectList[0]->FindLikeMe();
				echo "found ".count($list)." objects 'like me' (expect 1)<br>";
	
				if (count($list) >= 1)
				{
					return true;
				}
			}
			return false;
		}

		//test w/ arguments
		
	}
}
?>