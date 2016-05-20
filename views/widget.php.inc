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
  return t('<!--Start of Tawk.to Script-->
    <script type="text/javascript">
        var Tawk_API = Tawk_API || {}, Tawk_LoadStart = new Date();
        (function(){
            var s1 = document.createElement("script"), s0 = document.getElementsByTagName("script")[0];
            s1.async = true;
            s1.src = "https://embed.tawk.to/@p/@w";
            s1.charset = "UTF-8";
            s1.setAttribute("crossorigin","*");
            s0.parentNode.insertBefore(s1,s0);
        })();
        <!-- Custom code can go here -->
    </script><!--End of Tawk.to Script-->', array('@p' => $page_id, '@w' => $widget_id));
}
