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
        <div class="row">
            <div class="col-md-4"><b>Session Info</b></div>
            <div class="col-md-8">
                <?php if (Session::isLoggedIn()) { ?>
                    <div class="panel panel-default">
                        <div class="panel-heading" role="tab" id="headingSessionInfo">
                            <a role="button" data-toggle="collapse" data-parent="#sessionInfoAccordion" href="#collapseSessionInfo">
                                <b><?= t('debug_session_info') ?></b>
                            </a>
                        </div>
                        <div id="collapseSessionInfo" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingSessionInfo">
                            <div class="panel-body">
                                <div class="container-fluid">
                                    <?php foreach (Session::getAllSessionInfo() as $key => $value) { ?>
                                        <div class="row">
                                            <b><?= $key ?></b>:
                                            <i><?= $value ?></i>
                                        </div>
                                    <?php } ?>
                                </div>
                            </div>
                        </div>
                    </div>
                <?php } else { ?>
                    <i>not logged in</i>
                <?php } ?>
            </div>
        </div>
    </div>
    <div class="col-md-4">
        <h4><?= t('tos_title') ?></h4>
        <p><?= t('tos_content') ?></p>
    </div>
</div>
