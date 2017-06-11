<?php
class AjaxLinkedMealRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        // Check Permission
        $this->checkPermissions(self::PERM_LEVEL_LOGGED_IN);

        $meal_id = array_slice(PathUtils::getCurrentPathAsArray(), -2, 1)[0];
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
                TableWhereObject::getLike('LINKED_MEAL_NAME', $searchText)
            ];
        }

        if (PathUtils::currentPathMatches('/AJAX/Meal/*/LinkedMeals')) {
            array_push($conditions, TableWhereObject::getEq('MEAL_ID', $meal_id));
        } else if (PathUtils::currentPathMatches('/AJAX/Meal/*/ConnectedMeals')) {
            array_push($conditions, TableWhereObject::getEq('LINKED_MEAL_ID', $meal_id));
        }

        // Get Data
        $meals = DatabaseTools::getWhereAdv(
            MVLinkedMeal::TABLE_NAME,
            new MVLinkedMeal(),
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
            switch ($PARAM_action) {
                case 'deleteLinkedMeal':
                    $PARAM_id = AppUtils::getKeyDefault($vars, 'id', null);
                    if (empty($PARAM_id)) {
                        $this->sendErrorResponse(t('ajax_response_no_data'), self::HTTP_CODE_BAD_REQUEST);
                    } else {
                        $this->deleteLinkedMeal($PARAM_id);
                    }
                    break;
                case 'addLinkedMeal':
                    $PARAM_source_meal = AppUtils::getKeyDefault($vars, 'sourceMeal', null);
                    $PARAM_selected_meal = AppUtils::getKeyDefault($vars, 'linkMeal', null);

                    if (empty($PARAM_source_meal) || empty($PARAM_selected_meal)) {
                        $this->sendErrorResponse(
                            t('ajax_response_no_data'),
                            self::HTTP_CODE_BAD_REQUEST
                        );
                    } else {
                        $this->linkMeal($PARAM_source_meal, $PARAM_selected_meal);
                    }
                    break;
                default:
                    $this->sendErrorResponse(t('ajax_response_unknown_action', [$PARAM_action]), self::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        }
    }

    private function linkMeal($source_meal, $selected_meal) {
        $meals = DatabaseTools::getWhereAdv(
            MMeal::TABLE_NAME,
            new MMeal(),
            [
                TableWhereObject::getEq('ID', $source_meal),
                TableWhereObject::getEq('ID', $selected_meal, TableWhereObject::PREFIX_OR)
            ],
            [], 0, 10
        );

        if ($meals->recordsFiltered == 2) {
            $res = DatabaseTools::insert(
                MLinkedMeal::TABLE_NAME,
                [
                    'meal_id' => $source_meal,
                    'linked_meal_id' => $selected_meal
                ]
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        } else {
            $this->sendErrorResponse(t('ajax_response_meal_id_not_found', [ $source_meal ]), self::HTTP_CODE_BAD_REQUEST);
        }
    }

    private function deleteLinkedMeal($refId) {
        $linked_meal = DatabaseTools::getWhereSimple(
            MLinkedMeal::TABLE_NAME,
            new MLinkedMeal(),
            [ 'ref_id' => $refId ]
        );
        if (count($linked_meal) != 1) {
            $this->sendErrorResponse(t('ajax_response_meal_id_not_found', [$refId]), self::HTTP_CODE_BAD_REQUEST);
        } else {
            $res = DatabaseTools::delete(
                MLinkedMeal::TABLE_NAME,
                MLinkedMeal::KEY_NAME,
                $refId
            );
            if ($res != 1) {
                $this->sendErrorResponse(t('ajax_response_db_save_fail'), self::HTTP_CODE_INTERNAL_ERROR);
            } else {
                $this->sendObjectResponse(null, self::HTTP_CODE_NO_CONTENT);
            }
        }
    }
}
