<?php

function rest_api_mail($key, &$message, $params) {

  switch ($key) {
    case 'contact':

      // note: data can be passed to this function in the $params array
      $message['subject'] = $params['subject'];
      $message['body'] = $params['body'];
      break;    
  }
}


function rest_api_contact_process_query() {
	$data = $_GET;

	var_dump($_GET);

	if (!isset($data)) {
		return;
	}

	$from = $_GET['email'];
	$params = array(
		'subject' => 'Contato de '. $_GET['name'] .' ('. $_GET['email'] .')',
		'body' => array( $_GET['message'] ),
	);

	$email_success = drupal_mail('rest_api', 'contact', 'it@nailonwall.com', 'english', $params, 'it@nailonwall.com', TRUE);

	$email_success = drupal_mail('rest_api', 'contact', 'contato@nailonwall.com', 'english', $params, 'it@nailonwall.com', TRUE);


	echo '<br>status: <pre>'. print_r($email_success, TRUE);
}