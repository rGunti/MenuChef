<?php
class AjaxMealRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        // Check Permission
        $this->checkPermissions(self::PERM_LEVEL_LOGGED_IN);

        // Get Parameters
        $params = $this->prepareDataTableArguments($vars);
        $order = $params->getSqlOrderColumns();

        // Get Conditions
        $conditions = [];
        if ($params->hasSearchTerm()) {
            $searchText = $params->getSearchTerm();
            $conditions = [
                TableWhereObject::getLike('NAME', $searchText)
            ];
        }

        // Get Data
        $meals = DatabaseTools::getWhereAdv(
            MMeal::TABLE_NAME,
            new MMeal(),
            $conditions,
            $order,
            $params->start,
            $params->length
        );

        // Send Data
        $this->sendObjectResponse($meals);
    }

    public function post($vars = []) {
        $this->checkPermissions(self::PERM_LEVEL_LOGGED_IN);
        $PARAM_action = AppUtils::getKeyDefault($vars, 'action', '');

        if (empty($PARAM_action)) {
            $this->sendErrorResponse(t('ajax_response_no_action'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            $PARAM_meal_id = AppUtils::getKeyDefault($vars, 'id', null);
            switch ($PARAM_action) {
                case 'changeName':
                    $PARAM_meal_name = AppUtils::getKeyDefault($vars, 'name', null);
                    $this->updateMealName($PARAM_meal_id, $PARAM_meal_name);
                    break;
                default:
                    $this->sendErrorResponse(t('ajax_response_unknown_action', [$PARAM_action]), self::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        }
    }

    private function checkMealID($meal_id) {
        if (empty($meal_id)) {
            $this->sendErrorResponse(t('ajax_response_meal_no_id'), self::HTTP_CODE_BAD_REQUEST);
        }
    }

    private function updateMealName($meal_id, $new_name) {
        $this->checkMealID($meal_id);

        if (empty($new_name)) {
            $this->sendErrorResponse(t('ajax_response_meal_name_empty'), self::HTTP_CODE_BAD_REQUEST);
        }

        $meal = new MMeal();
        $meal = $meal->getByKey($meal_id);
        if (empty($meal)) {
            $this->sendErrorResponse(t('ajax_response_meal_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else if ($meal->name == $new_name) {
            $this->sendErrorResponse(t('ajax_response_meal_name_equal'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            $res = DatabaseTools::update(
                MMeal::TABLE_NAME,
                MMeal::KEY_NAME,
                $meal->id,
                [ 'name' => $new_name ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }
}
