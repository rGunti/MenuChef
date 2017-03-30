<?php
require_once __DIR__ . '/modals/modalBase.inc';

/** @var MealEditorRequest $req */
$req = RequestProcessor::getProcessedRequest();
$meal = $req->getEditingMeal();
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
        <a href="<?= PathUtils::getLink("/Meal") ?>"
           class="btn btn-default">
            <?= t('cancel') ?>
        </a>
        <button type="submit" class="btn btn-primary"><?= t('save') ?></button>
    </div>
</form>

<h2><?= t('ingredient_pl') ?></h2>
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
        ingredientTable = $('#mealIngredientTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                { data: 'ref_id' },
                { data: 'amount_text' },
                { data: 'ingredient_name' },
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
