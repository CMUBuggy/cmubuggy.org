<?php
// Disable the admin bar, which overlaps our own nav bar.
add_filter( 'show_admin_bar', '__return_false' );

// Force exact matching instead of prefix matching for /news/... URLs.
add_filter('strict_redirect_guess_404_permalink', '__return_true');

// Yoast Duplicate Post and Discord Webhook Plugins fight eachother.  Stop that.
function clear_webhook_on_duplicate( $meta_excludelist ) {
    return array_merge( $meta_excludelist, [ '_discord_webhook_published' ] );
}
add_filter('duplicate_post_excludelist_filter', 'clear_webhook_on_duplicate');

// Add our CSS scripts.
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


add_filter( 'oembed_response_data', 'cmubuggy_oembed_cleanup' );
function cmubuggy_oembed_cleanup( $data ) {
  unset($data['author_url']);
  unset($data['author_name']);
  return $data;
}

?>
