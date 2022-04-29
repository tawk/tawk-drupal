'use strict';

var tawktoSettings = Drupal.settings.tawkto || {};

window.Tawk_LoadStart = new Date();
window.Tawk_API = window.Tawk_API || {};

if (tawktoSettings.user && tawktoSettings.enableVisitorRecognition) {
  window.Tawk_API.visitor = {
    name : tawktoSettings.user.name,
    email : tawktoSettings.user.email
  };
}

var curpage = window.location.href;
var hash = window.location.hash;
window.Tawk_API.onLoad = function() {
  if (curpage.indexOf('admin/') != -1 || hash.indexOf('overlay')!= -1) {
    window.Tawk_API.hideWidget();
  }
};

(function() {
  var s1=document.createElement("script"),s0=document.getElementsByTagName("script")[0];
  s1.async=true;
  s1.src="https://embed.tawk.to/" + tawktoSettings.pageId + "/" + tawktoSettings.widgetId;
  s1.charset="UTF-8";
  s1.setAttribute("crossorigin","*");
  s0.parentNode.insertBefore(s1,s0);
})();
