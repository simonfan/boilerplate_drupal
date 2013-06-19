define(['example-module'], function(Example) {

return function() {
	
	test('This test is wrapped inside a function. You can choose when I am going to be run.', function() {
		ok(1);
	});

}
});