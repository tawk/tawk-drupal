<?php

/**
 * @file
 * @package   Tawk.to module for Drupal
 * @copyright (C) 2014- Tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

/**
 * Creates markup for settings page.
 */
function tawk_to_render_widget_iframe($base_url, $iframe_url) {
  return '<script type="text/javascript" src="' . $base_url . '/public/js/jquery-1.11.0.min.js"></script>

  <iframe
      id="tawkIframe"
      src=""
      style="min-height: 400px; width : 100%; border: none">
  </iframe>

  <script type="text/javascript">
      var currentHost = window.location.protocol + "//" + window.location.host;
      var url = "' . $iframe_url . '&parentDomain=" + currentHost;

      jQuery("#tawkIframe").attr("src", url);

      var iframe = jQuery("#tawk_widget_customization")[0];

      window.addEventListener("message", function(e) {
          if(e.origin === "' . $base_url . '") {

              if(e.data.action === "setWidget") {
                  setWidget(e);
              }

              if(e.data.action === "removeWidget") {
                  removeWidget(e);
              }
          }
      });

      function setWidget(e) {
          jQuery.post("/admin/config/tawk/setwidget", {
              pageId : e.data.pageId,
              widgetId : e.data.widgetId
          }, function(r) {
              if(r.success) {
                  e.source.postMessage({action: "setDone"}, "' . $base_url . '");
              } else {
                  e.source.postMessage({action: "setFail"}, "' . $base_url . '");
              }
          });
      }

      function removeWidget(e) {
          jQuery.post("/admin/config/tawk/removewidget", function(r) {
              if(r.success) {
                  e.source.postMessage({action: "removeDone"}, "' . $base_url . '");
              } else {
                  e.source.postMessage({action: "removeFail"}, "' . $base_url . '");
              }
          });
      }
  </script>';

}
