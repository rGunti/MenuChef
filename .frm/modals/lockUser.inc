<?php
require_once __DIR__ . '/modalBase.inc';
MODAL_createSimpleDialog(
    'modalLockUser',
    t('disable_login'),
    t('modal_disable_login_question', ['<span class="modal-variable lockuser-username">_</span>']),
    t('no'),
    t('yes')
);
MODAL_createSimpleDialog(
    'modalUnlockUser',
    t('enable_login'),
    t('modal_enable_login_question', ['<span class="modal-variable lockuser-username">_</span>']),
    t('no'),
    t('yes')
);
?>
<script>
    function reloadUserListOnSuccess() {
        userTable.ajax.reload(null, false); // false: Keep page
    }

    function onUserModificationError(jqXHR, textStatus, errorThrown) {
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

    $('#modalLockUser,#modalUnlockUser').on('show.bs.modal', function (event) {
        var button = $(event.relatedTarget);
        var userID = button.data('user-id');
        var username = button.data('user-name');
        var modal = $(this);
        modal.find('.lockuser-username').html(username);
        modal.find('.hidden-data-id').val(userID);
    });
    $(document).ready(function() {
        $('#modalLockUser_form').submit(function(e) {
            e.preventDefault();
            var userID = $('#modalLockUser_data-id').val();
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Users', { id: userID, action: 'lockUser' },
                function() {
                    // Before Send
                    $('#modalLockUser button[type=submit]').prop('disabled',true);
                },
                reloadUserListOnSuccess,
                onUserModificationError,
                function(jqXHR, textStatus) {
                    // Complete
                    $('#modalLockUser button[type=submit]').prop('disabled',false);
                    $('#modalLockUser').modal('hide');
                });
        });


        $('#modalUnlockUser_form').submit(function(e) {
            e.preventDefault();
            var userID = $('#modalUnlockUser_data-id').val();
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Users', { id: userID, action: 'unlockUser' },
                function() {
                    // Before Send
                    $('#modalUnlockUser button[type=submit]').prop('disabled',true);
                },
                reloadUserListOnSuccess,
                onAjaxError,
                function(jqXHR, textStatus) {
                    // Complete
                    $('#modalUnlockUser button[type=submit]').prop('disabled',false);
                    $('#modalUnlockUser').modal('hide');
                });
        });
    });
</script>
