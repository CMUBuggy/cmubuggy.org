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

				<h2 class="page-title"><?php
					printf( __( 'Category Archives: %s', 'themename' ), '<span>' . single_cat_title( '', false ) . '</span>' );
				?></h2>

				<?php $categorydesc = category_description(); if ( ! empty( $categorydesc ) ) echo apply_filters( 'archive_meta', '<div class="archive-meta">' . $categorydesc . '</div>' ); ?>

				<?php get_template_part( 'loop', 'category' ); ?>

			</div><!-- #content -->
		</div><!-- #primary -->

<?php get_sidebar(); ?>
<?php get_footer(); ?>