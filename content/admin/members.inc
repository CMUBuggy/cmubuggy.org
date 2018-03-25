<script>
  function dispmsg(valence, msg){
    $("#message").addClass(valence).removeClass('d-none').html(msg);
  }

  $(function () {
    //Edit membership years
    $("input.memberyear").change(function () {
      var newval = 0;
      if ($(this).is(':checked')) {
        newval = 1;
      }
      $.post(
        "/data.php",
        { type: "update", element_id: $(this).attr("id"), update_value: newval },
        function (data) {
          dispmsg("alert-success", "Membership status updated");
        }
      );
    });

    //Edit GradYear
    $(".eip").editInPlace({
      default_text: "&hellip;",
      params:"type=update",
      url: "/data.php",
      success: function (enteredText) {
        $(this).html(enteredText);
        dispmsg("alert-success", "Graduation year updated");
      }
    })

    $("#AddMemberSubmit").click(function () {
      var data = $("#addmember input").serializeArray();
      $.post("/data.php", data, function (data) {
        $("#addmember input:text").val("");
        $("#addmember input:checkbox").removeAttr('checked');
        dispmsg("alert-success", "Member added");
      });
    });
  });
</script>

<?php
  $member = new member();
  $memberList = $member->GetList(null,"lastname");
  $list09 = $member->GetList(array(array("mem2009","=","1")));
  $list10 = $member->GetList(array(array("mem2010","=","1")));
  $list11 = $member->GetList(array(array("mem2011","=","1")));
  $list12 = $member->GetList(array(array("mem2012","=","1")));
  $list13 = $member->GetList(array(array("mem2013","=","1")));
  $list14 = $member->GetList(array(array("mem2014","=","1")));
?>

<h1>Manage Membership Records</h1>

<div id="message" class="alert d-none" role="alert"></div>

<button type="button" class="btn btn-primary mb-3" data-toggle="collapse" data-target="#addmember" aria-expanded="false" aria-controls="addmember">Add a Member?</button>

<div id="addmember" class="collapse">
  <form action="" method="">
    <fieldset>
      <legend></legend>
      <input type="hidden" name="type" value="add" />
      <input type="hidden" name="objtype" value="member" />
      <div class="form-group">
        <label for="firstname">First Name</label>
        <input type="text" class="form-control" name="firstname" />
      </div>
      <div class="form-group">
        <label for="lastname">Last Name</label>
        <input type="text" class="form-control" name="lastname" />
      </div>
      <div class="form-group">
        <label for="email">Email</label>
        <input type="email" class="form-control" name="email" />
      </div>
      <div class="form-group">
        <label for="gradyear">Graduation Year</label>
        <input type="text" class="form-control" name="gradyear" size="5" placeholder="YYYY" />
      </div>
      <div class="form-check mb-3">
        <!-- TODO: Generalize to current (race) year -->
        <input type="checkbox" class="form-check-input" name="mem2014" value="1">
        <label for="mem2014" class="form-check-label">Membership 2014</label>
      </div>
    </fieldset>
    <div class="form-group">
      <input type="button" class="btn btn-primary" value="Add Member" id="AddMemberSubmit" />
    </div>
  </form>
</div>

<h2>Current and Past Members</h2>
<div class="table-responsive">
  <table class="table">
    <thead>
      <tr>
        <th>Member</th>
        <th>Email</th>
        <th>Grad Year</th>
        <th>2009</th>
        <th>2010</th>
        <th>2011</th>
        <th>2012</th>
        <th>2013</th>
        <th>2014</th>
      </tr>
    </thead>
    <tbody>
      <?php
        foreach($memberList as $member){
          $mem2009 = "";
          $mem2010 = "";
          $mem2011 = "";
          $mem2012 = "";
          $mem2013 = "";
          $mem2014 = "";
          if($member->mem2009){$mem2009 = "checked=\"checked\"";}
          if($member->mem2010){$mem2010 = "checked=\"checked\"";}
          if($member->mem2011){$mem2011 = "checked=\"checked\"";}
          if($member->mem2012){$mem2012 = "checked=\"checked\"";}
          if($member->mem2013){$mem2013 = "checked=\"checked\"";}
          if($member->mem2014){$mem2014 = "checked=\"checked\"";}
          echo("<tr><td>".$member->firstname." ".$member->lastname."</td>");
          echo("<td><div class=\"eip\"id=\"member-".$member->memberId."-email\">".$member->email."</div></td>");
          echo("<td><div class=\"eip\" id=\"member-".$member->memberId."-gradyear\">".$member->gradyear."</div></td>");
          echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2009\" class=\"memberyear\"".$mem2009." /></td>");
          echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2010\" class=\"memberyear\"".$mem2010." /></td>");
          echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2011\" class=\"memberyear\"".$mem2011." /></td>");
          echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2012\" class=\"memberyear\"".$mem2012." /></td>");
          echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2013\" class=\"memberyear\"".$mem2013." /></td>");
          echo("<td><input type=\"checkbox\" id=\"member-".$member->memberId."-mem2014\" class=\"memberyear\"".$mem2014." /></td></tr>");
        }
      ?>
    </tbody>
    <tfoot>
      <tr>
        <th>Total Members</th>
        <th></th>
        <th></th>
        <th><?php echo(count($list09)); ?></th>
        <th><?php echo(count($list10)); ?></th>
        <th><?php echo(count($list11)); ?></th>
        <th><?php echo(count($list12)); ?></th>
        <th><?php echo(count($list13)); ?></th>
        <th><?php echo(count($list14)); ?></th>
      </tr>
    </tfoot>
  </table>
</div>
