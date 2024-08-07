cmubuggy.org/news runs [WordPress 5.8.1](http://wordpress.org/).

# Theme
The cmubuggy theme is included in the `cmubuggy` repo at `/news/wp-content/themes/cmubuggy-child`.

# Plugins
We use various plugins on our WordPress site as tools and to display our content more nicely.

## Akismet

This catches lots of spam comments!

## Broken Link Checker

This scans our pages and posts and ensures that all links are working properly.

## Clear Cache for Me

This adds a button to the top of the dashboard that says "Clear Cache for Me". Clicking this will force users' browsers to reload CSS and JS on the site.

## Conditional Menus

This allows us to display menus at the tops of pages related to the section of the website where the page exists.

Test by: Going to the [About Us page](https://cmubuggy.org/about/) and confirming there is a menu above the content linking to pages about the BAA.

## Embed Iframe

We use this to embed Google Drive content in WordPress pages and posts.

Test by: Checking out the [Membership post](https://cmubuggy.org/news/2019/11/giving-cmu-day-and-new-membership-levels/?s=membership) and confirming a Google Sheet is embedded near the bottom.

## Genesis Custom Blocks

This allows us to build our own WordPress blocks to style content uniformly.

Test by: Going to the [Raceday page](https://cmubuggy.org/raceday) and confirming that the various links are nicely formatted in a table.

## WP-Polls

This allows us to add polls to pages and posts, which are stored in the WordPress database alongside other WordPress content.

Test by: Confirming you can see the poll data on [this page](https://cmubuggy.org/news/2010/03/thursday-poll-for-love-or-buggy).


# Updating WordPress
Follow the instructions [here](https://wordpress.org/support/article/upgrading-wordpress-extended-instructions/) to update the WordPress version.

## Troubleshooting
**When re-activating plugins, WordPress requests web server credentials.**

WordPress does not have modification rights within the `wp-content` directory. To fix this, run:

```
cd news
sudo chown -R www-data:www-data .
```
