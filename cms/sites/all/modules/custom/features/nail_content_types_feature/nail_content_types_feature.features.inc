<?php
/**
 * @file
 * nail_content_types_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function nail_content_types_feature_node_info() {
  $items = array(
    'artist' => array(
      'name' => t('Artist'),
      'base' => 'node_content',
      'description' => t('Artist node bundle.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'artwork' => array(
      'name' => t('Artwork'),
      'base' => 'node_content',
      'description' => t('Artwork node bundle type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'gallery' => array(
      'name' => t('Gallery'),
      'base' => 'node_content',
      'description' => t('Gallery node type bundle.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
