<?php
require_once __DIR__ . '/modalBase.inc';
require_once __DIR__ . '/lockUser.inc';

MODAL_createSimpleDialog(
    'modalDeleteUser',
    t('delete_user'),
    t('modal_delete_user_question', ['<span class="modal-variable deleteuser-username">_</span>']),
    t('no'), t('yes')
);
?>
<script>
    $('#modalDeleteUser').on('show.bs.modal', function (event) {
        var button = $(event.relatedTarget);
        var userID = button.data('user-id');
        var username = button.data('user-name');
        var modal = $(this);
        modal.find('.deleteuser-username').html(username);
        modal.find('.hidden-data-id').val(userID);
    });
    $(document).ready(function() {
        $('#modalDeleteUser .modal-header').addClass('bg-warning');
        $('#modalDeleteUser button[type=submit]').addClass('btn-warning');
        $('#modalDeleteUser_form').submit(function (e) {
            e.preventDefault();
            var userID = $('#modalDeleteUser_data-id').val();
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Users', {id: userID, action: 'deleteUser'},
                function () {
                    // Before Send
                    $('#modalDeleteUser button[type=submit]').prop('disabled', true);
                },
                reloadUserListOnSuccess,
                onAjaxError,
                function (jqXHR, textStatus) {
                    // Complete
                    $('#modalDeleteUser button[type=submit]').prop('disabled', false);
                    $('#modalDeleteUser').modal('hide');
                });
        });
    });
</script>
