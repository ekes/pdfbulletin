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
function theme_pdfbulletin_email_pdf($pdfbulletin, $html, $header, $footer) {
  $head = '
<head>
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
