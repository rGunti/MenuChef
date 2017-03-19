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

        $update_data = [];

        $user = Session::getUserInfo();
        $form = UserSettingsForm::getFromPost($vars);
        $submit = true;
        if (!empty($form->newPassword1)) {
            if ($form->newPassword1 != $form->newPassword2) {
                $submit = false;
                // TODO: Write Error
            } else {
                $update_data['passhash'] = DatabaseTools::hashNSaltPassword($form->newPassword1);
            }
        }
        $update_data['mail'] = $form->mail;

        if ($submit) {
            DatabaseTools::update(MUser::TABLE_NAME, MUser::KEY_NAME, $user->id, $update_data);
            $user = DatabaseTools::getWhereSimple(MUser::TABLE_NAME, new MUser(), [ MUser::KEY_NAME => $user->id ])[0];
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
