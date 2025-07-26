<?php
/*
Plugin Name: CMUBuggy MOTD Controller
Description: Control the MOTD on the cmubuggy home page.
Author: Rob Siemborski
Version: 1.0
Requires at least: 6.8
Requires PHP: 7.4
*/

// Useful for testing
// ini_set('display_errors',1);

// Useful for consistency
define('CMUBUGGY_MOTD_OPTION', 'cmubuggy-motd');

register_deactivation_hook(__FILE__, 'deactivate_plugin');

function deactivate_plugin() {
  // This assumes that deactivating, rather than uninstalling, the plugin should clear
  // any currently posted message.  Seems reasonable given that we won't be installing dynamically.
  delete_option(CMUBUGGY_MOTD_OPTION);
}

// If we are not on the admin panel, do not load any further.
if (!is_admin()) {
  return;
}

add_action('admin_menu', 'dashboard_menu');

function dashboard_menu() {
  new CMUBuggyMotdPanel();
}

class CMUBuggyMotdPanel {
  var $wp_ok = false;

  function __construct() {
    $this->checkWPVersion();
    $this->dashboard_menu();
  }

  // Check for 6.8, when we wrote this.
  function checkWPVersion() {
    global $wp_version;
    $version = explode('.', $wp_version);
    $major = intval($version[0]);
    $minor = intval($version[1]);
    if ($major > 6 || ($major == 6 && $minor >= 8)) {
      $this->wp_ok = true;
    } else {
      // Redundant, but safer.
      $this->wp_ok = false;
    }

    if (!$this->wp_ok) {
      echo('CMUBuggy MOTD Controller WP Version Check Failed.');
    }
  }

  // Create the Dashboard Widget
  function dashboard_menu() {
    if (!$this->wp_ok) {
      return;
    }

    // Only load for editors and administrators.
    if (!current_user_can('administrator') && !current_user_can('editor')) {
      return;
    }

    // While we shouldn't even be herre for people other than editors and adminitrators, but if for some
    // reason we are, default to 'edit pages' as the requirement to be able to modify the motd.
    //
    // 26 places us at the bottom of the topmost section (just below "Pages" and "Comments") so
    // that this control is easy to find.
    add_menu_page('CMUBuggy MOTD', 'CMUBuggy MOTD', 'edit_pages', 'cmubuggy-motd',
                  array($this, 'motd_manage'), 'dashicons-admin-generic', 26);
  }

  function motd_manage() {
    if (!$this->wp_ok) {
      return;
    }
    echo('<h1>CMUBuggy MOTD Control</h1>');
    if ($_POST["action"] == "savemotd") {  // Probably an excessive check.
     if (isset($_POST["clearbutton"])) {
        // clear action.  delete any existing content.
        delete_option(CMUBUGGY_MOTD_OPTION);
        echo('<div class="updated"><p><strong>MOTD Cleared.</strong></p></div>');
      } else {
        // assume save action taken.
        //
        // This is not a useful option to autoload, ever, so say that.
        update_option(CMUBUGGY_MOTD_OPTION, stripslashes($_REQUEST['motdcontent']), false);
        echo('<div class="updated"><p><strong>MOTD Updated.</strong></p></div>');
      }
    }
    // TODO Clear Button

    // The form is below.
?>
<div class="wrap">
  <form method="post">
    <p>Put the text you would like to appear on the site's home page below.  Note that full HTML is allowed,
       but plaintext is entirely fine for most purposes.  The content will go live immedaitely upon save.</p>
    <p>Use caution, we trust you.</p>
    <p><input type="submit" value="Save MOTD"><input type="Submit" name="clearbutton" value="Clear MOTD"></p>
<?php
      wp_editor(get_option(CMUBUGGY_MOTD_OPTION), 'motdcontent',
                array('media_buttons' => false,
                      'teeny' => true,
                      'tinymce' => false));
?>
  <input type="hidden" name="action" value="savemotd">
  <br>
  <input type="submit" name="savebutton" value="Save MOTD">
  <input type="submit" name="clearbutton" value="Clear MOTD">
  </form>
</div>

<?php
  }
}
?>
