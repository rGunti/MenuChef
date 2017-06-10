<div class="row">
    <div class="col-md-4">
        <h4><?= t('copyright_title') ?></h4>
        <p><?= t('copyright_content', date('Y')) ?></p>
        <p>
            <a href="<?= PathUtils::getLink('/_Docs/Copyright') ?>">
                <?= t('copyright_show_more') ?>
            </a>
        </p>
    </div>
    <div class="col-md-4">
        <h4>App Info</h4>
        <div class="row">
            <div class="col-md-4"><b><?= t('app_version') ?></b></div>
            <div class="col-md-8"><?= AppConfig::APP_VERSION ?></div>
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
        <?php if (AppConfig::FEEDBACK_MAIL) { ?>
            <h4><?= t('feedback_title') ?></h4>
            <p>
                <?= t('feedback_content', [
                    '<a href="mailto:' . AppConfig::FEEDBACK_MAIL . '?subject='
                    . t(AppConfig::FEEDBACK_SUBJECT) . '">'
                    . AppConfig::FEEDBACK_MAIL
                    . '</a>'
                ]) ?>
            </p>
        <?php } ?>

        <h4><?= t('imprint_box_title') ?></h4>
        <ul>
            <li><a href="<?= PathUtils::getLink('/_Docs/Imprint') ?>"><?= t('imprint_title') ?></a></li>
            <li><a href="<?= PathUtils::getLink('/_Docs/ToS') ?>"><?= t('tos_title') ?></a></li>
        </ul>
    </div>
</div>
