<?php
class MealRequest extends BaseMultiRequest {
    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public function getFormPath() { return "meal.inc"; }
    public function getPageTitle() { return t('meal_pl'); }

    public function get($vars = []) {
        // Check Permission
        Session::enforceLoggedIn();
    }
}
