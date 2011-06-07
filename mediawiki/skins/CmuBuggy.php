<?php
include_once("../util.inc");

// initialization code
if( !defined('MEDIAWIKI') )
        die("This Skin file is not a valid Entry Point.");
require_once('includes/SkinTemplate.php');
 
// inherit main code from SkinTemplate, set the CSS and template filter
class SkinCmuBuggy extends SkinTemplate {
        function initPage(&$out) {
                SkinTemplate::initPage($out);
                $this->skinname  = 'cmubuggy';
                $this->stylename = 'cmubuggy';
                $this->template  = 'CmuBuggyTemplate';
        }
}
 
class CmuBuggyTemplate extends QuickTemplate {
        //Other code sections will be appended to this class body
        /* hijack category functions to create a proper list */
 
        function getCategories() {
                $catlinks=$this->getCategoryLinks();
                if(!empty($catlinks)) {
                        return "<ul id='catlinks'>{$catlinks}</ul>";
                }
        }
 
        function getCategoryLinks() {
                global $wgOut, $wgUser, $wgTitle, $wgUseCategoryBrowser;
                global $wgContLang;
 
                if(count($wgOut->mCategoryLinks) == 0)
                        return '';
 
                $skin = $wgUser->getSkin();
 
                # separator
                $sep = "";
 
                // use Unicode bidi embedding override characters,
                // to make sure links don't smash each other up in ugly ways
                $dir = $wgContLang->isRTL() ? 'rtl' : 'ltr';
                $embed = "<li dir='$dir'>";
                $pop = '</li>';
                $t = $embed . implode ( "{$pop} {$sep} {$embed}" , $wgOut->mCategoryLinks ) . $pop;
 
                $msg = wfMsgExt('pagecategories', array('parsemag', 'escape'), count($wgOut->mCategoryLinks));
                $s = $skin->makeLinkObj(Title::newFromText(wfMsgForContent('pagecategorieslink')), $msg)
                        . $t;
 
                # optional 'dmoz-like' category browser - will be shown under the list
                # of categories an article belongs to
                if($wgUseCategoryBrowser) {
                        $s .= '<br /><hr />';
 
                        # get a big array of the parents tree
                        $parenttree = $wgTitle->getParentCategoryTree();
                        # Skin object passed by reference because it can not be
                        # accessed under the method subfunction drawCategoryBrowser
                        $tempout = explode("\n", Skin::drawCategoryBrowser($parenttree, $this));
                        # clean out bogus first entry and sort them
                        unset($tempout[0]);
                        asort($tempout);
                        # output one per line
                        $s .= implode("<br />\n", $tempout);
                }
 
                return $s;
        }
        
