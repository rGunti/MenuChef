<table class="table table-hover table-condensed table-striped" id="unitTable">
    <thead>
    <tr>
        <th><?= t('measuring_unit') ?></th>
        <th><?= t('unit_symbol') ?></th>
        <th><?= t('unit_group') ?></th>
        <th><?= t('unit_super_unit') ?></th>
        <th><?= t('actions') ?></th>
    </tr>
    </thead>
</table>
<script>
    var unitTable = null;
    var ajaxSource = "<?= PathUtils::getLink("/AJAX/Units") ?>";
    $(document).ready(function () {
        ingredientTable = $('#unitTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                { data: "name", render: function(d,t,r) {
                    return '<span title="Code: ' + d + '">' + htmlEscapedCellRenderer(r.t_name,t,r) + '</span>';
                } },
                { data: "symbol", render: htmlEscapedCellRenderer },
                { data: "unit_group", render: function(d,t,r) {
                    return '<span title="Code: ' + d + '">' + htmlEscapedCellRenderer(r.t_unit_group,t,r) + '</span>';
                } },
                { data: "super_unit", render: function(d,t,r) {
                    if (d === null) {
                        return '-';
                    } else {
                        return '<span title="Code: ' + d + '&#013;Multiplier: ' + r.super_unit_multiplier + '">' +
                                htmlEscapedCellRenderer(r.t_super_unit,t,r) +
                                ' (x' + r.super_unit_multiplier + ')' +
                                '</span>';
                    }
                } },
                { data: null, width: 50, render: function(d,t,r) {
                    return null;
                } }
            ],
            columnDefs : [
                //{ targets: 1, orderable: false },
                //{ targets: -2, orderable: false },
                { targets: -1, orderable: false }
            ],
            pagingType : "full_numbers",
            language : <?php require __DIR__ . '/general/datatable.l10n.inc' ?>
        });
    });
</script>
