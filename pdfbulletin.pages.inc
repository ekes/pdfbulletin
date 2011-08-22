<?php

function pdfbulletin_edit_form($form_state, $pdfbulletin) {
  $form['pdfbulletin'] = array(
    '#type' => 'value',
    '#value' => $pdfbulletin,
  );
  $form['id'] = array(
    '#title' => t('Bulletin ID'),
    '#type' => 'textfield',
    '#value' => $pdfbulletin->id,
    '#disabled' => TRUE,
  );
  $form['name'] = array(
    '#title' => t('View name'),
    '#type' => 'textfield',
    '#value' => $pdfbulletin->name,
    '#disabled' => TRUE,
  );
  $form['display_id'] = array(
    '#title' => t('View display'),
    '#type' => 'textfield',
    '#value' => $pdfbulletin->display_id,
    '#disabled' => TRUE,
  );
  $form['frequency'] = array(
    '#type' => 'select',
    '#options' => array(
      '604800' => 'weekly',
    ),
    '#title' => t('Frequency'),
    '#default_value' => $pdfbulletin->frequency,
  );
  $form['date'] = array(
    '#type' => 'date',
    '#title' => t('Start date'),
    '#default_vaule' => $pdfbulletin->date, // @todo formatting
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#submit' => array('pdfbulletin_delete'),
    '#value' => t('Delete'),
  );
  return $form;
}

function pdfbulletin_edit_form_submit(&$form, &$form_state) {
  $pdfbulletin = $form_state['values']['pdfbulletin'];

  // @todo if changed?
  $start_date = $form_state['values']['date'];
  $start_time = strtotime($start_date['year'] . '-' . $start_date['month'] . '-' . $start_date['day']);
  $pending = variable_get('pdfbulletin_pending', array());
  $pending[$pdfbulletin->id] = array('start' => $start_time, 'frequency' => (int) $form_state['values']['frequency']);
  variable_set('pdfbulletin_pending', $pending);
}

function pdfbulletin_subscribers_form($form_state, $pdfbulletin) {
  $subscribers = '';
  foreach ($pdfbulletin->subscribers as $email) {
    $subscribers .= check_plain($email) . "\n";
  }

  $form['pdfbulletin'] = array(
    '#type' => 'value',
    '#value' => $pdfbulletin,
  );
  $form['id'] = array(
    '#title' => t('Bulletin ID'),
    '#type' => 'textfield',
    '#value' => $pdfbulletin->id,
    '#disabled' => TRUE,
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

function pdfbulletin_subscribers_form_validate($form, &$form_state) {
  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (! empty($email) && ! valid_email_address($email)) {
      form_set_error('subscribers', t('Invalid e-mail address: @email', array('@email' => $email)));
    }
  }
}

function pdfbulletin_subscribers_form_submit($form, &$form_state) {
  $subscriptions = array();

  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (!empty($email) && valid_email_address($email)) {
      $subscriptions[$email] = $email;
    }
  }
  pdfbulletin_subscribers_save($form_state['values']['pdfbulletin']->id, $subscriptions);
  drupal_set_message(t('Subscriptions saved'));
}

function pdfbulletin_sendtest_form($form_state, $pdfbulletin) {
  $form['pdfbulletin'] = array(
    '#type' => 'value',
    '#value' => $pdfbulletin,
  );
  $form['id'] = array(
    '#title' => t('Bulletin ID'),
    '#type' => 'textfield',
    '#value' => $pdfbulletin->id,
    '#disabled' => TRUE,
  );
  $form['subscribers'] = array(
    '#type' => 'textarea',
    '#title' => t('e-mail addresses'),
    '#description' => t('Add one e-mail address per line.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form; 
}

function pdfbulletin_sendtest_form_validate($form, &$form_state) {
  $emails = explode("\n", $form_state['values']['subscribers']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (! empty($email) && ! valid_email_address($email)) {
      form_set_error('subscribers', t('Invalid e-mail address: @email', array('@email' => $email)));
    }
  }
}

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
  pdfbulletin_generate_bulletin($pdfbulletin);
  pdfbulletin_send_email($pdfbulletin);

  drupal_set_message('Test message sent.');
}

function pdfbulletin_generate_pdf_page($pdfbulletin) {
  pdfbulletin_generate_bulletin($pdfbulletin);
  return theme('pdfbulletin_generate_pdf_page', $pdfbulletin, $pdfbulletin->html, $pdfbulletin->file->filepath);
} 
