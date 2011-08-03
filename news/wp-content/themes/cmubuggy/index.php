<?php
	get_header();
?>
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
			<li><a target="_blank" href="http://feedburner.google.com/fb/a/mailverify?uri=BuggyAlumniAssociationNews&amp;loc=en_US">Subscribe to News by Email</a></li>
			<li><a href="mailto:news@cmubuggy.org">Submit News</a></li>
		</ul>
	</div>
<?
	get_template_part( 'loop', 'index' ); 
	get_footer();
?>