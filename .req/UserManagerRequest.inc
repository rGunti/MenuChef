<?php
class UserManagerRequest extends BaseRequest {
    public function getFormPath() { return "manage_user.inc"; }
    public function getPageTitle() { return t('admin_tools_users'); }

    public function process($path, $get = [], $post = []) { Session::enforceAdmin(); }
}