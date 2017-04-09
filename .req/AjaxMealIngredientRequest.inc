<?php
class AjaxMealIngredientRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        // Check Permission
        $this->checkPermissions(self::PERM_LEVEL_LOGGED_IN);

        $meal_id = array_slice(PathUtils::getCurrentPathAsArray(), -1, 1)[0];
        if (empty($meal_id)) {
            $this->sendObjectResponse([]);
        }

        // Get Parameters
        $params = $this->prepareDataTableArguments($vars);
        $order = $params->getSqlOrderColumns();

        // Get Conditions
        $conditions = [];
        if ($params->hasSearchTerm()) {
            $searchText = $params->getSearchTerm();
            $conditions = [
                TableWhereObject::getLike('INGREDIENT_NAME', $searchText, null, 'AND')
            ];
        }
        array_push($conditions, TableWhereObject::getEq('MEAL_ID', $meal_id));

        // Get Data
        $ingrs = DatabaseTools::getWhereAdv(
            MVMealIngredient::TABLE_NAME,
            new MVMealIngredient(),
            $conditions,
            $order,
            $params->start,
            $params->length
        );

        // Send Data
        $this->sendObjectResponse($ingrs);
    }

    public function post($vars = []) {
        $this->checkPermissions(self::PERM_LEVEL_LOGGED_IN);
        $PARAM_action = AppUtils::getKeyDefault($vars, 'action', '');

        $meal_id = array_slice(PathUtils::getCurrentPathAsArray(), -1, 1)[0];
        if (empty($meal_id)) {
            $this->sendErrorResponse(t('ajax_response_meal_no_id'), self::HTTP_CODE_BAD_REQUEST);
        }

        if (empty($PARAM_action)) {
            $this->sendErrorResponse(t('ajax_response_no_action'), self::HTTP_CODE_BAD_REQUEST);
        } else {
            switch ($PARAM_action) {
                case 'addIngredient':
                    $PARAM_ingr = AppUtils::getKeyDefault($vars, 'ingredient', null);
                    if (empty($PARAM_ingr)) {
                        $this->sendErrorResponse(t('ajax_response_no_data'), self::HTTP_CODE_BAD_REQUEST);
                    }

                    $ingr = new MIngredient();
                    $ingr->id = AppUtils::getKeyDefault($PARAM_ingr, 'id', 0);
                    $ingr->name = AppUtils::getKeyDefault($PARAM_ingr, 'name', null);

                    $mingr = new MMealIngredient();
                    $mingr->meal_id = $meal_id;
                    $mingr->amount = AppUtils::getKeyDefault($PARAM_ingr, 'amount', 1);
                    $mingr->amount_unit = AppUtils::getKeyDefault($PARAM_ingr, 'unit', null);

                    $this->addIngredientToMeal($mingr, $ingr);
                    break;
                default:
                    $this->sendErrorResponse(t('ajax_response_unknown_action', [$PARAM_action]), self::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        }
    }

    /**
     * @param $meal_ingredient MMealIngredient
     * @param $ingredient MIngredient
     */
    private function addIngredientToMeal($meal_ingredient, $ingredient) {
        // Check if ID is given
        if (!empty($ingredient->id)) {
            $db_ingredient = $ingredient->getByKey($ingredient->id);
            if (empty($db_ingredient)) {
                $this->sendErrorResponse(t('ajax_response_meal_editor_ingredient_not_found', [$ingredient->id]), self::HTTP_CODE_BAD_REQUEST);
            } else {
                $meal_ingredient->ingredient_id = $db_ingredient->id;
            }
        } else {
            // Create Ingredient first (with validation)
            if (empty($ingredient->name)) {
                $this->sendErrorResponse(t('ajax_response_meal_editor_ingredient_name_empty'), self::HTTP_CODE_BAD_REQUEST);
            } else {
                $meal_ingredient->ingredient_id = DatabaseTools::insert(
                    MIngredient::TABLE_NAME,
                    [ 'name' => $ingredient->name ],
                    true
                );
            }
        }

        // Validate
        if (empty($meal_ingredient->ingredient_id)) {
            $this->sendErrorResponse(t('ajax_response_meal_editor_ingredient_no_ingredient'), self::HTTP_CODE_BAD_REQUEST);
        }
        if (empty($meal_ingredient->meal_id)) {
            $this->sendErrorResponse(t('ajax_response_meal_editor_ingredient_no_meal'), self::HTTP_CODE_BAD_REQUEST);
        }
        if (empty($meal_ingredient->amount)) {
            $this->sendErrorResponse(t('ajax_response_meal_editor_ingredient_no_amount'), self::HTTP_CODE_BAD_REQUEST);
        }
        if (empty($meal_ingredient->amount_unit)) {
            $this->sendErrorResponse(t('ajax_response_meal_editor_ingredient_no_unit'), self::HTTP_CODE_BAD_REQUEST);
        }

        // Add Meal Ingredient
        $res = DatabaseTools::insert(
            MMealIngredient::TABLE_NAME,
            [
                'meal_id' => $meal_ingredient->meal_id,
                'ingredient_id' => $meal_ingredient->ingredient_id,
                'amount_unit' => $meal_ingredient->amount_unit,
                'amount' => $meal_ingredient->amount
            ]
        );
        if ($res != 1) {
            $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
        } else {
            $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
        }
    }
}
