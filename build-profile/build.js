/*
	Hey!
	There is a file in this same directory named build.example.js.

	If you have any doubt on how to configure the build profile, go there and do your research!
*/


({
	appDir: "../src",
	baseUrl: ".",
	dir: "../built",
	mainConfigFile: '../src/js/main.js',

	modules: [
		{
			name: 'main',
			/*
			override: {
				pragmas: {
					fooExclude: true
				}
			},
			include: ["foo/bar/bee"],
			exclude: [
                "foo/bar/bop"
            ],
            excludeShallow: [
                "foo/bar/bot"
            ],
            insertRequire: ["foo/baz"]

			*/
		}
	],
	paths: {
		// Most paths are defined at the mainConfigFile.
		// If you wish to override some of those paths, do so here.
		// Path configuration is a pain in the ***, so be careful (;
	},
	shim: {
		'backbone': {
			deps: ['underscore', 'jquery'],
			exports: 'Backbone'
		},
	},

	waitSeconds: 7,

	// TEXT!
	inlineText: true,
	// TEXT!

	// DEV options
	optimize: 'none',
	skipDirOptimize: true,
//	fileExclusionRegExp: /^\./,
	// DEV options
})