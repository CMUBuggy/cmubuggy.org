<?php
  // We use active_re at the top level as a regex for URIs that will trigger
  // that heading to be active.  This is because of awkwardness with how
  // we handle wordpress, and pages that don't sit comfortably in one section
  // such as /history/video
  //
  // Because these are all paths, we're going to use @ as the character to
  // surround the regex with.
  $navItems = [
    0 => (object) [
      'label' => 'News',
      'href' => '/news',
      // /news is the wordpress prefix and we'd rather highlight the correct
      // section even if we landed at an awkward /news-prefixed uri.
      'active_re' => '@^/news(?!/(reference|about|history|gallery|membership))@'
    ],
    1 => (object) [
      'label' => 'About Buggy',
      'href' => '/reference',
      'active_re' => '@^(/news)?/reference@',
      'children' => [
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
          'label' => 'Starting a Team',
          'href' => '/reference/new-team',
        ],
        6 => (object) [
          'label' => 'How To Build a Buggy',
          'href' => '/reference/how-to-build-a-buggy',
        ],
        7 => (object) [
          'label' => 'Sweepstakes Bylaws',
          'href' => '/reference/sweepstakes-bylaws',
        ],
      ]
    ],
    2 => (object) [
      'label' => 'About the BAA',
      'href' => '/about',
      'active_re' => '@^(/news)?/about@',
      'children' => [
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
          'label' => 'Code of Conduct',
          'href' => '/about/code-of-conduct',
        ],
      ],
    ],
    3 => (object) [
      'label' => 'History',
      'href' => '/history',
      // All history pages _except_ video.
      'active_re' => '@^(/news)?/history(?!/video)@',
      'children' => [
        0 => (object) [
          'label' => 'Overview',
          'href' => '/history',
        ],
        1 => (object) [
          'divider' => true,
        ],
        2 => (object) [
          'label' => 'Races',
          'href' => '/history/raceday',
        ],
        3 => (object) [
          'label' => 'Top Times',
          'href' => '/history/toptimes',
        ],
        4 => (object) [
          'label' => 'Awards',
          'href' => '/history/award',
        ],
        5 => (object) [
          'divider' => true,
        ],
        6 => (object) [
          'label' => 'Sweepstakes',
          'href' => '/history/sweepstakes',
        ],
        7 => (object) [
          'label' => 'Organizations',
          'href' => '/history/org',
        ],
        8 => (object) [
          'divider' => true,
        ],
        9 => (object) [
          'label' => 'Buggies',
          'href' => '/history/buggy',
        ],
        10 => (object) [
          'label' => 'Buggy Books',
          'href' => '/history/buggybook',
        ],
        11 => (object) [
          'label' => 'People',
          'href' => '/history/person',
        ],
      ],
    ],
    4 => (object) [
      'label' => 'Gallery',
      'href' => '/gallery',
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
    5 => (object) [
      'label' => 'Membership',
      'href' => '/membership',
      'active_re' => '@^(/news)?/membership@',
    ],
  ];

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
?>

<!--
  Multi-level dropdown implementation from:
  https://stackoverflow.com/a/45755948
 -->
<ul class="navbar-nav <?php echo("$nav_class"); ?>">
  <?php foreach($navItems as $navItem) createTopLevelNavItem($navItem) ?>
</ul>


