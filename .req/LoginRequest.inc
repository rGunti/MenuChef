<?php
class LoginRequest extends BaseMultiRequest {
    public function getPageTitle() { return "Login"; }
    public function getFormPath() { return "login.inc"; }

    public function get($vars = []) { }
    public function post($vars = []) {
        PathUtils::internalRedirect("/");
    }
}