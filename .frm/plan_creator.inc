<?php
/** @var PlanCreatorRequest $req */
$req = RequestProcessor::getProcessedRequest();
$step = $req->getStepNumber();
?>

<?php if ($step == 1) {
    $weekdays = $req->getWeekdays();
    ?>
    <div class="container">
        <p><?= t('plan_creator_intro') ?></p>
    </div>
    <div class="container">
        <p><?= t('plan_creator_step_1') ?></p>
        <form id="planCreatorStep1Form"
              action="<?= PathUtils::getLink("/PlanCreator/Step/2") ?>"
              method="post"
        >
            <?php for ($weekday = 0; $weekday < 7; $weekday++) { ?>
                <div class="form-group checkbox checkbox-primary">
                    <input type="checkbox"
                           id="planCreatorStep1Weekday<?= $weekday ?>"
                           name="planCreatorStep1Weekday<?= $weekday ?>"
                           class="styled"
                           <?= ($weekdays[$weekday] ? 'checked' : '') ?>
                           />
                    <label for="planCreatorStep1Weekday<?= $weekday ?>">
                        <?= t("weekday_$weekday") ?>
                    </label>
                </div>
            <?php } ?>

            <hr>
            <div class="form-group text-right">
                <button class="btn btn-primary" type="submit">
                    <?= t('plan_creator_next_step') ?>&nbsp;
                    <span class="glyphicon glyphicon-arrow-right"></span>
                </button>
            </div>
        </form>
    </div>
<?php } else if ($step == 2) { ?>
    <?php
    $weekdays = $req->getWeekdays();
    $weekdays_count = $req->getWeekdaysCount();
    $meals = $req->getMeals();
    ?>
    <?php if ($weekdays_count > count($meals)) { ?>
        <div class="alert alert-warning" role="alert">
            <?= t('warning_plan_creator_not_enough_meals') ?>
        </div>
    <?php } ?>
    <form id="planCreatorStep2Form"
          action="<?= PathUtils::getLink('/PlanCreator/Step/3') ?>"
          method="post"
    >
        <p><?= t('plan_creator_step_2') ?></p>
        <?php for ($weekday_no = 0; $weekday_no < count($weekdays); $weekday_no++) { ?>
            <div class="form-group">
                <div class="row">
                    <div class="col-lg-2">
                        <h4><?= t("weekday_$weekday_no") ?></h4>
                    </div>
                    <div class="col-lg-10">
                        <h5>
                            <?php if ($weekdays[$weekday_no]) { ?>
                                <?php
                                if ($weekday_no + 1 > count($meals)) {
                                    $meal = $meals[rand(0, count($meals) - 1)];
                                } else {
                                    $meal = $meals[$weekday_no];
                                }
                                ?>
                                <input type="hidden"
                                       name="planCreatorStep2MealID<?= $weekday_no ?>"
                                       value="<?= $meal->id ?>"
                                />
                                <?= htmlspecialchars($meal->name) ?>
                            <?php } else { ?>
                                <span class="glyphicon glyphicon-option-horizontal"></span>
                            <?php } ?>
                        </h5>
                        <input type="hidden"
                               name="planCreatorStep1Weekday<?= $weekday_no ?>"
                               value="<?= ($weekdays[$weekday_no] ? 'on' : '') ?>"
                        />
                    </div>
                </div>
            </div>
        <?php } ?>

        <hr>
        <div class="form-group">
            <div class="col-lg-6">
                <button class="btn btn-default" type="submit" name="submitName" value="back">
                    <span class="glyphicon glyphicon-arrow-left"></span>&nbsp;
                    <?= t('plan_creator_prev_step') ?>
                </button>
            </div>
            <div class="col-lg-6 text-right">
                <button class="btn btn-primary" type="submit" name="submitName" value="next">
                    <?= t('plan_creator_next_step') ?>&nbsp;
                    <span class="glyphicon glyphicon-arrow-right"></span>
                </button>
            </div>
        </div>
    </form>
<?php } else if ($step == 3) { ?>
    <?php
    $weekdays = $req->getWeekdays();
    $meals = $req->getMeals();
    $linked_meals = $req->getLinkedMeals();
    ?>
    <form id="planCreatorStep3Form"
          action="<?= PathUtils::getLink('/PlanCreator/Step/4') ?>"
          method="post"
    >
        <p><?= t('plan_creator_step_3') ?></p>
        <?php for ($weekday_no = 0; $weekday_no < count($weekdays); $weekday_no++) { ?>
            <div class="form-group">
                <div class="row">
                    <?php if ($weekdays[$weekday_no]) { ?>
                        <?php
                        if ($weekday_no + 1 >= count($meals)) {
                            $meal = $meals[rand(0, count($meals) - 1)];
                        } else {
                            $meal = $meals[$weekday_no];
                        }
                        ?>

                        <div class="col-lg-6">
                            <label><?= t('plan_creator_meal_for_weekday', [t("weekday_$weekday_no")]) ?></label>
                            <input type="hidden"
                                   name="planCreatorStep2MealID<?= $weekday_no ?>"
                                   value="<?= $meal->id ?>"
                            />
                            <input type="text"
                                   class="form-control"
                                   value="<?= htmlspecialchars($meal->name) ?>"
                                   readonly
                            >
                        </div>
                        <div class="col-lg-6">
                            <label for="planCreatorStep3LinkedMeal<?= $weekday_no ?>"><?= t('linked_meal') ?></label>
                            <select name="planCreatorStep3LinkedMeal<?= $weekday_no ?>" class="form-control">
                                <option value="0">-</option>
                                <?php foreach ($linked_meals[$weekday_no] as $linked_meal) { ?>
                                    <option value="<?= $linked_meal->linked_meal_id ?>">
                                        <?= htmlspecialchars($linked_meal->linked_meal_name) ?>
                                    </option>
                                <?php } ?>
                            </select>
                        </div>
                    <?php } else { ?>
                        <div class="col-lg-6">
                            <label><?= t('plan_creator_meal_for_weekday', [t("weekday_$weekday_no")]) ?></label>
                            <input type="hidden"
                                   name="planCreatorStep2MealID<?= $weekday_no ?>"
                                   value="0"
                            />
                            <input type="text"
                                   class="form-control"
                                   value="-"
                                   readonly
                            />
                        </div>
                        <div class="col-lg-6">
                            <label for="planCreatorStep3LinkedMeal<?= $weekday_no ?>"><?= t('linked_meal') ?></label>
                            <select name="planCreatorStep3LinkedMeal<?= $weekday_no ?>"
                                    class="form-control"
                                    disabled
                                    readonly="readonly">
                                <option value="0">-</option>
                            </select>
                        </div>
                    <?php } ?>
                </div>
                <input type="hidden"
                       name="planCreatorStep1Weekday<?= $weekday_no ?>"
                       value="<?= ($weekdays[$weekday_no] ? 'on' : '') ?>"
                />
            </div>
        <?php } ?>

        <hr>
        <div class="form-group">
            <div class="col-lg-6">
                <button class="btn btn-default"
                        type="submit"
                        name="submitName"
                        value="back"
                        title="<?= htmlspecialchars(t('warning_plan_creator_loose_progress')) ?>"
                        data-toggle="tooltip"
                        data-placement="right"
                >
                    <span class="glyphicon glyphicon-arrow-left"></span>&nbsp;
                    <?= t('plan_creator_prev_step') ?>
                </button>
            </div>
            <div class="col-lg-6 text-right">
                <button class="btn btn-primary" type="submit" name="submitName" value="next">
                    <?= t('plan_creator_next_step') ?>&nbsp;
                    <span class="glyphicon glyphicon-arrow-right"></span>
                </button>
            </div>
        </div>
    </form>
<?php } else { ?>
    <div class="container">
        <div class="alert alert-danger" role="alert">
            <b><?= t('error') ?></b>:
            <?= t('error_plan_creator_invalid_step', [$step]) ?>
        </div>
    </div>
<?php } ?>

<script>
    $(document).ready(function() {
        $('[data-toggle="tooltip"]').tooltip();
    });
</script>
