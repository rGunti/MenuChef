<?php
class AjaxIngredientRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        if (PathUtils::currentPathMatches('/AJAX/Ingredients')) {
            $this->sendErrorResponse('Not yet implemented', self::HTTP_CODE_NOT_IMPLEMENTED);
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
