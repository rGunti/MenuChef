<?php

/**
 * Class AppUtils
 */
class AppUtils {
    private static $basePath;

    /**
     * Returns a default value if the given value is null or empty
     * @param mixed $value Value to check
     * @param mixed $default Default value to return
     * @return mixed
     */
    public static function getDefaultValue($value, $default = '') {
        return (!isset($value) || is_null($value)) ? $default : $value;
    }

    /**
     * Returns the applications base path for usage in Links etc.
     * @return string
     */
    public static function getBasePath() {
        if (empty(self::$basePath)) {
            $base = explode(PathUtils::PATH_DELIMITER, $_SERVER['SCRIPT_NAME']);
            array_pop($base);
            self::$basePath = implode(PathUtils::PATH_DELIMITER, $base);
        }
        return self::$basePath;
    }
}

/**
 * Class StringUtils
 */
class StringUtils {
    /**
     * Returns true if the string $haystack starts with the given string $needle.
     * @param string $haystack
     * @param string $needle
     * @return bool
     */
    public static function startsWith($haystack, $needle) {
        $length = strlen($needle);
        return (substr($haystack, 0, $length) === $needle);
    }

    /**
     * Returns true if the string $haystack ends with the given string $needle.
     * @param string $haystack
     * @param string $needle
     * @return bool
     */
    public static function endsWith($haystack, $needle) {
        $length = strlen($needle);
        if ($length == 0) {
            return true;
        }
        return (substr($haystack, -$length) === $needle);
    }
}

/**
 * Class PathUtils
 */
class PathUtils {
    /** Path delimiter used to split the navigation path */
    const PATH_DELIMITER = '/';

    /**
     * Returns the Current Navigation Path.
     * @return string Current Navigation Path
     */
    public static function getCurrentPath() {
        return AppUtils::getDefaultValue(@$_SERVER['PATH_INFO'], self::PATH_DELIMITER);
    }

    /**
     * Returns the Current Navigation Path as an array of string elements.
     * @return array
     */
    public static function getCurrentPathAsArray() {
        return explode(self::PATH_DELIMITER, self::getCurrentPath());
    }

    /**
     * Returns true if the Current Path matches a given pattern.
     * @param $check_path string Path Pattern to check against. Wildcard * matches with a numeric element.
     * @return bool True, if the pattern matches the current path
     */
    public static function currentPathMatches($check_path) {
        return self::pathMatches(self::getCurrentPath(), $check_path);
    }

    /**
     * Returns true if the given Path matches a given pattern.
     * @param $path string Path to check
     * @param $check_path string Path Pattern to check against. Wildcard * matches with a numeric element.
     * @return bool True, if the pattern matches the given path
     */
    public static function pathMatches($path, $check_path) {
        $current_path = $path;
        $current_path_arr = explode(self::PATH_DELIMITER, $current_path);
        $check_path_arr = explode(self::PATH_DELIMITER, $check_path);

        //echo "<pre>Path:    $path\nPattern: $check_path</pre>";
        //echo "<pre>";
        //print_r($current_path_arr);
        //print_r($check_path_arr);
        //echo "</pre>";

        // An unequal amount of Path Elements means that the paths are not equal
        if (count($current_path_arr) != count($check_path_arr)) {
            return false;
        }

        //echo "<pre>";
        $expr_els = [];
        for ($i = 0; $i < count($check_path_arr); $i++) {
            //$el_current = $current_path[$i];
            $el_check = $check_path_arr[$i];
            //echo "$i : $el_check\n";

            if (empty($el_check)) {
                array_push($expr_els, "");
            } else if ($el_check == "*") {
                array_push($expr_els, "([0-9]*)");
            } else {/*
                $expr_el = "";
                for ($k=0; $k < strlen($el_check); $k++) {
                    $expr_el .= "\\" . $el_check[$k];
                }
                echo " - $expr_el";
                array_push($expr_els, $expr_el);*/
                array_push($expr_els, $el_check);
            }
        }
        //echo "</pre>";

        $expr = implode("\\/", $expr_els);
        //echo "<pre>Expression: /^$expr$/</pre>";
        return (preg_match("/^$expr" . '$/', $current_path) == 1);
    }

    /**
     * Returns an internal link to use within the application
     * @param $absolute_link
     * @return string
     */
    public static function getLink($absolute_link) {
        return AppUtils::getBasePath() . $absolute_link;
    }
}

/**
 * Class RequestUtils
 */
class RequestUtils {
    public static function getRemoteIP() { return $_SERVER['REMOTE_ADDR']; }
    public static function getRequestTime() { return $_SERVER['REQUEST_TIME']; }
    public static function getRequestMethod() { return $_SERVER['REQUEST_METHOD']; }
    public static function getUserAgentString() { return $_SERVER['HTTP_USER_AGENT']; }
    public static function getUserAcceptLang() { return $_SERVER['HTTP_ACCEPT_LANGUAGE']; }
}
