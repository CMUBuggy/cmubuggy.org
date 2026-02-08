<li class="row">
    <div class="col-sm-3 circular-image-container">
        <div class="circular-image">
            <img src="<?php block_field('image-url'); ?>" alt="<?php block_field('image-alt'); ?>">
        </div>
    </div>
    <div class="col-sm-9">
        <h5 class="fw-normal text-dark"><?php block_field('title'); ?></h5>
        <h4>
            <?php block_field('name'); ?>
            <small><?php block_field('pronouns'); ?></small>
        </h4>
        <div class="small">
            <?php
               if(!block_value('current-student-toggle')) {
                 echo("c/o ");
               }
               block_field('graduation-year');

               // Yes, this field name was really misspelled in the database too.
               $teamInfo = block_field('team-postions', false);
               if(!empty($teamInfo)) {
                 echo(" | ".$teamInfo);
               }
               $histKey = block_field('history-db-key', false);
               if(!empty($histKey)) {
                 echo(" | <a href=\"/history/person/".$histKey."\">history</a>");
               }
               $emailData = block_field('email', false);
               if(!empty($emailData)) {
                 echo(" | <a href=\"".$emailData."\">email</a>");
               }
            ?>
	    </div>
        <br>
        <div><?php block_field('about'); ?></div>
        <br>
        <?php if (!empty(block_field('student-major', false))) { ?>
        <div>
            <small>Major</small><br>
            <?php block_field('student-major'); ?>
        </div>
        <?php } ?>
        <?php if (!empty(block_field('professional-field', false))) { ?>
        <div>
            <small>Profession</small><br>
            <?php block_field('professional-field'); ?>
        </div>
        <?php } ?>
        <div>
            <small><?php block_field('question-1'); ?></small><br>
            <?php block_field('answer-1'); ?>
        </div>
        <div>
            <small><?php block_field('question-2'); ?></small><br>
            <?php block_field('answer-2'); ?>
        </div>
    </div>
</li>

