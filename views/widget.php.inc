<?php

/**
 * @file
 * @package   Tawk.to module for Drupal
 * @copyright (C) 2014- Tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

/**
 * Creates markup for embed script element.
 */
function tawk_to_render_widget($page_id, $widget_id) {
  return '<!--Start of Tawk.to Script-->
  <script type="text/javascript">
  var $_Tawk_API={},$_Tawk_LoadStart=new Date();
  (function(){
  var s1=document.createElement("script"),s0=document.getElementsByTagName("script")[0];
  s1.async=true;
  s1.src="https://embed.tawk.to/' . $page_id . '/' . $widget_id . '";
  s1.charset="UTF-8";
  s1.setAttribute("crossorigin","*");
  s0.parentNode.insertBefore(s1,s0);
  })();
  </script>
  <!--End of Tawk.to Script-->';
}
