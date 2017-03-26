<div class="row">
    <div class="col-md-4">
        <h4><?= t('copyright_title') ?></h4>
        <p><?= t('copyright_content', date('Y')) ?></p>
    </div>
    <div class="col-md-4">
        <h4>App Info</h4>
        <div class="row">
            <div class="col-md-4"><b><?= t('app_version') ?></b></div>
            <div class="col-md-8">0.1</div>
        </div>
        <?php if (AppConfig::SHOW_INSTANCE_NAME) { ?>
            <div class="row">
                <div class="col-md-4"><b><?= t('debug_instance') ?></b></div>
                <div class="col-md-8"><kbd><?= AppConfig::INSTANCE_NAME ?></kbd></div>
            </div>
        <?php } ?>
        <div class="row">
            <div class="col-md-4"><b><?= t('language') ?></b></div>
            <div class="col-md-8">
                <?= L10N::getLanguageName() ?><br>
                <?= t('_LANG_BY_STRING', [L10N::getLanguageAuthor()]) ?>
            </div>
        </div>
    </div>
    <div class="col-md-4">
        <h4><?= t('tos_title') ?></h4>
        <p><?= t('tos_content') ?></p>
    </div>
</div>
