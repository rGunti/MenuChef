<table class="table table-hover table-condensed table-striped" id="ingredientTable">
    <thead>
    <tr>
        <th><?= t('id') ?></th>
        <th><?= t('ingredient') ?></th>
        <th><?= t('meal_pl') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>
<script>
    var ingredientTable = null;
    var ajaxSource = "<?= PathUtils::getLink("/AJAX/Ingredients") ?>";
    $(document).ready(function () {
        ingredientTable = $('#ingredientTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                { data: "id", width: 50 },
                { data: "name", render: htmlEscapedCellRenderer },
                { data: "meal_count", render: htmlEscapedCellRenderer },
                { data: null, width: 50, render: function(d,t,r) {
                    return null;
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
