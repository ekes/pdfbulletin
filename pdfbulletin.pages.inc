<?php

/**
 * Form constructor for an individal PDF Bulletin setting.
 * 
 * @param pdfbulletin
 *   PDF Bulletin object from pdfbulletin_load().
 *
 * @see pdfbulletin_edit_form_submit().
 * @ingroup forms.
 */
function pdfbulletin_edit_form(&$node, $form_state) {
  $type = node_get_types('type', $node);
  $pdfbulletin = $node->pdfbulletin;
  $form['pdfbulletin'] = array(
    '#type' => 'value',
    '#value' => $pdfbulletin,
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => check_plain($type->title_label),
    '#required' => TRUE,
    '#default_value' => $node->title,
    '#weight' => -5,
  );

  $form['header_format'] = array(
    '#tree' => FALSE,
  );
  $form['header_format']['header'] = array(
    '#title' => t('Header'),
    '#type' => 'textarea',
    '#default_value' => $pdfbulletin->header,
  );
  $form['header_format']['format'] = filter_form($pdfbulletin->header_format, NULL, array('header_format'));

  $form['footer_format'] = array(
    '#tree' => FALSE,
  );
  $form['footer_format']['footer'] = array(
    '#title' => t('Footer'),
    '#type' => 'textarea',
    '#default_value' => $pdfbulletin->footer,
  );
  $form['footer_format']['format'] = filter_form($pdfbulletin->footer_format, NULL, array('footer_format'));

  $form['email_format'] = array(
    '#tree' => FALSE, 
  );
  $form['email_format']['email'] = array(
    '#title' => t('Text for e-mail'),
    '#type' => 'textarea',
    '#default_value' => $pdfbulletin->email,
  );
  $form['email_format']['format'] = filter_form($pdfbulletin->email_format, NULL, array('email_format'));

  $form['empty_text_format'] = array(
    '#tree' => FALSE,
  );
  $form['empty_text_format']['empty_text'] = array(
    '#title' => t('Empty text'),
    '#type' => 'textarea',
    '#default_value' => $pdfbulletin->empty_text,
    '#description' => t('Text for e-mail if it is sent with an empty bulletin.'),
  );
  $form['empty_text_format']['format'] = filter_form($pdfbulletin->empty_text_format, NULL, array('empty_text_format'));

  return $form;
}

function pdfbulletin_settings_form($form_state, &$node) {
  $pdfbulletin = $node->pdfbulletin;
  $schedule = $pdfbulletin->schedule;

  $form['pdfbulletin'] = array(
    '#value' => $pdfbulletin,
    '#type' => 'value',
  );
  $form['frequency'] = array(
    '#type' => 'select',
    '#options' => array(
      '86400' => 'daily',
      '604800' => 'weekly',
      '1209600' => 'bi-weekly',
      '2419200' => 'monthly',
    ),
    '#title' => t('Frequency'),
    '#default_value' => $schedule['frequency'],
  );
  $form['date'] = array(
    '#type' => 'date',
    '#title' => t('Start date'),
    '#default_vaule' => $schedule['date'], // @todo formatting
  );
  $form['send_empty'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send e-mail if the bulletin is empty'),
    '#default_value' => $schedule['send_empty'],
  );
  $form['scheduled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable sending of mail'),
    '#default_vaule' => $schedule['scheduled'] | PDFBULLETIN_SCHEDULED_YES,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Form validation handler for pdfbulletin_edit_form().
 */
function pdfbulletin_settings_form_validate(&$form, &$form_state) {
  // @todo SERIOUSLY
}

/**
 * Form submission handler for pdfbulletin_edit_form().
 */
function pdfbulletin_settings_form_submit(&$form, &$form_state) {
  $pdfbulletin = $form_state['values']['pdfbulletin'];
  $schedule = $pdfbulletin->schedule;

  $schedule['frequency'] = $form_state['values']['frequency'];
  $start_date = $form_state['values']['date'];
  $schedule['date'] = strtotime($start_date['year'] . '-' . $start_date['month'] . '-' . $start_date['day']);
  $schedule['send_empty'] = $form_state['values']['send_empty'];
  $schedule['scheduled'] = $schedule['scheduled'] & $form_state['values']['scheduled'] ? PDFBULLETIN_SCHEDULED_YES : PDFBULLETIN_SCHEDULED_NO;
  pdfbulletin_schedule_save($schedule);
}

/**
 * Form constructor for an individual PDF Bulletin subscribers.
 *
 * @param pdfbulletin.
 *  PDF Bulletin object from pdfbulletin_load().
 *
 * @see pdfbulletin_subscribers_form_validate().
 * @see pdfbulletin_subscribers_form_sumbit().
 * @ingroup forms.
 */
function pdfbulletin_subscribers_form($form_state, &$node) {
  $pdfbulletin = $node->pdfbulletin;
  $subscribers = '';
  foreach ($pdfbulletin->subscribers as $email) {
    $subscribers .= check_plain($email) . "\n";
  }

  $form['pdfbulletin'] = array(
    '#type' => 'value',
    '#value' => $pdfbulletin,
  );
  $form['subscribers'] = array(
    '#type' => 'textarea',
    '#title' => t('e-mail addresses'),
    '#description' => t('Add one e-mail address per line.'),
    '#default_value' => $subscribers,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
} 

/**
 * Form validation handler for pdfbulletin_subscribers_form().
 *
 * @see pdfbulletin_subscribers_form_submit().
 */
function pdfbulletin_subscribers_form_validate($form, &$form_state) {
  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (! empty($email) && ! valid_email_address($email)) {
      form_set_error('subscribers', t('Invalid e-mail address: @email', array('@email' => $email)));
    }
  }
}

/**
 * Form submission handler for pdfbulletin_subscribers_form().
 *
 * @see pdfbulletin_subscribers_form_validate().
 */
function pdfbulletin_subscribers_form_submit($form, &$form_state) {
  $subscriptions = array();

  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (!empty($email) && valid_email_address($email)) {
      $subscriptions[$email] = $email;
    }
  }
  pdfbulletin_subscribers_save($form_state['values']['pdfbulletin']->nid, $subscriptions);
  drupal_set_message(t('Subscriptions saved'));
}

