<?php
/**
 * @file
 * nail_search_api_feature.features.inc
 */

/**
 * Implements hook_default_search_api_index().
 */
function nail_search_api_feature_default_search_api_index() {
  $items = array();
  $items['nail_index'] = entity_import('search_api_index', '{
    "name" : "Nail index",
    "machine_name" : "nail_index",
    "description" : "Index of nodes",
    "server" : "artwork_db_search",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "title" : { "type" : "text", "boost" : "8.0" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_medium" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_year" : { "type" : "integer" },
        "field_artist" : { "type" : "integer", "entity_type" : "node" },
        "search_api_language" : { "type" : "string" },
        "body:value" : { "type" : "text" },
        "field_artist:title" : { "type" : "text", "boost" : "3.0" },
        "field_artist:field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_artist:field_medium" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_artist:field_location" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "artwork" : "artwork" } }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : { "title" : true, "body:value" : true, "field_artist:title" : true } }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : { "body:value" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true, "body:value" : true, "field_artist:title" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 1,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true, "body:value" : true, "field_artist:title" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_page().
 */
function nail_search_api_feature_default_search_api_page() {
  $items = array();
  $items['artworks'] = entity_import('search_api_page', '{
    "index_id" : "nail_index",
    "path" : "admin\\/search_artworks",
    "name" : "Artworks",
    "machine_name" : "artworks",
    "description" : "Search for artworks on Nail",
    "options" : {
      "mode" : "terms",
      "fields" : {
        "title" : "title",
        "body:value" : "body:value",
        "field_artist:title" : "field_artist:title"
      },
      "per_page" : "30",
      "get_per_page" : 1,
      "view_mode" : "search_api_page_result"
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function nail_search_api_feature_default_search_api_server() {
  $items = array();
  $items['artwork_db_search'] = entity_import('search_api_server', '{
    "name" : "Database search",
    "machine_name" : "artwork_db_search",
    "description" : "Search based on Database service",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "3",
      "indexes" : { "nail_index" : {
          "title" : {
            "table" : "search_api_db_nail_index_title",
            "type" : "text",
            "boost" : "8.0"
          },
          "field_tags" : {
            "table" : "search_api_db_nail_index_field_tags",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_medium" : {
            "table" : "search_api_db_nail_index_field_medium",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_year" : {
            "table" : "search_api_db_nail_index_field_year",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_artist" : {
            "table" : "search_api_db_nail_index_field_artist",
            "type" : "integer",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_nail_index_search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "field_artist:title" : {
            "table" : "search_api_db_nail_index_field_artist_title",
            "type" : "text",
            "boost" : "3.0"
          },
          "field_artist:field_tags" : {
            "table" : "search_api_db_nail_index_field_artist_field_tags",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_artist:field_medium" : {
            "table" : "search_api_db_nail_index_field_artist_field_medium",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_artist:field_location" : {
            "table" : "search_api_db_nail_index_field_artist_field_location",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "body:value" : {
            "table" : "search_api_db_nail_index_body_value",
            "type" : "text",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
