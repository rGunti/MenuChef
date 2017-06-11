<?php
class MealPrintRequest extends BaseMultiRequest {

    /**
     * @return MMeal
     */
    public function getPrintableMeal() { return $this->getStorageValue('_meal'); }

    /**
     * @param $meal MMeal
     */
    public function setPrintableMeal($meal) { $this->setStorageValue('_meal', $meal); }

    /**
     * @return string
     */
    public function getMarkdownMessage() { return $this->getStorageValue('_parsedNote'); }

    /**
     * @param $note string
     */
    protected function setMarkdownMessage($note) { $this->setStorageValue('_parsedNote', $note); }

    /**
     * @return MVMealIngredient[]
     */
    public function getMealIngredients() { return $this->getStorageValue('_ingredients'); }

    /**
     * @param $ingredients MVMealIngredient[]
     */
    protected function setMealIngredients($ingredients) { $this->setStorageValue('_ingredients', $ingredients); }

    /**
     * @return MVLinkedMeal[]
     */
    public function getLinkedMeals() { return $this->getStorageValue('_linked_meals'); }

    /**
     * @param $linked_meals MVLinkedMeal[]
     */
    protected function setLinkedMeals($linked_meals) { $this->setStorageValue('_linked_meals', $linked_meals); }

    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public function getFormPath() { return "meal_print.inc"; }
    public function getPageTitle() {
        $meal = $this->getPrintableMeal();
        if (empty($meal)) {
            return t('meal');
        } else {
            return htmlspecialchars($meal->name);
        }
    }

    public function get($vars = []) {
        // Check Permission
        Session::enforceLoggedIn();

        // Redirect to Meal List, if path is invalid
        if (!PathUtils::currentPathMatches("/Meal/*/Print")) {
            PathUtils::internalRedirect("/Meal");
            return;
        }

        // Get Meal ID
        $current_path = PathUtils::getCurrentPathAsArray();
        $meal_id = array_slice($current_path, -2, 1)[0];
        if (empty($meal_id)) {
            Session::addNotification(new SessionNotification(
                'error_meal_id_invalid', [],
                null, null,
                SessionNotification::LEVEL_ERROR
            ));
            http_response_code(BaseAjaxRequest::HTTP_CODE_BAD_REQUEST);
            PathUtils::internalRedirect("/Meal");
            return;
        }

        // Get Meal
        $meal = new MMeal();
        $meal = $meal->getByKey($meal_id);
        if (empty($meal)) {
            Session::addNotification(new SessionNotification(
                'error_meal_not_found_title', [$meal_id],
                'error_meal_not_found_message', [],
                SessionNotification::LEVEL_ERROR
            ));
            http_response_code(BaseAjaxRequest::HTTP_CODE_NOT_FOUND);
            PathUtils::internalRedirect("/Meal");
            return;
        } else {
            $parse = new Parsedown();
            $parsedMarkdown = $parse->text($meal->notes);
            if (empty($parsedMarkdown)) {
                $parsedMarkdown = $parse->text(t('meal_notes_empty_markdown'));
            }
            $this->setMarkdownMessage($parsedMarkdown);
        }

        // Get Ingredients
        $ingredients = DatabaseTools::getWhereSimple(
            MVMealIngredient::TABLE_NAME,
            new MVMealIngredient(),
            [ 'MEAL_ID' => $meal->id ]
        );

        // Get Linked Meals
        $linked_meals = DatabaseTools::getWhereSimple(
            MVLinkedMeal::TABLE_NAME,
            new MVLinkedMeal(),
            [ 'MEAL_ID' => $meal->id ]
        );

        $this->setPrintableMeal($meal);
        $this->setMealIngredients($ingredients);
        $this->setLinkedMeals($linked_meals);
    }
}
