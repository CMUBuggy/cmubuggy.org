This is the git repo for the source code running cmubuggy.org.

> Q: What do you call the code for the CMU Sweepstakes Alumni Website?
>
> A: Buggy Software!
>
>   -- Anonymous

cmubuggy.org is the public website for the Carnegie Mellon University affiliated Buggy Alumni Association.

The site is built around a number of 3rd party platforms and tools. If you want to set up a local dev version of the site, cloning the repo is a start, but depending on your project you may need additional pieces of the puzzle:

 - Data:  Contact the current administrator to get access to an exported version of the relevant data.
 - pChart: Needed for graphing historical trend data on the organization history pages.  Available at http://www.pchart.net/download -- install into lib/pChart.  Warning! pChart is old and does not work properly with PHP 7.  For that, you need a fixed version (2.1.4b, available here from a third party: https://github.com/bozhinov/pChart2.0-for-PHP7/releases)
 - Photos: Currently, photo hosting is provided by SmugMug at https://cmubuggy.smugmug.com
   - Previously, our self hosted gallery ran gallery3 (http://gallery.menalto.com/).
 - News: /news runs Wordpress (http://wordpress.org/).  Version info is available in `/news/README`
 - Wiki: As of 2021, `/reference` points to files in WordPress

# LAMP Setup
This site is built to run on a LAMP platform (Linux/Apache/PHP/MySQL).  We make extensive use of the apache modules `mod_rewrite` and `mod_expires`.

# Wiki
As of October 2021, `/reference` points to reference-style pages hosted in our WordPress installation.

Previously, `/reference` ran [Mediawiki](http://www.mediawiki.org) from the `mediawiki` directory in the repo root. Backups of the old `mediawiki` directory and the  corresponding `cmubuggy_wiki` database table can be found in the Google Drive BAA folder under Website/Backups.

# History
cmubuggy.org was first launched in October of 2008.  The majority of the original code and design were by Sam Swift (samswift@cmubuggy.org).

Adam McCue and Scott Ziolko helped considerably with data structure and population.  Aiton Goldman is the primary author of the (now deprecated) raceday lead-truck auction bidding system and has also contributed to the log-in/user-management system.

Refinements were made in an un-managed and as-needed basis for 2+ years.

A major overhaul of the site was "completed" just in time for raceday 2011.  This version of the site was committed to the repo in the summer of 2011 to allow greater community involvement in coding the site.

In early 2022, a massive revamp of the history database and schema was completed by Jeremy Tuttle, and the web site code was updated to match by Rob Siemborski.
