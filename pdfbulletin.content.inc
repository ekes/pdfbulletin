<?php

/*
 *
 * CCK Field definitions.
 */
function pdfbulletin_content_default_fields() {
  return array (
    'pdfbulletin_schedule' => 
    array (
      'type_name' => 'pdfbulletin', 
      'label' => 'Schedule',
      'field_name' => 'field_schedule',
      'type' => 'datestamp',
      'widget_type' => 'date_text_repeat',
      'change' => 'Change basic information',
      'weight' => '32',
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'input_format' => 'Y-m-d H:i:s',
      'input_format_custom' => '',
      'advanced' => 
      array (
        'label_position' => 'above',
        'text_parts' => 
        array (
          'year' => 0,
          'month' => 0,
          'day' => 0,
          'hour' => 0,
          'minute' => 0,
          'second' => 0,
        ),
      ),
      'increment' => '1',
      'year_range' => '-1:+3',
      'label_position' => 'above',
      'text_parts' => 
      array (
      ),
      'description' => '',
      'group' => false,
      'required' => 0,
      'multiple' => 1,
      'repeat' => 1,
      'todate' => '',
      'granularity' => 
      array (
        'year' => 'year',
        'month' => 'month',
        'day' => 'day',
        'hour' => 'hour',
        'minute' => 'minute',
      ),
      'default_format' => 'medium',
      'tz_handling' => 'site',
      'timezone_db' => 'UTC',
      'repeat_collapsed' => '0',
      'op' => 'Save field settings',
      'module' => 'date',
      'widget_module' => 'date',
      'columns' => 
      array (
        'value' => 
        array (
          'type' => 'int',
          'not null' => false,
          'sortable' => true,
          'views' => true,
        ),
        'rrule' => 
        array (
          'type' => 'text',
          'not null' => false,
          'sortable' => false,
          'views' => false,
        ),
      ),
      'display_settings' => 
      array (
        'label' => 
        array (
          'format' => 'above',
          'exclude' => 0,
        ),
        'teaser' => 
        array (
          'format' => 'default',
          'exclude' => 0,
        ),
        'full' => 
        array (
          'format' => 'default',
          'exclude' => 0,
        ),
        4 => 
        array (
          'format' => 'default',
          'exclude' => 0,
        ),
      ),
    ),
  );
}
