<?php
class UserManagerRequest extends BaseMultiRequest {
    public function getFormPath() { return "manage_user.inc"; }
    public function getPageTitle() { return t('admin_tools_users'); }

    public function get($vars = []) {
        $users = DatabaseTools::getAll(MUser::TABLE_NAME, new MUser());
        $this->setStorageValue('users', $users);
    }
}