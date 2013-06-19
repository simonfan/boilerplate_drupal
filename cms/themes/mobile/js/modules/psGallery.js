define(['jquery','photoswipe','underscore'], function($, undef, undef) {

	var PSGallery = function(options) {
		this.options = options;
	}

	PSGallery.prototype.instantiate = function(images) {
		// images:
		// at: index of image to show or a function
		// to filter that image out.

		// save images
		this.images = images;

		var _this = this,
			PhotoSwipe = window.Code.PhotoSwipe;

		this.instance = PhotoSwipe.attach(images, this.options);


		// onDisplayImage
		this.instance.addEventHandler(PhotoSwipe.EventTypes.onDisplayImage, function(e){
			var curImg = _this.instance.getCurrentImage();

			console.log(curImg);

			_this.setImageData(curImg.metaData.id);
		});

	};


	PSGallery.prototype.show = function(at) {
		// now get the index of the image to be shown.
		if (typeof at === 'function') {
			at = _.find(this.images, at);
		}

		at = at ? at : 0;

		this.instance.show(at);
	};


	PSGallery.prototype.destroy = function() {
		var instance = this.instance;

		window.Code.PhotoSwipe.unsetActivateInstance(instance);
		window.Code.PhotoSwipe.detatch(instance); 
	}






	PSGallery.prototype.setImageData = function(id) {
		// first set all the html data fields to loading value.
		$('.ps-caption-content').html('');
		$('.artwork-info-wrapper').html('');

		// spin the info spinner.
		$('.artwork-info-spinner').animate({opacity: 1}, 300);

		var request = this._getArtworkData(id);

		request.done(function(data, textStatus, jqXHR) {
			console.log('single request answered');
			console.log(data);

			if (data.price) {
				$('.ps-caption-content').html('R$ ' + data.price);
			}


			// build the information at bottom.
			var bottomInfo = data.artist.title 

			if (data.observations) {
				bottomInfo += ' - ' + data.observations;
			}

			$('.artwork-info-wrapper').html(bottomInfo);
		});

		request.fail(function(jqXHR, textStatus, errorThrown) {
			$('.ps-caption-content').html('---');

			$('.artwork-info-wrapper').html('---');
		});

		request.always(function(data_or_jqXHR, textStatus, jqXHR_or_errorThrown) {
			$('.artwork-info-spinner').animate({opacity: 0}, 300);
		});
	}









	// internal methods
	PSGallery.prototype._getArtworkData = function(id) {
		var request = $.ajax({
			url: CONFIG.restEndpoint,
			type: 'GET',
			dataType: 'json',
			data: { 
				request: 'single',
				id: id
			},
			cache: false
		});

		return request;
	}

	return PSGallery;
});