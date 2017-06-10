<?php
require_once __DIR__ . '/modalBase.inc';
?>
<div class="modal fade" tabindex="-1" role="dialog" id="modalEditMealNote">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
                <h4 class="modal-title"><?= t('edit_named', [t('meal_notes')]) ?></h4>
            </div>
            <form id="modalEditMealNote_form">
                <input type="hidden" id="modalEditMealNoteId" value="" />
                <div class="modal-body">
                    <div class="form-group">
                        <label><?= t('meal_notes') ?>*</label>
                        <textarea class="form-control" rows="10"><?= htmlspecialchars($meal->notes) ?></textarea>
                        <p class="help-block"><?= t('meal_notes_markdown') ?></p>
                    </div>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal"><?= t('cancel') ?></button>
                    <button type="submit" class="btn btn-primary"><?= t('edit_named', [t('meal_notes')]) ?></button>
                </div>
            </form>
        </div>
    </div>
</div>
<script>
    $(document).ready(function() {
        var originalMealNoteValue = '';
        $('#modalEditMealNote').on('shown.bs.modal', function() {
            $('#modalEditMealNote textarea').focus();
        });
        $('#modalEditMealNote').on('hidden.bs.modal', function() {
            $('#modalEditMealNote textarea').val(originalMealNoteValue);
        });
        $('#modalEditMealNote_form').submit(function(e) {
            e.preventDefault();
            var mealData = {
                action : 'editMealNote',
                id: $('#modalEditMealNoteId').val(),
                note : $('#modalEditMealNote textarea').val()
            };
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Meal', mealData,
                function() {
                    // Before Send
                    $('#modalEditMealNote button[type=submit]').prop('disabled', true);
                    $('#modalEditMealNote').modal('hide');
                },
                function(data, textStatus, jqXHR) {
                    // Success
                    window.location.reload(true);
                },
                function(jqXHR, textStatus, errorThrown) {
                    // On Error
                    onMealEditorError(jqXHR, textStatus, errorThrown);
                },
                function() { }
            );
        });
        $('#mealEditorEditMealNotesLink').click(function() {
            var mealId = $('#mealEditorEditMealNotesLink').data('id');
            originalMealNoteValue = $('#modalEditMealNote textarea').val();
            $('#modalEditMealNoteId').val(mealId);
            $('#modalEditMealNote').modal('show');
        });
    });
</script>
