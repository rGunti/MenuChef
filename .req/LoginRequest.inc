<?php
class LoginRequest extends BaseMultiRequest {
    const KEY_FORM = 'form';

    public function getPageTitle() { return t('login'); }
    public function getFormPath() { return "login.inc"; }

    public function get($vars = []) {
        if (PathUtils::currentPathMatches("/Logout")) {
            Session::logout();
            Session::addNotification(new SessionNotification('message_logged_out', null, null, null, SessionNotification::LEVEL_SUCCESS));
            PathUtils::internalRedirect("/");
        } else {
            $form = new LoginForm();
            if (!empty($vars['to'])) {
                $form->redirectUrl = urldecode($vars['to']);
            }
            $this->setStorageValue(self::KEY_FORM, $form);
        }
    }
    public function post($vars = []) {
        Session::clearAllNotifications();
        $form = LoginForm::getFromPost($vars);

        $users = DatabaseTools::getWhereSimple(MUser::TABLE_NAME, new MUser(), [
            'USERNAME' => $form->username,
            'PASSHASH' => DatabaseTools::hashNSaltPassword($form->password)
        ]);
        Logger::debug("Found " . count($users) . " users with given creds");
        if (count($users) != 1) {
            Session::addNotification(new SessionNotification(
                'error_login_invalid', [],
                'error_login_invalid_content', [],
                SessionNotification::LEVEL_ERROR
            ));
        } else if ($users[0]->is_blocked) {
            Session::addNotification(new SessionNotification(
                'error_login_blocked', [],
                'error_login_blocked_content', [],
                SessionNotification::LEVEL_ERROR
            ));
        } else {
            Session::login($users[0]);
            Session::addNotification(
                new SessionNotification(
                    'message_logged_in', [$users[0]->username],
                    'message_logged_in_content', null,
                    SessionNotification::LEVEL_SUCCESS)
            );
            if (empty($form->redirectUrl)) {
                PathUtils::internalRedirect("/");
            } else {
                PathUtils::internalRedirect($form->redirectUrl);
            }
        }
        // Passwort wird vor dem Übertragen aus dem Form entfernt
        $form->password = null;
        $this->setStorageValue(self::KEY_FORM, $form);
    }
}

class LoginForm {
    public $username;
    public $password;
    public $redirectUrl;

    public static function getFromPost($req) {
        $form = new LoginForm();
        $form->username = $req['loginUsername'];
        $form->password = $req['loginPassword'];
        $form->redirectUrl = $req['loginRedirectUrl'];
        return $form;
    }
}
