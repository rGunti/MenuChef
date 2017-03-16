<?php

/**
 * Class AppUtils
 */
class AppUtils {
    /**
     * Returns a default value if the given value is null or empty
     * @param mixed $value Value to check
     * @param mixed $default Default value to return
     * @return mixed
     */
    public static function getDefaultValue($value, $default = '') {
        return (!isset($value) || is_null($value)) ? $default : $value;
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
        $current_path_arr = explode($current_path, self::PATH_DELIMITER);
        $check_path_arr = explode($check_path, self::PATH_DELIMITER);

        // An unequal amount of Path Elements means that the paths are not equal
        if (count($current_path_arr) != count($check_path_arr)) {
            return false;
        }

        $expr_els = [];
        for ($i = 0; $i < count($check_path_arr); $i++) {
            //$el_current = $current_path[$i];
            $el_check = $check_path_arr[$i];

            if ($el_check == "*") {
                array_push($expr_els, "([0-9]*)");
            } else {
                array_push($expr_els, $el_check);
            }
        }

        $expr = implode("\\/", $expr_els);
        return (preg_match("/^$expr$/", $current_path) == 1);
    }
}
