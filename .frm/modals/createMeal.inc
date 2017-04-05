<?php
require_once __DIR__ . '/modalBase.inc';
MODAL_createSimpleDialog(
    'modalCreateMealSuccess',
    t('create_meal'),
    t('modal_create_meal_success'),
    t('close'),
    t('open_in', [t('meal_editor')])
);
?>
<div class="modal fade" tabindex="-1" role="dialog" id="modalCreateMeal">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
                <h4 class="modal-title"><?= t('create_meal') ?></h4>
            </div>
            <form id="modalCreateMeal_form">
                <div class="modal-body">
                    <div class="form-group">
                        <label><?= t('meal_name') ?>*</label>
                        <input type="text" class="form-control createmeal-name" placeholder="<?= htmlspecialchars(t('meal_name')) ?>" required>
                    </div>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal"><?= t('cancel') ?></button>
                    <button type="submit" class="btn btn-primary"><?= t('create_meal') ?></button>
                </div>
            </form>
        </div>
    </div>
</div>
<script>
    $(document).ready(function() {
        function validateCreateMealInput(data) {
            var isValid = true;
            $('#modalCreateMeal div.form-group').removeClass('has-error');
            if (!data.name || data.name.trim().length === 0) {
                isValid = false;
                $('#modalCreateMeal input.createmeal-name').parent().addClass('has-error');
            }
            return isValid;
        }
        $('#modalCreateMeal').on('shown.bs.modal', function() {
            $('#modalCreateMeal input[type=text]:first').focus();
        });
        $('#modalCreateMeal').on('hidden.bs.modal', function() {
            $('#modalCreateMeal input[type=text]').val('');
            $('#modalCreateMeal div.form-group').removeClass('has-error');
        });
        $('#modalCreateMeal_form').submit(function(e) {
            e.preventDefault();
            var mealData = {
                action : 'createMeal',
                name : $('#modalCreateMeal input.createmeal-name').val()
            };
            if (!validateCreateMealInput(mealData)) {
                return;
            }
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Meal', mealData,
                function() {
                    // Before Send
                    $('#modalCreateMeal button[type=submit]').prop('disabled', true);
                },
                function(data, textStatus, jqXHR) {
                    // Success
                    $('#modalCreateMealSuccess').data('meal-id', data.mealID);
                    $('#modalCreateMealSuccess').modal('show');
                    reloadMealTable();
                },
                onErrorAutoHandle,
                function(jqXHR, textStatus) {
                    // Complete
                    $('#modalCreateMeal button[type=submit]').prop('disabled', true);
                    $('#modalCreateMeal').modal('hide');
                }
            );
        });
        $('#modalCreateMealSuccess_form').submit(function(e) {
            e.preventDefault();
            var newMealID = $('#modalCreateMealSuccess').data('meal-id');
            window.location.href = '<?= PathUtils::getLink('/Meal/') ?>' + newMealID + '/Editor';
        });
    });
</script>
