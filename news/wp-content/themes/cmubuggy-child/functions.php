<?php
function buggy_theme_enqueue_scripts() {
	wp_enqueue_style( 'cmubuggy',
		get_stylesheet_directory_uri() . '/style.css',
		wp_get_theme()->get('Version')
	);
}
add_action( 'wp_enqueue_scripts', 'buggy_theme_enqueue_scripts', 11 );

function remove_parent_styles() {
	remove_action( 'wp_enqueue_scripts', 'wp_bootstrap_starter_scripts' );
}
add_action( 'init', 'remove_parent_styles' );
?>
