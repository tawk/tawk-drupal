<?php
/**
 * @file
 * @package   tawk.to module for Drupal CMS
 * @copyright (C) 2021 tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

class TawkHelper {
  const TAWK_TO_PAGE_ID = 'page_id';
  const TAWK_TO_WIDGET_ID = 'widget_id';
  const TAWK_TO_WIDGET_OPTIONS = 'widget_options';
  const TAWK_TO_WIDGET_USER_ID = 'widget_user_id';
  const TAWK_TO_CONFIG_NAME = 'tawk_to.settings';

  /**
   * Gets the selected property and widget id
   */
  public static function get_widget() {
    $config_name = TawkHelper::TAWK_TO_CONFIG_NAME;
    return array(
      'page_id' => variable_get($config_name, TawkHelper::TAWK_TO_PAGE_ID),
      'widget_id' => variable_get($config_name,TawkHelper::TAWK_TO_WIDGET_ID),
    );
  }

  /**
   * Checks if the current user is the same user that selected the widget
   */
  public static function check_same_user($current_user) {
    $saved_user = variable_get(
      TawkHelper::TAWK_TO_CONFIG_NAME,
      TawkHelper::TAWK_TO_WIDGET_USER_ID
    );

    if (empty($saved_user)) {
      return false;
    }

    return $current_user === $saved_user;
  }

  /**
   * Base url for tawk.to application which serves iframe
   */
  public static function get_base_url() {
    return 'https://plugins.tawk.to';
  }

  /**
   * Constructs url for configuration iframe
   */
  public static function get_iframe_url() {
    $widget = TawkHelper::get_widget();

    if (!$widget) {
      $widget = array(
        'page_id'   => '',
        'widget_id' => '',
      );
    }
    return TawkHelper::get_base_url() . '/generic/widgets?currentWidgetId=' . $widget['widget_id'] . '&currentPageId=' . $widget['page_id'];
  }

  /**
   * Gets the module path
   */
  public static function get_module_path() {
    return drupal_get_path('module', 'tawk_to');
  }
}
