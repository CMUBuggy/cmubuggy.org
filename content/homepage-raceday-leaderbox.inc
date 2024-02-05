<?php
 // This loads a lot of javascript and CSS directly onto the home page, so it probably
 // shouldn't be enabled that often.  It also puts load on our RTDB with the home page,
 // but only slightly unless the leaderboard is active.
 //
 // This loading happens in the middle of <body> which isn't great but probably is
 // tolerable for the few days a year this box is up.  We don't want to load firebase
 // in cssjs.inc since we don't use it for things other than the leaderboard/tv portal
 ?>
<style>
  .tab-pane { counter-reset: place; }
  .race-result [data-note]:empty { display: none; }
  .race-result {
    opacity: 1;
    animation: fadeUp 1s forwards;
    will-change: opacity, transform;
  }

  .race-result {
    background-color: #b6d7a8 !important;
  }

  .race-result:nth-child(n+7) {
    background-color: #efefef !important;
  }

  .race-result [data-place]::before {
    counter-increment: place;
    content: counter(place);
    position: absolute;
  }
  .race-result.dq.dq {
    background-color: #fff !important;
  }
  .race-result.dq [data-place]::before {
    content: 'DQ';
  }

  @keyframes fadeUp {
    0% {
      opacity: 0;
      transform: translateY(50px);
    }
    30% {
      opacity: 0;
    }
    100% {
      opacity: 1;
      transform: translateY(0);
    }
  }
</style>

<template id="raceResult">
  <div class="race-result p-3 mb-1 border rounded" data-id>
    <div class="d-flex justify-content-between" data-place>
      <div data-name class="ml-5"></div>
      <div data-time class="ml-2 text-monospace"></div>
    </div>
  </div>
</template>

<script src="https://cdn.polyfill.io/v2/polyfill.min.js"></script>
<script src="https://www.gstatic.com/firebasejs/4.12.1/firebase.js"></script>
<script>
  // Initialize Firebase
  var config = {
    apiKey: 'AIzaSyCjdOwIz6r5P0OScBb84x9o9udtveSKpFM',
    authDomain: 'cmu-buggy-leaderboard.firebaseapp.com',
    databaseURL: 'https://cmu-buggy-leaderboard.firebaseio.com',
    projectId: 'cmu-buggy-leaderboard',
    storageBucket: 'cmu-buggy-leaderboard.appspot.com',
    messagingSenderId: '31785879580'
  };
  firebase.initializeApp(config);

  const MAX_PLACES = 6;
  const raceResult = document.querySelector('#raceResult');
  const VALID_CLASSES = {
    'womens_prelims' : "Women's Prelims",
    'mens_prelims': "Men's Prelims",
    'allgender_prelims': "All Gender Prelims",
    'womens_finals' : "Women's Finals",
    'mens_finals': "Men's Finals",
    'allgender_finals': "All Gender Finals",
    'exhibitions': "Exhibitions"
  }

  // Currently filled in state
  let current_tab = "NONE";  // configured class
  let current_ref = null;    // firebase ref for class

  function populateNodeText(node, value) {
    node.querySelector('[data-name]').textContent = value.team;
    node.querySelector('[data-time]').textContent = value.time || ' ';
  }

  function addRaceResult(tab, data, previousChildKey) {
    var node = document.importNode(raceResult.content, true),
      value = data.val(),
      previousNode = previousChildKey && tab.querySelector('[data-id=' + previousChildKey + ']');
    node.querySelector('[data-id]').setAttribute('data-id', data.key);

    populateNodeText(node, value);

    if (value.dq) {
      node.querySelector('.race-result').classList.add('dq');
    }
    if (previousNode) {
      tab.insertBefore(node, previousNode.nextSibling);
    } else {
      tab.insertBefore(node, tab.firstChild);
    }
    console.debug('result added: %s - %s', tab.id, data.key);
  }

  function updateRaceResult(tab, data, previousChildKey) {
    var node = tab.querySelector('[data-id=' + data.key + ']'),
    value = data.val();

    populateNodeText(node, value);

    if (value.dq) {
      node.classList.add('dq');
    } else {
      node.classList.remove('dq');
    }
    console.debug('result updated: %s - %s', tab.id, data.key);
  }

  function removeRaceResult(tab, data) {
    tab.removeChild(tab.querySelector('[data-id=' + data.key + ']'))
    console.debug('result removed: %s - %s', tab.id, data.key);
  }

  function moveRaceResult(tab, data, previousChildKey) {
    var node = tab.querySelector('[data-id=' + data.key + ']'),
      previousNode = previousChildKey && tab.querySelector('[data-id=' + previousChildKey + ']');
    tab.removeChild(node);
    if (previousNode) {
      tab.insertBefore(node, previousNode.nextSibling);
    } else {
      tab.insertBefore(node, tab.firstChild);
    }
    console.debug('result moved: %s - %s', tab.id, data.key);
  }


  // Determine which tabs are visible.
  let visibleconfigref = firebase.database().ref("config/CURRENT_TAB");
  visibleconfigref.on('value', function (snapshot) {
      const data = snapshot.val()
      let new_tab = data;
      console.debug("CURRENT_TAB set to %s", new_tab);

      const box = document.querySelector('#leaderboard-box');
      const bodyNode = document.querySelector('#leaderboard-body');
      const box_header = document.querySelector('#leaderboard-header');

      // We don't understand this, so act like it is NONE.
      if (new_tab != "NONE" && !Object.keys(VALID_CLASSES).includes(new_tab)) {
        console.debug("ignoring");
        new_tab = "NONE"
      }

      // Remove any current listner & contents of DOM
      if (current_ref) {
        current_ref.off();
        current_ref = null;

        while (bodyNode.firstChild) {
          bodyNode.removeChild(bodyNode.lastChild);
        }
      }

      current_tab = new_tab;

      if (current_tab == "NONE") {
        box.style.display = "none";
      } else {
        current_ref = firebase.database().ref(current_tab)
                        .orderByChild('time_sort').limitToFirst(MAX_PLACES);

        current_ref.on('child_added', function (snapshot, previousChildKey) {
          addRaceResult(bodyNode, snapshot, previousChildKey);
        });
        current_ref.on('child_removed', function (snapshot) {
          removeRaceResult(bodyNode, snapshot);
        });
        current_ref.on('child_changed', function (snapshot, previousChildKey) {
          updateRaceResult(bodyNode, snapshot, previousChildKey);
        });
        current_ref.on('child_moved', function (snapshot, previousChildKey) {
          moveRaceResult(bodyNode, snapshot, previousChildKey);
        });

        box.style.display = "flex";
        box_header.innerHTML = "Leaderboard: " + VALID_CLASSES[current_tab]
      }
  });
</script>

<div class="card mb-3" style="display: none" id="leaderboard-box">
  <h5 class="card-header" id="leaderboard-header">Leaderboard</h5>
  <div class="card-body">
    <div id="leaderboard-body" class="tab-pane"></div>
  </div>
</div>