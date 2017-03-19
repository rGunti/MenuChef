<form action="<?= PathUtils::getLink("/Login") ?>" method="post">
    <div class="form-group">
        <label for="loginUsername"><?= t('username') ?></label>
        <input type="text" class="form-control" id="loginUsername" name="loginUsername" placeholder="<?= t('username') ?>">
    </div>
    <div class="form-group">
        <label for="loginPassword"><?= t('password') ?></label>
        <input type="password" class="form-control" id="loginPassword" name="loginPassword" placeholder="<?= t('password') ?>">
    </div>
    <div class="form-group">
        <button type="submit" class="btn btn-primary"><?= t('login') ?></button>
    </div>
</form>
