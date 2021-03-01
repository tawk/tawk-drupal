<?php
/**
 * @file
 * @package   tawk.to module for Drupal
 * @copyright (C) 2014-2021 tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

/**
 * Creates markup for settings page.
 */
function tawk_to_render_widget_iframe($base_url, $iframe_url, $widget=array(), $display_opts = null, $sameUser = true)
{
    ob_start();
    ?><link href="https://plugins.tawk.to/public/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <style>
        #module_form .checkbox {
            display: inline-block;
            min-height: 20px;
        }

        @media only screen and (min-width: 1200px) {
            #module_form .checkbox {
                display: block;
            }
        }
    </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
    <?php if (!$sameUser) : ?>
        <div id="widget_already_set" style="width: 100%; float: left; color: #3c763d; border-color: #d6e9c6; font-weight: bold; margin: 20px 0 0;" class="alert alert-warning">Notice: Widget already set by other user</div>
    <?php endif; ?>
    <iframe id="tawkIframe" src=""
        style="min-height: 275px; width: 100%; border: none; margin: 5px 0; padding: 10px; background: #FFF;"></iframe>
    <input type="hidden" class="hidden" name="page_id" value="<?php echo $widget['page_id']?>">
    <input type="hidden" class="hidden" name="widget_id" value="<?php echo $widget['widget_id']?>">
    <div id="content" class="bootstrap" style="margin-top: -20px;">
        <hr>
        <div class="row">
            <div class="col-lg-8">
                <form id="module_form" class="form-horizontal" action="" method="post">
                    <div class="panel panel-default" id="fieldset_1">
                        <div class="form-group col-lg-12">
                            <div class="panel-heading"><strong>Visibility Settings</strong></div>
                        </div>
                        <br>
                        <div class="form-group col-lg-12">
                            <label for="always_display" class="col-lg-6 control-label">Always show Tawk.To widget on every page</label>
                            <div class="col-lg-6 control-label ">
                                <?php
                                $checked = true;
                                if (!is_null($display_opts)) {
                                    if (!$display_opts->always_display) {
                                        $checked = false;
                                    }
                                }
                                ?>
                                <input type="checkbox" class="checkbox" name="always_display" id="always_display" value="1"
                                    <?php echo ($checked)?'checked':'';?> />
                            </div>
                        </div>
                        <div class="form-group col-lg-12">
                            <label for="hide_oncustom" class="col-lg-6 control-label">Except on pages:</label>
                            <div class="col-lg-6 control-label">
                                <?php if (!empty($display_opts->hide_oncustom)) : ?>
                                    <?php $whitelist = json_decode($display_opts->hide_oncustom) ?>
                                    <textarea class="form-control hide_specific" name="hide_oncustom"
                                        id="hide_oncustom" cols="30" rows="10"><?php foreach ($whitelist as $page) { echo $page."\r\n"; } ?></textarea>
                                <?php else : ?>
                                    <textarea class="form-control hide_specific" name="hide_oncustom" id="hide_oncustom" cols="30" rows="10"></textarea>
                                <?php endif; ?>
                                <br>
                                <p style="text-align: justify;">
                                Add URLs to pages in which you would like to hide the widget. ( if "always show" is checked )<br>
                                Put each URL in a new line.
                                </p>
                            </div>
                        </div>

                        <div class="form-group col-lg-12">
                            <label for="show_onfrontpage" class="col-lg-6 control-label">Show on frontpage</label>
                            <div class="col-lg-6 control-label ">
                                <?php
                                $checked = false;
                                if (!is_null($display_opts)) {
                                    if ($display_opts->show_onfrontpage) {
                                        $checked = true;
                                    }
                                }
                                ?>
                                <input type="checkbox" class="checkbox show_specific" name="show_onfrontpage"
                                    id="show_onfrontpage" value="1"
                                    <?php echo ($checked)?'checked':'';?> />
                            </div>
                        </div>

                        <div class="form-group col-lg-12">
                            <label for="show_oncategory" class="col-lg-6 control-label">Show on category pages</label>
                            <div class="col-lg-6 control-label ">
                                <?php
                                $checked = false;
                                if (!is_null($display_opts)) {
                                    if ($display_opts->show_oncategory) {
                                        $checked = true;
                                    }
                                }
                                ?>
                                <input type="checkbox" class="checkbox show_specific" name="show_oncategory" id="show_oncategory" value="1"
                                    <?php echo ($checked)?'checked':'';?>  />
                            </div>
                        </div>
                        <div class="form-group col-lg-12">
                            <label for="show_oncustom" class="col-lg-6 control-label">Show on pages:</label>
                            <div class="col-lg-6 control-label">
                                <?php if (isset($display_opts->show_oncustom) && !empty($display_opts->show_oncustom)) : ?>
                                    <?php $whitelist = json_decode($display_opts->show_oncustom) ?>
                                    <textarea class="form-control show_specific" name="show_oncustom"
                                        id="show_oncustom" cols="30" rows="10"><?php foreach ($whitelist as $page) { echo $page."\r\n"; } ?></textarea>
                                <?php else : ?>
                                    <textarea class="form-control show_specific" name="show_oncustom" id="show_oncustom" cols="30" rows="10"></textarea>
                                <?php endif; ?>
                                <br>
                                <p style="text-align: justify;">
                                Add URLs to pages in which you would like to show the widget.<br>
                                Put each URL in a new line.
                                </p>
                            </div>
                        </div>

                        <div class="form-group col-lg-12">
                            <div class="panel-heading"><strong>Privacy Options</strong></div>
                        </div>
                        <br>
                        <div class="form-group col-lg-12">
                            <label for="enable_visitor_recognition" class="col-lg-6 control-label">Enable Visitor Recognition</label>
                            <div class="col-lg-6 control-label">
                                <?php
                                    $checked = 'checked';
                                    if (!is_null($display_opts) && !$display_opts->enable_visitor_recognition) {
                                        $checked = '';
                                    }
                                ?>
                                <input type="checkbox" class="checkbox" name="enable_visitor_recognition" id="enable_visitor_recognition" value="1"
                                    <?php echo $checked ?> />
                            </div>
                        </div>
                    </div>
                    <div class="panel-footer">
                        <div class="col-lg-6 col-xs-12" style="text-align: right; margin-bottom: 10px;">
                            <button type="submit" value="1" id="module_form_submit_btn" name="submitBlockCategories" class="btn btn-default"><i class="process-icon-save"></i> Save</button>
                        </div>
                        <div class="col-lg-6 col-xs-12" style="min-height: 60px;">
                            <div id="optionsSuccessMessage" style="background-color: #dff0d8; color: #3c763d; border-color: #d6e9c6; font-weight:bold; display: none; margin-bottom: 0;" class="alert alert-success col-lg-12">Successfully set widget options to your site</div>
                        </div>
                    </div>
                </form>

            </div>
            <div class="col-lg-4"></div>
        </div>
    </div>
    <script type="text/javascript">
      var currentHost = window.location.protocol + "//" + window.location.host;
      var url = "<?php echo $iframe_url; ?>&parentDomain=" + currentHost;

      jQuery("#tawkIframe").attr("src", url);

      var iframe = jQuery("#tawk_widget_customization")[0];

      window.addEventListener("message", function(e) {
          if(e.origin === "<?php echo $base_url; ?>") {

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
                $('input[name="page_id"]').val(e.data.pageId);
                $('input[name="widget_id"]').val(e.data.widgetId);
                $('#widget_already_set').hide();
                e.source.postMessage({action: "setDone"}, "<?php echo $base_url; ?>");
            } else {
                e.source.postMessage({action: "setFail"}, "<?php echo $base_url; ?>");
            }
          });
      }

        function removeWidget(e) {
            jQuery.post("/admin/config/tawk/removewidget", function(r) {
                if(r.success) {
                    $('input[name="page_id"]').val('');
                    $('input[name="widget_id"]').val('');
                    $('#widget_already_set').hide();
                    e.source.postMessage({action: "removeDone"}, "<?php echo $base_url; ?>");
                } else {
                    e.source.postMessage({action: "removeFail"}, "<?php echo $base_url; ?>");
                }
            });
        }

    jQuery(document).ready(function() {
        if(jQuery("#always_display").prop("checked")){
            jQuery('.show_specific').prop('disabled', true);
        } else {
            jQuery('.hide_specific').prop('disabled', true);
        }

        jQuery("#always_display").change(function() {
            if(this.checked){
                jQuery('.hide_specific').prop('disabled', false);
                jQuery('.show_specific').prop('disabled', true);
            } else {
                jQuery('.hide_specific').prop('disabled', true);
                jQuery('.show_specific').prop('disabled', false);
            }
        });

        // process the form
        jQuery('#module_form').submit(function(event) {
            $path = "/admin/config/tawk/setoptions";
            jQuery.post($path, {
                action     : 'set_visibility',
                ajax       : true,
                page_id    : jQuery('input[name="page_id"]').val(),
                widget_id  : jQuery('input[name="widget_id"]').val(),
                options    : jQuery(this).serialize()
            }, function(r) {
                if(r.success) {
                    $('#optionsSuccessMessage').toggle().delay(3000).fadeOut();
                }
            });

            // stop the form from submitting the normal way and refreshing the page
            event.preventDefault();
        });
    });
    </script>
    <?php
    $markup = ob_get_contents();
    ob_end_clean();
    return $markup;
}
