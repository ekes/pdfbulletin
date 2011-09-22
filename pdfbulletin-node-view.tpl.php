<?php 

/**
 * @file 
 *  PDF Bulletin node view template.
 *
 * @see template_preprocess_pdfbulletin_node_view().
 */

?>
<div class="bulletin-info">
  <h3><?php print t('Bulletin information'); ?></h3>
  <p><?php print $view_name; ?></p>
  <?php print $filters; ?>
</div>

<div class="schedule">
  <h3><?php print t('Schedule'); ?></h3>
  <?php if ($scheduled): ?>
    <p><?php print t('Scheduled:') ?><br />
    <?php print $schedule; ?></p>
  <?php else: ?>
    <p><?php print t('Not Scheduled') ?></p>
  <?php endif; ?>
  <?php print $schedule_link; ?></p>
</div>

<div class="test">
  <h3><?php print t('Test'); ?></h3>
  <p><?php print $test_link; ?></p>
</div>
