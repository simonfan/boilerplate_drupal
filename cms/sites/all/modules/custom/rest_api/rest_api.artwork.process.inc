<?php

function rest_api_artwork_process_query() {
	$data = $_GET;

	if (!isset($data)) {
		return;
	}

	$required_data = array(
		// properties: property_name
		'properties' => array(
			'title' => array(
				'alias' => 'title',
			),
			'nid' => array(
				'alias' => 'id',
			)
		),
		// fields: field_name => array( key_in_field => , alias => );
		'fields' => array(
			'field_artist' => array(
				'type' => 'entityreference',
				'required_entity_fields' => array('title'),
				'key' => 'target_id',
				'alias' => 'artist'
			),
			'body' => array(
				'key' => 'value',
				'alias' => 'observations',
			),
			'field_image' => array(
				'type' => 'image',
				'alias' => 'images',
				'styles' => array('thumbnail', 'medium', 'large'),	// this is a var used only by the image value getter.
			),
			'field_price' => array(
				'key' => 'value',
				'alias' => 'price',
			),
			'field_colors' => array(
				'key' => 'rgb',
				'alias' => 'colors',
			),
			'field_height' => array(
				'key' => 'value',
				'alias' => 'height',
			),
			'field_width' => array(
				'key' => 'value',
				'alias' => 'width',
			),
			'field_depth' => array(
				'key' => 'value',
				'alias' => 'depth',
			)
		),
	);





	//////////////////////////////////
	////////// PAGING ////////////////
	//////////////////////////////////


	$length = ( isset( $data['page-length'] ) && $data['page-length'] != 'not-set' ) ? $data['page-length'] : 21;
	$start = ( isset( $data['lastPos'] ) && $data['lastPos'] != 'not-set') ? $data['lastPos'] +1 : 0;


	////////////////////////////////
	/////// PAGING PARAMS //////////
	////////////////////////////////






	/////////////////////////////////////////
	/////////// TEMPORARY ///////////////////
	/////////////////////////////////////////

	// for now, we redirect the search by here, because of the front-end. 
	// As at the client-side the url used is the same.
	if ($_GET['action'] == 'search-request' && !empty($_GET['query']) && $_GET['query'] != 'not-set' ) {
		$index = search_api_index_load("nail_index");

		// build the search query object
		$search_query = new SearchApiQuery($index);

		// parse a query
		$search_query->keys($_GET['query']);

		// set the range
		$search_query->range($start, $length);

		$data = $search_query->execute();
		$results = $data['results'];

		// all the results contain are the ID's with the scores.
		// now get the entities effectively.
		$artworks = array();

		if (!empty($results)) {
			$ids = array_keys($results);

			$artworks = node_load_multiple($ids);

			// filter out the data out of the required_data array.
			foreach ($artworks as $id => $artwork) {
				$artworks[ $id ] = new ArtworkObj($artwork, $required_data);
			}
		}

		rest_api_artwork_respond($artworks, 'search-query response', $_GET['debug']);
	}






	//////////////////////////////////////////
	////////// TEMPORARY /////////////////////
	//////////////////////////////////////////















	$query = new ArtworkQuery($required_data, $start, $length);

	if (isset($data['id'])) {
		// directly query for the object
		$query->propertyCondition('nid', $data['id']);

		$artworks = $query->execute();

		if ( count($artworks) > 0) {
			$res = array_shift($artworks);
			$res = json_encode($res);

			print $res;
			die();
		}

	} else {

		////////////////////////////////////////
		///// ORDER BY STICKY //// /////////////
		////////////////////////////////////////

		// set the query to be ordered by 'sticky'
		$query->propertyOrderBy('sticky', 'DESC');
		$query->propertyOrderBy('created', 'DESC');

		// set the field_image as a pre condition
		$query->fieldCondition('field_image', 'fid', 'NULL', '!=');




		// filter by medium
		// check if medium was passed
		$medium_check = rest_api_check_received_data($data['medium']);
		if ( $medium_check ) {
			// field_medium is a taxonomy_term_reference, so we must load the 
			// taxonomy term that corresponds to the given medium, then
			// set it as a field condition
			$term = taxonomy_get_term_by_name($data['medium'], 'medium');
			$term =  (!empty($term)) ? array_shift($term) : FALSE;

			if (!$term) {
				$query->fieldCondition('field_medium', 'tid', '-1', '=');
			} else {
				$query->fieldCondition('field_medium','tid', $term->tid, '=');
			}
			
		}

		// filter by color
		$color_check = rest_api_check_received_data($data['color']);
		if ( $color_check ) {
			// we must build the color, because the client cannot pass the '#122351' string via GET.
			$color = '#' . $data['color'];

			$query->fieldCondition('field_colors', 'rgb', $color, '=');
		}

		// filter by width, height and depth
		// as the size filter always assumes squares or cubes, one measure is enough
		$size_check = rest_api_check_received_data($data['size']);
		if ( $size_check ) {

			// as the sizes we deal with are always integers, 
			// we may define a pseudo-maxsize and a pseudo-minsize
			// that are not integers, but numbers between them
			// Always multiply by 100, in order to get the centimetre measure

			// only filter by size if it is not set to 0;
			if ($data['size'] != 0) {
				$max_size = $data['size'] + 30;
				$min_size = $data['size'] - 30;

				$measures = array(
					'field_width',
					'field_height',
			//		'field_depth'			// ignore field depth for now..
				);

				foreach($measures AS $m) {
					$query->fieldCondition($m, 'value', $min_size, '>=');

					// only set a max size if the size is not 300
					if ($data['size'] != 300) {
						$query->fieldCondition($m, 'value', $max_size, '<=');
					}
				}

			}

		}

		//////////////////////////////////////////////
		////////////// PRICE /////////////////////////
		//////////////////////////////////////////////

		$priceValues = array(
			1000, 2500, 5000, 7500, 10000, 15000, 20000, 30000, 40000,
			50000, 75000, 100000, 150000, 200000, 300000, 1000000000
		);

		// filter by min-price
		$price0_check = ( isset($data['price']) && is_array($data['price']) );
		if ( $price0_check ) {

			$min_price = $priceValues[ $data['price'][0] ];

			$query->fieldCondition('field_price', 'value', $min_price, '>=');
		}


		// filter by max-price
		$price1_check = ( isset($data['price']) && is_array($data['price']) );
		if ( $price1_check ) {

			$max_price = $priceValues[ $data['price'][1] ];

			$query->fieldCondition('field_price', 'value', $max_price, '<=');
		}

		//////////////////////////
		/// ADDITIONAL FILTERS ///
		//////////////////////////

		// filter by artist
		$artist_check = rest_api_check_received_data($data['artist']);
		if ( $artist_check ) {

			// as field_artist is of type 'entityreference', 
			// we need to get the id for the artist and then
			// put the id in the fieldCondition.
			$artist_query = new EntityFieldQuery();

			$artist_query->entityCondition('entity_type', 'node')
				->entityCondition('bundle','artist')
				->propertyCondition('status',1)
				->propertyCondition('title', $data['artist']);

			$artist = $artist_query->execute();
			$artist = $artist['node'];
			$artist = !empty($artist) ? array_shift($artist) : FALSE;

			if (!$artist) {
				// none found, there should be no artworks for this query.
				$query->fieldCondition('field_artist', 'target_id', '-1', '=');
			} else {
				$query->fieldCondition('field_artist', 'target_id', $artist->nid , '=');
			}
		}

		// filter by tags
		$tags_check = rest_api_check_received_data($data['tags']);
		if ( $tags_check && count($data['tags']) > 0 ) {
			foreach($data['tags'] AS $tag_name) {
				// field_tags is a taxonomy_term_reference, so we must load the 
				// taxonomy term that corresponds to the given tag, then
				// set it as a field condition
				$term = taxonomy_get_term_by_name($tag_name, 'tags');
				$term =  (!empty($term)) ? array_shift($term) : FALSE;

				if (!$term) {
					$query->fieldCondition('field_tags', 'tid', '-1', '=');
				} else {
					$query->fieldCondition('field_tags','tid', $term->tid, '=');
				}
			}
		}

		$artworks = $query->execute();
	}







	
	$debug = isset($data['debug']) ? TRUE : FALSE;
	rest_api_artwork_respond(
		$artworks,		// artworks
		NULL,			// message to be sent to the client
		$debug 			// debug mode
	);
}















/// helper functions
function rest_api_check_received_data($data, $not_set_value = 'not-set') {
	return ( isset($data) && $data != '' && $data != $not_set_value);
}



// function takes as input an array of artworks and formats them accordingly
// to return a pattern response.
function rest_api_artwork_respond($artworks, $message = NULL, $debug = FALSE) {
	$res = array();

	if (!$artworks) {

		$res['message'] = $message ? $message : 'no-artworks-available';

	} else {
		$res['message'] = $message ? $message : 'artworks-available';
		$res['artworks'] = $artworks;

		// shuffle the idList
		shuffle($res['artworks']);
	}


	if ($debug) {
		echo '<pre>';
		var_dump($res);
	} else {
		$res = json_encode($res);
		echo $res;
	}

	die();
}