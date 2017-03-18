<?php
require_once __DIR__ . '/log.inc';
Logger::logRequest();

function rgunti_require_all($path, $pattern = '*.inc') {
    foreach (glob($path . '/' . $pattern, GLOB_MARK) as $file) {
        Logger::logRequire($file);
        require_once $file;
    }
}

rgunti_require_all(__DIR__);
require_once __DIR__ . '/models/.requireAll.inc';
require_once __DIR__ . '/../.cfg/config.inc';
require_once __DIR__ . '/../.cfg/navconfig.inc';
