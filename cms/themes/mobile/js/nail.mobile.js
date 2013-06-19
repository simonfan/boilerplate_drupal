define(['jquery','jquery.mobile','tiles'   ,'psGallery','underscore'], 
function(   $   ,       jqm     , TileView , PSGallery , undef) {




	/// display the selectors only when
	// all the js has been loaded.
	$('#footer-toolbar-wrapper').animate({opacity: 1}, 400);



	var tOptions = _.extend({
		$el: $('#tiles'),
		tilesize: Math.floor( ( $(window).width() - 12 ) / 3 )
	}, CONFIG);

	window.tiles = new TileView(tOptions);



	/////////////////////////
	//////// PS gallery /////
	/////////////////////////

	window.psgallery = new PSGallery({
		captionAndToolbarAutoHideDelay: 0,
		loop: false,
		preventHide: false,
	//	cacheMode: window.Code.PhotoSwipe.Cache.Mode.aggressive,
		backButtonHideEnabled: false,			// do not hide back button.
		getImageSource: function($img){
			return $img.data().images.large;
		},
		getImageMetaData: function($img) {
			return $img.data();
		},

		getImageCaption: function($img){
			var id = $img.data().id;

			return '';
		},

		getToolbar: function(){
			return '<div class="ps-toolbar-close"><div class="ps-toolbar-content"></div></div><div class="ps-toolbar-previous" style="display: none;">Previous</div><div class="ps-toolbar-next" style="display: none;">Next</div><div class="artwork-info-spinner"><img src="'+CONFIG.themeUrl + '/images/loader.gif" /></div><div class="artwork-info-wrapper"></div>';
			// NB. Calling PhotoSwipe.Toolbar.getToolbar() wil return the default toolbar HTML
		}
	});
	/////////////////////////
	//////// PS gallery /////
	/////////////////////////


	tiles.on('fetch-ready', function() {
		tiles.build('reset');
	});


	var CRITERIA = {
		gallery: 'arterix',
		'page-length': 60,
	}

	// INITIAL FETCH
	tiles.fetch('reset', CRITERIA);





	// EVENT HANDLING
	$('.gallery-criteria').change(function() {
		var $this = $(this),
			name = $this.attr('name'),
			value = $this.val();

		CRITERIA[name] = value;

		tiles.fetch('reset', CRITERIA);
	});






	// HANDLE TILE CLICKS
	$('#tiles').delegate('img', 'click', function(e) {

		var data = $(this).data();

		console.log(data);

		window.psgallery.instantiate(window.tiles.images);

		window.psgallery.show(function($img) {
			return $img.data().id == data.id;
		});

		e.preventDefault();
	});




	////////////////////////////////////
	////////////// QR //////////////////
	////////////////////////////////////
	// ___QR___ is set directly inside a script tag by the SERVER.
	if (typeof ___QR___ != 'undefined' && ___QR___) {
		var artist = ___QR___.artist,
			id = ___QR___.id;

		// wait for the first gallery to be ready and then
		// fetch the gallery for the artist
		tiles.once('tiles-built', function(e) {

			$('#artist')
				.val(artist)
				.trigger('change');

			tiles.once('tiles-built', function(e) {
				console.log('tile built');

				// instantiate photoswipe
				window.psgallery.instantiate(tiles.images);

				// then show at the required object
				window.psgallery.show(function($img) {
					return $img.data().id == ___QR___.artwork_id;
				});

			});
		})


	}


});