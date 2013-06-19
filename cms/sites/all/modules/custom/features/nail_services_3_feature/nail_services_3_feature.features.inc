<?php
/**
 * @file
 * nail_services_3_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nail_services_3_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
