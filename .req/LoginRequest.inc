<?php
class LoginRequest extends BaseMultiRequest {
    const KEY_FORM = 'form';

    public function getPageTitle() { return t('login'); }
    public function getFormPath() { return "login.inc"; }

    public function get($vars = []) {
        if (PathUtils::currentPathMatches("/Logout")) {
            Session::logout();
            // TODO: Write Notification Message: Logged Out
            PathUtils::internalRedirect("/");
        } else {
            $this->setStorageValue(self::KEY_FORM, new LoginForm());
        }
    }
    public function post($vars = []) {
        $form = LoginForm::getFromPost($vars);

        $users = DatabaseTools::getWhereSimple(MUser::TABLE_NAME, new MUser(), [
            'USERNAME' => $form->username,
            'PASSHASH' => DatabaseTools::hashNSaltPassword($form->password)
        ]);
        Logger::debug("Found " . count($users) . " users with given creds");
        if (count($users) != 1) {
            //$this->setStorageValue('')
            // TODO: Write Error Message: Creds invalid
        } else if ($users[0]->is_blocked) {
            // TODO: Write Error Message: User is blocked
        } else {
            // TODO: Write Notification Message: Logged In
            Session::login($users[0]);
            PathUtils::internalRedirect("/");
        }
        // Passwort wird vor dem Übertragen aus dem Form entfernt
        $form->password = null;
        $this->setStorageValue(self::KEY_FORM, $form);
    }
}

class LoginForm {
    public $username;
    public $password;

    public static function getFromPost($req) {
        $form = new LoginForm();
        $form->username = $req['loginUsername'];
        $form->password = $req['loginPassword'];
        return $form;
    }
}
