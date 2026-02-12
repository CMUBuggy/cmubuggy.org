<div class="d-flex"><div class="flex-shrink-0">
	<img src="<?php block_field( 'icon' ); ?>" alt="<?php block_field( 'icon-alt' ); ?>" class="me-3 raceday-thumb">
    </div><div class="flex-grow-1 ps-3">
		<h5 class="mt-0">
			<a 
			   <?php if ( block_field( 'external-link' ) ) { echo 'target="_blank" rel="noopener renoferrer"'; } ?>
			   href="<?php block_field( 'title-url' ); ?>">
				<?php block_field( 'title-text' ); ?>
			</a>
		</h5>
		<?php block_field( 'description' ); ?>
	</div>
</div>