        function execute() {
                // declaring global variables and getting the skin object in case you need to use them later
                global $wgUser, $wgSitename;
                //$skin = $wgUser->getSkin();
 
                // retrieve site name
                $this->set('sitename', $wgSitename);
 
                // suppress warnings to prevent notices about missing indexes in $this->data
                wfSuppressWarnings();
                
					?>
					<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
					<html xmlns="http://www.w3.org/1999/xhtml">
					<head>
						<meta http-equiv="Content-Type" content="<?php $this->text('mimetype') ?>; charset=<?php $this->text('charset') ?>" />
						<meta name="keywords" content="" />
						<meta name="description" content="" />
						<title><?php $this->text('pagetitle') ?> | CMU Buggy Alumni Association</title>
						<?php include_once(ROOT_DIR."/content/cssjs.inc"); ?>
						<link rel="stylesheet" type="text/css" href="/css/cmubuggy-mediawiki.css" />
	               <?php print Skin::makeGlobalVariablesScript($this->data); ?>
	               <?php /*** various MediaWiki-related scripts and styles ***/ ?>
	               <script type="<?php $this->text('jsmimetype') ?>" src="<?php $this->text('stylepath') ?>/common/wikibits.js?<?php echo $GLOBALS['wgStyleVersion'] ?>"><!-- wikibits js --></script>
						<?php       if($this->data['jsvarurl']) { ?>
						                <script type="<?php $this->text('jsmimetype') ?>" src="<?php $this->text('jsvarurl') ?>"><!-- site js --></script>
						<?php       } ?>
						<?php       if($this->data['pagecss']) { ?>
						                <style type="text/css"><?php $this->html('pagecss') ?></style>
						<?php       }
						                if($this->data['usercss']) { ?>
						                <style type="text/css"><?php $this->html('usercss') ?></style>
						<?php       }
						                if($this->data['userjs']) { ?>
						                <script type="<?php $this->text('jsmimetype') ?>" src="<?php $this->text('userjs' ) ?>"></script>
						<?php       }
						                if($this->data['userjsprev']) { ?>
						                <script type="<?php $this->text('jsmimetype') ?>"><?php $this->html('userjsprev') ?></script>
						<?php       }
						                if($this->data['trackbackhtml']) print $this->data['trackbackhtml']; ?>
						                <!-- Head Scripts -->
	                <?php $this->html('headscripts') ?>
					</head>
					<!-- Body -->
					<?php
						$headline = "Reference"; 
						include_once(ROOT_DIR."/content/pre-content.inc");
					?>
					<!--Toolbars -->
					<div id="topnav">
						<ul class="sf-menu">
							<li><a href="/reference">Navigation</a>
								<ul>
									<li><a href="/reference">Reference Home</a></li>
									<li><a href="/reference/Category:Terminology">Terminology</a></li>
									<li><a href="/reference/Rules">Rules</a></li>
									<li><a href="/reference/Category:Guides">Guides</a></li>				
								</ul>
							</li>
							<li><a href="">My Account</a>
								<ul>
								<?php                       
									foreach($this->data['personal_urls'] as $key => $item) { ?>
										<li id="pt-<?php echo $key ?>">
											<a href="<?php echo $item['href'] ?>"><?php echo $item['text'] ?></a></li>
								<?php } ?>
								</ul>
							</li>
							<li><a href="">Page Actions</a>
								<ul>
									<?php 
										foreach($this->data['content_actions'] as $key => $tab) { ?>
											<li id="ca-<?php echo $key ?>">
												<a href="<?php echo $tab['href'] ?>"><?php echo htmlspecialchars($tab['text']) ?></a></li>
									<?php                        } ?>
								</ul>
							</li>
							<li><a href="">Toolbox</a>
								<ul>
								<?php
									foreach( array( 'contributions', 'blockip', 'emailuser', 'upload', 'specialpages' ) as $special ) {
							 			if( $this->data['nav_urls'][$special] ) { ?>
							 				<li id="t-<?php echo $special ?>">
							 					<a href="<?php echo htmlspecialchars($this->data['nav_urls'][$special]['href'])?>">
							 						<?php $this->msg($special) ?>
							 					</a>
							 				</li>
								<?php
										}
									} ?>
								 											
								</ul>
						</ul>
					</div>
					<div id="ref" class="pane">
						<!-- ACTUAL WIKI CONTENT -->
											
						<!--Page title and subtitle -->
						<h1 class="firstHeading"><?php $this->data['displaytitle']!=""?$this->html('title'):$this->text('title') ?></h1>
						<div id="contentSub"><?php $this->html('subtitle') ?></div>
						
						<!--Page content -->
						<?php $this->html('bodytext') ?>
						
						<!--Toolbox portlet -->
						<div style="clear:both"></div>		
					</div>	
						<!--Category Links -->
						<?php if($this->data['catlinks']) { ?><div id="catlinks" class=""><?php $this->html('catlinks') ?></div><?php } ?>
						
						<!--Page stats for footer -->
						<?php
                	$footerlinks = array('lastmod', 'viewcount');
                	foreach( $footerlinks as $aLink ) {
                        if( isset( $this->data[$aLink] ) && $this->data[$aLink] ) {
						?> <li id="<?php echo$aLink?>"><?php $this->html($aLink) ?></li>
						<?php               }
						                }
						?>
						<!-- END ACTUAL WIKI CONTENT -->
					
					<?php $this->html('bottomscripts'); /* JS call to runBodyOnloadHook */ ?>
					<?php if ( $this->data['debug'] ): ?>
					<!-- Debug output:
					<?php $this->text( 'debug' ); ?>
					 
					-->
					<?php endif; ?>
					<?php include_once(ROOT_DIR."/content/post-content.inc"); ?>
					</body>
					</html>
					<?php
					wfRestoreWarnings();
		} // end of execute() method
} // end of class
?>         