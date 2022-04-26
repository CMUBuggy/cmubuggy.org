/* Custom JS included in all pages via the cmubuggy cssjs script
 *
 * Remember to update the cachebuster when this file is updated.
 */
function changeTab(hash) {
  hash = hash.replace('#','#tab-');
  $('[href="' + hash + '"]').tab('show');
}

$(function () {
  if (window.location.hash) {
    changeTab(window.location.hash);
  }
});

$(window).on('hashchange', function () {
  changeTab(window.location.hash);
});

$(document)
.on('shown.bs.tab', '.nav-tabs a', function (e) {
  window.location.hash = e.target.hash.replace('#tab-', '#');
})
.on('show.bs.modal', '[id^="youtube-"]', function (e) {
  var $playerDiv = $('div[id^="player-"]', this);
  if ($playerDiv.length == 0) return;
  var $playerParams = { videoId: $playerDiv.data('videoId'), playerVars: {} };

  if (typeof $playerDiv.data('videoStart') !== "undefined") {
    $playerParams["playerVars"]["start"] = $playerDiv.data('videoStart');
  }
  if (typeof $playerDiv.data('videoEnd') !== "undefined") {
    $playerParams["playerVars"]["end"] = $playerDiv.data('videoEnd');
  }

  $(this).data('player', new YT.Player($playerDiv.attr('id'), $playerParams));
})
.on('hide.bs.modal', '[id^="youtube-"]', function (e) {
  $(this).data('player').stopVideo();
});

function onYouTubeIframeAPIReady() {}

// Ensure we scroll any non-tab hash targets to below the header bar.
$(function() {
  // Some browsers may require a delay after the DOM is ready before we can successfully scroll,
  // but it does not appear to be required for modern edge and chrome, at least on our site.
  //
  // So, don't wait.
  //
  // See: https://stackoverflow.com/questions/4086107/fixed-page-header-overlaps-in-page-anchors#35452468
  //
  // setTimeout(doFragmentTargetOffset, 500);
  doFragmentTargetOffset();
});

// Actually perform the scroll.
function doFragmentTargetOffset(){
  var offset = $(':target').offset();
  if(offset){
      var scrollto = offset.top - 60; // minus fixed header height
      $('html,body').animate({scrollTop:scrollto}, 0);
  }
}
