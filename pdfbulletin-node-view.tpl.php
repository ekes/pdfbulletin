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

<div class="test">
  <h3><?php print t('Test'); ?></h3>
  <p><?php print $test_link; ?></p>
</div>
