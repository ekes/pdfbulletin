<?php

/**
 * @file
 *   Theme functions for pdf bulletin.
 */

/**
 * Theme the HTML version of the e-mail.
 */
function theme_pdfbulletin_email_html($pdfbulletin, $html) {
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
 */
function theme_pdfbulletin_email_pdf($pdfbulletin, $html) {
  return $html;
}

/**
 * Theme the admin preview page.
 */
function theme_pdfbulletin_generate_pdf_page($pdfbulletin, $html, $filepath) {
  $output = l(t('Attachment PDF'), $filepath);
  $output .= '<h2>' . t('HTML') . '</h2>';
  $output .= $pdfbulletin->html;
  return $output;
}
