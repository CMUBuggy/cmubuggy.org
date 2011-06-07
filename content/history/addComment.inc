<script type="text/javascript">
	function addComment(){
		$("#commentList").load("/history/ajax/postComment.php",
			{
				name: $("#name").val(),
				email: $("#email").val(),
				content: $("#content").val()
			});
		$("#commentform input").val("");
		$("#commentform").slideUp();
	}
</script>

<h3><a href="#" onclick="$('#commentform').slideDown(); return false;">Add your own</a></h3>
<div id="commentform" style="display:none;">
	<form method="post" action="<?php echo($_SERVER["REQUEST_URI"]); ?>" />
	<table>
		<tr>
			<td>Your name</td>
			<td><input type="text" id="name" /></td>
			<td></td>
			<td></td>
		</tr>
		<tr>
			<td>Your email</td>
			<td><input type="text" id="email" /></td>
			<td>It won't be public, but please include it so we may contact you to clarify if necessary</td>
			<td></td>
		</tr>
		<tr>
			<td>Your Comment or Story</td>
			<td colspan="2"><textarea name="content" id="content" rows="15" style="width:450px;"></textarea></td>
		</tr>
		<tr>
			<td></td>
			<td><input type="button" name="submit" value="Submit" onclick="addComment();"> <input type="button" name="Cancel" value="Cancel" onclick="$('#commentform').slideUp();"></td>
		</tr>			
	</table>
	</form>
</div>
