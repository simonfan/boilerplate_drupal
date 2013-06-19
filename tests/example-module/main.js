require.config({
	urlArgs: "bust=" + Math.random(),
	baseUrl: '',
	paths: {
		// basic libraries
		'jquery': '../../src/components/jquery/jquery',
		'underscore': '../../src/components/underscore/underscore',
		'backbone': '../../src/components/backbone/backbone',

		// modules
		// basic own modules
	//	'setup': '../../src/js/modules/setup',
	//	'mixins': '../../src/js/modules/mixins',
	//	'buildable': '../../src/js/modules/buildable',

		// the module files go here
		'example-module': '../../src/js/modules/example-module',

		// DEMO
		'demo-main': 'demo/demo',	// the main file for the demo

		// UNIT TESTS
		'tests-main': 'tests/tests',	// the main file for tests

		// other tests go here
		'example-tests': 'tests/example-tests',
	},
	shim: {
		'backbone': {
			deps: ['underscore', 'jquery'],
			exports: 'Backbone'
		}
	}
});
	
if (window.__unit) {

	// load the tests
	require(['tests-main'], function(undef) {

		// tests were already run in the main tests file

		// QUnit was set not to autostart inline in tests.html
		// finally start the QUnit engine.
		QUnit.load();
		QUnit.start();
	});

} else {

	require(['demo-main'], function(demo) {

	});

}