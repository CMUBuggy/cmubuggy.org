<?php
	include_once('../util.inc');
	include_once('../lib/pog/pog_includes.inc');
	$headline = 'News';
?>
<!doctype html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<title>News | <?php the_title(); ?></title>

	<meta property="og:title" content="<?php the_title(); ?>"/>
	<meta property="og:type" content="article" />
	<meta property="og:site_name" content="CMU Buggy Alumni Association"/>
	<meta property="og:url" content="<?php the_permalink(); ?>"/>
	<meta property="og:description" content="Breaking buggy news and rolls reports from the Buggy Alumni Association"/>
	<meta property="fb:admins" content="swiftsam"/>
	<meta property="fb:app_id" content="150469765045743"/>

	<?php include_once('../content/cssjs.inc'); ?>
	<?php if (is_admin_bar_showing()) { ?>
		<style>
			:root { --wp-margin: 32px }
			@media screen and (max-width: 782px) { :root { --wp-margin: 46px; } }
			@media screen and (max-width: 600px) { #masthead { position: sticky; margin-top: -4.5rem; top: 0; } }
		</style>
	<?php } ?>

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
			'fallback_cb' => 'wp_bootstrap_navwalker::fallback',
			'walker' => new wp_bootstrap_navwalker()
		)
	);
?>
<?php if ( ! is_page_template( 'blank-page.php' ) && ! is_page_template( 'blank-page-with-container.php' )) { ?>
	<div class="row">
<?php
	}
