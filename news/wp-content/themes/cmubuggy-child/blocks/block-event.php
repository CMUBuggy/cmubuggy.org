<div class="card mb-3">
  <div class="card-body">
    <h5 class="card-title"><?php block_field('title'); ?></h5>
    <h6 class="card-subtitle mb-2 text-muted">
      <?php block_field('location'); ?> @ <?php block_field('time'); ?>
    </h6>
    <div class="card-text"><?php block_field('description'); ?></div>
    <?php
      $buttonUrl = block_field('button-url', false);
      if (!empty($buttonUrl)) {
        $buttonText = block_field('button-text', false);
        echo("<a target=\"_blank\" href=\"".$buttonUrl."\" class=\"btn btn-primary\">".$buttonText."</a>");
      }
    ?>
  </div>
</div>