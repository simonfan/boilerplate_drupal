define(["jquery","photoswipe","underscore"],function(e,t,t){var n=function(e,t){this.filter=e,this.options=t};return n.prototype._fetch=function(){var t=this,n=e.ajax({url:this.options.restEndpoint,type:"GET",dataType:"json",data:_.extend({},{request:"filter"},this.filter),cache:!1});n.done(function(e,n,r){t.artworks=e.artworks,t.images=_.map(e.artworks,function(e,t){return{src:e.images.large,title:e.title,id:t}}),console.log(t.images),t._build()}),n.fail(function(e,t,n){}),n.always(function(e,t,n){})},n.prototype._build=function(){var e=window.Code.PhotoSwipe,t={target:this.options.wrapperEl,captionAndToolbarHide:!0,loop:!1,preventHide:!0,getImageSource:function(e){return e.src},getImageCaption:function(e){return e.title},getImageMetaData:function(e){return{id:e.id}}};this.psInstance=e.attach(this.images,t),this.psInstance.show(2)},n});