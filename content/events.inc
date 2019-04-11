<?php

  $events = array(
      array(
        "Monday, Apr 8 @ 9am",
        "Online",
        "Lead Truck Auction Opens!",
        array(
          "Bid online on your favorite preliminary heats for your chance at the best buggy viewing experience!",
          "Go to our <a href=\"/auction\">auction site</a> for how to bid on finals heats."
        )
      ),
      array(
        "Tuesday, Apr 9 @ noon",
        "Email",
        "Raceday Preview Release",
        array(
          "All members will find the much anticipated Raceday Preview in their inboxes. Make sure you've <a href=\"https://securelb.imodules.com/s/1410/giving/form-social.aspx?sid=1410&gid=1&pgid=382&cid=990&appealcode=A3291&dids=98\">renewed your membership</a> TODAY!"
        )
      ),
      array(
        "Wednesday, Apr 10 @ 8&ndash;9pm",
        "<a href=\"http://www.wrct.org\">WRCT</a>",
        "WRCT Pre-Broadcast",
        array(
          "Tune in to hear current students and locals share their predictions for this year's races, listen locally on 88.3 fm or online via&nbsp;<a href=\"http://www.wrct.org/\">wrct.org</a>",
          "Speakers will be announced soon!"
        )
      ),
      array(
        "Wednesday, Apr 10 @ 10pm",
        "Online",
        "Lead Truck Auction Prelims Closes!",
        array(
          "Online bidding for all races will close, so make sure you keep an eye on any you don't want to miss!",
          "Bidding for the Finals races will conclude Friday evening once we know the matchups."
        )
      ),
      array(
        "Thursday, Apr 11 @ noon&ndash;2pm",
        "Weigand Gymnasium, CUC",
        "Sweepstakes Design Showcase",
        array(
          "Come view the current and latest buggy designs and talk with the teams. Plus, kids 12 and under can build and race their own LEGO&reg; buggy on our custom-built track!"
        )
      ),
      array(
        "Thursday, Apr 11 @ 12:30&ndash;1:30pm",
        "Weigand Gymnasium (Stage), CUC",
        "BAA Student & Alumni Panel",
        array(
          "If you're around on Thursday, swing by the Design Showcase and join us for a rousing panel discussion comparing stories between students and alumni."
        )
      ),
      array(
        "Thursday, Apr 11 @ 7-9pm",
        "Fuel &amp; Fuddle (212 Oakland Ave)",
        "BAA Welcome Back",
        array(
          'Join the BAA for a casual "welcome back to Pittsburgh" event to kick-start the weekend. Reminisce at Fuel &amp; Fuddle in Oakland about buggy days and debate who will be the lead contenders this year.'
        )
      ),
      array(
        "Friday, Apr 12 @ 8am&ndash;12:30pm",
        "Buggy Course (Tech-Schenley-Frew)",
        "Preliminary Races &amp; Lead Truck Rides",
        array(
          "The 99th anniversary of the races kicks off at 8am EDT! Join us live on the buggy course, or online <a href=\"https://cmubuggy.org/live\">here</a>!"
        )
      ),
      array(
        "Friday, Apr 12 @ 1:30&ndash;3pm",
        "Midway Reunion Tent",
        "History Of Buggy: Showcasing Reunion Years",
        array(
          "Come relive the excitement of Buggy with Buggy Alumni Association archivist and guru Tom Wood (E 1974), featuring Reunion years 1969, 1994, 2009, 2014 and 2018. Vintage buggies on display."
        )
      ),
      array(
        "Friday, Apr 12 @ 7&ndash;10pm",
        "Hough's Taproom (563 Greenfield Ave)",
        "Buggy Recap &amp; In-Person Finals Auction",
        array(
          "Join the Buggy Alumni Association at Hough's Taproom for some spirited discussions about the preliminary races and bid in-person for the live Lead Truck Auction!"
        )
      ),
      array(
        "Saturday, Apr 13 @ 8am&ndash;12:30pm",
        "Buggy Course (Flagstaff Hill)",
        "Exhibition and Finals Races &amp; Lead Truck Rides",
        array(
          "This is the main event! Join us live on the course as races kick off at 8am EST starting with some exhibition heats include the Reunion Race, and the first ever Staff &amp; Faculty CIT vs MCS!",
          "As always, CMUtv will be <a href=\"https://cmubuggy.org/live\">streaming the races</a>."
        )
      ),
      array(
        "Saturday, Apr 13 @ 4pm",
        "Midway Stage (The Cut)",
        "Spring Carnival Booth &amp; Sweepstakes Awards Ceremony",
        array(
          "Cheer on your team as all awards and trophies are handed out and join in the celebration!",
          "Rain location: McConomy Auditorium, 1st Floor, CUC"
        )
      )
  );

?>
<h1>Carnival 2019 BAA Event Schedule</h1>

<?php
  $eventsLength = count($events);
  for ($idx = 0; $idx < $eventsLength; $idx++) {
    $event = $events[$idx];
    echo '<div class="card mb-3">';
    echo '<div class="card-body">';
    echo '<h5 class="card-title">' . $event[2] . '</h5>';
    echo '<h6 class="card-subtitle mb-2 text-muted"> ' . $event[1] . ' - ' . $event[0] . '</h6>';
    for ($idx2 = 0; $idx2 < count($event[3]); $idx2++ ) {
      echo '<p class="card-text">' . $event[3][$idx2] . '</p>';
    }
    echo '</div>';
    echo '</div>';
  }
?>
