<?php if (PathUtils::currentPathMatches('/_Docs/*')) { ?>
    <p>
        <a href="<?= PathUtils::getLink('/_Docs') ?>" class="btn btn-default">
            <span class="glyphicon glyphicon-arrow-left"></span>
            <?= t('app_documents_title') ?>
        </a>
    </p>
    <?php
    /** @var AppDocumentRequest $request */
    $request = RequestProcessor::getProcessedRequest();
    echo $request->getPageContent();
    ?>
<?php } else { ?>
    <p><?= t('app_documents_content') ?></p>
    <ul>
        <li><a href="<?= PathUtils::getLink('/_Docs/ToS')       ?>"><?= t('tos_title') ?></a></li>
        <li><a href="<?= PathUtils::getLink('/_Docs/Imprint')   ?>"><?= t('imprint_title') ?></a></li>
        <li><a href="<?= PathUtils::getLink('/_Docs/Copyright') ?>"><?= t('copyright_title') ?></a></li>
    </ul>
<?php } ?>
