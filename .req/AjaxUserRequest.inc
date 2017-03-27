<?php
class AjaxUserRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        // Check Permission
        $this->checkPermissions(self::PERM_LEVEL_ADMIN);

        // Get Parameters
        $params = $this->prepareDataTableArguments($vars);
        $order = $params->getSqlOrderColumns();

        // Get Conditions
        $conditions = [];
        if ($params->hasSearchTerm()) {
            $searchText = $params->getSearchTerm();
            $conditions = [
                TableWhereObject::getLike('USERNAME', $searchText),
                TableWhereObject::getLike('MAIL', $searchText, TableWhereObject::PREFIX_OR)
            ];
        }

        // Get Data
        $users = DatabaseTools::getWhereAdv(
            MUser::VIEW_NAME,
            new MUser(),
            $conditions,
            $order,
            $params->start,
            $params->length
        );

        // Send Data
        $this->sendObjectResponse($users);
    }

    public function post($vars = []) {
        // Check Permissions
        $this->checkPermissions(self::PERM_LEVEL_ADMIN);

        // Get Parameters
        $PARAM_action = AppUtils::getKeyDefault($vars, 'action', '');

        if (empty($PARAM_action)) {
            $this->sendErrorResponse(t('ajax_response_no_action'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            $PARAM_user_id = AppUtils::getKeyDefault($vars, 'id', null);
            switch ($PARAM_action) {
                case 'lockUser':
                    $this->updateBlockedStatus($PARAM_user_id, 1);
                    break;
                case 'unlockUser':
                    $this->updateBlockedStatus($PARAM_user_id, 0);
                    break;
                case 'resetUser':
                    $this->resetUserPassword($PARAM_user_id);
                    break;
                case 'deleteUser':
                    $this->deleteUser($PARAM_user_id);
                    break;
                case 'createUser':
                    $this->createUser(
                        AppUtils::getKeyDefault($vars, 'username', ''),
                        AppUtils::getKeyDefault($vars, 'mail', '')
                    );
                    break;
                case 'changeUserLevel':
                    $this->changeUserLevel(
                        $PARAM_user_id,
                        AppUtils::getKeyDefault($vars, 'value', 0)
                    );
                    break;
                default:
                    $this->sendErrorResponse(t('ajax_response_unknown_action', [$PARAM_action]), self::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        }
    }

    private function checkUserID($user_id, $prevent_self = false, $prevent_self_message = null) {
        if (empty($user_id)) {
            $this->sendErrorResponse(t('ajax_response_user_no_id'), self::HTTP_CODE_BAD_REQUEST);
        } else if ($prevent_self && $user_id == Session::getUserInfo()->id) {
            $this->sendErrorResponse($prevent_self_message, self::HTTP_CODE_BAD_REQUEST);
        }
    }

    private function updateBlockedStatus($user_id, $to_disabled) {
        $this->checkUserID(
            $user_id,
            true,
            ($to_disabled ? t('ajax_response_user_disable_yourself') : t('ajax_response_user_enable_yourself'))
        );

        $users = DatabaseTools::getWhereSimple(
            MUser::TABLE_NAME,
            new MUser(),
            [ MUser::KEY_NAME => $user_id ]
        );
        if (count($users) != 1) {
            $this->sendErrorResponse(t('ajax_response_user_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else if ($users[0]->is_blocked == $to_disabled) {
            $this->sendErrorResponse(
                ($to_disabled ? t('ajax_response_user_disable_already') : t('ajax_response_user_enable_already')),
                self::HTTP_CODE_NOT_ACCEPTABLE);
        } else {
            /** @var MUser $user */
            $user = $users[0];
            $res = DatabaseTools::update(
                MUser::TABLE_NAME,
                MUser::KEY_NAME,
                $user->id,
                [ 'is_blocked' => $to_disabled ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }

    private function resetUserPassword($user_id) {
        $this->checkUserID($user_id, true, t('ajax_response_user_reset_yourself'));

        $users = DatabaseTools::getWhereSimple(
            MUser::TABLE_NAME,
            new MUser(),
            [ MUser::KEY_NAME => $user_id ]
        );
        if (count($users) != 1) {
            $this->sendErrorResponse(t('ajax_response_user_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            /** @var MUser $user */
            $user = $users[0];

            $new_password = self::generateRandomString();
            $new_pass_hash = DatabaseTools::hashNSaltPassword($new_password);

            $res = DatabaseTools::update(
                MUser::TABLE_NAME,
                MUser::KEY_NAME,
                $user->id,
                [ 'passhash' => $new_pass_hash ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse([
                    'HasError' => 0,
                    'UserName' => $user->username,
                    'NewPassword' => $new_password
                ], self::HTTP_CODE_OK);
            }
        }
    }

    private function deleteUser($user_id) {
        $this->checkUserID($user_id, true, t('ajax_response_user_delete_yourself'));

        if (in_array($user_id, MUser::PROTECTED_USER_IDS)) {
            $this->sendErrorResponse(t('ajax_response_user_delete_protected'), self::HTTP_CODE_BAD_REQUEST);
            return;
        }

        $users = DatabaseTools::getWhereSimple(
            MUser::TABLE_NAME,
            new MUser(),
            [ MUser::KEY_NAME => $user_id ]
        );
        if (count($users) != 1) {
            $this->sendErrorResponse(t('ajax_response_user_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            /** @var MUser $user */
            $user = $users[0];

            $res = DatabaseTools::delete(MUser::TABLE_NAME, MUser::KEY_NAME, $user->id);
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }

    /** Source: http://emailregex.com/ */
    const MAIL_REGEX = '/^(?!(?:(?:\x22?\x5C[\x00-\x7E]\x22?)|(?:\x22?[^\x5C\x22]\x22?)){255,})(?!(?:(?:\x22?\x5C[\x00-\x7E]\x22?)|(?:\x22?[^\x5C\x22]\x22?)){65,}@)(?:(?:[\x21\x23-\x27\x2A\x2B\x2D\x2F-\x39\x3D\x3F\x5E-\x7E]+)|(?:\x22(?:[\x01-\x08\x0B\x0C\x0E-\x1F\x21\x23-\x5B\x5D-\x7F]|(?:\x5C[\x00-\x7F]))*\x22))(?:\.(?:(?:[\x21\x23-\x27\x2A\x2B\x2D\x2F-\x39\x3D\x3F\x5E-\x7E]+)|(?:\x22(?:[\x01-\x08\x0B\x0C\x0E-\x1F\x21\x23-\x5B\x5D-\x7F]|(?:\x5C[\x00-\x7F]))*\x22)))*@(?:(?:(?!.*[^.]{64,})(?:(?:(?:xn--)?[a-z0-9]+(?:-[a-z0-9]+)*\.){1,126}){1,}(?:(?:[a-z][a-z0-9]*)|(?:(?:xn--)[a-z0-9]+))(?:-[a-z0-9]+)*)|(?:\[(?:(?:IPv6:(?:(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){7})|(?:(?!(?:.*[a-f0-9][:\]]){7,})(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,5})?::(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,5})?)))|(?:(?:IPv6:(?:(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){5}:)|(?:(?!(?:.*[a-f0-9]:){5,})(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,3})?::(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,3}:)?)))?(?:(?:25[0-5])|(?:2[0-4][0-9])|(?:1[0-9]{2})|(?:[1-9]?[0-9]))(?:\.(?:(?:25[0-5])|(?:2[0-4][0-9])|(?:1[0-9]{2})|(?:[1-9]?[0-9]))){3}))\]))$/iD';

    private function createUser($username, $mail) {
        $user = new MUser();
        $user->username = strtolower($username);
        $user->mail = $mail;
        $new_password = self::generateRandomString();
        $user->PassHash = DatabaseTools::hashNSaltPassword($new_password);

        if (empty($user->username) || strlen($user->username) < 3 || !preg_match('/^[a-z0-9]+$/', $user->username)) {
            $this->sendErrorResponse(t('ajax_response_user_create_name_info'), self::HTTP_CODE_BAD_REQUEST);
        } else if (!empty($user->mail) && !preg_match(self::MAIL_REGEX, $user->mail)) {
            $this->sendErrorResponse(t('ajax_response_user_create_mail_invalid'), self::HTTP_CODE_BAD_REQUEST);
        }

        $existingUsers = DatabaseTools::getWhereSimple(
            MUser::TABLE_NAME, new MUser(),
            [ MUser::KEY_NAME => $user->username ]
        );
        if (count($existingUsers) > 0) {
            $this->sendErrorResponse(
                t('ajax_response_user_create_exists', [$user->username]),
                self::HTTP_CODE_BAD_REQUEST
            );
        } else {
            $res = DatabaseTools::insert(MUser::TABLE_NAME, [
                'username' => $user->username,
                'passhash' => $user->PassHash,
                'mail' => $user->mail,
                'is_admin' => 0,
                'is_batch' => 0,
                'is_blocked' => 0
            ]);
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse([
                    'HasError' => 0,
                    'UserName' => $user->username,
                    'NewPassword' => $new_password
                ], self::HTTP_CODE_CREATED);
            }
        }
    }

    private function changeUserLevel($user_id, $is_admin) {
        $this->checkUserID($user_id, true, t('ajax_response_user_privilege_yourself'));

        if (in_array($user_id, MUser::PROTECTED_USER_IDS)) {
            $this->sendErrorResponse(t('ajax_response_user_privilege_protected'), self::HTTP_CODE_BAD_REQUEST);
            return;
        }

        $users = DatabaseTools::getWhereSimple(
            MUser::TABLE_NAME,
            new MUser(),
            [ MUser::KEY_NAME => $user_id ]
        );
        if (count($users) != 1) {
            $this->sendErrorResponse(t('ajax_response_user_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else if ($users[0]->is_batch == true) {
            $this->sendErrorResponse(t('ajax_response_user_privilege_batch'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            /** @var MUser $user */
            $user = $users[0];
            $res = DatabaseTools::update(
                MUser::TABLE_NAME,
                MUser::KEY_NAME,
                $user->id,
                [ 'is_admin' => $is_admin ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }

    /**
     * Source: http://stackoverflow.com/questions/4356289/php-random-string-generator
     * @param int $length Length of Random String
     * @return string Random String
     */
    public static function generateRandomString($length = 10) {
        $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,;:-_/|\*+"%&=?!()[]{}@€<>$';
        $charactersLength = strlen($characters);
        $randomString = '';
        for ($i = 0; $i < $length; $i++) {
            $randomString .= $characters[rand(0, $charactersLength - 1)];
        }
        return $randomString;
    }
}
