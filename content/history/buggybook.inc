<?php

$FIRST_YEAR = 1965;
$LAST_YEAR = 2024;

// Years in the above range which lack a buggy book (e.g. covid)
$SKIP_YEARS = [2020, 2021];

$yearsByDecade = array();
for($year = $LAST_YEAR; $year >= $FIRST_YEAR; $year--) {
  if (in_array($year, $SKIP_YEARS)) {
    continue;
  }

  $decade = strval((int)(floor($year/10) * 10));

  if(array_key_exists($decade, $yearsByDecade)) {
    array_push($yearsByDecade[$decade], $year);
  } else {
    $yearsByDecade[$decade] = array($year);
  }
}

function displayBuggyBookLink($year) {
  echo("<div>
    <a href='/files/buggybooks/buggybook_".$year.".pdf'
      class='m-1'
      target='_blank\'
      onclick=\"_gaq.push(['_trackEvent','Download','PDF',this.href]);\">
      <img alt='".$year." buggy book'
        title='View a PDF of the ".$year." buggy book'
        class='img-thumbnail' style='max-height: 200px;'
        src='/files/buggybooks/thumb_200/buggybook_".$year.".pdf.jpg' />
    </a>
  </div>");
}
?>

<?php foreach($yearsByDecade as $decade => $years) {
  echo("<h3>".$decade."s</h3>");
  echo("<div class='d-flex flex-wrap justify-content-between mb-3' style='margin: -.25em; row-gap: 10px;'>");

  foreach($years as $year) {
    displayBuggyBookLink($year);
  }

  echo("</div>");
} ?>
