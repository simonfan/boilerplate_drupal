define(['jquery','text!template_home','handlebars','taskrunner'],
function(   $   , template_home      , undef      , Taskrunner ) {

	// define the tasks

	// 0
	// parse parameters
	function parsequery(promise, common) {
		console.log('parsequery');

		console.log(common.route);

		promise.resolve();
	}

	// 1
	// fetch data according to query
	function fetchdata(promise, common) {
		// expect query object to be at common.query
		console.log('home fetchdata run');

		setTimeout(function() {

			common.data = {
				itemIds: [20, 65, 88]
			};

			promise.resolve();
		}, 1000);
	}

	// 2
	// render the page using the data provided by the previous task
	// (if the page hasn't been rendered yet by the server)
	function renderhtml(promise, common) {
		// expect data to be set on common.data;
		console.log('home renderhtml run');
		console.log('data received:', common.data);

		var tpl = Handlebars.compile(template_home),
			html = tpl(common.data);

		common.$home = $('#home');

		common.$home.html( html );

		promise.resolve();
	}

	// 3
	// set any js code, events, etc on the elements
	function setupjs(promise, common) {
		console.log('setupjs');

		promise.resolve();
	}

	// 4
	// display the page
	function display(promise, common) {
		// expect the global transitions object on commmon.Globals.Transitions
		console.log('display');

		common.$home.animate({ opacity: 1 }, {
			complete: promise.resolve
		});
	}

	// define the taskrunner
	var hometasks = Taskrunner.build(
		['parsequery','fetchdata','renderhtml','setupjs','display'],											// taskorder
		{ parsequery: parsequery, fetchdata: fetchdata, renderhtml: renderhtml, setupjs: setupjs, display: display }	// tasks (defined in a hash)
	);

	// listen to some events on the hometasks
	// set loading data
	hometasks.on('sequence-start', function() {
		console.log('seq sequence-start')
	});

	hometasks.on('sequence-complete', function() {
		console.log('sequence-complete')
	});

	// return the function to be run by the router
	return hometasks.run;
});