<?php

function rest_api_search_process_query() {
	$index = search_api_index_load("nail_index");

	// build the search query object
	$search_query = new SearchApiQuery($index);

	// parse a query
	$search_query->keys($_GET['query']);

	$data = $search_query->execute();
	$results = $data['results'];

	if ($_GET['debug']) {
		echo 'query = ' . $_GET['query'];
		echo '<pre>';
		var_dump($results);
	} else {
		$res = json_encode($results);
		print_r($res);
	}
}