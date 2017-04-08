<?php
require_once __DIR__ . '/modals/modalBase.inc';

/** @var MealEditorRequest $req */
$req = RequestProcessor::getProcessedRequest();
$meal = $req->getEditingMeal();
$units = $req->getMeasuringUnits();

require_once __DIR__ . '/modals/deleteMeal.inc';
?>
<form id="mealEditorForm">
    <div class="form-group">
        <label for="mealEditorName"><?= t('meal_name') ?></label>
        <input type="text"
               class="form-control"
               id="mealEditorName"
               name="mealEditorName"
               value="<?= htmlspecialchars($meal->name) ?>"
               required>
    </div>
    <div class="form-group">
        <div class="row">
            <div class="col-lg-6">
                <a href="<?= PathUtils::getLink("/Meal") ?>"
                   class="btn btn-default">
                    <?= t('cancel') ?>
                </a>
                <button type="submit" class="btn btn-primary"><?= t('save') ?></button>
            </div>
            <div class="col-lg-6" style="text-align: right">
                <a href="#" class="btn btn-danger" data-toggle="modal" data-target="#modalDeleteMeal">
                    <span class="glyphicon glyphicon-trash"></span>&nbsp;
                    <?= t('delete') ?>
                </a>
            </div>
        </div>
    </div>
</form>

<h2><?= t('ingredient_pl') ?></h2>
<div class="form-group">
    <div class="row">
        <div class="col-lg-6">
            <label for="mealEditorAddIngredientName"><?= t('ingredient') ?></label>
            <input type="text"
                   class="form-control"
                   id="mealEditorAddIngredientName"
                   name="mealEditorAddIngredientName"
                   placeholder="<?= t('ingredient') ?>"
            >
            <input type="hidden" id="mealEditorAddIngredientIngrID" value="">
        </div>
        <div class="col-lg-2">
            <label for="mealEditorAddIngredientAmount"><?= t('mein_amount') ?></label>
            <input type="number"
                   class="form-control"
                   id="mealEditorAddIngredientAmount"
                   name="mealEditorAddIngredientAmount"
                   style="text-align: right"
                   placeholder="<?= t('mein_amount') ?>"
            >
        </div>
        <div class="col-lg-2">
            <label for="mealEditorAddIngredientAmountUnit"><?= t('measuring_unit') ?></label>
            <select class="form-control"
                    id="mealEditorAddIngredientAmountUnit"
                    name="mealEditorAddIngredientAmountUnit"
            >
                <?php foreach ($units as $unit_group_name => $subunits) { ?>
                    <optgroup label="<?= htmlspecialchars(t($unit_group_name)) ?>">
                        <?php foreach ($subunits as $unit) { ?>
                            <option value="<?= $unit->getPrimaryKey() ?>" <?= $unit->symbol == '' ? 'selected' : '' ?>>
                                <?= empty($unit->symbol) ? t($unit->name) : $unit->symbol . " (" . t($unit->name) . ")" ?>
                            </option>
                        <?php } ?>
                    </optgroup>
                <?php } ?>
            </select>
        </div>
        <div class="col-lg-2">
            <label><?= t('actions') ?></label>
            <button type="submit" class="form-control btn btn-success">
                <span class="glyphicon glyphicon-plus"></span>
                <?= t('add_ingredient') ?>
            </button>
        </div>
    </div>
</div>
<table class="table table-hover table-condensed table-striped" id="mealIngredientTable">
    <thead>
    <tr>
        <th><?= t('id') ?></th>
        <th><?= t('mein_amount') ?></th>
        <th><?= t('mein_ingredient') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>
<script>
    var ingredientTable = null;
    var ajaxSource = "<?= PathUtils::getLink("/AJAX/MealIngredients/$meal->id") ?>";
    var ajaxMealEdit = "<?= PathUtils::getLink("/AJAX/Meal") ?>";

    function reloadIngrList() {
        ingredientTable.ajax.reload(null, false); // false: Keep page
    }

    $(document).ready(function() {
        $('#mealEditorAddIngredientName').autocomplete({
            source: function (request, response) {
                $.ajax({
                    url: '<?= PathUtils::getLink('/AJAX/Ingredients/AutoComplete') ?>',
                    //method: 'post',
                    data: {
                        term: request.term
                    },
                    // Expected Output: {id,label,value}
                    success: function(data) { response(data); },
                    error: onErrorAutoHandle
                })
            },
            minLength: 2,
            select: function (event, ui) {
                //console.log(event, ui);
                //console.log(ui.item);
                $('#mealEditorAddIngredientIngrID').val(ui.item.id);
            }
        });
        $('#mealEditorAddIngredientName').on('input propertychange paste', function(e) {
            $('#mealEditorAddIngredientIngrID').val(0);
        });
        ingredientTable = $('#mealIngredientTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                { data: 'ref_id', render: htmlEscapedCellRenderer },
                { data: 'amount_text', render: htmlEscapedCellRenderer },
                { data: 'ingredient_name', render: htmlEscapedCellRenderer },
                { data: null, render: function(d,t,r) {
                    return "-";
                } }
            ],
            columnDefs : [
                { targets: 0, width: 75, orderable: false },
                { targets: 1, width: 110, orderable: false },
                { targets: -1, orderable: false, width: 100 }
            ],
            order : [
                [ 2, "asc" ]
            ],
            pagingType : "full_numbers",
            language : <?php require __DIR__ . '/general/datatable.l10n.inc' ?>
        });
        $('#mealEditorForm').submit(function(e) {
            e.preventDefault();
            submitSimplePostRequest(ajaxMealEdit, { id: <?= $meal->id ?>, action: 'changeName', name: $('#mealEditorName').val() },
                function() {
                    $('#mealEditorForm button[type=submit]').prop('disabled', true);
                },
                function(data, textStatus, jqXHR) {
                    window.location.href = window.location.href;
                },
                function(jqXHR, textStatus, errorThrown) {
                    var response = jqXHR.responseJSON;
                    console.log(response);
                    if (typeof response.ErrorInfo == 'string') {
                        showError('<?= t('modal_default_error_title') ?>', response.ErrorInfo);
                    } else if (response.ErrorInfo.type == 'permission_error') {
                        showError('<?= t('modal_default_error_title') ?>', 'Permission Error: ' + response.ErrorInfo.message);
                    } else {
                        onAjaxError(jqXHR, textStatus, errorThrown);
                    }
                },
                function() {
                    $('#mealEditorForm button[type=submit]').prop('disabled', false);
                }
            );
        });
    });
</script>
