<?php $form = RequestProcessor::getProcessedRequest()->getStorageValue(UserSettingsRequest::KEY_FORM) ?>
<form action="<?= PathUtils::getLink("/MySettings") ?>" method="post">
    <div class="form-group">
        <label><?= t('username') ?></label>
        <input type="text"
               class="form-control"
               value="<?= htmlspecialchars($form->username) ?>"
               readonly>
    </div>
    <div class="form-group">
        <label for="userSettingsMail"><?= t('mail_address') ?></label>
        <input type="email"
               class="form-control"
               value="<?= htmlspecialchars($form->mail) ?>"
               id="userSettingsMail" name="userSettingsMail"
               maxlength="255">
    </div>
    <div class="form-group">
        <label for="userSettingsPassword1"><?= t('change_password') ?></label>
        <input type="password"
               class="form-control"
               id="userSettingsPassword1" name="userSettingsPassword1"
               maxlength="64">
        <p class="help-block"><?= t('change_password_help') ?></p>
    </div>
    <div class="form-group">
        <label for="userSettingsPassword2"><?= t('confirm_password') ?></label>
        <input type="password"
               class="form-control"
               id="userSettingsPassword2" name="userSettingsPassword2"
               maxlength="64">
    </div>
    <div class="form-group">
        <button type="submit" class="btn btn-primary">
            <span class="glyphicon glyphicon-check"></span>
            <?= t('save') ?>
        </button>
    </div>
</form>
