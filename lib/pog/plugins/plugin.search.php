<?php
class Search extends POG_Base implements POG_Plugin
{
	private $query;
	private $limit='';
	private $lazyLoad;
	private $columnsToSearch='';
	private $version = "1.0";
	private $sourceObject;
	private $argv;

	function Version()
	{
		return $this->version;
	}

	function Search($sourceObject,$argv)
	{
		$this->sourceObject = $sourceObject;
		$this->argv = $argv;
		@$this->query = $argv[0];
		@$this->columnsToSearch = $argv[1];
		@$this->limit = $argv[2];
	}

	function Describe()
	{
		return "This plugin performs a full text search against a particular table. Note that the table needs to have full text indexes enabled. You will need to alter the tables manually
		Alter table <object> add fulltext searching(<attribute1>, <attribute2>)";
	}

	function Execute()
	{
		if ($this->columnsToSearch == '')
		{
			//match against all columns
			$columns = $this->GetAttributes($this->sourceObject,'TEXT');
			$match = strtolower(trim(implode(',', $columns)));
		}
		else
		{
			$match = strtolower(trim(implode(',', $this->columnsToSearch)));
		}
		$sql = "select * from ".strtolower(get_class($this->sourceObject))." where match (".$match.") against ('$this->query');";
		if ($this->limit)
		{
			$sql .= "limit $this->limit";
		}

		return $this->FetchObjects($sql, get_class($this->sourceObject));
	}

	function SetupRender()
	{

		if (isset($_POST['install_search']))
		{
			$this->SetupExecute();

		}
		else
		{
			$connection = Database::Connect();
			$out = 'Select Tables that will support Full Text Search. Setup will alter the tables by creating full text search indexes for selected tables. You can also unselect tables and Setup will remove the indexes.<br /><br />';
			$objectList = unserialize($_SESSION['objectNameList']);
			$out .= '<form type="post">';
			$out .= "<select multiple='multiple' size='' name='objects[]' style='min-width:250px;min-height:100px;'>";
			foreach ($objectList as $object)
			{
				$count = 0;
				$sql = 'show index from `'.strtolower($object).'` where Key_name = "searching"';
				$cursor = Database::Reader($sql,$connection);
				while ($row = Database::Read($cursor))
				{
					$count++;
				}
				$out .= "<option ".($count > 0 ? "selected" : "").">".$object."</option>";
			}
			$out .= "</select><br /><br />";
			$out .= '<input type="submit"value="Save" name="install_search"/>';
			$out .= '</form>';
			echo $out;
		}



	}

	function SetupExecute()
	{
		$objectList = unserialize($_SESSION['objectNameList']);

		//remove all indexes
		$connection = Database::Connect();

		foreach ($objectList as $object)
		{
			$sql = 'Alter table `'.strtolower($object).'` drop index `searching`';
			Database::NonQuery($sql,$connection);
		}


		if (isset($_POST['objects'])){
			$toAdd = $_POST['objects'];
			foreach ($toAdd as $add){
				$add_lower = strtolower($add);
				$sql = 'alter table `'.$add_lower.'` add fulltext searching(';
				include("../objects/class.{$add_lower}.php");
				$add = new $add();
				foreach ($add->pog_attribute_type as $dbatt => $array){
					if ($array['db_attributes'][0] == 'TEXT'){
						$sql .= '`'.$dbatt.'`,';
					}
				}
				$sql = trim($sql, ',');
				$sql .=')';
				Database::NonQuery($sql,$connection);
			}
			unset($_POST['install_search']);
		}


		$_POST['install_search'] = null;
		$this->SetupRender();
		$_POST['objects'] = null;

	}

	function AuthorPage(){

	}
}
