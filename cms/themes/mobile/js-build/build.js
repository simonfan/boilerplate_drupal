({
	appDir: "../",
	baseUrl: "js",
	dir: "../js-build-res",
	modules: [
		{
			name: 'lib/requirejs/almond',
			include: ['main']
		}
	],
	paths: {
		'main': 'main',
	
		'nail.mobile': 'nail.mobile',

		'jquery': 'lib/jquery-1.9.1.min',
		'jquery.mobile': 'lib/jquery.mobile/jquery.mobile-1.3.0',

		// photoswipe
		'klass': 'lib/photoswipe/lib/klass.min',
		'photoswipe': 'lib/photoswipe/code.photoswipe.jquery-3.0.5',

		'underscore': 'lib/underscore-1.4.4.min',

		// jq mixins
		'jqEventEmitter': 'modules/jqEventEmitter',

		// modules
		'image': 'modules/image',
		'tiles': 'modules/tiles',
		'psGallery': 'modules/psGallery',
	},
	shim: {
		'jquery.mobile': {
			deps: ['jquery'],
		//	exports: 'Templates'
		},
		'photoswipe': {
			deps: ['klass']
		}
	}
})