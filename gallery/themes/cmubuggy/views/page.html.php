<?php defined("SYSPATH") or die("No direct script access.") ?>
<?php include_once("../util.inc");?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
          "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" <?= $theme->html_attributes() ?> xml:lang="en" lang="en">
  <head>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8" />
    <? $theme->start_combining("script,css") ?>
    <title>
      <? if ($page_title): ?>
        <?= $page_title ?>
      <? else: ?>
        <? if ($theme->item()): ?>
          <?= $theme->item()->title ?>
        <? elseif ($theme->tag()): ?>
          <?= t("Photos tagged with %tag_title", array("tag_title" => $theme->tag()->name)) ?>
        <? else: /* Not an item, not a tag, no page_title specified.  Help! */ ?>
          <?= item::root()->title ?>
        <? endif ?>
      <? endif ?> | CMU Buggy Alumni Association
    </title>
    <link rel="shortcut icon"
          href="<?= url::file(module::get_var("gallery", "favicon_url")) ?>"
          type="image/x-icon" />

    <? if ($theme->page_type == "collection"): ?>
      <? if ($thumb_proportion != 1): ?>
        <? $new_width = round($thumb_proportion * 213) ?>
        <? $new_height = round($thumb_proportion * 240) ?>
        <style type="text/css">
        .g-view #g-content #g-album-grid .g-item {
          width: <?= $new_width ?>px;
          height: <?= $new_height ?>px;
          /* <?= $thumb_proportion ?> */
        }
        </style>
      <? endif ?>
    <? endif ?>

    <?= $theme->script("json2-min.js") ?>
    <?= $theme->script("jquery.js") ?>
    <?= $theme->script("jquery.form.js") ?>
    <?= $theme->script("jquery-ui.js") ?>
    <?= $theme->script("gallery.common.js") ?>
    <? /* MSG_CANCEL is required by gallery.dialog.js */ ?>
    <script type="text/javascript">
    var MSG_CANCEL = <?= t('Cancel')->for_js() ?>;
    </script>
    <?= $theme->script("gallery.ajax.js") ?>
    <?= $theme->script("gallery.dialog.js") ?>
    <?= $theme->script("superfish/js/superfish.js") ?>
    <?= $theme->script("jquery.localscroll.js") ?>

    <? /* These are page specific but they get combined */ ?>
    <? if ($theme->page_subtype == "photo"): ?>
    <?= $theme->script("jquery.scrollTo.js") ?>
    <?= $theme->script("gallery.show_full_size.js") ?>
    <? elseif ($theme->page_subtype == "movie"): ?>
    <?= $theme->script("flowplayer.js") ?>
    <? endif ?>

    <?= $theme->head() ?>

    <? /* Theme specific CSS/JS goes last so that it can override module CSS/JS */ ?>
    <?= $theme->script("ui.init.js") ?>
    <? //$theme->css("yui/reset-fonts-grids.css") ?>
    <? //$theme->css("superfish/css/superfish.css")?>
    <?= $theme->css("themeroller/ui.base.css") ?>
    <?= $theme->css("screen.css") ?>
    <!--[if lte IE 8]>
    <link rel="stylesheet" type="text/css" href="<?= $theme->url("css/fix-ie.css") ?>"
          media="screen,print,projection" />
    <![endif]-->

    <!-- LOOKING FOR YOUR JAVASCRIPT? It's all been combined into the link below -->
    <?= $theme->get_combined("script") ?>
    <!--<script type="text/javascript" src="/js/jquery.infieldlabel.min.js" ></script> -->

    <!-- LOOKING FOR YOUR CSS? It's all been combined into the link below -->
    <?= $theme->get_combined("css") ?>
    <link rel="stylesheet" type="text/css" href="http://yui.yahooapis.com/3.2.0/build/cssreset/reset-min.css" />
	 <link rel="stylesheet" type="text/css" href="http://yui.yahooapis.com/3.2.0/build/cssfonts/fonts-min.css" />
    <link rel="stylesheet" type="text/css" href="http://yui.yahooapis.com/3.2.0/build/cssgrids/grids-min.css" />
    <link rel="stylesheet" type="text/css" href="/css/cmubuggy.css" />
    <link rel="stylesheet" type="text/css" href="/css/superfish-menu.css" />
    <link  href="https://fonts.googleapis.com/css?family=Lobster:regular" rel="stylesheet" type="text/css" />
	<!--Google analytics -->
	<script type="text/javascript">
	  var _gaq = _gaq || [];
	  _gaq.push(['_setAccount', 'UA-345857-14']);
	  _gaq.push(['_trackPageview']);
	
	  (function() {
	    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
	  })();
	</script>
  </head>
  <?php 
	  	$headline = "Gallery";
		include_once("/var/www/cmubuggy.org/content/pre-content.inc"); ?>
  <div id="topnav">
		<?= $theme->site_menu($theme->item() ? "#g-item-id-{$theme->item()->id}" : "") ?>
	</div>

  <? if ($theme->item() && !empty($parents)): ?>
  <ul class="g-breadcrumbs">
    <? $i = 0 ?>
    <? foreach ($parents as $parent): ?>
    <li<? if ($i == 0) print " class=\"g-first\"" ?>>
      <? // Adding ?show=<id> causes Gallery3 to display the page
         // containing that photo.  For now, we just do it for
         // the immediate parent so that when you go back up a
         // level you're on the right page. ?>
      <a href="<?= $parent->url($parent->id == $theme->item()->parent_id ?
               "show={$theme->item()->id}" : null) ?>">
        <? // limit the title length to something reasonable (defaults to 15) ?>
        <?= html::purify(text::limit_chars($parent->title,
              module::get_var("gallery", "visible_title_length"))) ?>
      </a>
    </li>
    <? $i++ ?>
    <? endforeach ?>
    <li class="g-active<? if ($i == 0) print " g-first" ?>">
      <?= html::purify(text::limit_chars($theme->item()->title,
            module::get_var("gallery", "visible_title_length"))) ?>
    </li>
  </ul>
  <? endif ?>
  
  <div id="g-content" class="">
  <?= $theme->messages() ?>
  <?= $content ?>
  </div>
  <div id="g-sidebar" class="" style="">
    <? if ($theme->page_subtype != "login"): ?>
    <?= new View("sidebar.html") ?>
    <? endif ?>
  </div>

	<div id="g-footer" class="ui-helper-clearfix">
	  <?= $theme->footer() ?>
	  <? if ($footer_text = module::get_var("gallery", "footer_text")): ?>
	  <?= $footer_text ?>
	  <? endif ?>
	
	  <? if (module::get_var("gallery", "show_credits")): ?>
	  <ul id="g-credits" class="g-inline">
	    <?= $theme->credits() ?>
	  </ul>
	  <? endif ?>
	</div>
    <?= $theme->page_bottom() ?>
    <?php include_once("/var/www/cmubuggy.org/content/post-content.inc"); ?>
  </body>
</html>
