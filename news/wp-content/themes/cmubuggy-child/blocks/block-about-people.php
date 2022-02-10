<li class="row">
    <div class="col-sm-3 circular-image-container">
        <div class="circular-image">
            <img src="<?php block_field( 'image-url' ); ?>" alt="<?php block_field( 'image-alt' ); ?>">
        </div>
    </div>
    <div class="col-sm-9">
        <h5 class="font-weight-normal text-dark"><?php block_field( 'title' ); ?></h5>
        <h4>
            <?php block_field( 'name' ); ?>
            <small><?php block_field( 'pronouns' ); ?></small>
        </h4>
        <div class="small">
            c/o <?php block_field( 'graduation-year' ); ?> |
                 <?php block_field( 'team-postions' ); ?>  |
                 <?php
                   $histKey = block_field('history-db-key', false);
                   if(!empty($histKey)) {
                     echo("<a href=\"/history/person/".$histKey."\">history</a> |");
                   }
                 ?>
                 <a href="<?php block_field( 'email' ); ?>">email</a>
	</div>
        <br>
        <div><?php block_field( 'about' ); ?></div>
        <br>
        <div>
            <small>Currently working in</small><br>
            <?php block_field( 'professional-field' ); ?>
        </div>
        <div>
            <small><?php block_field( 'question-1' ); ?></small><br>
            <?php block_field( 'answer-1' ); ?>
        </div>
        <div>
            <small><?php block_field( 'question-2' ); ?></small><br>
            <?php block_field( 'answer-2' ); ?>
        </div>
    </div>
</li>

