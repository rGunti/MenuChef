<?php
require_once __DIR__ . '/modalBase.inc';
require_once __DIR__ . '/lockUser.inc';

MODAL_createSimpleDialog(
    'modalResetUser',
    t('reset_password'),
    t('modal_reset_user_question', ['<span class="modal-variable resetuser-username"></span>']),
    t('no'),
    t('yes')
);
MODAL_createSimpleDialog(
    'modalResetUserSuccess',
    t('reset_password'),
    t('modal_reset_user_success', [
        '<span class="modal-variable resetuser-username"></span>',
        '<pre class="resetuser-newpassword password"></pre>'
    ]),
    t('ok')
);
?>
<script>
    $('#modalResetUser').on('show.bs.modal', function(event) {
        var button = $(event.relatedTarget);
        var userID = button.data('user-id');
        var username = button.data('user-name');
        var modal = $(this);
        modal.find('.resetuser-username').html(username);
        modal.find('.hidden-data-id').val(userID);
    });
    $(document).ready(function() {
        $('#modalResetUser_form').submit(function(e) {
            e.preventDefault();
            var userID = $('#modalResetUser_data-id').val();
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Users', { id: userID, action: 'resetUser' },
                function() {
                    $('#modalResetUser button[type=submit]').prop('disabled', true);
                },
                function(data, textStatus, jqXHR) {
                    $('#modalResetUserSuccess .resetuser-username').text(data.UserName);
                    $('#modalResetUserSuccess .resetuser-newpassword').text(data.NewPassword);
                    $('#modalResetUserSuccess').modal('show');
                    reloadUserListOnSuccess();
                },
                onAjaxError,
                function(jqXHR, textStatus) {
                    // Complete
                    $('#modalResetUser button[type=submit]').prop('disabled', false);
                    $('#modalResetUser').modal('hide');
                }
            );
        });
    });
</script>
