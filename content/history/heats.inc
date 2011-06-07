<?php 
	$raceyear = new raceyear();
	if(isset($_GET["year"])){
		$raceyear = $raceyear->Get($_GET["year"]);
	}

	$racedaylist = $raceyear->GetRacedayList();
	
	$prelims = null;
	$finals = null;

	foreach($racedaylist as $raceday){
		$heatArr = array(
							"E"=>array(),
							"W"=>array(),
							"WRR"=>array(),
							"M"=>array(),
							"MRR"=>array()
						);
		$heatlist = $raceday->GetHeatList(null,"number");
		foreach($heatlist as $heat){
			switch($heat->raceclassId) {
				case 1:
					if($heat->isreroll==1){
						$heatArr["MRR"][]=$heat;	
					}else {
						$heatArr["M"][]=$heat;
					}
					break;
				case 2:
					if($heat->isreroll==1){
						$heatArr["WRR"][]=$heat;
					}else {
						$heatArr["W"][]=$heat;
					}
					break;
				case 3:
					$heatArr["E"][]=$heat;
					break;				
			}
		}
		if($raceday->isFinals){
			$finals = $heatArr;
		} else {
			$prelims = $heatArr;
		}
	}
	
	function heattr($heat){
		echo("<tr>");
		$teamlist = $heat->GetTeamList();
		foreach($teamlist as $team){
			$entry=$team->GetEntry();
			$org=$entry->GetOrg();
			echo("<td><a href=\"/history/team/".$entry->urlkey."\">".$org->shortname."</a></td>");
		}
		echo("</tr>");
	}	
?>

<ul class="tabs">
	<li><a id="t1" href="#prelims">Prelims</a></li>
	<?php if($finals){ ?>
	<li><a id="t2" href="#finals">Finals</a></li>
	<?php } ?>
</ul>


<div class="panes">
	<div class="pane">
		Women's
		<table class="data" summary="" >
		<?php
			foreach($prelims["W"] as $heat){
				heattr($heat);
			}
		?>
		</table>
		Men's
		<table class="data" summary="" >
		<?php
			foreach($prelims["M"] as $heat){
				heattr($heat);
			}
		?>
		</table>
	</div>
	<?php if($finals){ ?>
	<div class="pane">
		<? if($finals["E"]){ ?>
		Exhibitions
		<table class="data" summary="" >
		<?php
			foreach($finals["E"] as $heat){
				heattr($heat);
			}
		?>
		</table>
		<? } ?>
		<? if($finals["WRR"]){ ?>
		Women's Rerolls
		<table class="data" summary="" >
		<?php
			foreach($finals["WRR"] as $heat){
				heattr($heat);
			}
		?>
		</table>
		<? } ?>
		<? if($finals["W"]){ ?>
		Women's
		<table class="data" summary="" >
		<?php
			foreach($finals["W"] as $heat){
				heattr($heat);
			}
		?>
		</table>
		<? } ?>
		<? if($finals["MRR"]){ ?>
		Men's Rerolls
		<table class="data" summary="" >
		<?php
			foreach($finals["MRR"] as $heat){
				heattr($heat);
			}
		?>
		</table>
		<? } ?>
		<? if($finals["M"]){ ?>
		Men's
		<table class="data" summary="" >
		<?php
			foreach($finals["M"] as $heat){
				heattr($heat);
			}
		?>
		</table>
		<? } ?>
	</div>
	<?php } ?>
</div>