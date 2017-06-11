<?php
/** @var MealPrintRequest $req */
$req = RequestProcessor::getProcessedRequest();
$meal = $req->getPrintableMeal();
$ingredients = $req->getMealIngredients();
$linked_meals = $req->getLinkedMeals();
?>

<div class="hide-from-printer">
    <button class="btn btn-primary" onclick="print()">
        <span class="glyphicon glyphicon-print"></span>
        <?= t('print') ?>
    </button>
</div>

<h2><?= t('ingredient_pl') ?></h2>
<div class="container">
    <ul>
        <?php foreach ($ingredients as $ingredient) { ?>
            <li>
                <?= (float)$ingredient->amount ?>
                <?= $ingredient->unit_symbol ?>
                <?= htmlspecialchars($ingredient->ingredient_name) ?>
            </li>
        <?php } ?>
    </ul>
</div>

<h2><?= t('meal_notes') ?></h2>
<div class="container">
    <?= $req->getMarkdownMessage() ?>
</div>

<?php if (count($linked_meals) > 0) { ?>
    <h2><?= t('linked_meal_pl') ?></h2>
    <div class="container">
        <ul>
            <?php foreach ($linked_meals as $linked_meal) { ?>
                <li>
                    <a href="<?= PathUtils::getLink("/Meal/$linked_meal->linked_meal_id/Print") ?>">
                        <?= htmlspecialchars($linked_meal->linked_meal_name) ?>
                    </a>
                </li>
            <?php } ?>
        </ul>
    </div>
<?php } ?>
