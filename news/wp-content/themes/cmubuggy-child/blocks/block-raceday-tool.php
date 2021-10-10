<div class="media">
	<img src="<?php block_field( 'icon' ); ?>" alt="<?php block_field( 'icon-alt' ); ?>" class="mr-3 raceday-thumb">
	<div class="media-body">
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