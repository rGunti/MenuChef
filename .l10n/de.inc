<?php
return [
    '_LANG_NAME' => 'Deutsch',
    '_LANG_AUTHOR' => 'rGunti',
    '_LANG_BY_STRING' => 'von %1$s',
    '_LANG_FLAG' => '/img/lang/flag-germany.png',

    'app_version' => 'App Version',

    'copyright_title' => 'Copyright',
    'copyright_content' => 'Copyright &COPY; %1$s rGunti',

    'language' => 'Sprache',
    'languages' => 'Sprachen',

    'login' => 'Login',
    'logout' => 'Logout',
    'save' => 'Speichern',

    'debug_title' => 'Debug Info',
    'debug_no_items' => 'keine Elemente',
    'debug_session_info' => 'Session Info',
    'debug_instance' => 'Instanz',

    'home' => 'Home',

    'username' => 'Benutzername',
    'password' => 'Passwort',
    'mail_address' => 'E-Mail-Adresse',

    'toggle_nav' => 'Navigation anzeigen / ausblenden',

    'user_settings_title' => 'Benutzereinstellungen',
    'change_password' => 'Passwort ändern',
    'confirm_password' => 'Geändertes Passwort bestätigen',
    'change_password_help' => 'Wenn du das Passwort nicht ändern möchtest, lass die Passwortfelder leer.',

    'tos_title' => 'Nutzungsbedingungen',
    'tos_content' => 'Nutzungsbedingungen wurden noch nicht erstellt.',

    'message_logged_in' => 'Willkommen, %1$s',
    'message_logged_in_content' => 'Du wurdest erfolgreich angemeldet!',
    'message_logged_out' => 'Du wurdest erfolgreich abgemeldet!',

    'error_login_invalid' => 'Ungültige Login-Daten',
    'error_login_invalid_content' => 'Deine Login-Daten scheinen ungültig zu sein. Bitte überprüfe deine Eingabe und versuche es noch einmal.',

    'error_login_blocked' => 'Gesperrt',
    'error_login_blocked_content' => 'Dein Account wurde gesperrt.',

    'error_navigation_login_needed' => 'Login benötigt',
    'error_navigation_login_needed_content' => 'Bitte melde dich an, um diesen Inhalt sehen zu können.',

    'error_navigation_admin_needed' => 'Administrative Rechte benötigt',
    'error_navigation_admin_needed_content' => 'Du kannst nicht auf diese Inhalte zugreifen, weil du nicht die erforderlichen Rechte hast.',

    'admin_tools' => 'Admin Tools',
    'admin_tools_users' => 'Benutzer verwalten',

    'id' => 'ID',
    'admin_permission' => 'Administrative Rechte',
    'admin_permission_short' => 'Admin',
    'batch' => 'Batch-Benutzer',
    'batch_short' => 'Batch',
    'disabled' => 'Benutzer gesperrt',
    'disabled_short' => 'Gesperrt',
    'actions' => 'Aktionen',

    'ok' => 'OK',
    'cancel' => 'Abbrechen',
    'yes' => 'Ja',
    'no' => 'Nein',

    'disable_login' => 'Account sperren',
    'enable_login' => 'Account entsperren',
    'reset_password' => 'Passwort zurücksetzen',
    'delete_user' => 'Account löschen',

    'modal_unhandled_error_title' => 'Unerwarteter Fehler',
    'modal_unhandled_error_text' => 'Es ist ein unerwarteter Fehler aufgetreten. Folgende Informationen stehen zur Verfügung:',

    'modal_disable_login_question' => 'Möchtest Du den Benutzer %1$s sperren?</p><p>' .
        '%1$s kann sich nicht neu anmelden und hat keinen Zugriff auf die eigenen Daten, bis die Sperre aufgehoben wird.',
    'modal_enable_login_question' => 'Möchtest Du den Benutzer %1$s entsperren?',
    'modal_reset_user_question' => 'Möchtest Du das Passwort von %1$s wirklich zurücksetzen?</p></p>' .
        '%1$s ist danach nicht mehr in der Lage, sich anzumelden ohne die Mitteilung des neuen Passworts.',
    'modal_reset_user_success' => 'Das Passwort von %1$s wurde erfolgreich zurückgesetzt. Das neue Passwort lautet:</p><p>%2$s',

    'datatable_decimal' => '.',
    'datatable_thousands' => ' ',
    'datatable_empty' => 'Keine Daten verfügbar',
    'datatable_info' => 'Zeige _START_ bis _END_ von _TOTAL_ Einträgen',
    'datatable_info_empty' => 'Keine Einträge vorhanden',
    'datatable_info_filtered' => '(gefiltert von insgesamt _MAX_ Einträgen)',
    'datatable_info_postfix' => '',
    'datatable_length_menu' => 'Zeige _MENU_ Einträge',
    'datatable_loading' => 'Lade...',
    'datatable_processing' => 'Verarbeite...',
    'datatable_search' => 'Schnellsuche: ',
    'datatable_zero_records' => 'Kein passender Eintrag gefunden',
    'datatable_paginate_first' => 'Erste Seite',
    'datatable_paginate_last' => 'Letzte Seite',
    'datatable_paginate_next' => 'Nächste',
    'datatable_paginate_prev' => 'Vorherige',
    'datatable_aria_sort_asc' => ': zum aufsteigenden Sortieren klicken',
    'datatable_aria_sort_desc' => ': zum absteigenden Sortieren klicken',

    'ajax_response_no_action' => 'Keine Action übergeben.',
    'ajax_response_unknown_action' => 'Aktion "%1$s" wird nicht unterstützt.',

    'ajax_response_db_save_fail' => 'Beim Speichern der Änderungen ist ein unbekannter Fehler aufgetreten.',

    'ajax_response_user_no_id' => 'Keine User-ID übergeben.',
    'ajax_response_user_id_not_found' => 'User-ID nicht gefunden.',
    'ajax_response_user_disable_already' => 'Account ist schon gesperrt.',
    'ajax_response_user_disable_yourself' => 'Du kannst dich nicht selbst sperren.',
    'ajax_response_user_enable_already' => 'Account ist schon entsperrt.',
    'ajax_response_user_enable_yourself' => 'Du kannst dich nicht selbst entsperren.',
    'ajax_response_user_reset_yourself' => 'Du kannst dein eigenes Passwort nicht zurücksetzen.',
];
