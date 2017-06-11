<?php
require_once __DIR__ . '/modalBase.inc';

MODAL_createSimpleDialog(
    'modalDeleteLinkedMeal',
    t('modal_delete_linked_meal'),
    t('modal_delete_linked_meal_question', [
        '<span class="modal-variable delete-meal-link-name">_</span>'
    ]),
    t('no'), t('yes')
);
?>
<script>
    $('#modalDeleteLinkedMeal').on('show.bs.modal', function(event) {
        var button = $(event.relatedTarget);
        var mealID = button.data('id');
        var mealName = button.data('meal-name');
        var modal = $(this);
        modal.find('.delete-meal-link-name').html(mealName);
        modal.find('.hidden-data-id').val(mealID);
    });
    $(document).ready(function() {
        $('#modalDeleteLinkedMeal .modal-header').addClass('bg-warning');
        $('#modalDeleteLinkedMeal button[type=submit]').addClass('btn-warning');
        $('#modalDeleteLinkedMeal_form').submit(function (e) {
            e.preventDefault();
            var mealID = $('#modalDeleteLinkedMeal_data-id').val();
            submitSimplePostRequest(AJAX_BASE_PATH + '/AJAX/LinkedMeal', { id: mealID, action: 'deleteLinkedMeal' },
                function() {
                    // Before Send
                    $('#modalDeleteLinkedMeal button[type=submit]').prop('disabled', true);
                },
                reloadLinkedMealListsOnSuccess,
                onErrorAutoHandle,
                function() {
                    $('#modalDeleteLinkedMeal button[type=submit]').prop('disabled',false);
                    $('#modalDeleteLinkedMeal').modal('hide');
                }
            );
        });
    });
</script>
