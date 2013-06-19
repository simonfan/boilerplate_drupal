<?php

/**
 * Pre-process data to be filled in the index page.
 * Discover which page is being requested, retrieve additional data
 * and build titles, descriptions and metatags for the page requested.
 */

// URL configurations
global $base_url;
global $base_path;
global $theme_path;

$theme_url = $base_url .'/'. $theme_path;


// decode the queried url.

$url_query = explode('/', $_GET['q']);







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
	'Anete Ring',
);


$DICTIONARY = array(
	// qrID => nID
	41 => 480,
	42 => 481,
	50 => 684,
	47 => 688,
	39 => 740,
	40 => 741,
	38 => 742,
	7 => 775,
	22 => 832,
	21 => 835,
	20 => 841,
	5 => 888,
	6 => 889,
	17 => 907,
	16 => 908,
	19 => 909,
	4 => 1013,
	14 => 1081,
	51 => 1112,
	30 => 1114,
	31 => 1115,
	26 => 1116,
	25 => 1117,
	28 => 1118,
	27 => 1119,
	29 => 1120,
	9 => 1122,
	8 => 1123,
	10 => 1124,
	2 => 1127,
	1 => 1129,
	13 => 1134,
	11 => 1142,
	44 => 1146,
	48 => 1147,
);





?>


<!DOCTYPE html>
<html>

<head>

	<title>Nail on Wall</title>

	<!-- meta tags -->
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no">
		
	


	<!-- QR! -->
	<script type="text/javascript">

		<?php

		if ($url_query[0] == 'qr' && !empty($url_query[1]) ) {

			// create a entityFieldQuery
			$query = new EntityFieldQuery();

			$query
				// we're interested in ARTWORK NODES
				->entityCondition('entity_type', 'node')
				->entityCondition('bundle','artwork')
				// Default to published
				->propertyCondition('status', 1)
				// where the QR id is equal to the url queried value
				->fieldCondition('field_qr_id', 'value', $url_query[1], '=');



			// load the node
			$nid_query = $query->execute();
			$nid_query = !empty($nid_query['node']) ? $nid_query['node'] : FALSE;

			if ($nid_query) {
				$nid_query = array_shift($nid_query);
			} else {
				return;
			}

			$node = node_load($nid_query->nid);

			// get entity ref
			$artist_entity_ref = field_get_items('node', $node, 'field_artist');
			$artist_entity_ref = array_shift($artist_entity_ref);

			// artist id
			$a_id = $artist_entity_ref['target_id'];

			// artist object
			$artist = node_load($a_id);

			// name
			$a_name = $artist->title;

			echo 'window.___QR___ = { artist: "'. $a_name .'", artist_id: "'. $a_id .'", artwork_id: "'. $node->nid .'" }';
		};

		?>
	</script>





	
	<!-- Raleway -->
<!--	<link href='http://fonts.googleapis.com/css?family=Raleway:400,600,500,700' rel='stylesheet' type='text/css'>
	<!-- Neuton -->
<!--	<link href='http://fonts.googleapis.com/css?family=Neuton:200,300,400' rel='stylesheet' type='text/css'>
	
-->
	<!-- the main stylesheet -->
	<link rel="stylesheet" type="text/css" href="<?php print $theme_url; ?>/css/style.css" />
	<!-- jquery mobile css -->
	<link rel="stylesheet" type="text/css" href="<?php print $theme_url; ?>/js/lib/jquery.mobile/jquery.mobile-1.3.0.min.css" />
	<!-- photoswipe css -->
	<link rel="stylesheet" type="text/css" href="<?php print $theme_url; ?>/js/lib/photoswipe/photoswipe.css" />



	<!-- javascript will be loaded through requireJS -->


	<!-- config script -->
	<script>
		window.CONFIG = {
			siteBaseUrl: '<?php print $base_url; ?>',

			themeUrl: '<?php print $theme_url;?>',

			jsBaseUrl: '<?php print $theme_url."/js";?>',
			resourcesUrl: '<?php print $base_url; ?>',

			restEndpoint: '<?php print $base_url; ?>/rest/mobile',

			artworkEndpoint: '<?php print $base_url; ?>/rest/artwork',
			artistEndpoint: '<?php print $base_url; ?>/rest/artist',
		};
	</script>
	
	<!-- main.js file! -->
	<script data-main="<?php print $theme_url; ?>/js/main.js" src="<?php print $theme_url; ?>/js/lib/requirejs/requireJS.min.js" ></script>
	
	<!-- remember!: we are going to use almond.js!!!! -->


</head>
	
<body>

	<!-- jquery mob page -->
	<div data-role="page" data-theme="a" data-fullscreen="true">

<!-- no header.
		<div data-role="header" id="header" data-position="fixed">
			<h1>Header</h1>
		</div>
-->

		<div data-role="content" id="content">
			<!-- tiles div -->
			<ul data-role="none" id="tiles"></ul>

		</div>
		
		<div data-role="footer" id="footer" data-position="fixed" data-tap-toggle="false">

			<div data-role="none" id="footer-toolbar-wrapper" style="opacity: 0;">

				<select class="gallery-criteria" name="artist" id="artist">
					<option value="not-set">All artists</option>

					<?php
						foreach ($ARTISTS as $key => $a_name) {
							echo '<option>'. $a_name .'</option>';
						}
					?>
				</select>

				<select class="gallery-criteria" name="onwall" id="onwall" data-role="slider">
					<option value="onwall">Only exhibited</option>
					<option value="all">All artworks</option>
				</select>

			</div>
		</div>
		
		
	</div>
	
</body>
</html>
