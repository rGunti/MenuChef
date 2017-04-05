<?php require_once __DIR__ . '/modals/createMeal.inc' ?>
<table class="table table-hover table-condensed table-striped" id="mealTable">
    <thead>
    <tr>
        <th><?= t('meal_name') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>
<div class="container">
    <a href="#" class="btn btn-default" data-toggle="modal" data-target="#modalCreateMeal">
        <span class="glyphicon glyphicon-plus"></span>
        <?= t('create_meal') ?>
    </a>
</div>
<script>
    var mealTable = null;
    var ajaxSource = "<?= PathUtils::getLink("/AJAX/Meal") ?>";
    var editorPathPrefix = "<?= PathUtils::getLink("/Meal/") ?>";
    var editorPathSuffix = "/Editor";
    function reloadMealTable() {
        mealTable.ajax.reload(null, false);
    }
    $(document).ready(function() {
        mealTable = $('#mealTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                { data: "name", render: htmlEscapedCellRenderer },
                //{ data: "base_portion_size" },
                { data: null, render: function(d,t,r) {
                    var editorUrl = editorPathPrefix + r.id + editorPathSuffix;
                    var editorLink = '<a href="' + editorUrl + '" class="btn btn-default btn-xs" ' +
                        'title="<?= t('meal_editor') ?>">' +
                        '<span class="glyphicon glyphicon-pencil"></span>' +
                        '</a>';
                    return editorLink;
                } }
            ],
            columnDefs : [
                { targets: -1, orderable: false }
            ],
            pagingType : "full_numbers",
            language : <?php require __DIR__ . '/general/datatable.l10n.inc' ?>
        });
    });
</script>
