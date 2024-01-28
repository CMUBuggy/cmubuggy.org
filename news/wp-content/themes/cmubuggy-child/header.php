<?php
	include_once('../util.inc');

  $SHOW_BREADCRUMBS = true;
  if (!defined($BREADCRUMB_LIST) || count($BREADCRUMB_LIST) == 0) {
	// If someone has set something up before header.php is called, keep using that.
	$BREADCRUMB_LIST = [["/", "Home"]];  // List of breadcrumb (url, text) pairs.
  }

  // Determine our title tag for cssjs.inc & title/breadcrumbs for pre-content.inc
  $BASE_TITLE = "BAA News";
  if ( is_page() ) {
    // Page -- Find all parents for breadcrumbs.
    $BASE_TITLE = esc_attr(wp_strip_all_tags(get_the_title()));
    $MORE_CRUMBS = [];
    $parent = get_post_parent();
    while ($parent != null) {
      $title = esc_attr(wp_strip_all_tags(get_the_title($parent)));
      $url = get_permalink($parent);
      array_unshift($MORE_CRUMBS, [$url, $title]);
      $parent = get_post_parent($parent);
    }
    $BREADCRUMB_LIST = array_merge($BREADCRUMB_LIST, $MORE_CRUMBS);
  } else if ( is_singular() ) {
    // Single Post (but not a page)
    // Always a "news" breadcrumb.
    $BASE_TITLE = esc_attr(wp_strip_all_tags(get_the_title()));
    array_push($BREADCRUMB_LIST, ["/news", "News"]);
  } else {
    // Multiple posts on one page.
    //
    // Has a special archive title.
    // If this is the top level home page, no breadcrumbs.  Otherwise "News"
    $BASE_TITLE = "News ".esc_attr(wp_strip_all_tags(get_the_archive_title()));
    if (!is_home()) {
      array_push($BREADCRUMB_LIST, ["/news", "News"]);
    }
  }
  $TITLE_TAG = $BASE_TITLE." | CMU Buggy Alumni Association";
?>
<!doctype html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
	<meta property="og:type" content="article" />
	<meta property="og:site_name" content="CMU Buggy Alumni Association"/>
	<meta property="og:url" content="<?php the_permalink(); ?>"/>

<?php
// Grab excerpt of the post if this is a single post page, otherwise use something
// appropriately generic.
if ( is_singular() ) {
  echo "\t".'<meta property="og:title" content="',esc_attr(wp_strip_all_tags(get_the_title())),'"/>'."\n";
  echo "\t".'<meta property="og:description" content="',esc_attr(wp_strip_all_tags(get_the_excerpt())),'"/>';
} else {
  echo "\t".'<meta property="og:title" content="',esc_attr(wp_strip_all_tags(get_the_archive_title())), esc_attr(wp_strip_all_tags(get_the_archive_description())),'"/>'."\n";
  echo "\t".'<meta property="og:description" content="Breaking buggy news and rolls reports from the Buggy Alumni Association"/>';
}
?>

	<?php
	  // Pull in the main site's CSS and JS.
	  // This also provides the <title> tag via the contents of the TITLE_TAG variable.
	  include_once('../content/cssjs.inc');
	?>
	<style>
		:root { --wp-margin: 0px; }
		#masthead { top: var(--wp-margin); }
		@supports ((postition: -webkit-sticky) or (position: sticky)) {
			#navigation {
				top: 3.5rem;
				top: calc(3.5rem + var(--wp-margin));
				max-height: calc(100vh - 3.5rem);
			}
			@media (min-width: 992px) {
				#navigation {
					top: 4.5rem;
					top: calc(4.5rem + var(--wp-margin));
					max-height: calc(100vh - 4.5rem);
				}
			}
		}
		<?php if (is_admin_bar_showing()) { ?>
			:root { --wp-margin: 32px }
			@media screen and (max-width: 782px) { :root { --wp-margin: 46px; } }
			@media screen and (max-width: 600px) { #masthead { position: sticky; margin-top: -4.5rem; top: 0; } }
		<?php } ?>
	</style>

	<?php wp_head(); ?>
</head>
<?php
	include_once('../content/pre-content.inc');

	wp_nav_menu(
		array(
			'theme_location' => 'primary',
			'menu_class' => 'navbar-nav flex-wrap',
			'menu_id' => false,
			'container' => 'nav',
			'container_class' => 'navbar navbar-light navbar-expand bg-light mb-3',
			'container_id' => false,
			'fallback_cb' => '',
			'walker' => new wp_bootstrap_navwalker()
		)
	);
?>
<?php if ( ! is_page_template( 'blank-page.php' ) && ! is_page_template( 'blank-page-with-container.php' )) { ?>
	<div class="row">
<?php
	}
