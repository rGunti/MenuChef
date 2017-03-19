<?php
class UserSettingsRequest extends BaseMultiRequest {
    const KEY_FORM = 'form';

    public function getFormPath() { return 'mysettings.inc'; }
    public function getPageTitle() { return t('user_settings_title'); }

    public function get($vars = []) {
        Session::enforceLoggedIn();

        $form = UserSettingsForm::getFromSession();
        $this->setStorageValue(self::KEY_FORM, $form);
    }
    public function post($vars = []) {
        Session::enforceLoggedIn();

        $user = Session::getUserInfo();
        $form = UserSettingsForm::getFromPost($vars);
        $submit = true;
        if (!empty($form->newPassword1)) {
            if ($form->newPassword1 != $form->newPassword2) {
                $submit = false;
                // TODO: Write Error
            }
        }
        $user->mail = $form->mail;

        if ($submit) {
            // TODO: Update DB
            Session::login($user, true);
            PathUtils::internalRedirect("/MySettings");
        } else {
            $this->setStorageValue(self::KEY_FORM, $form);
        }
    }
}

class UserSettingsForm {
    public $username;
    public $mail;
    public $newPassword1;
    public $newPassword2;

    /**
     * @param $req array
     * @return UserSettingsForm
     */
    public static function getFromPost($req) {
        $form = new UserSettingsForm();
        $form->username = Session::getUserInfo()->username;
        $form->mail = $req['userSettingsMail'];
        $form->newPassword1 = $req['userSettingsPassword1'];
        $form->newPassword2 = $req['userSettingsPassword2'];
        return $form;
    }

    /**
     * @return UserSettingsForm
     */
    public static function getFromSession() {
        $form = new UserSettingsForm();
        $user = Session::getUserInfo();
        $form->username = $user->username;
        $form->mail = $user->mail;
        return $form;
    }
}
