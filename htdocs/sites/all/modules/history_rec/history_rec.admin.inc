<?php

/**
 * @file
 * Administration interface for Browsing History Recommender 
 */

/**
 * Administration form
 */
function history_rec_settings_form() {
  $form = array();

  $form['enabled_types'] = array(
    '#title' => t("Enabled content types"),
    '#type' => 'checkboxes',
    '#default_value' => variable_get('history_rec_enabled_types', array()),
    '#options' => node_get_types('names'),
    '#description' => t('Please select which content types you want to enable for node browsing history recommendation.')
  );

  $form['display_num_rel'] = array(
    '#title' => t('Number of items to display in the Related block'),
    '#type' => 'textfield',
    '#default_value' => variable_get('history_rec_display_num_rel', 5),
    '#size' => 4,
    '#maxlength' => 2,
    '#description' => t('Please specify how many items to show in the "Related Nodes" block list.')
  );

  $form['display_num_rec'] = array(
    '#title' => t('Number of items to display in the Recommended block'),
    '#type' => 'textfield',
    '#default_value' => variable_get('history_rec_display_num_rec', 5),
    '#size' => 4,
    '#maxlength' => 2,
    '#description' => t('Please specify how many items to show in the "Recommended Nodes" block list.')
  );

  $form['no_duplicates'] = array(
    '#title' => t('Aviod duplicate results'),
    '#type' => 'checkbox',
    '#description' => t('Check the box to ensure that if a node is being displayed somewhere else in the page, it is not listed as a recommendation.'),
    '#default_value' => variable_get('history_rec_no_duplicates', 1),
  );

  $form['boost_comments'] = array(
    '#title' => t('Boost comments'),
    '#type' => 'checkbox',
    '#description' => t('Check the box to consider commenting as browse history too.'),
    '#default_value' => variable_get('history_rec_boost_comments', 1),
  );

  $form['boost_recency'] = array(
    '#title' => t('Boost recent items'),
    '#type' => 'checkbox',
    '#description' => t('Check the box to boost recent node browsing history and recent comment history (if enabled).'),
    '#default_value' => variable_get('history_rec_boost_recency', 1),
  );

  /* $form['algorithm'] = array(
    '#title' => t('Choose recommender algorithm'),
    '#type' => 'radios',
    '#default_value' => variable_get('history_rec_algorithm', 'classical'),
    '#options' => array(
      'cooccurrence' => t("Cooccurrence (less accurate; better performance)"),
      'classical' => t("Classical (more accurate; slower performance)"),
    ),
    '#description' => t('Different algorithms are useful in different situations. Please leave it as the default classical algorithm unless you have large number of nodes/users.')
  ); */

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit administration form
 */
function history_rec_settings_form_submit($form, &$form_state) {
  $display_num['rel'] = intval($form_state['values']['display_num_rel']);
  $display_num['rec'] = intval($form_state['values']['display_num_rec']);
  $boost_comments = $form_state['values']['boost_comments'];
  $boost_recency = $form_state['values']['boost_recency'];
  $no_duplicates = $form_state['values']['no_duplicates'];
  $enabled_types = array_diff($form_state['values']['enabled_types'], array('0'));
  //$algorithm = $form_state['values']['algorithm']; // default is the classical algorithm

  variable_set('history_rec_no_duplicates', $no_duplicates);
  variable_set('history_rec_display_num_rel', $display_num['rel']);
  variable_set('history_rec_display_num_rec', $display_num['rec']);
  variable_set('history_rec_boost_comments', $boost_comments);
  variable_set('history_rec_boost_recency', $boost_recency);
  variable_set('history_rec_enabled_types', $enabled_types);
  //variable_set('history_rec_algorithm', $algorithm);

  drupal_set_message(t("The configuration options have been saved."));
}

/**
 * Validate administration form
 */
function history_rec_settings_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['display_num_rel'])) {
    form_set_error('display_num_rel', t('"Number of items to display in the Related block" must be numeric.'));
  }
  if (!is_numeric($form_state['values']['display_num_rec'])) {
    form_set_error('display_num_rec', t('"Number of items to display in the Recommended block" must be numeric.'));
  }
}