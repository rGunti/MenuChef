<?php

class DebugViewRequest extends BaseRequest {
    public function getFormPath() { return "debug.inc"; }
    public function getPageTitle() { return "Debug Info"; }

    public function process($path, $get = [], $post = []) {
        $this->setStorageValue('_server', $_SERVER);
        $this->setStorageValue('_session', $_SESSION);
        $this->setStorageValue('_get', $get);
        $this->setStorageValue('_post', $post);
        $this->setStorageValue('_cookie', $_COOKIE);
        $this->setStorageValue('_files', $_COOKIE);
    }
}