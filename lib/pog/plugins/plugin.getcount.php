<?php
class GetCount
{
	var $sourceObject;
	var $argv;
	var $version = '0.1';

	function Version()
	{
		return $this->version;
	}

	function GetCount($sourceObject, $argv)
	{
		$this->sourceObject = $sourceObject;
		$this->argv = $argv;
	}

	function Execute()
	{
		$objectName = get_class($this->sourceObject);

		if (sizeof($this->argv) > 0)
		{
			$fcv_array = $this->argv[0];
		}
		$sql = 'select count(*) as mycount from `'.strtolower($objectName).'`';

		if (isset($fcv_array) && sizeof($fcv_array) > 0)
		{
			$sql .= " where ";
			for ($i=0, $c=sizeof($fcv_array); $i<$c; $i++)
			{
				if (sizeof($fcv_array[$i]) == 1)
				{
					$sql .= " ".$fcv_array[$i][0]." ";
					continue;
				}
				else
				{
					if ($i > 0 && sizeof($fcv_array[$i-1]) != 1)
					{
						$sql .= " AND ";
					}
					if (isset($this->sourceObject->pog_attribute_type[$fcv_array[$i][0]]) && $this->sourceObject->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $this->sourceObject->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
					{
						if ($GLOBALS['configuration']['db_encoding'] == 1)
						{
							$value = POG_Base::IsColumn($fcv_array[$i][2]) ? "BASE64_DECODE(".$fcv_array[$i][2].")" : "'".$fcv_array[$i][2]."'";
							$sql .= "BASE64_DECODE(`".$fcv_array[$i][0]."`) ".$fcv_array[$i][1]." ".$value;
						}
						else
						{
							$value =  POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".POG_Base::Escape($fcv_array[$i][2])."'";
							$sql .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
						}
					}
					else
					{
						$value = POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$fcv_array[$i][2]."'";
						$sql .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
					}
				}
			}
		}


		$connection = Database::Connect();
		$cursor = Database::Reader($sql, $connection);
		while ($row = Database::Read($cursor))
		{
			$count = $row['mycount'];
		}
		return $count;
	}

	function SetupRender()
	{
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
			include_once("../objects/class.".strtolower($anyObject).".php");
			$anyObjectInstance = new $anyObject();
			$count = $anyObjectInstance->GetCount();

			$count2 = 0;
			$sql = 'select count(*) from `'.strtolower($anyObject).'`;';
			$connection = Database::Connect();
			$cursor = Database::Reader($sql, $connection);
			if ($cursor !== false)
			{
				while($row = Database::Read($cursor))
				{
					$count2 = $row['count(*)'];
				}
			}

			if ($count == $count2)
			{
				return true;
			}
			return false;

		}

		//test w/ arguments


	}
}
