define(['backbone','transitions','home','nav'],
function(Backbone , Transitions , Home , Nav ) {
	console.log('App running');


	// build the nav
	$('#main-nav').Nav({ dropdownInteraction: 'hover' });


	var Router = Backbone.Router.extend({
		routes: {
			'*anything': 'home'
		},
	});

	// define the router
	window.Globals = {
		router: new Router(),									// router
		transitions: Transitions.build({ $ul: $('#pages') }),	// transitions object
	}


	// hook on router events
	Globals.router.on('route:home', function(route) {
		Home({
			route: route,
			Globals: Globals,
		});
	});

	// start backbone history.
	Backbone.history.start({ pushState: true });
});