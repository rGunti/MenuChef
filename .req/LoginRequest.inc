<?php
class LoginRequest extends BaseMultiRequest {
    public function getPageTitle() { return t('login'); }
    public function getFormPath() { return "login.inc"; }

    public function get($vars = []) {
        if (PathUtils::currentPathMatches("/Logout")) {
            Session::logout();
            PathUtils::internalRedirect("/");
        }
    }
    public function post($vars = []) {
        $users = DatabaseTools::getWhereSimple(MUser::TABLE_NAME, new MUser(), [
            'USERNAME' => $vars['loginUsername'],
            'PASSHASH' => DatabaseTools::hashNSaltPassword($vars['loginPassword'])
        ]);
        Logger::debug("Found " . count($users) . " users with given creds");
        if (count($users) != 1) {
            // Write Error Message
        } else {
            Session::login($users[0]);
            PathUtils::internalRedirect("/");
        }
    }
}