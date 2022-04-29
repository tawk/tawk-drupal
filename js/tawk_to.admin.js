'use strict';

// initialize variables
var tawktoSettings = {};

jQuery(document).ready(function() {
  tawktoSettings = Drupal.settings.tawkto || {};

  var currentHost = window.location.protocol + "//" + window.location.host;
  var url = tawktoSettings.iframeUrl + "&pltf=drupal&parentDomain=" + currentHost;

  jQuery("#tawkIframe").attr("src", url);

  if (jQuery("#always_display").prop("checked")) {
    jQuery('.show_specific').prop('disabled', true);
    jQuery(".div_show_specific").hide();
  } else {
    jQuery('.hide_specific').prop('disabled', true);
    jQuery(".div_hide_specific").hide();
  }

  jQuery("#always_display").change(function() {
    if (this.checked) {
      jQuery('.hide_specific').prop('disabled', false);
      jQuery('.show_specific').prop('disabled', true);
      jQuery(".div_hide_specific").show();
      jQuery(".div_show_specific").hide();
    } else {
      jQuery('.hide_specific').prop('disabled', true);
      jQuery('.show_specific').prop('disabled', false);
      jQuery(".div_hide_specific").hide();
      jQuery(".div_show_specific").show();
    }
  });
});

window.addEventListener("message", function(e) {
  if (e.origin === tawktoSettings.baseUrl) {
    if (e.data.action === "setWidget") {
      setWidget(e);
    }

    if (e.data.action === "removeWidget") {
      removeWidget(e);
    }

    if (e.data.action === 'reloadHeight') {
      reloadIframeHeight(e.data.height);
    }
  }
});

function setWidget(e) {
  jQuery.post("?q=admin/config/tawk/setwidget", {
    pageId : e.data.pageId,
    widgetId : e.data.widgetId
  }, function(r) {
    if (r.success) {
      jQuery('input[name="page_id"]').val(e.data.pageId);
      jQuery('input[name="widget_id"]').val(e.data.widgetId);
      jQuery('#widget_already_set').hide();
      e.source.postMessage({action: "setDone"}, tawktoSettings.baseUrl);
    } else {
      e.source.postMessage({action: "setFail"}, tawktoSettings.baseUrl);
    }
  });
}

function removeWidget(e) {
  jQuery.post("?q=admin/config/tawk/removewidget", function(r) {
    if (r.success) {
      jQuery('input[name="page_id"]').val('');
      jQuery('input[name="widget_id"]').val('');
      jQuery('#widget_already_set').hide();
      e.source.postMessage({action: "removeDone"}, tawktoSettings.baseUrl);
    } else {
      e.source.postMessage({action: "removeFail"}, tawktoSettings.baseUrl);
    }
  });
}

function reloadIframeHeight(height) {
  if (!height) {
    return;
  }

  var iframe = jQuery('#tawkIframe');
  if (height === iframe.height()) {
    return;
  }

  iframe.height(height);
}
