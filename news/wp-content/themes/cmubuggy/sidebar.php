<?php
/**
 * @package WordPress
 * @subpackage Toolbox
 */
?>
<!--
		<div id="secondary" class="widget-area">
			<ul class="xoxo">
			<?php if ( ! dynamic_sidebar( 'sidebar' ) ) : ?>

				<li id="search" class="widget-container widget_search">
					<?php get_search_form(); ?>
				</li>

				<li id="archives" class="widget-container">
					<h2 class="widget-title"><?php _e( 'Archives', 'themename' ); ?></h2>
					<ul>
						<?php wp_get_archives( array( 'type' => 'monthly' ) ); ?>
					</ul>
				</li>

				<li id="meta" class="widget-container">
					<h2 class="widget-title"><?php _e( 'Meta', 'themename' ); ?></h2>
					<ul>
						<?php wp_register(); ?>
						<li><?php wp_loginout(); ?></li>
						<?php wp_meta(); ?>
					</ul>
				</li>

			<?php endif; // end sidebar widget area ?>
			</ul>
		</div><!-- #secondary .widget-area 
		-->
		