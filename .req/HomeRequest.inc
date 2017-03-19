<?php

class HomeRequest extends BaseRequest {
    public function getFormPath() { return "home.inc"; }
    public function getPageTitle() { return t('home'); }

    public function process($path, $get = [], $post = []) { }
}