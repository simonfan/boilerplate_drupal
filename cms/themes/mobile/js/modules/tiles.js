define(['jquery','image','jqEventEmitter','underscore'], 
function(   $   , Image ,      undef     ,     undef  ) {
	// for now, all this module does is set up the tile stuff.

	var TileView = function(options) {
		// OPTIONS: restEndpoint, $el, criteria, tilesize

		// bind methods
		_.bindAll(this);

		// save the options
		this.options = _.extend({
			tilesize: 100,
		}, options);

		// save the wrapper
		this.$el = options.$el;

		// save filter criteria
		this.criteria = options.criteria;

		// create the array that holds the artworks.
		this.artworks = {};

		// create the array that holds the images.
		this.images = [];


		// initialization logic:
		this.initialize();
	}

	// make TileView an Event emiiter
	$.extend(TileView.prototype, $.eventEmitter);


	TileView.prototype.initialize = function() {
		console.log('Tile view initialized');


		// get the window dimensions;
		$w = $(window);

		this.wDimensions = {
			height: $w.height(),
			width: $w.width(),
		};

	};


	// fetch method gets the artworks.
	TileView.prototype.fetch = function(action, criteria) {
		// action: string: 'reset', 'merge'
		var _this = this;

		var request = $.ajax({
			beforeSend: function() { $.mobile.showPageLoadingMsg(); }, //Show spinner

			url: this.options.restEndpoint,
			type: 'GET',
			dataType: 'json',
			data: _.extend({}, { request: 'filter' }, criteria),
			cache: false
		});


		// emit the fetch start event.
		this.emit('fetch-start');

		request.done(function(data, textStatus, jqXHR) {

			// save the artworks.
			if (action === 'reset') {
				_this.artworks = data.artworks;

			} else if (action === 'merge') {
				_.each(data.artworks, function(artwork, id) {
					_this.artworks[id] = artwork;
				});
			}

			console.log(_this.artworks);


			

			// trigger the "fetch-ready" event
			_this.emit('fetch-ready');
		});

		request.fail(function(jqXHR, textStatus, errorThrown) {

		});

		request.always(function(data_or_jqXHR, textStatus, jqXHR_or_errorThrown) {
			$.mobile.hidePageLoadingMsg();		// hide spinner
		});

	};


	// adds a single image to the tile gallery.
	TileView.prototype.addTile = function(src, data) {

		var _this = this,
			$img = new Image({
				src: src,
				data: data
			}),
			$li = $('<li></li>');

		$li.css({
				'height': this.options.tilesize,
				'width': this.options.tilesize,
			})
			.append($img);

		// append the image to the $el
		this.$el.append($li);

		this.images.push($img);
	}


	// build method uses an array of artworks and builds the tile gallery from
	// those.
	TileView.prototype.build = function(action) {
		var _this = this;

		if (action === 'reset') {
			this.reset();
		}

		_.each(this.artworks, function(artwork, id) {

			if (!artwork.__tiled || typeof artwork.__tiled === 'undefined') {

				var tileSrc = _this._selectTile(artwork, _this.wDimensions),
					data = {
						id: id,
						images: artwork.images,
					};

				_this.addTile(tileSrc, data);

				// after adding the tile, set a property on the artwork object
				// defining that it has already been rendered
				artwork.__tiled = true;
			}
		});


		this.emit('tiles-built');
	};


	// reset
	TileView.prototype.reset = function() {
		this.images = [];
		this.$el.html('');
	}




	// private functions

	// _selectTile evaluates the window dimensions and returns the
	// appropriate src for the tile image.
	TileView.prototype._selectTile = function(artwork, dimensions) {

		dimensions = dimensions ? dimensions : this.wDimensions;

		var images = artwork.images;

		if (dimensions.width < 500) {
			// phone device..
			return images.tile100 ? images.tile100 : images.original;
		} else if (dimensions.width < 1000) {
			// tablet
			return images.tile100 ? images.tile100 : images.original;
		} else {
			// big.
			return images.tile100 ? images.tile100 : images.original;
		}
	}



	return TileView;
});