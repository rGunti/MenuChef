<?php require_once __DIR__ . '/modals/lockUser.inc' ?>
<?php require_once __DIR__ . '/modals/resetUser.inc' ?>
<?php require_once __DIR__ . '/modals/deleteUser.inc' ?>
<?php require_once __DIR__ . '/modals/createUser.inc' ?>
<?php require_once __DIR__ . '/modals/privilegeUser.inc' ?>
<table class="table table-hover table-condensed table-striped" id="userTable">
    <thead>
        <tr>
            <th><?= t('id') ?></th>
            <th><?= t('username') ?></th>
            <th><?= t('mail_address') ?></th>
            <th class="text-center"><?= t('admin_permission_short') ?></th>
            <th class="text-center"><?= t('batch_short') ?></th>
            <th class="text-center"><?= t('disabled_short') ?></th>
            <th><?= t('actions') ?></th>
        </tr>
    </thead>
</table>
<div class="container">
    <a href="#" class="btn btn-default" data-toggle="modal" data-target="#modalCreateUser">
        <span class="glyphicon glyphicon-plus"></span>
        <?= t('create_user') ?>
    </a>
</div>
<script>
    var userTable = null;
    var ownUserID = <?= Session::getUserInfo()->id ?>;
    var ajaxSource = "<?= PathUtils::getLink("/AJAX/Users") ?>";
    $(document).ready(function() {
        userTable = $('#userTable').DataTable({
            processing : true,
            serverSide : true,
            ajax : ajaxSource,
            columns : [
                { data: "id" },
                { data: "username", render: function(d,t,r) {
                    if (r.errorInfo) {
                        if (Array.isArray(r.errorInfo)) {
                            return r.errorInfo.join('<br>');
                        } else {
                            return "<pre>" + JSON.stringify(r.errorInfo, null, '  ') + "</pre>";
                        }
                    } else {
                        return d;
                    }
                } },
                { data: "mail" },
                { data: "is_admin", className: 'text-center', render: function(d,t,r) {
                    return getHtmlCheckbox(d);
                }  },
                { data: "is_batch", className: 'text-center', render: function(d,t,r) {
                    return getHtmlCheckbox(d);
                }  },
                { data: "is_blocked", className: 'text-center', render: function(d,t,r) {
                    return getHtmlCheckbox(d);
                } },
                { data: null, render: function(d,t,r) {
                    //if (r.id == ownUserID) { return ""; }

                    var disableLink = '<a href="#" class="btn btn-default btn-xs" id="disableLogin' + r.id + '" ' +
                        'data-toggle="modal" data-target="#modalLockUser" data-user-id="' + r.id + '" data-user-name="' + escapeHtml(r.username) + '"' +
                        'title="<?= htmlspecialchars(t('disable_login')) ?>">' +
                        '<span class="glyphicon glyphicon-lock"></span>' +
                        '</a>';
                    var enableLink = '<a href="#" class="btn btn-default btn-xs" id="enableLogin' + r.id + '" ' +
                        'data-toggle="modal" data-target="#modalUnlockUser" data-user-id="' + r.id + '" data-user-name="' + escapeHtml(r.username) + '"' +
                        'title="<?= htmlspecialchars(t('enable_login')) ?>">' +
                        '<span class="glyphicon glyphicon-check"></span>' +
                        '</a>';
                    var resetPasswordLink = '<a href="#" class="btn btn-default btn-xs" id="resetPassword' + r.id + '" ' +
                        'data-toggle="modal" data-target="#modalResetUser" data-user-id="' + r.id + '" data-user-name="' + escapeHtml(r.username) + '"' +
                        'title="<?= htmlspecialchars(t('reset_password')) ?>">' +
                        '<span class="glyphicon glyphicon-refresh"></span>' +
                        '</a>';
                    var deleteLink = '<a href="#" class="btn btn-default btn-xs" id="deleteUser' + r.id + '" ' +
                        'data-toggle="modal" data-target="#modalDeleteUser" data-user-id="' + r.id + '" data-user-name="' + escapeHtml(r.username) + '"' +
                        'title="<?= htmlspecialchars(t('delete_user')) ?>">' +
                        '<span class="glyphicon glyphicon-trash"></span>' +
                        '</a>';
                    var privilegeLink = '<a href="#" class="btn btn-default btn-xs" id="privilegeUser' + r.id + '" ' +
                        'data-toggle="modal" data-target="#modalPrivilegeUser" data-user-id="' + r.id + '" data-user-name="' + escapeHtml(r.username) + '"' +
                        'data-is-admin="' + (r.is_admin ? 1 : 0) + '" data-is-batch="' + r.is_batch + '" ' +
                        'title="<?= htmlspecialchars(t('privilege_user')) ?>">' +
                        '<span class="glyphicon glyphicon-cog"></span>' +
                        '</a>';

                    return '<div class="btn-group btn-group-xs">' +
                        (r.is_blocked ? enableLink : disableLink) +
                        (r.is_blocked || r.is_batch ? '' : resetPasswordLink) +
                        (r.is_blocked ? '' : privilegeLink) +
                        deleteLink +
                        '</div>';
                } }
            ],
            columnDefs : [
                { targets: -1, orderable: false }
            ],
            pagingType : "full_numbers",
            language : <?php require_once __DIR__ . '/general/datatable.l10n.inc' ?>
        })
    })
</script>
