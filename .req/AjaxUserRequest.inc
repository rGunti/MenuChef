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
            switch ($PARAM_action) {
                case 'lockUser':
                    $PARAM_user_id = AppUtils::getKeyDefault($vars, 'id', null);
                    $this->updateBlockedStatus($PARAM_user_id, 1);
                    break;
                case 'unlockUser':
                    $PARAM_user_id = AppUtils::getKeyDefault($vars, 'id', null);
                    $this->updateBlockedStatus($PARAM_user_id, 0);
                    break;
                case 'resetUser':
                    $PARAM_user_id = AppUtils::getKeyDefault($vars, 'id', null);
                    $this->resetUserPassword($PARAM_user_id);
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
