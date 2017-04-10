<?php
class IngredientRequest extends BaseMultiRequest {
    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public function getFormPath() { return "ingredients.inc"; }
    public function getPageTitle() { return t('ingredient_pl'); }

    public function get($vars = []) {
        // Check Permission
        Session::enforceAdmin();
    }
}
