<?php
/**
 * @param $id string
 * @param $title string
 * @param $text string
 * @param $cancelLabel string
 * @param $okLabel string
 */
function MODAL_createSimpleDialog($id, $title, $text, $cancelLabel, $okLabel = null) {
    echo "\n<!-- START OF DIALOG $id -->\n" .
        '<div class="modal fade" tabindex="-1" role="dialog" id="' . $id . '">' .
        '<div class="modal-dialog" role="document">' .
        '<div class="modal-content">' .
        '<div class="modal-header">' .
        '<button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>' .
        '<h4 class="modal-title">' . $title . '</h4>' .
        '</div>' .
        '<form id="' . $id . '_form">' .
        '<div class="modal-body">' .
        '<input type="hidden" class="hidden-data-id" id="' . $id . '_data-id" value="-1">' .
        "<p>$text</p>" . '</div>' .
        '<div class="modal-footer">' .
        '<button type="button" class="btn btn-default" data-dismiss="modal">' . $cancelLabel . '</button>' .
        (!empty($okLabel) ? '<button type="submit" class="btn btn-primary">' . $okLabel . '</button>' : '') .
        '</div>' .
        '</form>' .
        '</div>' .
        '</div>' .
        '</div>';
    echo "\n<!-- END OF DIALOG $id -->\n";
}
?>

<!-- START OF ERROR DIALOG -->
<div class="modal fade" tabindex="-1" role="dialog" id="unhandledErrorDialog">
    <div class="modal-dialog modal-lg" role="document">
        <div class="modal-content">
            <div class="modal-header bg-danger">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title">
                    <span class="glyphicon glyphicon-exclamation-sign"></span>
                    <?= t('modal_unhandled_error_title') ?>
                </h4>
            </div>
            <div class="modal-body">
                <p><?= t('modal_unhandled_error_text') ?></p>
                <pre id="unhandledErrorInfo"></pre>
            </div>
            <div class="modal-footer bg-danger">
                <button type="button" class="btn btn-default" data-dismiss="modal"><?= t('ok') ?></button>
            </div>
        </div>
    </div>
</div>
<!-- <button type="button" class="btn btn-danger" onclick="showUnhandledError('This is a test')">Show Error Modal</button> -->
<!-- END OF ERROR DIALOG -->

<script src="<?= PathUtils::getLink('/js/ajaxSubmitTools.js') ?>"></script>
<script>
    var AJAX_BASE_PATH = '<?= AppUtils::getBasePath() ?>';
</script>
