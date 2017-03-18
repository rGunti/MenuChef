<?php
function debug_view_render_table($rq_key, $title) {
    $col = RequestProcessor::getProcessedRequest()->getStorageValue($rq_key);
    ?>
    <div class="panel panel-default">
        <div class="panel-heading" role="tab" id="heading<?= $rq_key ?>">
            <h2 class="panel-title">
                <a role="button" data-toggle="collapse" data-parent="#debugAccordion" href="#collapse<?= $rq_key ?>" aria-expanded="true" aria-controls="collapse<?= $rq_key ?>">
                    <b><?= $title ?></b> <span class="badge"><?= count($col) ?></span>
                </a>
            </h2>
        </div>
        <div id="collapse<?= $rq_key ?>" class="panel-collapse collapse" role="tabpanel" aria-labelledby="heading<?= $rq_key ?>">
            <div class="panel-body">
                <?php if (count($col) == 0) { ?>
                    <p>No Items</p>
                <?php } ?>
                <?php foreach ($col as $key => $value) { ?>
                    <div class="row">
                        <div class="col-md-4"><b><?= $key ?></b></div>
                        <div class="col-md-8" style="word-wrap:break-word;"><?php
                            if (is_array($value)) {
                                foreach ($value as $subkey => $subval) {
                                    echo '<div class="row"><div class="col-md-4"><i>' .
                                        $subkey .
                                        '</i></div><div class="col-md-8">' .
                                        $subval .
                                        '</div></div>';
                                }
                            } else if ($rq_key == "_server" && ($key == "PATH" || $key == "PATHEXT")) {
                                echo "<ul>";
                                foreach (explode(';', $value) as $value_item) {
                                    echo "<li>$value_item</li>";
                                }
                                echo "</ul>";
                            } else {
                                echo $value;
                            }
                            ?></div>
                    </div>
                <?php } ?>
            </div>
        </div>
    </div>
    <?php
}
?>
<!--
<p>
    <a href="./Debug/PhpInfo" class="btn btn-default">Show PHP Info</a>
</p>
-->

<div class="panel-group" id="debugAccordion" role="tablist" aria-multiselectable="true">
    <?php debug_view_render_table('_server', 'SERVER') ?>
    <?php debug_view_render_table('_session', 'SESSION') ?>
    <?php debug_view_render_table('_get', 'GET') ?>
    <?php debug_view_render_table('_post', 'POST') ?>
    <?php debug_view_render_table('_cookie', 'COOKIE') ?>
    <?php debug_view_render_table('_files', 'FILES') ?>
</div>

