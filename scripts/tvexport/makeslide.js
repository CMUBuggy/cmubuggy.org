// Puppeteer script to generate tv slides with transparent backgrounds
// from the CMUBuggy TV Portal.
//
// Requires Docker for the puppeteer executions.
//
// First, load the puppeteer container image:
// docker pull ghcr.io/puppeteer/puppeteer:latest
//
// How to run (single entry)
//
// docker run -i --init --cap-add=SYS_ADMIN -v .:/out --rm ghcr.io/puppeteer/puppeteer:latest node -e "$(cat ./makeslide.js)" -- YYYY.ORG.CT
//
// You can optionally specfiy a type of data before the key.  For example:
// node -e "$(cat ./makeslide.js)" -- roster-view YYYY.ORG.CT
// node -e "$(cat ./makeslide.js)" -- roster-view-photos YYYY.ORG.CT
// node -e "$(cat ./makeslide.js)" -- heat-view YYYY-FXM##
//
// To get list of entries from the database:
// mysql [[-u USERNAME -p DBNAME]] -s -r -e 'SELECT entryid FROM hist_raceentries WHERE year=YYYY;'
//
// Example of running in bulk (can be one line):
// for thing in `cat filename-with-list-of-entries`;
//  do docker run -i --init --cap-add=SYS_ADMIN -v .:/out \
//     --rm ghcr.io/puppeteer/puppeteer:latest node -e \
//     "$(cat ./makeslide.js)" -- $thing;
// done
//
// Final step:
//
// 1920x1080 RGBA Targa Files can be helpful.  To get these, use imagemagick:
//   convert -auto-orient 2023-FRI-MD.png 2023-FRI-MD.tga
//
// To do in bulk, use massconvert.sh
//
const { exit } = require('process');
const puppeteer = require('puppeteer');

// slice 1, since we only get node and not the eval or --.
const args = process.argv.slice(1);
let entry = "";
let query = "roster-view"

if (args.length == 2) {
    // 2 args are [file type] [key]
    const valid = ["roster-view","roster-view-photos","heat-view"];
    if (!valid.includes(args[0])) {
      console.error(args[0] + " not valid.  Expected roster-view, roster-view-photos, or heat-view.")
      exit();
    }
    query = args[0];
    entry = args[1];
} else if (args.length != 1) {
    console.error(process.argv);
    console.error ("Must supply a key such as 2023.FRI.MD or 2023-FXM01");
    exit();
} else {
    entry = args[0];
}

console.log("Running for entry: " + entry);

(async (e) => {

  const browser = await puppeteer.launch();
  const page = await browser.newPage();

  // Set the viewport's width and height
  await page.setViewport({ width: 1920, height: 1080 });

  // Open Page
  const url = 'https://cmubuggy.org/content/tv/tv'+query+'.php?t='+e;
  console.log('Using: ' + url);
  await page.goto(url);

  // Obviously this assumes knowledge of the page format.
  await page.evaluate(() => document.body.style.background = 'transparent');
  await page.evaluate(() => document.querySelector('.fullscreen').style.background = 'transparent');

  try {
    // Capture screenshot and save it in the current folder:
    const file = '/out/'+e.replaceAll('.','-')+'.png';
    await page.screenshot({ path: file, omitBackground: true });
    console.log("wrote to: " + file);
  } catch (err) {
    console.log(`Error: ${err.message}`);
  } finally {
    await browser.close();
    console.log(`Screenshot has been captured successfully`);
  }
})(entry);
