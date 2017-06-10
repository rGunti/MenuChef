<?php
class MealEditorRequest extends BaseMultiRequest {
    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public function getFormPath() { return "meal_editor.inc"; }
    public function getPageTitle() {
        $meal = $this->getEditingMeal();
        if (empty($meal)) {
            return t('meal_editor');
        } else {
            return t('meal_editor_titled', htmlspecialchars($meal->name));
        }
    }

    /**
     * @return MMeal
     */
    public function getEditingMeal() { return $this->getStorageValue('_meal'); }

    /**
     * @param $meal MMeal
     */
    public function setEditingMeal($meal) { $this->setStorageValue('_meal', $meal); }

    /**
     * @return MMeasuringUnit[]
     */
    public function getMeasuringUnits() { return $this->getStorageValue('_units'); }

    /**
     * @param $units MMeasuringUnit[]
     */
    protected function setMeasuringUnits($units) { $this->setStorageValue('_units', $units); }

    /**
     * @return string
     */
    public function getMarkdownMessage() { return $this->getStorageValue('_parsedNote'); }

    /**
     * @param $note string
     */
    protected function setMarkdownMessage($note) { $this->setStorageValue('_parsedNote', $note); }

    public function get($vars = []) {
        // Check Permission
        Session::enforceLoggedIn();

        // Redirect to Meal List, if path is invalid
        if (!PathUtils::currentPathMatches("/Meal/*/Editor")) {
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

        $this->setEditingMeal($meal);

        // Get Measuring Units
        $unit = new MMeasuringUnit();
        $units_map = $unit->getUnitMap();
        $this->setMeasuringUnits($units_map);
    }
}
