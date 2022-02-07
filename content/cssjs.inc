<!--CSS-->
<link rel="stylesheet" href="/css/cmubuggy-bootstrap.css" />
<style>
  body { margin-top: 4.5rem; }
  @supports ((postition: -webkit-sticky) or (position: sticky)) {
    #navigation {
      z-index: 1000;
      background: #fff;
      position: -webkit-sticky;
      position: sticky;
      top: 3.5rem;
      max-height: calc(100vh - 3.5rem);
      overflow-y: auto;
      margin-top: -1rem;
    }
    @media (min-width: 992px) {
      #navigation {
        margin-top: 0;
        top: 4.5rem;
        max-height: calc(100vh - 4.5rem);
      }
    }
  }
  .navbar-dark .navbar-toggler { border-color: #fff; }
  .navbar-dark .navbar-toggler-icon { background-image: url("data:image/svg+xml;charset=utf8,%3Csvg viewBox='0 0 30 30' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath stroke='%23fff' stroke-width='2' stroke-linecap='round' stroke-miterlimit='10' d='M4 7h22M4 15h22M4 23h22'/%3E%3C/svg%3E"); }
  .img-fa { width: .875em; margin: .0675em auto; position: absolute; top: 0; bottom: 0; left: 0; right: 0; }
  #googlesearch input[type="text"] { background-position: .375rem center !important; }
  .youtube-preview { width: 120px; }
  .youtube-preview img { width: 120px; height: 90px; }
  .video-grid { margin-left: -.5rem; margin-right: -.5rem; }
  .video-grid > a { margin-left: .5rem; margin-right: .5rem; }
  .raceday-thumb { width: 3em; }
  .sponsors img { max-width: 200px; max-height: 200px; }
  @supports (object-fit: contain) { .sponsors img { object-fit: contain; width: 200px; } }
</style>

<!--JS-->
<script src="https://code.jquery.com/jquery-3.2.1.min.js" integrity="sha256-hwg4gsxgFZhOsEEamdOYGBf13FyQuiTwlAQgxVSNgt4=" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.0/js/bootstrap.min.js" integrity="sha384-uefMccjFJAIv6A+rW+L4AHf99KvxDjWSu1z9VI8SKNVmz4sk7buKt/6v9KI65qnm" crossorigin="anonymous"></script>
<script defer src="https://use.fontawesome.com/releases/v5.14.0/js/all.js" integrity="sha384-3Nqiqht3ZZEO8FKj7GR1upiI385J92VwWNLj+FqHxtLYxd9l+WYpeqSOrLh0T12c" crossorigin="anonymous"></script>
<script type="text/javascript" src="/js/googleanalytics.js"></script>
<script src="https://www.youtube.com/iframe_api" defer></script>
<script type="text/javascript">
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
    $(this).data('player', new YT.Player($playerDiv.attr('id'), { videoId: $playerDiv.data('videoId') }));
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
</script>
