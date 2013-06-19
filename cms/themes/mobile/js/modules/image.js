define(['jquery'], function($) {
	var Image = function(info) {
		// info: src, data

		var $img = $('<img src="'+ info.src +'" />');
		
		$img.data(info.data)
			.load(function() {
				$(this).fadeIn(400, function () {
					$(this).css('display', 'block')
				});
			});

		return $img;
	}

	return Image;
});