<div class="card event-card mb-3">
  <div class="card-body">
    <div class="event-card-text flex-grow-1">
      <h5 class="card-title"><?php block_field('title'); ?></h5>
      <h6 class="card-subtitle mb-2 text-muted">
        <?php
          $location = block_field('location', false);
          $locationUrl = block_field('location-url', false);
          if (!empty($locationUrl)) {
            echo("<a target='_blank' href='".$locationUrl."'>".$location."</a>");
          } else {
            echo($location);
          }

          $time = block_field('time', false);
          if (!empty($time)) {
            echo(" @ ".$time);
          }
        ?>
      </h6>
      <div class="card-text"><?php block_field('description'); ?></div>
      <?php
        $buttonUrl = block_field('button-url', false);
        if (!empty($buttonUrl)) {
          $buttonText = block_field('button-text', false);
          echo("<a target='_blank' href='".$buttonUrl."' class='btn btn-primary'>".$buttonText."</a>");
        }
      ?>
    </div>
    <?php
      $imageUrl = block_field('image-url', false);
      if (!empty($imageUrl)) {
        echo("<div class='event-card-image'><img src='".$imageUrl."' class='rounded'></div>");
      }
    ?>
  </div>
</div>