/**
 * Form constructor for sending a one of test of an inidividual PDF Bulletin.
 *
 * @param pdfbulletin.
 *   PDF Bulletin object from pdfbulletin_load().
 *
 * @see pdfbulletin_sendtest_form_validate().
 * @see pdfbulletin_sendtest_form_submit().
 * @ingroup forms.
 */
function pdfbulletin_sendtest_form($form_state, $node) {
  $pdfbulletin = $node->pdfbulletin;
  pdfbulletin_generate_bulletin($pdfbulletin);
  $stage1 = '<h2>' . t('Step 1: Download a copy of the pdf') . '</h2>';
  $stage1 .= theme('pdfbulletin_generate_pdf_link', $pdfbulletin->file->filepath, $pdfbulletin);
  $form['stage1'] = array(
    '#type' => 'markup',
    '#value' => $stage1,
  );
  $form['stage2'] = array(
    '#type' => 'markup',
    '#value' => '<h2>' . t('Step 2: Send a copy with a test e-mail') . '</h2>',
  );
  $form['pdfbulletin'] = array(
    '#type' => 'value',
    '#value' => $pdfbulletin,
  );
  $form['subscribers'] = array(
    '#type' => 'textarea',
    '#title' => t('e-mail addresses to send test message to'),
    '#description' => t('Add one e-mail address per line.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form; 
}

/**
 * Form validation handler for pdfbulletin_sendtest_form().
 *
 * @see pdfbulletin_sendtest_form_submit().
 */
function pdfbulletin_sendtest_form_validate($form, &$form_state) {
  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (! empty($email) && ! valid_email_address($email)) {
      form_set_error('subscribers', t('Invalid e-mail address: @email', array('@email' => $email)));
    }
  }
}

/**
 * Form submission handler for pdfbulletin_sendtest_form_submit().
 * 
 * @see pdfbulletin_sendtest_form_validate().
 */
function pdfbulletin_sendtest_form_submit($form, &$form_state) {
  $subscriptions = array();

  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (!empty($email) && valid_email_address($email)) {
      $subscriptions[$email] = $email;
    }
  }
 
  $pdfbulletin = $form_state['values']['pdfbulletin'];
  $pdfbulletin->subscribers = $subscriptions;
  pdfbulletin_send_email($pdfbulletin);

  drupal_set_message('Test message sent.');
  // @todo make this more redirect friendly
  drupal_goto('/pdfbulletin/' . $pdfbulletin->id . '/subscribers');
}

/**
 * Page callback for a sample of an individual PDF Bulletin.
 *
 * @param pdfbulletin.
 *  PDF BUlletin object from pdfbulletin_load().
 */
function pdfbulletin_generate_pdf_page($pdfbulletin) {
  pdfbulletin_generate_bulletin($pdfbulletin);
  return theme('pdfbulletin_generate_pdf_page', $pdfbulletin, $pdfbulletin->file->filepath, $pdfbulletin->html, $pdfbulletin->header_safe, $pdfbulletin->footer_safe);
}
