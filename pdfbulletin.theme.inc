<?php

/**
 * @file
 *   Theme functions for pdf bulletin.
 */

/**
 * Theme the HTML version of the e-mail.
 */
function theme_pdfbulletin_email_html($pdfbulletin, $html) {
  $html = '<div class="pdfbulletin">' . $html . '</div>';
  return $html;
}

/**
 * Theme the plain text version of the e-mail.
 */
function theme_pdfbulletin_email_text($pdfbulletin, $text) {
  return $text;
}

/**
 * Theme the HTML used to make the PDF.
 *
 * @todo add title.
 */
function theme_pdfbulletin_email_pdf($pdfbulletin, $html) {
  $head = '
<head>
<style type="text/css">
.pdfbulletin .view-filters, .pdfbulletin .views-admin-links { display: none; }
</style>
</head>
';
  $body = '<body><div class="pdfbulletin">' . $html . '</div></body>';
  return '<html>' . $head . $body . '</html>';
}

/**
 * Theme the admin preview page.
 */
function theme_pdfbulletin_generate_pdf_page($pdfbulletin, $html, $filepath) {
  $output = l(t('Attachment PDF'), $filepath);
  $output .= '<h2>' . t('HTML') . '</h2>';
  $html = '<div class="pdfbulletin">' . $pdfbulletin->html . '</div>';
  $output .= $html;
  return $output;
}
