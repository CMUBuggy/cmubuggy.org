// How to use this:
//
// Create radio buttons on the page named "classFilter" with values
// of "ALL" and then one for each CSS class name of the buggy class
// rows (e.g. "mensRow", "womensRow", etc.)
//
// In the table, tag every _row_ with the "classRow" class, as well
// as the appropriate CSS class for the buggy classes from above.
// Obviously, the header row will lack any CSS class.
//
// If you are parity-coloring the table using table-parity-color, and you
// need that to be removed on the filtered views, also tag those rows
// with table-parity so it can be disabled/enabled when the views change.
//
// Finally, if you have a buggy class column that you wish to hide,
// tag all that column's _cells_, as well as the header cell, with the
// "classCol" CSS class.

$("input[type=radio][name=classFilter]").on("change", function() {
  if (this.value == "ALL") {
    $(".classRow,.classCol").show();
    $(".classRow.year-parity").addClass("table-parity-color");
  } else {
    $(".classRow,.classCol").hide();
    $(".classRow.year-parity").removeClass("table-parity-color");
    $("."+this.value).show();
  }
})
