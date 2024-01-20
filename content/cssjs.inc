<?php // This file takes place entirely inside of the HEAD tag ?>
<?php // To keep Wordpress and the site consistent, it provides the TITLE tag based on the $TITLE_TAG variable. ?>

<title><?php echo($TITLE_TAG); ?></title>

<!--Favicon-->
<link rel="apple-touch-icon" sizes="180x180" href="/favicons/apple-touch-icon.png">
<link rel="icon" type="image/png" sizes="32x32" href="/favicons/favicon-32x32.png?v=2022022500">
<link rel="icon" type="image/png" sizes="16x16" href="/favicons/favicon-16x16.png?v=2022022500">
<link rel="icon" type="image/svg+xml" sizes="all" href="/img/logo-2022-b.svg">
<link rel="manifest" href="/favicons/site.webmanifest">
<link rel="mask-icon" href="/favicons/safari-pinned-tab.svg" color="#bb0000">
<meta name="msapplication-TileColor" content="#bb0000">
<meta name="msapplication-config" content="/favicons/browserconfig.xml">
<meta name="theme-color" content="#ffffff">

<?php // WARNING: Update standalone files too if you change CSS versions (notably, in ./tv) ?>
<!--CSS-->
<link rel="stylesheet" href="/css/cmubuggy-bootstrap.css?ver=2023091303" />
<link rel="stylesheet" href="/css/cmubuggy-all.css?ver=2023120401" />

<!--JS-->
<script defer src="https://cdn.jsdelivr.net/npm/jquery@3.5.1/dist/jquery.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
<script defer src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js" integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN" crossorigin="anonymous"></script>
<script defer src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-fQybjgWLrvvRgtW6bFlB7jaZrFsaBXjsOMm/tB9LTS58ONXgqbR9W8oWht/amnpF" crossorigin="anonymous"></script>
<script defer src="https://cdn.jsdelivr.net/npm/@fortawesome/fontawesome-free@5.15.4/js/all.min.js" integrity="sha384-rOA1PnstxnOBLzCLMcre8ybwbTmemjzdNlILg8O7z1lUkLXozs4DHonlDtnE7fpc" crossorigin="anonymous"></script>

<?php if(isset($ENABLE_GA_TAG) && $ENABLE_GA_TAG) { ?>
<script async src="https://www.googletagmanager.com/gtag/js?id=G-VCW3VN91ZX"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());

  gtag('config', 'G-VCW3VN91ZX');
</script>
<?php } ?>

<script defer src="https://www.youtube.com/iframe_api"></script>

<script defer src="/js/cmubuggy-all.js?ver=2022042000" type="text/javascript"></script>
<!--END CSSJS-->
