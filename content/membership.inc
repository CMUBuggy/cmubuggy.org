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

<h1 class="sr-only">Membership</h1>

<ul class="nav nav-tabs mb-2" role="tablist">
  <li class="nav-item">
    <a id="join-tab" href="#tab-join" class="nav-link active" data-toggle="tab" role="tab" aria-controls="tab-join" aria-selected="true">Join the Team</a>
  </li>
  <li class="nav-item">
    <a id="roster-tab" href="#tab-roster" class="nav-link" data-toggle="tab" role="tab" aria-controls="tab-roster" aria-selected="false">Check the Roster</a>
  </li>
</ul>

<div class="tab-content">
  <div class="tab-pane fade show active" id="tab-join" role="tabpanel" aria-labelledby="join-tab">
    <h2 class="sr-only">Join the Team</h2>

    <p>Most of the services of the Buggy Alumni Association are available to everyone in the buggy and CMU community. We want the hard work we have done collecting, organizing, and sharing the past and present of buggy to be enjoyed by all. We also want everyone to benefit from stronger, broader participation in today's buggy races. By becoming a member, you can support these goals and let us and the school know you agree that buggy is the best and should be supported.</p>

    <h3>Benefits of being a member</h3>
    <ol>
      <li><b>Supporting our mission</b>: The most important reason to become a member is that we can't operate without a budget. Most of our services are all-volunteer and low-cost. When we do spend money we try to ensure we get the most bang for our buck. For example, we paid 50% of the cost of renting a new timing system in 2010 so that Sweepstakes could test it out for a full month before races and ensure it would be the revolutionary improvement we expected. Ongoing rental of the timing system fits within Sweepstake's annual budget. More info about our goals and our activities can be found in the <a href="/about">About Us</a> section.</li>
      <li><b>Special communications</b>: We contact our members directly a couple of times per year with in-depth updates on the buggy world. No more coming back for carnival and wondering who is good these days, or what big drama is unfolding. Check out the <a onclick="javascript: pageTracker._trackPageview('/files/RacedayPreview2009.pdf');" href="/files/RacedayPreview2009.pdf">2009</a> and <a onclick="javascript: pageTracker._trackPageview('/files/RacedayPreview2010.pdf');" href="/files/RacedayPreview2010.pdf">2010</a> Raceday Previews for example. You're going to want one of those in your inbox.</li>
      <li><b>Raceday Reception</b>: Each year we host a reception after the races on Friday for fans and alumni to meet up (in real life for once, not just on the internet), have some food, and talk about the morning's races. It's suggested that you become a member if you come to the reception since the food ain't free.</li>
      <li><b>Members-only Specials</b>:  We're constantly trying to think of ways to entertain and help out our members. You'll be first in line for prizes, discounts, and anything else can put together.</li>
    </ol>

    <h3>Wow! How do I join?</h3>
    <p>To become an official member of the Buggy Alumni Association for the year, <b>all you have to do is give a gift of any size</b>. Any amount is fine, we just want to know that you've got our back. All gifts are tax-deductible and funds go directly to the CMU Buggy Alumni Association allowing us to rent timing systems, jumbotrons, and have receptions.</p>

    <p>Being a member of the Buggy Alumni Association is an annual commitment, and our "year" starts and ends at Raceday. All gifts received before and during carnival make you a member of the BAA team for that race-year. For example, gifts received May 2011-April 2012 make you a member of the 2012 team.</p>

    <a target="_blank" onclick="_gaq.push(['_trackEvent','Outbound','Membership',this.href]);" href="https://securelb.imodules.com/s/1410/giving/form.aspx?sid=1410&gid=1&pgid=382&cid=990&appealcode=A3291&dids=98" class="btn btn-primary mb-3">Join (or Renew) Now</a>

    <h4>Notes</h4>
    <ul>
      <li>The "Join Now" button will take you to the CMU giving site where you'll see on step 2 that the Buggy Alumni Association has been pre-selected as the designee. Thank you!</li>
      <li>We only get updates on who has become a member once a month. To get your new membership processed immediately, forward your gift confirmation e-mail to <a href="mailto:join@cmubuggy.org">join@cmubuggy.org</a>.</li>
      <li>Registering on this site is free and unrelated to becoming a "Member."  Registering allows you to post in the forum, upload pictures, etc. You can <a href="/user/register">register here</a>.</li>
    </ul>
  </div>
  <div class="tab-pane fade" id="tab-roster" role="tabpanel" aria-labelledby="roster-tab">
    <h2 class="sr-only">Check the Roster</h2>

    <p>Listed below are the generous and wise buggy alumni and fans that have become members since our founding in 2008. We especially thank our inaugural members and our multi-year supporters that have helped make this organization the strongest, fastest growing alumni group from CMU.</p>

    <p>Our record keeping hasn't always been impeccable, so if you think you have been omitted from this list, we sincerely apologize, and by all means let us know. Just send an e-mail to <a href="mailto:join@cmubuggy.org">join@cmubuggy.org</a> and we'll straighten it out.</p>

    <div class="table-responsive">
      <table class="table">
        <thead>
          <tr>
            <th>Member</th>
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
              $icon = "<img src=\"/img/icon_buggy.gif\" />";
              $mem2009 = "";
              $mem2010 = "";
              $mem2011 = "";
              $mem2012 = "";
              $mem2013 = "";
              $mem2014 = "";
              if($member->mem2009){$mem2009 = $icon;}
              if($member->mem2010){$mem2010 = $icon;}
              if($member->mem2011){$mem2011 = $icon;}
              if($member->mem2012){$mem2012 = $icon;}
              if($member->mem2013){$mem2013 = $icon;}
              if($member->mem2014){$mem2014 = $icon;}
              echo("<tr><td>".$member->firstname." ".$member->lastname."</td>");

              echo("<td>".$member->gradyear."</td>");
              echo("<td>".$mem2009."</td>");
              echo("<td>".$mem2010."</td>");
              echo("<td>".$mem2011."</td>");
              echo("<td>".$mem2012."</td>");
              echo("<td>".$mem2013."</td>");
              echo("<td>".$mem2014."</td></tr>");
            }
          ?>
        </tbody>
        <tfoot>
          <tr>
            <th>Total Members</th>
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
  </div>
</div>
