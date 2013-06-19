define(['jquery'], function(jQuery) {
  // this module does not return any object.
  // it just sets up a jQuery eventEmitter object to extend to other objects.

  jQuery.eventEmitter = {
    _JQInit: function() {
      this._JQ = jQuery(this);
    },
    emit: function(evt, data) {
      !this._JQ && this._JQInit();
      this._JQ.trigger(evt, data);
    },
    once: function(evt, handler) {
      !this._JQ && this._JQInit();
      this._JQ.one(evt, handler);
    },
    on: function(evt, handler) {
      !this._JQ && this._JQInit();
      this._JQ.bind(evt, handler);
    },
    off: function(evt, handler) {
      !this._JQ && this._JQInit();
      this._JQ.unbind(evt, handler);
    }
  };


});

/*


It’s a mixin, and you can use it like so:
function App() {
  // do stuff
}
 
jQuery.extend(App.prototype, jQuery.eventEmitter);
 
var myApp = new App();
 
// myApp supports events!
 
myApp.on('someEvent', function() {
  alert('someEvent!');
});
myApp.emit('someEvent'); // 'someEvent' alerted

*/