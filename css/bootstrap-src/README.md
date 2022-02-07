# Bootstrap CSS Generation

This directory contains the necessary tools to regenerate the bootstrap-derived `/css/cmubuggy-bootstrap.css` file.

Bootstrap is available at http://getbootstrap.com.  We currently use the somewhat ancient version 4.1.0.  See [the documetation for that version](https://getbootstrap.com/docs/4.1/getting-started/introduction/).

## Key Notes

- We just rely on the CDN for the JS side of
  bootstrap, and only create our own CSS to get our theming applied.  Any customization of the JS side will require more work.

## Build a new cmubuggy-bootstrap.css
  - npm install
  - npm run css
  - copy `cmubuggy-bootstrap.css` file from `dist/css/` to `/css` and commit it.
    - We do not currently use the minified version, but it is generated as part of this process.

## Steps to consider if updating Bootstrap version
  - Update package.json for correct versions for new bootstrap of all dependencies.  Remember to commit `package-lock.json` too when you regenerate.
  - Update any of the commands in package.json that are relevant to CSS generation.  Note that we disable source map generation as it isn't terribly useful in our case currently (as we only change colors and publish a nonminified CSS).
  - Historically, we have used precision 10 instead of precision 6 (bootstrap default) for SASS.  This may not actually be required.
  - Compare `postcss.config.js` with bootstrap's `build/postcss.config.js` and update as needed.
  - Compare `.stylelintrc` with bootstrap's, but see
    https://stackoverflow.com/questions/50520001/bootstrap4-custom-override-expected-default-flag-for-body-bg as we need to override at least one flag.
