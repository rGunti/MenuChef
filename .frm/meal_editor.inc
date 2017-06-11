<?php
require_once __DIR__ . '/modals/modalBase.inc';

/** @var MealEditorRequest $req */
$req = RequestProcessor::getProcessedRequest();
$meal = $req->getEditingMeal();
$units = $req->getMeasuringUnits();

require_once __DIR__ . '/modals/deleteMeal.inc';
require_once __DIR__ . '/modals/editMealNote.inc';
require_once __DIR__ . '/modals/deleteLinkedMeal.inc';
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
                    <span class="glyphicon glyphicon-arrow-left"></span>
                    <?= t('back_to', [t('meal_pl')]) ?>
                </a>
                <button type="submit" class="btn btn-primary">
                    <span class="glyphicon glyphicon-ok"></span>
                    <?= t('rename') ?>
                </button>
            </div>
            <div class="col-lg-6" style="text-align: right">
                <a href="#" class="btn btn-danger" data-toggle="modal" data-target="#modalDeleteMeal">
                    <span class="glyphicon glyphicon-trash"></span>&nbsp
                    <?= t('delete') ?>
                </a>
            </div>
        </div>
    </div>
</form>

<h2 id="index"><?= t('index') ?></h2>
<div class="row">
    <div class="col-lg-12">
        <div class="btn-group" role="group">
            <button type="button" class="quick-nav-link btn btn-default" data-target="#mealIngrediens"><?= t('ingredient_pl') ?></button>
            <button type="button" class="quick-nav-link btn btn-default" data-target="#mealNotes"><?= t('meal_notes') ?></button>
            <button type="button" class="quick-nav-link btn btn-default" data-target="#linkedMeals"><?= t('linked_meal_pl') ?></button>
            <button type="button" class="quick-nav-link btn btn-default" data-target="#connectedMeals"><?= t('connected_meal_pl') ?></button>
        </div>
    </div>
</div>

<h2 id="mealIngrediens">
    <?= t('ingredient_pl') ?>
    <small class="back-to-index"><a class="quick-nav-link" data-target="#index"><?= t('back_to', [t('index')]) ?></a></small>
</h2>
<form id="mealEditorAddIngredientForm">
    <div class="row">
        <div class="col-lg-6">
            <div class="form-group">
                <label for="mealEditorAddIngredientName"><?= t('ingredient') ?></label>
                <input type="text"
                       class="form-control"
                       id="mealEditorAddIngredientName"
                       name="mealEditorAddIngredientName"
                       placeholder="<?= t('ingredient') ?>"
                >
                <input type="hidden" id="mealEditorAddIngredientIngrID" value="">
            </div>
        </div>
        <div class="col-lg-2">
            <div class="form-group">
                <label for="mealEditorAddIngredientAmount"><?= t('mein_amount') ?></label>
                <input type="number"
                       step="any"
                       class="form-control"
                       id="mealEditorAddIngredientAmount"
                       name="mealEditorAddIngredientAmount"
                       style="text-align: right"
                       placeholder="<?= t('mein_amount') ?>"
                >
            </div>
        </div>
        <div class="col-lg-2">
            <div class="form-group">
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
        </div>
        <div class="col-lg-2">
            <label><?= t('actions') ?></label>
            <button type="submit" class="form-control btn btn-success">
                <span class="glyphicon glyphicon-plus"></span>
                <?= t('add_ingredient') ?>
            </button>
        </div>
    </div>
</form>
<table class="table table-hover table-condensed table-striped" id="mealIngredientTable">
    <thead>
    <tr>
        <!-- <th><?= t('id') ?></th> -->
        <th><?= t('mein_amount') ?></th>
        <th><?= t('mein_ingredient') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>

<h2 id="mealNotes">
    <?= t('meal_notes') ?>
    <small class="back-to-index"><a class="quick-nav-link" data-target="#index"><?= t('back_to', [t('index')]) ?></a></small>
</h2>
<div class="row"><div class="col-lg-12"><?= $req->getMarkdownMessage() ?></div></div>
<div class="row">
    <div class="col-lg-12">
        <a href="#mealNotes"
           id="mealEditorEditMealNotesLink"
           data-id="<?= $meal->id ?>"
           class="btn btn-primary">
            <span class="glyphicon glyphicon-pencil"></span>
            <?= t('edit_named', [t('meal_notes')]) ?>
        </a>
    </div>
</div>

<h2 id="linkedMeals">
    <?= t('linked_meal_pl') ?>
    <small class="back-to-index"><a class="quick-nav-link" data-target="#index"><?= t('back_to', [t('index')]) ?></a></small>
</h2>
<table class="table table-hover table-condensed table-striped" id="linkedMealTable">
    <thead>
    <tr>
        <th><?= t('meal') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>

