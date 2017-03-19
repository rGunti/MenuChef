<?php
class L10N {
    const L10N_DICTIONARY = "/.l10n";
    const L10N_DEFAULT = "en";
    const L10N_UNKNOWN_STRING = 'Unknown Text "%1$s"';

    const L10N_LANG_INFO_NAME = '_LANG_NAME';
    const L10N_LANG_INFO_AUTHOR = '_LANG_AUTHOR';

    const L10N_ALLOWED_CHARS = 'abcdefghijklmnopqrstuvwxyz';

    private static $l10n;

    private static function getL10NPath($language) {
        return __DIR__ . '/..' . self::L10N_DICTIONARY . '/' .
            StringUtils::removeIllegalChars(strtolower($language), self::L10N_ALLOWED_CHARS) .
            ".inc";
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
        Logger::logRequire($lang_path);
        self::$l10n = require $lang_path;
    }

    public static function initL10N() {
        if (empty(self::$l10n)) {
            Logger::debug("L10N is being initialized for the first time in this request...");
            $user_lang = self::getUserLanguage();
            Logger::debug("Users language is $user_lang");
            self::loadL10N($user_lang);
        }
    }

    public static function getString($key, $args = []) {
        // Load L10N file if not loaded
        self::initL10N();

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

    public static function getLanguageCookie() {
        return @$_COOKIE['ForcedLanguage'];
    }

    public static function setLanguageCookie($lang) {
        Logger::info("Setting Language Cookie: $lang");
        setcookie('ForcedLanguage', $lang);
        $_COOKIE['ForcedLanguage'] = $lang;
    }

    public static function clearLanguageCookie() {
        setcookie('ForceLanguage', '', -1);
    }

    public static function getUserLanguage() {
        if (!empty($_GET['lang'])) {
            $lang = $_GET['lang'];
            Logger::debug("Language Change has been forced by URL, changing to $lang");
            if (self::l10nExists($lang)) {
                L10N::setLanguageCookie($lang);
                return $lang;
            } else {
                Logger::warn("Requested Language $lang does not exist, returning to default procedure");
            }
        }

        if (!empty(self::getLanguageCookie())) {
            Logger::verbose("Language Cookie is present, reading it...");
            return self::getLanguageCookie();
        } else {
            Logger::verbose("No language Cookie available, parsing HTTP header...");
            return self::parseUserLanguageSettings();
        }
    }

    public static function parseUserLanguageSettings() {
        foreach (explode(',', $_SERVER['HTTP_ACCEPT_LANGUAGE']) as $language) {
            Logger::verbose("Language setting in HTTP header: $language");
            $lang_info = explode(';', $language);
            if (self::l10nExists($lang_info[0])) {
                Logger::debug("Found Language in HTTP header, using $lang_info[0]");
                self::setLanguageCookie($lang_info[0]);
                return $lang_info[0];
                break;
            }
        }
        Logger::debug("No known language in HTTP header, using Default...");
        self::setLanguageCookie(self::L10N_DEFAULT);
        return self::L10N_DEFAULT;
    }

    /**
     * Returns a list of available languages
     * @return array
     */
    public static function getLanguageList() {
        $languages = [];
        foreach (glob(__DIR__ . '/..' . self::L10N_DICTIONARY . '/*.inc', GLOB_MARK) as $file) {
            $lang = str_replace('.inc', '', basename($file));
            $lang_c = require self::getL10NPath($lang);
            $languages[$lang] = $lang_c[self::L10N_LANG_INFO_NAME];
        }
        return $languages;
    }
}

function t($key, $args = []) { return L10N::getString($key, $args); }
