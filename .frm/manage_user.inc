<?php $users = RequestProcessor::getProcessedRequest()->getStorageValue('users') ?>
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
    </thead><tbody>
        <?php foreach ($users as $user) { ?>
            <tr>
                <td><?= htmlspecialchars($user->id) ?></td>
                <td><?= htmlspecialchars($user->username) ?></td>
                <td><?= htmlspecialchars($user->mail) ?></td>
                <td class="text-center"><?= ($user->is_admin) ? '<span class="glyphicon glyphicon-ok-sign"></span>' : '' ?></td>
                <td class="text-center"><?= ($user->is_batch) ? '<span class="glyphicon glyphicon-ok-sign"></span>' : '' ?></td>
                <td class="text-center"><?= ($user->is_blocked) ? '<span class="glyphicon glyphicon-ok-sign"></span>' : '' ?></td>
                <td></td>
            </tr>
        <?php } ?>
    </tbody>
</table>
