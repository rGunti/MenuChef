<?php
class AjaxMealRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        if (PathUtils::currentPathMatches('/AJAX/Meal')) {
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
                MVMeal::TABLE_NAME,
                new MVMeal(),
                $conditions,
                $order,
                $params->start,
                $params->length
            );

            // Send Data
            $this->sendObjectResponse($meals);
        } else if (PathUtils::currentPathMatches('/AJAX/Meal/AutoComplete')) {
            $term = AppUtils::getKeyDefault($vars, 'term', '');
            $currentMeal = AppUtils::getKeyDefault($vars, 'currentMeal', '');
            $meals_request = DatabaseTools::getWhereAdv(
                MMeal::TABLE_NAME,
                new MMeal(),
                [
                    TableWhereObject::getLike('name', $term),
                    new TableWhereObject(
                        'id',
                        '!=',
                        $currentMeal,
                        TableWhereObject::PREFIX_AND
                    )
                ],
                [ 'name ASC' ],
                0, 50
            );

            /** @var MMeal[] $meals */
            $meals = $meals_request->data;
            $response = [];
            foreach ($meals as $meal) {
                array_push($response, [
                    'id' => $meal->id,
                    'value' => $meal->name,
                    'label' => $meal->name,
                    'object' => $meal
                ]);
            }
            $this->sendObjectResponse($response);
        } else {
            $this->sendErrorResponse(null, self::HTTP_CODE_BAD_REQUEST);
        }
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
                    $PARAM_meal_ignore_in_plan = AppUtils::getKeyDefault($vars, 'ignoreInPlan', false);
                    $this->updateMealName($PARAM_meal_id, $PARAM_meal_name, $PARAM_meal_ignore_in_plan);
                    break;
                case 'createMeal':
                    $PARAM_meal_name = AppUtils::getKeyDefault($vars, 'name', null);
                    $this->createNewMeal($PARAM_meal_name);
                    break;
                case 'editMealNote':
                    $PARAM_meal_id = AppUtils::getKeyDefault($vars, 'id', null);
                    $PARAM_meal_note = AppUtils::getKeyDefault($vars, 'note', null);
                    $this->editMealNote($PARAM_meal_id, $PARAM_meal_note);
                    break;
                case 'deleteMeal':
                    $this->deleteMeal($PARAM_meal_id);
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

    private function updateMealName($meal_id, $new_name, $ignore_in_plan) {
        $this->checkMealID($meal_id);

        if (empty($new_name)) {
            $this->sendErrorResponse(t('ajax_response_meal_name_empty'), self::HTTP_CODE_BAD_REQUEST);
        }

        $meal = new MMeal();
        $meal = $meal->getByKey($meal_id);
        if (empty($meal)) {
            $this->sendErrorResponse(t('ajax_response_meal_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            $res = DatabaseTools::update(
                MMeal::TABLE_NAME,
                MMeal::KEY_NAME,
                $meal->id,
                [
                    'name' => $new_name,
                    'ignore_in_plan' => ($ignore_in_plan === 'true' ? 1 : 0)
                ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }

    private function editMealNote($meal_id, $new_note) {
        $this->checkMealID($meal_id);

        $meal = new MMeal();
        $meal->getByKey($meal_id);
        if (empty($meal)) {
            $this->sendErrorResponse(t('ajax_response_meal_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            $res = DatabaseTools::update(
                MMeal::TABLE_NAME,
                MMeal::KEY_NAME,
                $meal_id,
                [ 'notes' => $new_note ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }

    private function createNewMeal($meal_name) {
        if (empty($meal_name)) {
            $this->sendErrorResponse(t('ajax_response_meal_name_empty'), self::HTTP_CODE_BAD_REQUEST);
        }

        $meal = new MMeal();
        $meal->name = $meal_name;
        $res = DatabaseTools::insert(
            $meal->getTableName(),
            [ 'name' => $meal->name ],
            true
        );
        if (empty($res)) {
            $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
        } else {
            $this->sendObjectResponse([
                'mealID' => $res
            ], self::HTTP_CODE_CREATED);
        }
    }

    private function deleteMeal($meal_id) {
        $this->checkMealID($meal_id);

        $meal = new MMeal();
        $meal = $meal->getByKey($meal_id);
        if (empty($meal)) {
            $this->sendErrorResponse(t('ajax_response_meal_id_not_found'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            // Get all Ingredients
            $mingrs = DatabaseTools::getWhereSimple(
                MMealIngredient::TABLE_NAME,
                new MMealIngredient(),
                [ 'meal_id' => $meal_id ]
            );
            array_push($mingrs, $meal);
            if (count($mingrs) > 0) {
                $res = DatabaseTools::massDelete($mingrs);
                if ($res < 1) {
                    $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
                } else {
                    $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
                }
            }
        }
    }
}
