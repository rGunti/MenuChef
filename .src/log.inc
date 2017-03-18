<?php
require_once __DIR__ . '/../.cfg/config.inc';
require_once __DIR__ . '/utils.inc';

class Logger {
    /** Log Level "VERBOSE" (the lowest) */
    const LEVEL_VERBOSE = 0;
    /** Log Level "DEBUG" */
    const LEVEL_DEBUG = 1;
    /** Log Level "INFO" */
    const LEVEL_INFO = 2;
    /** Log Level "WARNING" */
    const LEVEL_WARN = 3;
    /** Log Level "ERROR" */
    const LEVEL_ERROR = 4;
    /** Log Level "FATAL" (the highest) */
    const LEVEL_FATAL = 5;

    /**
     * Returns the log file name
     * @return string
     */
    public static function getLogFilePath() {
        return str_replace("%date%", date("Y-m-d"), AppConfig::LOG_PATH);
    }

    /**
     * Converts a Log Level to string
     * @param $level int Log Level
     * @return string
     */
    public static function getLogLevelName($level) {
        switch ($level) {
            case self::LEVEL_VERBOSE:   return "VERBOSE";
            case self::LEVEL_DEBUG:     return "DEBUG";
            case self::LEVEL_INFO:      return "INFO";
            case self::LEVEL_WARN:      return "WARNING";
            case self::LEVEL_ERROR:     return "ERROR";
            case self::LEVEL_FATAL:     return "FATAL";
            default:                    return " - ";
        }
    }

    /**
     * Logs a new message with a given level
     * @param $level int Log Level
     * @param $message string Log Message
     */
    public static function log($level, $message) {
        if (AppConfig::LOG_ENABLED && $level >= AppConfig::LOG_MIN_LEVEL) {
            error_log(
                sprintf('%1$s | %2$-7s | %3$s',
                    date(AppConfig::LOG_DATE_PATTERN),
                    self::getLogLevelName($level),
                    $message
                ) . "\n", 3, self::getLogFilePath()
            );
        }
    }

    /**
     * Logs a new message with the Level VERBOSE
     * @param $message string Log Message
     */
    public static function verbose($message) { self::log(self::LEVEL_VERBOSE, $message); }

    /**
     * @param $message string
     */
    public static function debug($message) { self::log(self::LEVEL_DEBUG, $message); }

    /**
     * @param $message string
     */
    public static function info($message) { self::log(self::LEVEL_INFO, $message); }

    /**
     * @param $message string
     */
    public static function warn($message) { self::log(self::LEVEL_WARN, $message); }

    /**
     * @param $message string
     */
    public static function error($message) { self::log(self::LEVEL_ERROR, $message); }

    /**
     * @param $message string
     */
    public static function fatal($message) { self::log(self::LEVEL_FATAL, $message); }

    /**
     * Logs dynamic file require if enabled in Config
     * @param $path string
     */
    public static function logRequire($path) {
        if (AppConfig::LOG_DYN_REQUIRES) {
            self::verbose("Required '$path'");
        }
    }

    /**
     * Logs the current request
     */
    public static function logRequest() {
        if (!AppConfig::LOG_REQUESTS) { return; }

        $requestPath = PathUtils::getCurrentPath();
        $requestIP = RequestUtils::getRemoteIP();
        $requestUA = RequestUtils::getUserAgentString();

        self::verbose("REQUEST: '$requestUA' from $requestIP requested $requestPath");
    }
}
