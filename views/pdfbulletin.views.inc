<?php

/**
 * @file
 *  Provide views data and handlers for pdfbulletin.module.
 */

/**
 * Implementation of hook_views_data().
 */
function pdfbulletin_views_data() {
  // table information
  $data['pdfbulletin_view']['table']['group'] = t('PDF Bulletins');

  // available as a base table
  $data['pdfbulletin_view']['table']['base'] = array(
    'field' => 'id',
    'title' => t('PDF Bulletins'),
    'help' => t('PDF bulletins views and ids.'),
  );

  // fields
  $data['pdfbulletin_view']['id'] = array(
    'title' => t('Bulletin number'),
    'help' => t('The ID of the PDF Bulletin'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'title',
      'zero is null' => TRUE,
    ),
    'filter' => array(
       //
    ),
  );

  $data['pdfbulletin_view']['name'] = array(
    'title' => t('View name'),
    'help' => t('Name of the view that the Bulletin is based on.'),
    'field' => array(
      'handler' => 'views_handler_field_xss', // @todo we're just looking at check_plain?
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['pdfbulletin_view']['display_id'] = array(
    'title' => t('View display'),
    'help' => t('Dispaly ID of the view that the Bulletin is based on.'),
    'field' => array(
      'handler' => 'views_handler_field_xss', // @todo we're just looking at check_plain?
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
