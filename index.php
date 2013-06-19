<?php
// LOAD DRUPAL!
chdir('cms');
/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

/*
	As a result of Drupal 7 bootstraping, we have all the following globals:

	$base_path					The base path of the Drupal installation.
	$base_root					The root URL of the host, excluding the path.
	$base_theme_info			An array of objects that represent the base theme.
	$base_url					The base URL of the Drupal installation.
	$channel					An associative array containing title, link, description and other keys.
	$conf						Array of persistent variables stored in 'variable' table.
	$cookie_domain				The domain to be used for session cookies.
	$databases					Array of database connections.
	$drupal_test_info			Global variable that holds information about the tests being run.
	$element					Structured array describing the data to be rendered.
	$forum_topic_list_header	An array of forum topic header information.
	$image						Current image tag used by aggregator parsing.
	$installed_profile			The name of the profile that has just been installed.
	$is_https					Boolean indicating whether or not the current request is secured by HTTPS.
	$item						General string or array.
	$items						Array of items used by aggregator.
	$language					An object containing the information for the active interface language.
	$language_content			An object containing the information for the active content language.
	$language_url				An object containing the information for the active URL language.
	$menu_admin					Boolean indicating that a menu administrator is running a menu access check.
	$multibyte					The current multibyte mode.
	$pager_limits				Array of the number of items per page for each pager.
	$pager_page_array			Array of current page numbers for each pager.
	$pager_total				Array of the total number of pages for each pager.
	$pager_total_items			Array of the total number of items for each pager.
	$tag						Active tag name.
	$theme						Name of the active theme.
	$theme_engine				The theme engine related to the active theme.
	$theme_info					Active theme object.
	$theme_key					Name of the active theme.
	$theme_path					The path to the active theme.
	$timers						Timers that have been created by timer_start().
	$update_free_access			Allows the update.php script to be run when not logged in as administrator.
	$user						An object representing the user currently visiting the site.

	http://api.drupal.org/api/drupal/globals
*/

////////////////
//// INIT //////
////////////////
// require_once('server/init.php');


?>
<!doctype html>

<html>

<head>

	<meta charset="utf-8">
	
	<title>Module boilerplate</title>

	<!-- main stylesheet -->
	<link rel="stylesheet" type="text/css" href="src/css/style.css">

	<?php
		// build the needed metatags
	//	echo metatags_build($_GET['q']);
	?>
	
</head>

<body>

	<ul id="main-nav" class="nav horizontal">
		<li class="dropdown">
			<a id="apresentacao" href="/apresentacao">APRESENTAÇÃO</a>
			<ul>
				<li class="button"><a id="apresentacao/guia" href="/apresentacao/guia">COMO FUNCIONA?</a></li>
				<li class="button"><a id="apresentacao/quem-somos" href="/apresentacao/quem-somos">QUEM SOMOS</a></li>
			</ul>
		</li>
		<li class="dropdown">
			<a href="/biblioteca">BIBLIOTECA</a>
			<ul>
				<li class="button"><a id="biblioteca/iniciantes" href="/biblioteca/iniciantes">INICIANTES</a></li>
				<li class="button"><a id="biblioteca/autonomos" href="/biblioteca/autonomos">AUTÔNOMOS</a></li>
				<li class="button"><a id="biblioteca/voraz" href="/biblioteca/voraz">VORAZ</a></li>
			</ul>
		</li>
		<li class="dropdown">
			<a id="leitores" href="/leitores">CÍRCULO DE LEITORES</a>
			<ul>
				<li class="button"><a id="leitores/mural" href="/leitores/mural">MURAL</a></li>
				<li class="button"><a id="leitores/chat" href="/leitores/chat">CHAT</a></li>
			</ul>
		</li>
		<li class="button"><a id="bau" href="/bau">BAÚ</a></li>
		<li class="dropdown">
			<a id="servicos" href="/servicos">SERVIÇOS</a>
			<ul>
				<li class="button"><a id="servicos/assinatura" href="/servicos/assinatura">MURAL</a></li>
				<li class="button"><a id="servicos/livros" href="/servicos/livros">CHAT</a></li>
			</ul>
		</li>
		<li style="float: none; clear: both; border: none;"></li>
	</ul>

	<ul id="pages">
		<li id="home">
			<!-- the home.html template will be rendered here -->
		</li>
	</ul>

	<!-- load scripts at the end -->
	
	<script type="text/javascript" data-main="src/js/main.js" src="src/components/requirejs/require.js"></script>
	
</body>

</html>
