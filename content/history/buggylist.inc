<?php
  $query = "SELECT buggyid, birthyear, shortname AS org, name, buggyid, b.note AS note FROM hist_buggies b
            LEFT JOIN hist_orgs o ON o.orgid = b.orgid
            ORDER BY birthyear DESC;";
  $buggies = dbQuery($HISTORY_DATABASE, $query);
?>
<h1>Buggies</h1>

<div class="table-responsive">
  <table class="table">
    <thead>
      <tr class="text-nowrap">
        <th>Year Built</th>
        <th>Organization</th>
        <th>Name</th>
        <th>Notes</th>
      </tr>
    </thead>
    <tbody>
      <?php
      while ($buggy = $buggies->fetch_assoc()) {
        echo("<tr><td>".$buggy["birthyear"]."</td><td>".$buggy["org"]."</td>");
        echo("<td><a href=\"/history/buggy/".$buggy["buggyid"]."\">".$buggy["name"]."</a></td>");
        echo("<td>".$buggy["note"]."</td></tr>");
      }
      ?>
    </tbody>
  </table>
</div>
