<?php
require_once __DIR__ . '/modalBase.inc';
require_once __DIR__ . '/lockUser.inc';
MODAL_createSimpleDialog(
    'modalCreateUserSuccess',
    t('create_user'),
    t('modal_create_user_success', [
        '<span class="modal-variable createuser-username"></span>',
        '<pre class="createuser-newpassword password"></pre>'
    ]),
    t('ok')
);
?>
<div class="modal fade" tabindex="-1" role="dialog" id="modalCreateUser">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
                <h4 class="modal-title"><?= t('create_user') ?></h4>
            </div>
            <form id="modalCreateUser_form">
                <div class="modal-body">
                    <div class="form-group">
                        <label><?= t('username') ?>*</label>
                        <input type="text" class="form-control createuser-username" placeholder="<?= htmlspecialchars(t('username')) ?>" required>
                        <span class="help-block"><?= t('username_helptext') ?></span>
                    </div>
                    <div class="form-group">
                        <label><?= t('mail_address') ?></label>
                        <input type="email" class="form-control createuser-mail" placeholder="<?= htmlspecialchars(t('mail_address')) ?>">
                        <span class="help-block"><?= t('mail_address_helptext') ?></span>
                    </div>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal"><?= t('cancel') ?></button>
                    <button type="submit" class="btn btn-primary"><?= t('create_user') ?></button>
                </div>
            </form>
        </div>
    </div>
</div>
<script>
    function validateCreateUserForm(data) {
        var hasError = false;
        $('#modalCreateUser div.form-group').removeClass('has-error');
        if (!data.username || data.username.length < 3 || !data.username.match(/^[a-z0-9]+$/)) {
            $('#modalCreateUser input.createuser-username').parent().addClass('has-error');
            hasError = true;
        }

        if (data.mail && !isValidMailAddress(data.mail)) {
            $('#modalCreateUser input.createuser-mail').parent().addClass('has-error');
            hasError = true;
        }
        return !hasError;
    }

    $(document).ready(function() {
        $('#modalCreateUser').on('shown.bs.modal', function () {
            $('#modalCreateUser input.createuser-username').focus();
        });
        $('#modalCreateUser').on('hidden.bs.modal', function () {
            $('#modalCreateUser input.createuser-username').val('');
            $('#modalCreateUser input.createuser-mail').val('');
            $('#modalCreateUser div.form-group').removeClass('has-error');
        });
        $('#modalCreateUser_form').submit(function(e) {
            e.preventDefault();
            var userData = {
                action : 'createUser',
                username : $('#modalCreateUser input.createuser-username').val(),
                mail : $('#modalCreateUser input.createuser-mail').val()
            };
            if (!validateCreateUserForm(userData)) {
                return;
            }
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Users', userData,
                function() {
                    // Before Send
                    $('#modalCreateUser button[type=submit]').prop('disabled', true);
                },
                function(data, textStatus, jqXHR) {
                    // On Success
                    $('#modalCreateUserSuccess .createuser-username').text(data.UserName);
                    $('#modalCreateUserSuccess .createuser-newpassword').text(data.NewPassword);
                    $('#modalCreateUserSuccess').modal('show');
                    reloadUserListOnSuccess();
                },
                onUserModificationError,
                function (jqXHR, textStatus) {
                    // Complete
                    $('#modalCreateUser button[type=submit]').prop('disabled', false);
                    $('#modalCreateUser').modal('hide');
                }
            );
        })
    });
</script>
