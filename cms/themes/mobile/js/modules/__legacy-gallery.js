define(['jquery','photoswipe','underscore'], function( $ , undef , undef) {

	// actually this is just a wrapper around the 
	// photoswipe gallery instance object.
	// it istantiated that object with images that correspond to the 
	// filter criteria.
	var Gallery = function(filter, options) {
		// filter: filtering options
		// options: {
		//     - restEndpoint.
		//     - photoSwipeOptions
		//     - wrapperEl -> html element that wraps the gallery
		// }

		// save data internally
		this.filter = filter;
		this.options = options;

		// get the artworks that attend the filter.

	};

	// fetch method gets the artworks.
	Gallery.prototype._fetch = function() {

		var _this = this;

		var request = $.ajax({
			url: this.options.restEndpoint,
			type: 'GET',
			dataType: 'json',
			data: _.extend({}, { request: 'filter' }, this.filter),
			cache: false
		});

		request.done(function(data, textStatus, jqXHR) {
			_this.artworks = data.artworks;

			// extract the image urls to a single object, hashed by artwork id.
			_this.images = _.map( data.artworks, function(artwork, id){
				return {
					src: artwork.images.large,
					title: artwork.title,
					id: id
				};
			});


			console.log(_this.images);

			// build the photoswipe gallery.
			_this._build();
		});

		request.fail(function(jqXHR, textStatus, errorThrown) {

		});

		request.always(function(data_or_jqXHR, textStatus, jqXHR_or_errorThrown) {

		});

	};


	// _build runs the logic to setup a photoswipe gallery.
	Gallery.prototype._build = function() {



		// create a shortcut to the PhotoSwipe object
		var PhotoSwipe = window.Code.PhotoSwipe;
		
		// instantiate the gallery using photoswipe
		var options = {
			target: this.options.wrapperEl,

			// hide both captions and toolbars from the photoswipe. 
			// we are going to implement our own toolbars.
			captionAndToolbarHide: true,

			loop: false,

			preventHide: true,

			getImageSource: function(obj){
				return obj.src;
			},
			getImageCaption: function(obj){
				return obj.title;
			},
			getImageMetaData: function(obj) {
				return {
					id: obj.id,
				}
			}
		};




		/*
		remember: photoswipe deals with 3 images at a time,
		so we may load infinite "images" inside a gallery.
		*/
		
		this.psInstance = PhotoSwipe.attach( this.images, options);

		this.psInstance.show(2);
	};

	return Gallery;
});