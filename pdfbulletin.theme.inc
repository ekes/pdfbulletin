<?php

/**
 * @file
 *   Theme functions for pdf bulletin.
 */

/**
 * Theme the HTML version of the e-mail.
 */
function theme_pdfbulletin_email_html($pdfbulletin, $html, $header, $footer) {
  $output .= '<div class="pdfbulletin-header">' . $header . '</div>';
  $output .= '<div class="pdfbulletin-email-intro">' . $html . '</div>'; 
  $output .= '<div class="pdfbulletin-footer">' . $footer . '</div>'; 
  return $output;
}

/**
 * Theme the plain text version of the e-mail.
 */
function theme_pdfbulletin_email_text($pdfbulletin, $text, $header, $footer) {
  return $text;
}

/**
 * Theme the HTML used to make the PDF.
 *
 * @todo add title.
 */
function theme_pdfbulletin_email_pdf($pdfbulletin, $html, $header, $footer, $css) {
  $head = '
<head>
<link type="text/css" rel="stylesheet" media="all" href="' . $css . '" />
<style type="text/css">
.pdfbulletin .view-filters, .pdfbulletin .views-admin-links { display: none; }
</style>
</head>
';
  $body = '<div class="pdfbulletin-header">' . $header . '</div>';
  $body .= '<body><div class="pdfbulletin">' . $html . '</div></body>';
  $body .= '<div class="pdfbulletin-footer">' . $footer . '</div>';
  return '<html>' . $head . $body . '</html>';
}

/**
 * Theme a link to download of sample copy of the bulltin.
 */
function theme_pdfbulletin_generate_pdf_link($filepath, $pdfbulletin) {
  $output = l(t('Download sample bulletin'), $filepath);
  return $output;
} 

/**
 * Preprocess for template function.
 */
function template_preprocess_pdfbulletin_node_view(&$vars) {
  $node = $vars['node'];
  $pdfbulletin = $node->pdfbulletin;

  $vars['view_name'] = check_plain($pdfbulletin->view_name);
  $filters = array();
  foreach ($pdfbulletin->filters as $key => $value) {
    if (! empty($value)) {
      $filters[] = array($key, $value);
    }
  }
  if (count($filters)) {
    $vars['filters'] = theme('table', array('filter', 'value'), $filters);
  }
  $vars['subscribers_number'] = count($pdfbulletin->subscribers);
  $vars['scheduled'] = $pdfbulletin->schedule['scheduled'];
  $vars['start'] = format_date($pdfbulletin->schedule['date'], 'custom', 'Y-m-d');
  $frequency = array(
      '86400' => t('daily'),
      '604800' => t('weekly'),
      '1209600' => t('bi-weekly'),
      '2419200' => t('monthly'),
  );
  $vars['frequency'] = $frequency[$pdfbulletin->schedule['frequency']];
  $vars['schedule'] = t('Sent %frequency starting %date', array('%frequency' => $vars['frequency'], '%date' => $vars['start']));
  $vars['schedule_link'] = l(t('Change the schedule of this bulletin'), 'node/' . $node->nid . '/settings');
  $vars['test_link'] = l(t('Test this bulletin'), 'node/' . $node->nid . '/sendtest');
}
