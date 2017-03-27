<?php
require_once __DIR__ . '/modalBase.inc';
require_once __DIR__ . '/lockUser.inc';

$options_html = '<div class="form-group">';
$options_html .= '<select class="form-control" id="privilegeUserRoleSelect">';
$options_html .= '<option value="1">' . t('privilege_level_admin') . '</option>';
$options_html .= '<option value="0">' . t('privilege_level_default') . '</option>';
$options_html .= '</select>';
$options_html .= '</div>';

MODAL_createSimpleDialog(
    'modalPrivilegeUser',
    t('privilege_user'),
    t('modal_privilege_user_content', [
        '<span class="modal-variable privilegeuser-username"></span>',
        $options_html
    ]),
    t('cancel'), t('save')
);
?>
<script>
    $('#modalPrivilegeUser').on('show.bs.modal', function(event) {
        var button = $(event.relatedTarget);
        var userID = button.data('user-id');
        var username = button.data('user-name');
        var userIsAdmin = button.data('is-admin');
        var modal = $(this);
        modal.find('.privilegeuser-username').html(username);
        modal.find('#privilegeUserRoleSelect').val(userIsAdmin);
        modal.find('.hidden-data-id').val(userID);
    });
    $(document).ready(function() {
        $('#modalPrivilegeUser_form').submit(function(e) {
            e.preventDefault();
            var userID = $('#modalPrivilegeUser_data-id').val();
            var level = $('#privilegeUserRoleSelect').val();
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Users', { id: userID, action: 'changeUserLevel', value: level },
                function() {
                    $('#modalPrivilegeUser button[type=submit]').prop('disabled', true);
                },
                reloadUserListOnSuccess,
                onUserModificationError,
                function(jqXHR, textStatus) {
                    $('#modalPrivilegeUser button[type=submit]').prop('disabled', false);
                    $('#modalPrivilegeUser').modal('hide');
                }
            );
        });
    });
</script>
