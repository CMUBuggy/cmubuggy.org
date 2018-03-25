<?php
  $dataedit = new dataedit();
  $editList = $dataedit->GetList(null,"timestamp",FALSE);
?>

<div class="table-responsive">
  <table class="table">
    <thead>
      <tr>
        <th>Type</th>
        <th>Object</th>
        <th>Attribute</th>
        <th>ID</th>
        <th>Old Value</th>
        <th>New Value</th>
        <th>Time</th>
        <th>User</th>
      </tr>
    </thead>
    <tbody>
      <?php
        foreach($editList as $edit){
          $user = $edit->GetUser();
          echo("<tr>");
          echo("<td>".$edit->edittype."</td>");
          echo("<td>".$edit->objtype."</td>");
          echo("<td>".$edit->objattr."</td>");
          echo("<td>".$edit->objid."</td>");
          echo("<td>".$edit->oldvalue."</td>");
          echo("<td>".$edit->newvalue."</td>");
          echo("<td class=\"text-nowrap\">".strftime("%m/%d/%y %X",$edit->timestamp)."</td>");
          echo("<td>".$user->username."</td>");
          echo("</tr>");
        }
      ?>
    </tbody>
  </table>
</div>
