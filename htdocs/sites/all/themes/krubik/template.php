<?php


/**
 * Implementation of hook_theme().
 */
function krubik_theme() {
  $items = array();
  
  // theme('blocks') targeted override for content region.
  $items['blocks_content'] = array('arguments' => array('doit' => TRUE));

  $items['node_form'] = array(
    'arguments' => array('form' => array()),
    'path' => drupal_get_path('theme', 'rubik') .'/templates',
    'template' => 'form-default',
    'preprocess functions' => array(
      'rubik_preprocess_form_filter',
      'rubik_preprocess_form_buttons',
      'krubik_preprocess_form_node',
    ),
  );

  return $items;
}

function krubik_blocks_content($doit = TRUE) {
  static $blocks;
  if (!isset($blocks)) {
    $blocks = module_exists('context') && function_exists('context_blocks') ? context_blocks('content') : theme_blocks('content');
  }
  return $doit ? $blocks : '';
}


/**
 * Preprocessor for theme('node_form').
 */
function krubik_preprocess_form_node(&$vars) { //print_r($vars);
  $sidebar = array(
    'taxonomy', 'menu', 'author', 'revision_information', 'comment_settings', 
    'options',
  );
  $vars['sidebar'] = isset($vars['sidebar']) ? $vars['sidebar'] : array();
  foreach ($sidebar as $sideb) {
    if (isset($vars['form'][$sideb])) {
      $vars['sidebar'][$sideb] = $vars['form'][$sideb];
      unset($vars['form'][$sideb]);
    }
  }
}

