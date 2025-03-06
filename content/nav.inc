<?php
  // Turn this on to enable the raceday menu and merge the About Buggy / About BAA menus
  // to make room for the additional menu.  Should be done roughly a week before raceday
  // when content is prepared.
  $RACEDAY_MENU_ACTIVE = false;

  // These arrays define the structure of the menubar.  We first define the about menus,
  // and then use array_push to assemble the final menu out of these parts, as well as
  // the state of $RACEDAY_MENU_ACTIVE.
  //
  // We use active_re at the top level as a regex for URIs that will trigger
  // that heading to be active.  This is because of awkwardness with how
  // we handle wordpress, and pages that don't sit comfortably in one section
  // such as /history/video
  //
  // Because these are all paths, we're going to use @ as the character to
  // surround the regex with instead of the typical use of /.
  //
  // "external" means to open the link in a _blank tab.
  $ABOUT_BUGGY_SUBMENU = [
    0 => (object) [
      'label' => 'Overview',
      'href' => '/reference',
    ],
    1 => (object) [
      'label' => 'Who is Involved',
      'children' => [
        0 => (object) [
          'label' => 'Sweepstakes Committee',
          'href' => '/reference/sweepstakes',
        ],
        1 => (object) [
          'label' => 'Buggy Teams',
          'href' => '/reference/teams',
        ],
      ],
    ],
    2 => (object) [
      'label' => 'About the Race',
      'children' => [
        0 => (object) [
          'label' => 'Buggy, the Vehicle',
          'href' => '/reference/buggy-the-vehicle',
        ],
        1 => (object) [
          'label' => 'Course',
          'href' => '/reference/course',
        ],
        2 => (object) [
          'label' => 'Safety',
          'href' => '/reference/safety',
        ],
        3 => (object) [
          'label' => 'Freerolls',
          'href' => '/reference/freerolls',
        ],
        4 => (object) [
          'label' => 'Spectating',
          'href' => '/reference/spectating',
        ],
        5 => (object) [
          'label' => 'Pushing Styles',
          'href' => '/reference/pushing-styles',
        ],
      ],
    ],
    3 => (object) [
      'divider' => true,
    ],
    4 => (object) [
      'label' => 'BAA Endowment Fund',
      'href' => '/reference/baa-endowment-fund',
    ],
    5 => (object) [
      'label' => 'Sweepstakes Rules',
      'href' => '/reference/sweepstakes-bylaws',
    ],
    6 => (object) [
      'label' => 'Team Resources',
      'children' => [
        0 => (object) [
          'label' => 'Starting a Team',
          'href' => '/reference/buggy-team-resources/new-team',
        ],
        1 => (object) [
          'label' => 'How To Build a Buggy',
          'href' => '/reference/buggy-team-resources/how-to-build-a-buggy',
        ],
        2 => (object) [
          'label' => 'Composites for Buggy',
          'href' => '/reference/buggy-team-resources/composites-for-buggy',
        ],
        3 => (object) [
          'label' => 'Other',
          'href' => '/reference/buggy-team-resources',
        ],
      ],
    ],
  ];

  $ABOUT_BAA_SUBMENU = [
    0 => (object) [
      'label' => 'Overview',
      'href' => '/about',
    ],
    1 => (object) [
      'label' => 'Leadership',
      'href' => '/about/people',
    ],
    2 => (object) [
      'label' => 'Get Involved',
      'href' => '/about/get-involved',
    ],
    3 => (object) [
      'label' => 'Accomplishments',
      'href' => '/about/accomplishments',
    ],
    4 => (object) [
      'label' => 'This Website',
      'href' => '/about/website',
    ],
    5 => (object) [
      'label' => 'Our Rules',
      'href' => '/about/our-rules',
    ],
  ];


  // The actual full menu
  $navItems = [];
  if ($RACEDAY_MENU_ACTIVE) {
    array_push($navItems, (object) [
      'label' => 'Raceday',
      'active_re' => '@^(/news)?/raceday@',
      'children' => [
        0 => (object) [
          'label' => 'Event Schedule',
          'href' => '/raceday',
        ],
        1 => (object) [
          'divider' => true,
        ],
        2 => (object) [
          'label' => 'Leaderboard',
          'href' => '/raceday/leaderboard',
        ],
        3 => (object) [
          'label' => 'Heat Schedule',
          'href' => '/raceday/heats',
        ],
        4 => (object) [
          'label' => 'Rosters',
          'href' => '/raceday/rosters',
        ],
        5 => (object) [
          'divider' => true,
        ],
        6 => (object) [
          'label' => 'Livestream',
          'href' => '/live',
          'external' => true
        ],
        7 => (object) [
          'label' => 'Chat',
          'href' => '/chat',
          'external' => true
        ],
      ],
    ]);
  }

  array_push ($navItems, (object) [
    'label' => 'News',
    // /news is the wordpress prefix and we'd rather highlight the correct
    // section even if we landed at an awkward /news-prefixed uri.
    //
    // Buggy history articles are particularly awkward.
    'active_re' => '@^/news(?!/(reference|about|history|gallery|membership|raceday|[0-9]{4}/[0-9]{2}/100-years-of-buggy-history))@',
    'children' => [
      0 => (object) [
        'label' => 'Recent',
        'href' => '/news',
      ],
      1 => (object) [
        'label' => 'Subscribe',
        'href' => 'https://groups.google.com/g/baa-news',
        'external' => true,
      ],
      2 => (object) [
        'divider' => true,
      ],
      // TODO: Dynamically generate category items? Note: This is a subset
      3 => (object) [
        'label' => 'Rolls Reports',
        'href' => '/news/category/rolls-reports/',
      ],
      4 => (object) [
        'label' => 'General Interest Buggy News',
        'href' => '/news/category/general-interest-buggy-stuff',
      ],
      5 => (object) [
        'label' => 'BAA News',
        'href' => '/news/category/buggy-alumni-association',
      ],
      6 => (object) [
        'label' => 'Sweepstakes News',
        'href' => '/news/category/sweepstakes-news',
      ],
      7 => (object) [
        'divider' => true,
      ],
      8 => (object) [
        'label' => 'Index',
        'href' => '/news/archives/',
      ],
    ],
    
  ]);

  // About Menus -- depends on RACEDAY_MENU_ACTIVE
  if ($RACEDAY_MENU_ACTIVE) {
    // Merge the menus, we need the space.
    array_push($navItems, (object) [
      'label' => 'About',
      'active_re' => '@^(/news)?/(reference|about)@',
      'children' => [
        0 => (object) [
          'label' => '...Buggy',
          'children' => $ABOUT_BUGGY_SUBMENU
        ],
        1 => (object) [
          'label' => '...the BAA',
          'children' => $ABOUT_BAA_SUBMENU
        ]
      ]
    ]);
  } else {
    array_push($navItems,
      (object) [
        'label' => 'About Buggy',
        'active_re' => '@^(/news)?/reference@',
        'children' => $ABOUT_BUGGY_SUBMENU
      ],
      (object) [
        'label' => 'About the BAA',
        'active_re' => '@^(/news)?/about@',
        'children' => $ABOUT_BAA_SUBMENU
      ]);
  }

  array_push($navItems, (object) [
      'label' => 'History',
      // All history pages _except_ video (which goes to gallery)
      //
      // OR the 100 years of history pages.
      'active_re' => '@^((/news)?/history(?!/video)|/news/[0-9]{4}/[0-9]{2}/100-years-of-buggy-history)@',
      'children' => [
        0 => (object) [
          'label' => 'Overview',
          'href' => '/history',
        ],
        1 => (object) [
          'label' => '100 Years of History',
          'href' => '/news/2019/09/100-years-of-buggy-history-intro-and-1920/'
        ],
        2 => (object) [
          'divider' => true,
        ],
        3 => (object) [
          'label' => 'Races',
          'href' => '/history/'.$RACEDAY_URL_PART,
        ],
        4 => (object) [
          'label' => 'Top Times',
          'href' => '/history/toptimes',
        ],
        5 => (object) [
          'label' => 'Awards',
          'href' => '/history/award',
        ],
        6 => (object) [
          'divider' => true,
        ],
        7 => (object) [
          'label' => 'Sweepstakes',
          'href' => '/history/sweepstakes',
        ],
        8 => (object) [
          'label' => 'Organizations',
          'href' => '/history/org',
        ],
        9 => (object) [
          'divider' => true,
        ],
        10 => (object) [
          'label' => 'Buggies',
          'href' => '/history/buggy',
        ],
        11 => (object) [
          'label' => 'People',
          'href' => '/history/person',
        ],
        12 => (object) [
          'divider' => true,
        ],
        13 => (object) [
          'label' => 'Buggy Books',
          'href' => '/history/buggybook',
        ],
        14 => (object) [
          'label' => 'Raceday Previews',
          'href' => '/news/history/raceday-previews',
        ],
        15 => (object) [
          'divider' => true,
        ],
        16 => (object) [
          'label' => 'BAA Leadership',
          'href' => '/history/baa',
        ],
      ],
    ],
    (object) [
      'label' => 'Gallery',
      // Really, just /history/video (/gallery doesn't exist)
      'active_re' => '@^((/news)?(/gallery|/history/video)|/video)@',
      'children' => [
        0 => (object) [
          'label' => 'Photos',
          'href' => 'https://cmubuggy.smugmug.com',
          'external' => true,
        ],
        1 => (object) [
          'label' => 'Videos',
          'href' => '/history/video',
        ],
      ],
    ],
    (object) [
      'label' => 'Membership',
      'href' => '/membership',
      'active_re' => '@^(/news)?/membership@',
    ]);

  // Created based on https://stackoverflow.com/a/45755948
  // Converted <ul>s to <div>s to avoid left indentation
  function createTopLevelNavItem($navItem) {
    $hasChildren = property_exists($navItem, 'children');

    $dropdownClass = $hasChildren ? 'dropdown' : '';
    echo("<li class='nav-item mx-1 {$dropdownClass}'>");

    $isActive = false;
    if (array_key_exists('REQUEST_URI', $_SERVER)) {
      $isActive = preg_match($navItem->active_re, $_SERVER['REQUEST_URI']);
    }

    if ($hasChildren) {
      createNavLink(
        $navItem,
        'nav-link dropdown-toggle',
        $isActive,
        'id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"'
      );
    } else {
      createNavLink($navItem, 'nav-link', $isActive);
    }

    if ($hasChildren) {
      createDropdownItems($navItem->children, true);
    }

    echo('</li>');
  }

  function createDropdownItems($dropdownItems, $isTopLevel = false) {
    $dropdownAria = $isTopLevel ? '' : 'aria-labelledby="navbarDropdownMenuLink"';
    echo("<div class=\"dropdown-menu\" {$dropdownAria}>");
      foreach($dropdownItems as $dropdownItem) {
        if (property_exists($dropdownItem, 'divider')) {
          echo('<div class="dropdown-divider"></div>');

        } else if (property_exists($dropdownItem, 'children')) {
          echo('<div class="dropdown-submenu">');

          // TODO: show active?
          createNavLink($dropdownItem, 'dropdown-item dropdown-toggle');
          createDropdownItems($dropdownItem->children);
          echo('</div>');

        } else {
          // TODO: show active?
          createNavLink($dropdownItem, 'dropdown-item');
        }
      }
    echo("</div>");
  }

  function createNavLink($dropdownItem, $class = '', $isActive = false, $attributes = '') {
    $href = property_exists($dropdownItem, 'href') && !property_exists($dropdownItem, 'children')
      ? "href=\"{$dropdownItem->href}\""
      : 'href="#"';
    $target = property_exists($dropdownItem, 'external') ? 'target="_blank"' : '';

    if ($isActive) {
      $class = $class . ' active';
    }

    echo("<a class=\"{$class}\" {$href} {$target} {$attributes}>");
    echo($dropdownItem->label);
    echo('</a>');
  }

/*
  Multi-level dropdown implementation from:
  https://stackoverflow.com/a/45755948
*/
?>
<ul class="navbar-nav">
  <?php foreach($navItems as $navItem) createTopLevelNavItem($navItem) ?>
</ul>


