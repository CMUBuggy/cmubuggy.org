<?php
	get_header();
?>
<div id="primary" class="col-12">
	<div id="container">
		<div id="content" role="main" class="entry-content">

			<?php the_post(); ?>
			<h1 class="entry-title"><?php the_title(); ?></h1>

			<div class="mb-3">
				<?php get_search_form(); ?>
			</div>

			<h2>Archives by Category</h2>
			<ul>
				<?php
					wp_list_categories(array(
						'orderby' => 'count',
						'order' => 'DESC',
						'show_count' => 'TRUE',
						'title_li' => '',
						'number' => 10,
					));
				?>
			</ul>

			<?php the_widget( 'WP_Widget_Tag_Cloud', array( 'title' => 'Archives by Tag' ), array( 'before_widget' => '', 'after_widget' => '' ) ); ?>

			<h2>Archives by Month</h2>
			<ul>
				<?php wp_get_archives('type=monthly'); ?>
			</ul>

		</div><!-- #content -->
	</div><!-- #container -->
</div>
<?php
	get_footer();
