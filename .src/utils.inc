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
     * Returns a value of an assoc array or a given default value if the key does not exist.
     * @param $arr array
     * @param $key string
     * @param $default mixed Default value to return if key cannot be found
     * @return mixed
     */
    public static function getKeyDefault($arr, $key, $default = 0) {
        if (isset($arr[$key])) { return $arr[$key]; }
        else { return $default; }
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

    /** Starts the Render Buffer */
    public static function startRenderBuffer() { ob_start(); }

    /** Gets the content of the Render Buffer */
    public static function getRenderBufferContent() { return ob_get_contents(); }

    /**
     * Clears the currently rendered content from the buffer.
     * @param $restart_buffer bool|true If True, the buffer will be restarted after it was cleared.
     */
    public static function clearRenderedContent($restart_buffer = true) {
        ob_clean();
        if ($restart_buffer) { self::startRenderBuffer(); }
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

    /**
     * @param string $s String to check
     * @param string $allowedChars Allowed characters
     * @return string String with only allowed characters
     */
    public static function removeIllegalChars($s, $allowedChars) {
        $allowedCharsArr = str_split($allowedChars);
        for ($i = 0; $i < strlen($s); ) {
            $char = $s[$i];
            if (in_array($char, $allowedCharsArr)) { $i++; }
            else {
                $s = str_replace($char, '', $s);
                $i = 0;
            }
        }
        return $s;
    }

    /**
     * Abbreviates a given string to a given length, if the String is longer than requested
     * @param $s string String to abbreviate
     * @param $maxLength int Max length of String (including Ellipse Character if needed)
     * @param $ellipse_char string Ellipse character (default: '&hellips;')
     * @return string Abbreviated String with a length of ($maxLength - 1 + $ellipse_char)
     */
    public static function abbreviate($s, $maxLength, $ellipse_char = '&hellip;') {
        if (strlen($s) > $maxLength) {
            return substr($s, 0, $maxLength - 1) . $ellipse_char;
        } else {
            return $s;
        }
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
     * Returns the last element of the given path
     * @param $path string|string[] Path to check (as array or string)
     * @return string Last path element
     */
    public static function getLastPathElement($path) {
        if (is_array($path)) {
            return $path[count($path) - 1];
        } else {
            $arr = explode(self::PATH_DELIMITER, $path);
            return $arr[count($arr) - 1];
        }
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
     * @param $check_path string Path Pattern to check against. Wildcard * matches with an alpha-numeric element.
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
                array_push($expr_els, "([^\\" . self::PATH_DELIMITER . "]*)");
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

    /**
     * Redirects to an app-internal link
     * @param $link string
     */
    public static function internalRedirect($link) {
        SessionNotification::preventNotificationClear();
        AppUtils::clearRenderedContent();
        header("Location: " . self::getLink($link));
    }
}

/**
 * Class RequestUtils
 */
class RequestUtils {
    const REQ_GET = "GET";
    const REQ_POST = "POST";
    const REQ_PUT = "PUT";
    const REQ_DELETE = "DELETE";

    public static function getRemoteIP() { return $_SERVER['REMOTE_ADDR']; }
    public static function getRequestTime() { return $_SERVER['REQUEST_TIME']; }
    public static function getRequestMethod() { return $_SERVER['REQUEST_METHOD']; }
    public static function getUserAgentString() { return $_SERVER['HTTP_USER_AGENT']; }
    public static function getUserAcceptLang() { return $_SERVER['HTTP_ACCEPT_LANGUAGE']; }
}
