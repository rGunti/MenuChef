<?php
class PhpInfoRequest extends BaseRequest {
    public function getFormPath() { return "phpinfo.inc"; }
    public function getPageTitle() { return "PHP Info"; }

    public function process($path, $get = [], $post = []) { }
}
