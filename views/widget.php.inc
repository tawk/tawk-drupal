<?php
/**
 * @file
 * @package   tawk.to module for Drupal
 * @copyright (C) 2014- tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

/**
 * Creates markup for embed script element.
 */
function tawk_to_render_widget($page_id, $widget_id, $options)
{
    global $user;
    $apiString = '';
    if ($GLOBALS['user']->uid && $options['enable_visitor_recognition']) {
        global $user;
        $apiString = '$_Tawk_API.visitor = {
            name  : "'.$user->name.'",
            email : "'.$user->mail.'",
        };';
    }

    ob_start();
    ?><!--Start of tawk.to Script-->
    <script type="text/javascript">
    var $_Tawk_API={},$_Tawk_LoadStart=new Date();
    (function(){
    var s1=document.createElement("script"),s0=document.getElementsByTagName("script")[0];
    s1.async=true;
    s1.src="https://embed.tawk.to/<?php echo $page_id; ?>/<?php echo $widget_id; ?>";
    s1.charset="UTF-8";
    s1.setAttribute("crossorigin","*");
    s0.parentNode.insertBefore(s1,s0);
    })();
    <?php echo $apiString; ?>

    var curpage = window.location.href;
    var hash = window.location.hash;
    $_Tawk_API.onLoad = function(){
        if (curpage.indexOf('admin/') != -1 || hash.indexOf('overlay')!= -1) {
            Tawk_API.hideWidget();
        }
    };
    </script><!--End of tawk.to Script-->
    <?php
    $markup = ob_get_contents();
    ob_end_clean();
    return $markup;
}
