<?php

function rest_api_mobile_process_query() {
	$data = $_GET;

	if (!isset($data)) {
		return;
	}



	//////////////////////////////////
	////////// PAGING ////////////////
	//////////////////////////////////


	$length = ( isset( $data['page-length'] ) && $data['page-length'] != 'not-set' ) ? $data['page-length'] : 90;
	$start = ( isset( $data['lastPos'] ) && $data['lastPos'] != 'not-set') ? $data['lastPos'] +1 : 0;


	////////////////////////////////
	/////// PAGING PARAMS //////////
	////////////////////////////////







$ARTISTS = array(
	'Sara Muller',
	'Amanda Mei',
	'Breno Rotatori',
	'Cholito Chowe',
	'Cris Rocha',
	'Feres Khoury',
	'Fernando Schmitt',
	'Giovanna Nucci',
	'Guilherme Portela',
	'Kika Levy',
	'Lilian Maus',
	'Marcelo Gandhi',
	'Marcelo Tinoco',
	'Mirian de Los Angeles',
	'Nina Kreis',
	'Sara Muller',
	'Virna Levin',
);




	// there are two request types:
	// - urls: get the urls hashed by the artwork ID. Accepts filter parameters
	// - full artwork: get all the information about a SINGLE artwork. Only accepts the ID parameter.

	if ($data['request'] == 'single') {

		// single request
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


		// INITIALIZE QUERY
		// (ArtworkQuery is always present, as this module requires the 
		// rest_api.artworkquery.inc file)
		$query = new ArtworkQuery($required_data, $start, $length);

		// directly query for the object
		$query->propertyCondition('nid', $data['id']);

		$artworks = $query->execute();

		// answer here
		if ( count($artworks) > 0) {
			$res = array_shift($artworks);
			$res = json_encode($res);

			print $res;
			die();
		}






















	} elseif ($data['request'] == 'filter') {










		// filter request
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
				'field_image' => array(
					'type' => 'image',
					'alias' => 'images',
					'styles' => array('tile100','large'),	// this is a var used only by the image value getter.
				),
			),
		);


		// INITIALIZE QUERY
		// (ArtworkQuery is always present, as this module requires the 
		// rest_api.artworkquery.inc file)
		$query = new ArtworkQuery($required_data, $start, $length);





		// for the mobile version, the filters available are:
		// - gallery
		// - artist

		// CHECK FILTER CONDITIONS

		// artist
		// filter by artist
		$artist_check =  isset($data['artist']) && $data['artist'] != '' && $data['artist'] != 'not-set';
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
		} else {

			
			// only constrain by exposition if there are no artists selected


			// CONSTRAIN THE QUERY TO ARTWORKS IN EXHIBITION
			$query->fieldCondition('field_on_exhibition', 'value', 'NULL', '!=');



		}



		$gallery_check = isset($data['gallery']) && $data['gallery'] != '' && $data['gallery'] != 'not-set';
		if ($gallery_check) {

			// field_gallery is of type 'entityreference',
			// we need toge tthe id for the gallery and then put the gallery id
			// as a condition for the artwork query.
			$gallery_query = new EntityFieldQuery();

			$gallery_query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'gallery')
				->propertyCondition('title', $data['gallery']);

			$gallery = $gallery_query->execute();
			$gallery = $gallery['node'];
			$gallery = !empty($gallery) ? array_shift($gallery) : FALSE;

			if (!$gallery) {
				// no artwork from the required gallery found.
				$query->fieldCondition('field_gallery', 'target_id', '-1', '=');
			} else {
				$query->fieldCondition('field_gallery', 'target_id', $gallery->nid, '=');
			}

		}



		// CHECK FILTER CONDITIONS





		// RUN QUERY
		$artworks = $query->execute();





		// respond to filter request
		$debug = isset($data['debug']) ? TRUE : FALSE;
		rest_api_mobile_respond(
			$artworks,		// artworks
			NULL,			// message to be sent to the client
			$debug 			// debug mode
		);




	} // close filter request IF







}


// an auxiliary function that formats the response.
// function takes as input an array of artworks and formats them accordingly
// to return a pattern response.
function rest_api_mobile_respond($artworks, $message = NULL, $debug = FALSE) {
	$res = array();

	if (!$artworks) {

		$res['message'] = $message ? $message : 'no-artworks-available';

	} else {
		$res['message'] = $message ? $message : 'artworks-available';
		$res['artworks'] = $artworks;
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