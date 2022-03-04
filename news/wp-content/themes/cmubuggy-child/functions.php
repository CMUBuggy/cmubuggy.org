<?php
// Force exact matching instead of prefix matching for /news/... URLs.
add_filter('strict_redirect_guess_404_permalink', '__return_true');

function buggy_theme_enqueue_scripts() {
	// Note: The "Clear Cache For Me" plugin usurps the versioning control
	// here, so in order to cachebust a new CSS version, you will need to click the
	// clear cache button on the wordpress dashboard.
	wp_enqueue_style( 'cmubuggy',
		get_stylesheet_directory_uri() . '/style.css',
		array(),
		wp_get_theme()->get('Version')
	);
}
add_action( 'wp_enqueue_scripts', 'buggy_theme_enqueue_scripts', 11 );

function remove_parent_styles() {
	remove_action( 'wp_enqueue_scripts', 'wp_bootstrap_starter_scripts' );
}
add_action( 'init', 'remove_parent_styles' );
?>
