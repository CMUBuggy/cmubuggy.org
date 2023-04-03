<?php
  $query = "SELECT b.buggyid, b.birthyear, o.shortname AS org, b.orgid,
                   b.name, b.buggyid, b.note AS note,
                   b.formerly AS formerid, fb.name AS fname,
                   fo.orgid AS forgid, fo.shortname AS forg
            FROM hist_buggies b
            LEFT JOIN hist_orgs o ON o.orgid = b.orgid
            LEFT JOIN hist_buggies fb ON b.formerly = fb.buggyid
            LEFT JOIN hist_orgs fo ON fo.orgid = fb.orgid
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
        echo("<tr><td>".$buggy["birthyear"]."</td>\n");
        echo("<td><a href=\"/history/org/".$buggy["orgid"]."\">".$buggy["org"]."</a></td>");
        echo("<td><a href=\"/history/buggy/".$buggy["buggyid"]."\">".$buggy["name"]."</a></td>\n");

        // Notes field also gets a bonus note if there is a "formerly" known as buggy.
        //
        // We add a period if there is no obvious ending punctuation on the note already
        // and there is a "former" buggy.
        echo("<td>");
        $punctuation = "";

        if (!empty($buggy["note"])) {
          echo($buggy["note"]);

          $lastchar = substr($buggy["note"], -1);
          if (!in_array($lastchar, [".","?","!",";",","])) {
            $punctuation = ".  ";
          }
        }
        if (!empty($buggy["fname"] && !empty($buggy["forg"]))) {
          echo($punctuation."Formerly ".$buggy["forg"]."'s ".$buggy["fname"]);
        }
        echo("</td></tr>\n");
      }
      ?>
    </tbody>
  </table>
</div>
