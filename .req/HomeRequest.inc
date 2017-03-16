<?php

class HomeRequest extends BaseRequest {
    public function getFormPath() { return "home.inc"; }
    public function getPageTitle() { return "Home"; }

    public function process($path, $get = [], $post = []) { }
}