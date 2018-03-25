<?php
  $buggy = new buggy();
  $buggyList = $buggy->GetList(null,"yearBuilt",FALSE);
?>
<h1>Buggies</h1>

<div class="table-responsive">
  <table class="table">
    <thead>
      <tr class="text-nowrap">
        <th>Year Built</th>
        <th>Organization</th>
        <th>Name</th>
      </tr>
    </thead>
    <tbody>
      <?php
      foreach($buggyList as $buggy){
        $year = $buggy->yearBuilt;
        if(!($year > 0)){
          $year = "";
        }
        echo("<tr><td>".$year."</td><td>".$buggy->GetOrg()->shortname."</td><td><a href=\"/history/buggy/".$buggy->urlKey."\">".$buggy->name."</a></td></tr>");
      }
      ?>
    </tbody>
  </table>
</div>
