<?php
	$comment = new Comment();
	if(isset($commentparent)){
		$commentList = $commentparent->GetCommentList(); 
	}else{
		$commentList = $comment->GetList(array(array("commentId", ">", "0")),"timeSubmitted",false);
	}

	if(count($commentList)>0){
		foreach ($commentList as $comment)
		{
			echo("<i>from</i> ".$comment->submitterName."<i> on ".date("M dS, Y",$comment->timeSubmitted)."</i>");
			echo("<div style=\"margin-left:35px;\">".$comment->content."</div>");
			echo("<hr />");
		}
	} else {
		echo("<i>Nobody has commented on this piece of buggy history yet.</i>");
	}
?>	
</div>

