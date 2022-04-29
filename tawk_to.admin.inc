<?php
/**
 * @file
 * @package   tawk.to module for Drupal CMS
 * @copyright (C) 2021 tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

require_once 'includes/tawk_to.helper.php';

/**
 * tawk.to main admin form
 */
function tawk_to_admin_form($form, &$form_state) {
  global $user;
  $same_user = TawkHelper::check_same_user($user->uid);
  $widget = TawkHelper::get_widget();
  $base_url = TawkHelper::get_base_url();
  $iframe_url = TawkHelper::get_iframe_url();
  $display_opts = variable_get(TawkHelper::TAWK_TO_WIDGET_OPTIONS, '');

  if ($display_opts && !empty($display_opts)) {
    $display_opts = json_decode($display_opts);
  }
  else {
    $display_opts = null;
  }

  // css and js files
  $module_path = TawkHelper::get_module_path();
  $form['#attached']['css'][] = array(
    'data' => $module_path . '/css/tawk_to.admin.css',
    'type' => 'file',
  );
  $form['#attached']['js'][] = array(
    'data' => $module_path . '/js/tawk_to.admin.js',
    'type' => 'file',
  );

  $form['#attached']['js'][] = array(
    'data' => array(
      'tawkto' => array(
        'iframeUrl' => $iframe_url,
        'baseUrl' => $base_url,
      ),
    ),
    'type' => 'setting',
  );

  $form['widget_selection'] = build_widget_selection($same_user, $widget);
  $form['visibility_settings'] = build_visibility_opts_form($display_opts);
  $form['privacy_settings'] = build_privacy_settings_form($display_opts);

  // submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  $form['#submit'][] = 'tawk_to_admin_form_submit';

  return $form;
}

/**
 * builds tawk.to widget selection area
 */
function build_widget_selection($same_user, $widget) {
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Property and Widget Selection'),
    '#description' => t('Select the property and widget from your tawk.to account')
  );

  if(!$same_user) {
    $form['already_set'] = array(
      '#type' => 'markup',
      '#markup' => '<div id="widget_already_set" class="alert alert-warning">Notice: Widget already set by other user</div>',
    );
  }

  $form['iframe'] = array(
    '#type' => 'markup',
    '#markup' => '
      <iframe id="tawkIframe" class="tawkto-property-widget-selection" src="" ></iframe>
      <input type="hidden" class="hidden" name="page_id" value="' . $widget['page_id'] . '">
      <input type="hidden" class="hidden" name="widget_id" value="' . $widget['widget_id'] . '">
      ',
  );

  return $form;
}

/**
 * builds tawk.to widget visibility options form.
 */
