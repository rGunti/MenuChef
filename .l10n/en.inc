<?php
return [
    '_LANG_NAME' => 'English (default)',
    '_LANG_AUTHOR' => 'rGunti',
    '_LANG_BY_STRING' => 'by %1$s',
    '_LANG_FLAG' => '/img/lang/flag-united-kingdom.png',

    'app_version' => 'App Version',

    'copyright_title' => 'Copyright',
    'copyright_content' => 'Copyright &COPY; %1$s rGunti',
    'copyright_show_more' => 'Show more...',
    'copyright_full_content' => '@file:.cfg/docs/copyright/en.html',

    'language' => 'Language',
    'languages' => 'Languages',

    'login' => 'Login',
    'logout' => 'Logout',
    'save' => 'Save',

    'debug_title' => 'Debug Info',
    'debug_no_items' => 'no items',
    'debug_session_info' => 'Session Info',
    'debug_instance' => 'Instance',

    'home' => 'Home',

    'username' => 'Username',
    'password' => 'Password',
    'mail_address' => 'Mail address',

    'toggle_nav' => 'Toggle navigation',

    'user_settings_title' => 'User Settings',
    'change_password' => 'Change Password',
    'confirm_password' => 'Confirm new Password',
    'change_password_help' => 'If you don\'t want to change your password, leave the password fields empty.',

    'app_documents_title' => 'Application Documents',
    'app_documents_content' => 'This page links to documents which are essential for operation and usage of ' .
        'this web application.',

    'tos_title' => 'Terms Of Use',
    'tos_content' => 'Terms of use have not been defined yet.',
    'tos_full_content' => '@file:.cfg/docs/tos/en.html',

    'imprint_box_title' => 'Imprint & ToS',
    'imprint_title' => 'Imprint',
    'imprint_full_content' => '@file:.cfg/docs/imprint/en.html',

    'message_logged_in' => 'Welcome, %1$s',
    'message_logged_in_content' => 'Your login was successful!',
    'message_logged_out' => 'You have been logged out!',

    'error_login_invalid' => 'Invalid Login Credentials',
    'error_login_invalid_content' => 'Your Login Credentials seem to be invalid. Please check your entry and try again.',

    'error_login_blocked' => 'Blocked',
    'error_login_blocked_content' => 'Your account has been blocked.',

    'error_navigation_login_needed' => 'Login needed',
    'error_navigation_login_needed_content' => 'Please login in order to access this content.',

    'error_navigation_admin_needed' => 'Administrative Permission required',
    'error_navigation_admin_needed_content' => 'You cannot access this content because you do not have the required administrative permission.',

    'admin_tools' => 'Admin Tools',
    'admin_tools_users' => 'Manage Users',

    'id' => 'ID',
    'admin_permission' => 'Administrative Permissions',
    'admin_permission_short' => 'Admin',
    'batch' => 'Batch User',
    'batch_short' => 'Batch',
    'disabled' => 'User Disabled',
    'disabled_short' => 'Disabled',
    'actions' => 'Actions',

    'ok' => 'OK',
    'cancel' => 'Cancel',
    'yes' => 'Yes',
    'no' => 'No',

    'disable_login' => 'Lock account',
    'enable_login' => 'Unlock account',
    'reset_password' => 'Reset password',
    'delete_user' => 'Delete account',

    'modal_unhandled_error_title' => 'Unexpected Error',
    'modal_unhandled_error_text' => 'An unexpected error has occured. Below is some information about the error:',

    'modal_default_error_title' => 'Error',

    'modal_disable_login_question' => 'Would you like to disable %1$s?</p><p>' .
        '%1$s cannot log in and cannot access their data until the account is unlocked again.',
    'modal_enable_login_question' => 'Would you like to enable %1$s?',
    'modal_reset_user_question' => 'Would you like to reset the login password of %1$s?</p></p>' .
        '%1$s will not be able to log into their account without their new password.',
    'modal_reset_user_success' => 'The password of %1$s has been reset. The new password is:</p><p>%2$s',
    'modal_delete_user_question' => 'Would you like to delete the account of %1$s?</p><p>' .
        'Deleting the account will also delete related data!',

    'datatable_decimal' => '.',
    'datatable_thousands' => ',',
    'datatable_empty' => 'No data available',
    'datatable_info' => 'Showing _START_ to _END_ of _TOTAL_ entries',
    'datatable_info_empty' => 'No entries available',
    'datatable_info_filtered' => '(filtered from _MAX_ total entries)',
    'datatable_info_postfix' => '',
    'datatable_length_menu' => 'Show _MENU_ entries',
    'datatable_loading' => 'Loading...',
    'datatable_processing' => 'Processing...',
    'datatable_search' => 'Quick Search: ',
    'datatable_zero_records' => 'No matching records found',
    'datatable_paginate_first' => 'First',
    'datatable_paginate_last' => 'Last',
    'datatable_paginate_next' => 'Next',
    'datatable_paginate_prev' => 'Prev.',
    'datatable_aria_sort_asc' => ': activate to sort column ascending',
    'datatable_aria_sort_desc' => ': activate to sort column descending',

    'ajax_response_no_action' => 'No action provided.',
    'ajax_response_unknown_action' => 'Action "%1$s" not supported.',

    'ajax_response_db_save_fail' => 'An unknown error occured while saving data.',

    'ajax_response_user_no_id' => 'No User ID provided.',
    'ajax_response_user_id_not_found' => 'User ID not found.',
    'ajax_response_user_disable_already' => 'Account is already disabled.',
    'ajax_response_user_disable_yourself' => 'You cannot disable yourself.',
    'ajax_response_user_enable_already' => 'Account is already enabled.',
    'ajax_response_user_enable_yourself' => 'You cannot enable yourself.',
    'ajax_response_user_reset_yourself' => 'You cannot reset your own password.',
    'ajax_response_user_delete_yourself' => 'You cannot delete yourself.',
    'ajax_response_user_delete_protected' => 'This account is protected and cannot be deleted.',
];
