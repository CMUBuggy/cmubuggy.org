<?php
  $query = "SELECT buggyid, birthyear, shortname AS org, b.orgid, name, buggyid, b.note AS note FROM hist_buggies b
            LEFT JOIN hist_orgs o ON o.orgid = b.orgid
            ORDER BY birthyear DESC, name ASC;";
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
        echo("<tr><td>".$buggy["birthyear"]."</td>");
        echo("<td><a href=\"/history/org/".$buggy["orgid"]."\">".$buggy["org"]."</a></td>");
        echo("<td><a href=\"/history/buggy/".$buggy["buggyid"]."\">".$buggy["name"]."</a></td>");
        echo("<td>".$buggy["note"]."</td></tr>");
      }
      ?>
    </tbody>
  </table>
</div>
