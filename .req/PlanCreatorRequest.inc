<?php
class PlanCreatorRequest extends BaseMultiRequest {
    /** @return int */
    public function getStepNumber() { return $this->getStorageValue('_step'); }
    /** @param $step int */
    protected function setStepNumber($step) { $this->setStorageValue('_step', $step); }

    /** @return bool[] */
    public function getWeekdays() { return $this->getStorageValue('_weekdays'); }
    /** @param $weekdays bool[] */
    protected function setWeekdays($weekdays) { $this->setStorageValue('_weekdays', $weekdays); }

    /** @return int */
    public function getWeekdaysCount() { return $this->getStorageValue('_weekdays_count'); }
    /** @param $weekdaysCount int */
    protected function setWeekdaysCount($weekdaysCount) { $this->setStorageValue('_weekdays_count', $weekdaysCount); }

    /** @return MMeal[] */
    public function getMeals() { return $this->getStorageValue('_meals'); }
    /** @param $meals MMeal[] */
    protected function setMeals($meals) { $this->setStorageValue('_meals', $meals); }

    /** @return MVLinkedMeal[][] */
    public function getLinkedMeals() { return $this->getStorageValue('_linked_meals'); }
    /** @param $meals MVLinkedMeal[][] */
    protected function setLinkedMeals($meals) { $this->setStorageValue('_linked_meals', $meals); }

    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public function getFormPath() { return "plan_creator.inc"; }
    public function getPageTitle() { return t('plan_creator'); }

    public function get($vars = []) {
        Session::enforceLoggedIn();

        if (PathUtils::currentPathMatches('/PlanCreator/Step/*')) {
            $step_no = PathUtils::getLastPathElement(PathUtils::getCurrentPath());
            $this->setStepNumber($step_no);
            switch ($step_no) {
                case 1:
                    $this->setWeekdays([ true, true, true, true, true, true, true ]);
                    break;
                default:
                    http_response_code(BaseAjaxRequest::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        } else {
            PathUtils::internalRedirect('/PlanCreator/Step/1');
        }
    }

    public function post($vars = []) {
        Session::enforceLoggedIn();

        if (PathUtils::currentPathMatches('/PlanCreator/Step/*')) {
            Logger::debug(json_encode($vars, JSON_PRETTY_PRINT));

            $step_no = PathUtils::getLastPathElement(PathUtils::getCurrentPath());
            $this->setStepNumber($step_no);
            switch ($step_no) {
                case 2:
                    $this->processStep2($vars);
                    break;
                case 3:
                    $submit = AppUtils::getKeyDefault($vars, 'submitName', 'next');

                    if ($submit == 'back') {
                        $this->setStepNumber(1);
                        $this->setWeekdays($this->parseWeekdays($vars));
                    } else {
                        $this->processStep3($vars);
                    }
                    break;
                case 4:
                    $submit = AppUtils::getKeyDefault($vars, 'submitName', 'next');
                    if ($submit == 'back') {
                        $this->setStepNumber(2);
                        $this->processStep2($vars);
                    }
                    break;
                default:
                    http_response_code(BaseAjaxRequest::HTTP_CODE_BAD_REQUEST);
                    break;
            }
        } else {
            PathUtils::internalRedirect('/PlanCreator/Step/1');
        }
    }

    protected function parseWeekdays($vars) {
        return [
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday0', "") == "on",
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday1', "") == "on",
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday2', "") == "on",
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday3', "") == "on",
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday4', "") == "on",
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday5', "") == "on",
            AppUtils::getKeyDefault($vars, 'planCreatorStep1Weekday6', "") == "on"
        ];
    }

    protected function processStep2($vars) {
        $weekdays = $this->parseWeekdays($vars);
        $this->setWeekdays($weekdays);

        $weekdays_count = 0;
        foreach ($weekdays as $weekday) {
            if ($weekday) { $weekdays_count++; }
        }
        $this->setWeekdaysCount($weekdays_count);

        $meals = DatabaseTools::getRandomWhere(
            MMeal::TABLE_NAME,
            new MMeal(),
            [ 'IGNORE_IN_PLAN' => 0 ],
            $weekdays_count
        );

        $this->setMeals($meals);
    }

    protected function processStep3($vars) {
        $weekdays = $this->parseWeekdays($vars);
        $this->setWeekdays($weekdays);

        $table_where = [];
        $first = true;
        for ($i = 0; $i < count($weekdays); $i++) {
            if ($weekdays[$i]) {
                array_push(
                    $table_where,
                    TableWhereObject::getEq(
                        'ID',
                        $vars['planCreatorStep2MealID' . $i],
                        (!$first ? TableWhereObject::PREFIX_OR : '')
                    )
                );
                $first = false;
            }
        }

        // Get Meals
        $db_meals = DatabaseTools::getWhereAdv(
            MVMeal::TABLE_NAME,
            new MVMeal(),
            $table_where,
            [], 0, 7
        )->data;

        // Order Meals for Weekdays
        /** @var MVMeal[] $meals */
        $meals = [];
        for ($i = 0; $i < count($weekdays); $i++) {
            if ($weekdays[$i]) {
                $meal_id = $vars['planCreatorStep2MealID' . $i];
                foreach ($db_meals as $meal) {
                    if ($meal->id == $meal_id) {
                        $meals[$i] = $meal;
                        continue;
                    }
                }
            } else {
                $meals[$i] = new MMeal();
            }
        }
        $this->setMeals($meals);

        // Get Linked Meals
        $linked_meals = [];
        for ($i = 0; $i < count($weekdays); $i++) {
            if ($weekdays[$i]) {
                $meal = $meals[$i];
                $linked_meals[$i] = DatabaseTools::getWhereSimple(
                    MVLinkedMeal::TABLE_NAME,
                    new MVLinkedMeal(),
                    [ 'meal_id' => $meal->id ]
                );
            } else {
                $linked_meals[$i] = [];
            }
        }
        $this->setLinkedMeals($linked_meals);
    }
}