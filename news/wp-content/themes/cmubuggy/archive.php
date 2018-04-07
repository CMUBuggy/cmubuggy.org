<?php
/**
 * Template Name: Archive
 * @package WordPress
 * @subpackage Toolbox
 */

get_header(); ?>

<?php
  wp_nav_menu(
    array(
      'theme_location' => 'primary',
      'menu_class' => 'sf-menu',
      'container' => 'div',
      'container_id' => 'topnav'
    )
  );
?>

<div id="primary">
  <div id="container">
    <div id="content" role="main" class="entry-content">

      <?php the_post(); ?>
      <h1 class="entry-title"><?php the_title(); ?></h1>

      <?php get_search_form(); ?>
      <div class="clear"></div>

      <h2>Archives by Subject:</h2>
      <ul>
         <?php wp_list_categories(); ?>
      </ul>

      <h2>Archives by Month:</h2>
      <ul>
        <?php wp_get_archives('type=monthly'); ?>
      </ul>

    </div><!-- #content -->
  </div><!-- #container -->
</div>

<?php get_sidebar(); ?>
<?php get_footer(); ?>
