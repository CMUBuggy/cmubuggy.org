<!--CSS-->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
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
</style>

<!--JS-->
<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script defer src="https://use.fontawesome.com/releases/v5.0.8/js/all.js" integrity="sha384-SlE991lGASHoBfWbelyBPLsUlwY1GwNDJo3jSJO04KZ33K2bwfV9YBauFfnzvynJ" crossorigin="anonymous"></script>
<script type="text/javascript" src="/js/jquery.editinplace.js" ></script>
<script type="text/javascript" src="/js/googleanalytics.js"></script>
<script type="text/javascript" src="https://www.google.com/recaptcha/api/js/recaptcha_ajax.js"></script>
<script type="text/javascript" src="https://apis.google.com/js/plusone.js"></script>
<script src="https://www.youtube.com/iframe_api" defer></script>
<script type="text/javascript">
  function changeTab(hash) {
    $('[href="' + hash + '"').tab('show');
  }

  $(function () {
    if (window.location.hash) {
      changeTab(window.location.hash);
    }
  });

  $(window).on('hashchange', function () {
    changeTab(window.location.hash.replace('#', '#tab-'));
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
</script>
