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
}
