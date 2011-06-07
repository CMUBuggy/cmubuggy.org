<?php
/**
 * @package WordPress
 * @subpackage Toolbox
 */

get_header(); ?>
	<div id="topnav">
		<ul class="sf-menu">
			<li><a href="#">Categories</a>
				<ul>
					<?php wp_list_cats('sort_column=name&optioncount=0&hierarchical=0'); ?>
				</ul>
			</li>
			<li><a href="#">Archives</a>
				<ul>
					<?php wp_get_archives('type=monthly'); ?>
				</ul>
			</li>
		</ul>
	</div>
		<div id="primary">
			<div id="content">

				<?php the_post(); ?>

				<h2 class="page-title">
				<?php if ( is_day() ) : ?>
					<?php printf( __( 'Daily Archives: <span>%s</span>', 'themename' ), get_the_date() ); ?>
				<?php elseif ( is_month() ) : ?>
					<?php printf( __( 'Monthly Archives: <span>%s</span>', 'themename' ), get_the_date( 'F Y' ) ); ?>
				<?php elseif ( is_year() ) : ?>
					<?php printf( __( 'Yearly Archives: <span>%s</span>', 'themename' ), get_the_date( 'Y' ) ); ?>
				<?php else : ?>
					<?php _e( 'Blog Archives', 'themename' ); ?>
				<?php endif; ?>
				</h2>

				<?php rewind_posts(); ?>

				<?php get_template_part( 'loop', 'archive' ); ?>

			</div><!-- #content -->
		</div><!-- #primary -->

<?php get_sidebar(); ?>
<?php get_footer(); ?>