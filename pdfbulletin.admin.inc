<?php

/**
 * @file
 *  PDF Bulletin administration settings.
 */

function pdfbulletin_admin_settings_form($form_state) {
  $form = array();

  $form['pdfbulletin_pdfinfo'] = array(
    '#type' => 'textfield',
    '#default_value' => filter_xss_admin(pdfbulletin_util_settings('pdfinfo')),
    '#title' => t('Path to pdfinfo program'),
    '#required' => TRUE,
  );

  $form['pdfbulletin_wkhtmltopdf'] = array(
    '#type' => 'textfield',
    '#default_value' => filter_xss_admin(pdfbulletin_util_settings('wkhtmltopdf')),
    '#title' => t('Path to wkhtmltopdf'),
    '#required' => TRUE,
  );

  $form['pdfbulletin_options'] = array(
    '#type' => 'textfield',
    '#default_value' => filter_xss_admin(pdfbulletin_util_settings('options')),
    '#title' => t('Additional wkhtmltopdf options'),
  );

  return system_settings_form($form);  
}

function pdfbulletin_admin_settings_form_validate($form, &$form_state) {
  if (! is_executable($form_state['values']['pdfbulletin_pdfinfo'])) {
    form_set_error('pdfbulletin_pdfinfo', t('Incorrect path or not executable pdfinfo'));
  }
  if (! is_executable($form_state['values']['pdfbulletin_wkhtmltopdf'])) {
    form_set_error('pdfbulletin_wkhtmltopdf', t('Incorrect path or not executable wkhtmltopdf'));
  }
}
