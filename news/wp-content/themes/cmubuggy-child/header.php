<?php
	include_once('../util.inc');
?>
<!doctype html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<title><?php the_title(); ?> | CMU Buggy Alumni Association</title>

	<meta property="og:title" content="<?php the_title(); ?>"/>
	<meta property="og:type" content="article" />
	<meta property="og:site_name" content="CMU Buggy Alumni Association"/>
	<meta property="og:url" content="<?php the_permalink(); ?>"/>
	<meta property="og:description" content="Breaking buggy news and rolls reports from the Buggy Alumni Association"/>

	<?php include_once('../content/cssjs.inc'); ?>
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
