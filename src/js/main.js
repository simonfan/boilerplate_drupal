require.config({
	urlArgs: "bust=" + Math.random(),
	baseUrl: 'src',
	paths: {
		// basic external libraries
		'jquery': 'components/jquery/jquery',
		'underscore': 'components/underscore/underscore',
		'backbone': 'components/backbone/backbone',
		'text': 'components/requirejs-text/text',
		'handlebars': 'components/handlebars/handlebars',

		// components
		'buildable': 'components/buildable/buildable',
		'_.mixins': 'components/_.mixins/_.mixins',
		'taskrunner': 'components/taskrunner/taskrunner',
		'transitions': 'components/transitions/transitions',

		'nav': 'components/nav/nav',

		// pages
		'home': 'js/pages/home',

		// templates
		'template_home': 'templates/home.html',

		'main': 'js/main',
		'app': 'js/app',

		// modules
		// basic own modules
	//	'setup': 'js/modules/setup',
	//	'mixins': 'js/modules/mixins',
	//	'buildable': 'js/modules/buildable',

		'example-module': 'js/modules/example-module',
	},
	shim: {
		'backbone': {
			deps: ['underscore', 'jquery'],
			exports: 'Backbone'
		},
		'handlebars': {
			exports: 'Handlebars'
		}
	}
});
	
// load the main app page
require(['app']);