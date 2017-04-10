<?php
class AjaxIngredientRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        if (PathUtils::currentPathMatches('/AJAX/Ingredients')) {
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
                MIngredient::TABLE_NAME,
                new MIngredient(),
                $conditions,
                $order,
                $params->start,
                $params->length
            );

            // Send Data
            $this->sendObjectResponse($meals);
        } else if (PathUtils::currentPathMatches('/AJAX/Ingredients/*')) {
            $req_type = PathUtils::getLastPathElement(PathUtils::getCurrentPath());
            switch ($req_type) {
                case 'AutoComplete':
                    $term = AppUtils::getKeyDefault($vars, 'term', '');
                    $ings = DatabaseTools::getWhereAdv(
                        MIngredient::TABLE_NAME,
                        new MIngredient(),
                        [ TableWhereObject::getLike('name', $term) ],
                        [ 'name ASC' ],
                        0, 50
                    );
                    /** @var MIngredient[] $ingredients */
                    $ingredients = $ings->data;
                    $response = [];
                    foreach ($ingredients as $ingredient) {
                        array_push($response, [
                            'id' => $ingredient->id,
                            'value' => $ingredient->name,
                            'label' => $ingredient->name,
                            'object' => $ingredient
                        ]);
                    }
                    $this->sendObjectResponse($response);
                    break;
                default:
                    $this->sendErrorResponse("Unknown Ingredient Type \"$req_type\"", self::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        } else {
            $this->sendErrorResponse(null, self::HTTP_CODE_BAD_REQUEST);
        }
    }
}
