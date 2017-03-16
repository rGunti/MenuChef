<?php

function rgunti_require_all($path, $pattern = '*.inc') {
    foreach (glob($path . '/' . $pattern, GLOB_MARK) as $file) {
        require_once $file;
    }
}

rgunti_require_all(__DIR__);
