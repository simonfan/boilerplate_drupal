define(['_.interface'], function(undef) {


	window.data = {
		no: 1,
		obj: {},
		str: 'string',
	}

	_.interface({
		id: 'Demo interface',
		obj: data,
		typeofs: {
			no: 'number',
			obj: 'object',
			str: 'string',
			str_or_undef: ['undefined', 'string']
		}
	});
});