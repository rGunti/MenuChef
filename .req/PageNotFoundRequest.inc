<?php

class PageNotFoundRequest extends BaseRequest {
    public function getFormPath() { return "404.inc"; }
    public function getPageTitle() { return "Error 404: Page Not Found"; }

    public function process($path, $get = [], $post = []) { }
}
