<?php
class L10N {
    const L10N_DICTIONARY = "/.l10n";
    const L10N_DEFAULT = "en";
    const L10N_UNKNOWN_STRING = 'Unknown Text "%1$s"';

    const L10N_LANG_INFO_NAME = '_LANG_NAME';
    const L10N_LANG_INFO_AUTHOR = '_LANG_AUTHOR';

    private static $l10n;

    private static function getL10NPath($language) {
        return __DIR__ . '/..' . self::L10N_DICTIONARY . "/$language.inc";
    }

    public static function l10nExists($language) {
        return file_exists(self::getL10NPath($language));
    }

    public static function loadL10N($language) {
        if (self::l10nExists($language)) {
            $lang_path = self::getL10NPath($language);
        } else {
            $lang_path = self::getL10NPath(self::L10N_DEFAULT);
        }
        self::$l10n = require $lang_path;
    }

    public static function getString($key, $args = []) {
        // Load L10N file if not loaded
        if (empty($l10n)) {
            self::loadL10N(self::L10N_DEFAULT);
        }

        // Get Text if exists
        if (key_exists($key, self::$l10n)) {
            if (empty($args)) {
                return self::$l10n[$key];
            } else {
                return vsprintf(self::$l10n[$key], $args);
            }
        } else {
            return sprintf(self::L10N_UNKNOWN_STRING, $key);
        }
    }

    public static function getLanguageName() {
        return self::getString(self::L10N_LANG_INFO_NAME);
    }

    public static function getLanguageAuthor() {
        return self::getString(self::L10N_LANG_INFO_AUTHOR);
    }
}

function t($key, $args = []) { return L10N::getString($key, $args); }
