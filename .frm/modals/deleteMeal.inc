<?php
require_once __DIR__ . '/modalBase.inc';

MODAL_createSimpleDialog(
    'modalDeleteMeal',
    t('delete_meal'),
    t('modal_delete_meal_question', ['<span class="modal-variable">' . htmlspecialchars($meal->name) . '</span>']),
    t('cancel'),
    t('delete')
);
?>
<script>
    $(document).ready(function() {
        $('#modalDeleteMeal .modal-header').addClass('bg-danger');
        $('#modalDeleteMeal button[type=submit]').addClass('btn-danger');
        $('#modalDeleteMeal_data-id').val(<?= $meal->id ?>);

        $('#modalDeleteMeal_form').submit(function(e) {
            e.preventDefault();
            var mealData = {
                action : 'deleteMeal',
                id : $('#modalDeleteMeal_data-id').val()
            };
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/Meal', mealData,
                function() {
                    // Before Send
                    $('#modalDeleteMeal button[type=submit]').prop('disabled', true);
                },
                function(data, textStatus, jqXHR) {
                    // On Success
                    window.location.href = '<?= PathUtils::getLink('/Meal') ?>';
                },
                onErrorAutoHandle,
                function(jqXHR, textStatus) {
                    // Complete
                    $('#modalDeleteMeal button[type=submit]').prop('disabled', false);
                    $('#modalDeleteMeal').modal('hide');
                }
            );
        });
    });
</script>