function build_visibility_opts_form($display_opts) {
  // visibility settings
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility Settings'),
    '#description' => t('Define where the tawk.to widget will and won\'t show'),
  );

  // always display config
  $always_display_attr = array();
  if (!is_null($display_opts) && $display_opts->always_display) {
    $always_display_attr['checked'] = true;
  }

  $form['always_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always show Tawk.To widget on every page'),
    '#description' => t('Select to show on all except the exceptions
    De-select to select the specific pages'),
    '#id' => t('always_display'),
    '#attributes' => $always_display_attr,
  );

  // exclude url config
  $form['hide_oncustom'] = array(
    '#type' => 'textarea',
    '#title' => t('Except on pages:'),
    '#description' => t('Add URLs to pages in which you would like to hide the widget.<br>
    Put each URL in a new line and just include the leading \'/\' and page URL (e.g. /about)'),
    '#prefix' => '<div class="div_hide_specific">',
    '#suffix' => '</div>',
    '#id' => t('hide_oncustom'),
    '#default_value' => !is_null($display_opts) && $display_opts->hide_oncustom ?
      format_multiline_url_paths($display_opts->hide_oncustom) : '',
  );

  // show on front page config
  $show_onfrontpage_attr = array();
  if (!is_null($display_opts) && $display_opts->show_onfrontpage) {
    $show_onfrontpage_attr['checked'] = true;
  }

  $form['show_onfrontpage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on front page'),
    '#prefix' => '<div class="div_show_specific">',
    '#suffix' => '</div>',
    '#id' => t('show_onfrontpage'),
    '#attributes' => $show_onfrontpage_attr,
  );

  // show on taxonomy config
  $show_ontaxonomy_attr = array();
  if (!is_null($display_opts) && $display_opts->show_ontaxonomy) {
    $show_ontaxonomy_attr['checked'] = true;
  }

  $form['show_ontaxonomy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on taxonomy pages'),
    '#description' => t('Select to show on pages for taxonomy terms'),
    '#prefix' => '<div class="div_show_specific">',
    '#suffix' => '</div>',
    '#id' => t('show_ontaxonomy'),
    '#attributes' => $show_ontaxonomy_attr,
  );

  // include urls config
  $show_oncustom_default_value = '';
  if (!is_null($display_opts) && $display_opts->show_oncustom) {
    $show_oncustom_default_value = format_multiline_url_paths($display_opts->show_oncustom);
  }
  $form['show_oncustom'] = array(
    '#type' => 'textarea',
    '#title' => t('Show on pages:'),
    '#description' => t('Add URLs to pages in which you would like to show the widget.<br>
    Put each URL in a new line and just include the the leading \'/\' and page URL (e.g. /about)'),
    '#prefix' => '<div class="div_show_specific">',
    '#suffix' => '</div>',
    '#id' => t('show_oncustom'),
    '#default_value' =>  $show_oncustom_default_value,
  );

  return $form;
}

/**
 * builds tawk.to privacy settings form
 */
function build_privacy_settings_form($display_opts) {
  // privacy settings
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Privacy Settings'),
    '#description' => t('Define whether or not user information can be used'),
  );

  // enable visitor recognition config
  $enable_visitor_recognition_attr = array();
  if (!is_null($display_opts) && $display_opts->enable_visitor_recognition) {
    $enable_visitor_recognition_attr['checked'] = true;
  }
  $form['enable_visitor_recognition'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable visitor recognition'),
    '#description' => t('If selected, name and email address from logged in users will be used to identify the user to you when a chat comes in via tawk.to'),
    '#id' => t('enable_visitor_recognition'),
    '#attributes' => $enable_visitor_recognition_attr,
  );

  return $form;
}

/**
 * tawk.to admin form submit handler
 */
function tawk_to_admin_form_submit($form, &$form_state) {
  $jsonOpts = array(
    'always_display' => false,
    'hide_oncustom' => array(),
    'show_onfrontpage' => false,
    'show_ontaxonomy' => false,
    'show_oncustom' => array(),
    'enable_visitor_recognition' => false,
  );

  $options = $form_state['values'];

  foreach ($options as $column => $value) {
    switch ($column) {
      case 'hide_oncustom':
      case 'show_oncustom':
        // replace newlines and returns with comma, and convert to array for saving
        $value = str_replace(["\r\n", "\r", "\n"], ',', $value);
        $value = explode(',', $value);
        $value = (empty($value)||!$value)?array():$value;
        $jsonOpts[$column] = json_encode($value);
        break;
      case 'show_onfrontpage':
      case 'show_ontaxonomy':
      case 'always_display':
      case 'enable_visitor_recognition':
        $jsonOpts[$column] = $value == 1;
        break;
    }
  }

  variable_set(
    TawkHelper::TAWK_TO_WIDGET_OPTIONS,
    json_encode($jsonOpts)
  );

  // Flush page cache so widget options will update at next page load
  cache_clear_all(NULL, 'cache_page');

  drupal_set_message('Successfully set widget options to your site');
}

/**
 * Helper function to add new lines to url paths for displaying in textarea fields
 */
function format_multiline_url_paths($url_paths) {
  $paths = json_decode($url_paths);
  $formatted_paths = '';
  foreach($paths as $path) {
    if (!empty($formatted_paths)) {
      $formatted_paths .= "\r\n";
    }

    $formatted_paths .= $path;
  }
  return $formatted_paths;
}