<h2 id="connectedMeals">
    <?= t('connected_meal_pl') ?>
    <small class="back-to-index"><a class="quick-nav-link" data-target="#index"><?= t('back_to', [t('index')]) ?></a></small>
</h2>
<table class="table table-hover table-condensed table-striped" id="connectedMealTable">
    <thead>
    <tr>
        <th><?= t('meal') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>

<script>
    var ingredientTable = null;
    var linkedMealTable = null;
    var connectedMealTable = null;
    var ajaxSource = "<?= PathUtils::getLink("/AJAX/MealIngredients/$meal->id") ?>";
    var ajaxSourceLinkedMeals = "<?= PathUtils::getLink("/AJAX/Meal/$meal->id/LinkedMeals") ?>";
    var ajaxSourceConnectedMeals = "<?= PathUtils::getLink("/AJAX/Meal/$meal->id/ConnectedMeals") ?>";
    var ajaxMealEdit = "<?= PathUtils::getLink("/AJAX/Meal") ?>";

    function reloadIngrList() {
        ingredientTable.ajax.reload(null, false); // false: Keep page
    }

    function reloadLinkedMealListsOnSuccess() {
        linkedMealTable.ajax.reload(null, false); // false: Keep page
        connectedMealTable.ajax.reload(null, false); // false: Keep page
    }

    function onMealEditorError(jqXHR, textStatus, errorThrown) {
        var response = jqXHR.responseJSON;
        console.log(response);
        if (typeof response.ErrorInfo == 'string') {
            showError('<?= t('modal_default_error_title') ?>', response.ErrorInfo);
        } else if (response.ErrorInfo.type == 'permission_error') {
            showError('<?= t('modal_default_error_title') ?>', 'Permission Error: ' + response.ErrorInfo.message);
        } else {
            onAjaxError(jqXHR, textStatus, errorThrown);
        }
    }

    function validateAddIngredient(ing) {
        console.log(ing);
        $('#mealEditorAddIngredientForm .form-group').removeClass('has-error');
        var isValid = true;

        if ((!ing.id || ing.id === 0) && (!ing.name)) {
            $('#mealEditorAddIngredientName').parent().addClass('has-error');
            isValid = false;
        }

        if (!ing.amount || ing.amount <= 0) {
            $('#mealEditorAddIngredientAmount').parent().addClass('has-error');
            isValid = false;
        }

        if (!ing.unit) {
            $('#mealEditorAddIngredientAmountUnit').parent().addClass('has-error');
            isValid = false;
        }

        return isValid;
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

        var dataTableLanguage = <?php require __DIR__ . '/general/datatable.l10n.inc' ?>;

        ingredientTable = $('#mealIngredientTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                //{ data: 'ref_id', render: htmlEscapedCellRenderer },
                { data: null, render: function(d,t,r) {
                    // htmlEscapedCellRenderer
                    return (Number(r.amount) + ' ' + r.unit_symbol).trim();
                } },
                { data: 'ingredient_name', render: htmlEscapedCellRenderer },
                { data: null, render: function(d,t,r) {
                    var deleteIngredientTitle = '<?= htmlspecialchars(t('delete')) ?>';
                    var deleteIngredientLink = '<a href="#mealIngrediens" ' +
                        'class="btn btn-default btn-xs deleteIngredientLink" ' +
                        'data-id="' + r.ref_id + '" title="' + deleteIngredientTitle + '">' +
                        '<span class="glyphicon glyphicon-trash"></span>' +
                        '</a>';
                    window.setTimeout(function() {
                        $('.deleteIngredientLink').off('click').on('click', function(e) {
                            var itemID = $(e.delegateTarget).data('id');
                            var data = {
                                action : 'deleteIngredient',
                                id : itemID
                            };
                            submitSimplePostRequest(ajaxSource, data,
                                function() { },
                                reloadIngrList,
                                onMealEditorError,
                                function() { }
                            );
                        });
                    }, 500);
                    return deleteIngredientLink;
                } }
            ],
            columnDefs : [
                //{ targets: 0, width: 75, orderable: false },
                { targets: 0, width: 110, orderable: false },
                { targets: 1, orderable: true },
                { targets: -1, orderable: false, width: 100 }
            ],
            order : [
                [ 1, "asc" ]
            ],
            pagingType : "full_numbers",
            language : dataTableLanguage
        });

        var linkedMealColumnDefs = [
            //{ targets: 0, width: 110, orderable: false },
            { targets: 0, orderable: true },
            { targets: -1, orderable: false, width: 100 }
        ];
        var linkedMealColumnOrder = [
            [ 0, "asc" ]
        ];

        linkedMealTable = $('#linkedMealTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSourceLinkedMeals,
            columns : [
                { data: 'linked_meal_name', render: htmlEscapedCellRenderer },
                { data: null, render: function(d,t,r) {
                    var viewLinkTitle = '<?= t('open_in_nohtml', [ t('meal_editor') ]) ?>';
                    var unlinkTitle = '<?= htmlspecialchars(t('delete_named', [ t('linked_meal_sh') ])) ?>';
                    var viewLink = '<a ' +
                        'href="<?= PathUtils::getLink('/Meal') ?>/' + r.linked_meal_id + '/Editor" ' +
                        'class="btn btn-default btn-xs" ' +
                        'title="' + viewLinkTitle + '">' +
                        '<span class="glyphicon glyphicon-pencil"></span>' +
                        '</a>';
                    var deleteLink = '<a ' +
                        'href="#linkedMeals" ' +
                        'class="btn btn-default btn-xs remove-linked-meal-link" ' +
                        'title="' + unlinkTitle + '" ' +
                        'data-toggle="modal" ' +
                        'data-target="#modalDeleteLinkedMeal" ' +
                        'data-id="' + r.ref_id + '" ' +
                        'data-meal-name="' + escapeHtml(r.linked_meal_name) + '"' +
                        '>' +
                        '<span class="glyphicon glyphicon-trash"></span>' +
                        '</a>';
                    return viewLink + deleteLink;
                } }
            ],
            columnDefs : linkedMealColumnDefs,
            order : linkedMealColumnOrder,
            pagingType : "full_numbers",
            language : dataTableLanguage
        });
        connectedMealTable = $('#connectedMealTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSourceConnectedMeals,
            columns : [
                { data: 'meal_name', render: htmlEscapedCellRenderer },
                { data: null, render: function(d,t,r) {
                    var viewLinkTitle = '<?= t('open_in_nohtml', [ t('meal_editor') ]) ?>';
                    var unlinkTitle = '<?= htmlspecialchars(t('delete_named', [ t('linked_meal_sh') ])) ?>';
                    var viewLink = '<a ' +
                        'href="<?= PathUtils::getLink('/Meal') ?>/' + r.meal_id + '/Editor" ' +
                        'class="btn btn-default btn-xs" ' +
                        'title="' + viewLinkTitle + '">' +
                        '<span class="glyphicon glyphicon-pencil"></span>' +
                        '</a>';
                    var deleteLink = '<a ' +
                        'href="#linkedMeals" ' +
                        'class="btn btn-default btn-xs remove-linked-meal-link" ' +
                        'title="' + unlinkTitle + '" ' +
                        'data-toggle="modal" ' +
                        'data-target="#modalDeleteLinkedMeal" ' +
                        'data-id="' + r.ref_id + '" ' +
                        'data-meal-name="' + escapeHtml(r.linked_meal_name) + '"' +
                        '>' +
                        '<span class="glyphicon glyphicon-trash"></span>' +
                        '</a>';
                    return viewLink + deleteLink;
                } }
            ],
            columnDefs : linkedMealColumnDefs,
            order : linkedMealColumnOrder,
            pagingType : "full_numbers",
            language : dataTableLanguage
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
                onMealEditorError,
                function() {
                    $('#mealEditorForm button[type=submit]').prop('disabled', false);
                }
            );
        });
        $('#mealEditorAddIngredientForm').submit(function(e) {
            e.preventDefault();
            var addIngData = {
                action: 'addIngredient',
                ingredient: {
                    id: $('#mealEditorAddIngredientIngrID').val(),
                    name: $('#mealEditorAddIngredientName').val(),
                    unit: $('#mealEditorAddIngredientAmountUnit').val(),
                    amount: $('#mealEditorAddIngredientAmount').val()
                }
            };
            if (!validateAddIngredient(addIngData.ingredient)) {
                return;
            }
            submitSimplePostRequest(ajaxSource, addIngData,
                function() {
                    $('#mealEditorAddIngredientForm button[type=submit]').prop('disabled', true);
                },
                function(data, textStatus, jqXHR) {
                    reloadIngrList();
                    $('#mealEditorAddIngredientIngrID').val(0);
                    $('#mealEditorAddIngredientName').val('');
                    $('#mealEditorAddIngredientAmountUnit').val('unit_none');
                    $('#mealEditorAddIngredientAmount').val('');
                    $('#mealEditorAddIngredientName').focus();
                },
                onMealEditorError,
                function () {
                    $('#mealEditorAddIngredientForm button[type=submit]').prop('disabled', false);
                }
            );
        });

        $('.quick-nav-link').click(function(e) {
            var sourceEl = $(e.delegateTarget);
            $('html,body').animate({
                scrollTop: $(sourceEl.data('target')).offset().top - 75
            }, 2000);
        });
    });
</script>
