<?php
/**
 * @file
 *  PDF Bulletin rules defaults.
 */

/**
 * Implementation of hook_rules_defaults().
 */
function pdfbulletin_rules_defaults() {
  return array (
    'rules' => 
    array (
      'pdfbulletin_schedule' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Schedule pdfbulletin',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'pdfbulletin',
        ),
        '#status' => 'default',
        '#conditions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Created content is PDF Bulletin',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => 
            array (
              'type' => 
              array (
                'pdfbulletin' => 'pdfbulletin',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'task_identifier' => 'Schedule pdfbulletin [node:nid]',
              'task_date' => '[node:field_schedule-next-timestamp]',
              '#argument map' => 
              array (
                'node' => 'node',
              ),
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'task_identifier' => 
                  array (
                    0 => 'node',
                  ),
                  'task_date' => 
                  array (
                    0 => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'rules_action_schedule_set_pdfbulletin_schedule_pdfbulletin',
            '#info' => 
            array (
              'arguments' => 
              array (
                'task_identifier' => 
                array (
                  'type' => 'string',
                  'label' => 'Identifier',
                  'description' => 'User provided string to identify the task. Existing tasks for this rule set with the same identifier will be replaced.',
                ),
                'task_date' => 
                array (
                  'type' => 'date',
                  'label' => 'Scheduled evaluation date',
                ),
                'node' => 
                array (
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'label' => 'Schedule "Schedule pdfbulletin"',
              'status' => 'default',
              'categories' => 
              array (
                0 => 'pdfbulletin',
              ),
              'module' => 'Rule Scheduler',
              'base' => 'rules_scheduler_action',
              'set' => 'pdfbulletin_schedule_pdfbulletin',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'pdfbulletin_schedule_next' => 
      array (
        '#type' => 'rule',
        '#set' => 'pdfbulletin_schedule_pdfbulletin',
        '#label' => 'Schedule next pdfbulletin',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'pdfbulletin',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              'number1' => '[node:field_date-next-timestamp]',
              'number2' => '1',
              'operation' => 'greater',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'number1' => 
                  array (
                    0 => 'node',
                    1 => ':global',
                  ),
                  'number2' => 
                  array (
                    0 => ':global',
                  ),
                ),
              ),
            ),
            '#name' => 'rules_condition_number_compare',
            '#info' => 
            array (
              'label' => 'Numeric comparison',
              'arguments' => 
              array (
                'number1' => 
                array (
                  'label' => 'Number 1',
                  'type' => 'number',
                ),
                'number2' => 
                array (
                  'label' => 'Number 2',
                  'type' => 'number',
                ),
              ),
              'module' => 'Rules',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'arguments' => 
              array (
                'task_identifier' => 
                array (
                  'type' => 'string',
                  'label' => 'Identifier',
                  'description' => 'User provided string to identify the task. Existing tasks for this rule set with the same identifier will be replaced.',
                ),
                'task_date' => 
                array (
                  'type' => 'date',
                  'label' => 'Scheduled evaluation date',
                ),
                'node' => 
                array (
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'label' => 'Schedule "Schedule pdfbulletin"',
              'status' => 'default',
              'categories' => 
              array (
                0 => 'pdfbulletin',
              ),
              'module' => 'Rule Scheduler',
              'base' => 'rules_scheduler_action',
              'set' => 'pdfbulletin_schedule_pdfbulletin',
            ),
            '#name' => 'rules_action_schedule_set_pdfbulletin_schedule_pdfbulletin',
            '#settings' => 
            array (
              'task_identifier' => 'Schedule pdfbulletin [node:nid]',
              'task_date' => '[node:field_schedule-next-timestamp]',
              '#argument map' => 
              array (
                'node' => 'node',
              ),
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'task_identifier' => 
                  array (
                    0 => 'node',
                    1 => ':global',
                  ),
                  'task_date' => 
                  array (
                    0 => 'node',
                    1 => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'pdfbulletin_send_pdfbulletin' => 
      array (
        '#type' => 'rule',
        '#set' => 'pdfbulletin_schedule_pdfbulletin',
        '#label' => 'Send pdfbulletin',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
        ),
        '#status' => 'altered',
        '#conditions' => 
        array (
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Send a PDF bulletin',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'PDF Bulletin to send',
                ),
              ),
              'module' => 'PDF Bulletin',
            ),
            '#name' => 'pdfbulletin_send_action',
            '#settings' => 
            array (
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
    'rule_sets' => 
    array (
      'pdfbulletin_schedule_pdfbulletin' => 
      array (
        'arguments' => 
        array (
          'node' => 
          array (
            'label' => 'Content',
            'type' => 'node',
          ),
        ),
        'label' => 'Schedule pdfbulletin',
        'status' => 'default',
        'categories' => 
        array (
          0 => 'pdfbulletin',
        ),
      ),
    ),
  );
}
