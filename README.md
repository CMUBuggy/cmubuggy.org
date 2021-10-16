This is the git repo for the source code running cmubuggy.org.
cmubuggy.org is the public website for the Carnegie Mellon University affiliated Buggy Alumni Association.

cmubuggy.org was first launched in October of 2008.  The majority of the original code and design were by Sam Swift (samswift@cmubuggy.org).
Adam McCue and Scott Ziolko helped considerably with data structure and population.  Aiton Goldman is the primary author of the raceday lead-truck auction bidding system and has also contributed to the log-in/user-management system.
Refinements were made in an un-managed and as-needed basis for 2+ years.

The first major overhaul of the site was "completed" just in time for raceday 2011.  This version of the site was committed to the repo in the summer of 2011 to allow greater community involvement in coding the site.  Please, if you're reading this, do not hesitate to get involved.

The site is built around a number of 3rd party platforms and tools.  If you want to set up a local dev version of the site, cloning the repo is a start, but depending on your project you may need additional pieces of the puzzle:

 --> Data:  Contact samswift@cmubuggy.org or the current administrator to get access to an exported version of the relevant data.  A mostly accurate db schema is located at /lib/pog/cmubuggy-2.0-schema.png
 --> Data Objects: all custom data objects make use of the PHP Object Generator library (http://www.phpobjectgenerator.com/).  Code for each object is in /lib/pog/objects and can be modified by pasting the unique object url and generating new code on phpobjectgenerator.com
 --> Forum: /forum runs phpBB (http://www.phpbb.com/).  version info is available in /forum/README
 --> Gallery: /gallery runs gallery3 (http://gallery.menalto.com/). version info is available in /gallery/README
 --> Wiki: /reference points to files in WordPress
 --> News: /news runs Wordpress (http://wordpress.org/).  version info is available in /news/README

# Wiki
As of October 2021, `/reference` points to reference-style pages hosted in our WordPress installation.

Previously, `/reference` ran [Mediawiki](http://www.mediawiki.org) from the `mediawiki` directory in the repo root. Backups of the old `mediawiki` directory and the  corresponding `cmubuggy_wiki` database table can be found in the Google Drive BAA folder under Website/Backups.
