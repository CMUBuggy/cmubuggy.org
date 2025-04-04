<?php
/**
 * The template for displaying 404 pages (not found)
 *
 * @link https://codex.wordpress.org/Creating_an_Error_404_Page
 *
 * @package WP_Bootstrap_Starter
 */

get_header(); ?>

	<section id="primary" class="content-area col-sm-12<?php if ( is_active_sidebar( 'sidebar-1' ) ) { echo ' col-lg-8'; } ?>">
		<main id="main" class="site-main" role="main">

			<section class="error-404 not-found">
                           <div class="row">
                           <div class="col-sm-3">
                             <img src="/img/tool-schenley-right.png" class="img-fluid">
                           </div>
                           <div class="col-sm-9">
                             <header class="page-header">
				<h1 class="page-title"><?php esc_html_e( 'Oops! That page can&rsquo;t be found.', 'wp-bootstrap-starter' ); ?></h1>
                             </header><!-- .page-header -->

			     <div class="page-content">
					<p><?php esc_html_e( 'It looks like nothing was found at this location. Maybe try one of the links below or a search?', 'wp-bootstrap-starter' ); ?></p>
					<?php
						get_search_form();
					?>
			     </div><!-- .page-content -->
                           </div></div><!-- col-9, row -->
			</section><!-- .error-404 -->

		</main><!-- #main -->
	</section><!-- #primary -->

<?php
get_sidebar();
get_footer();
