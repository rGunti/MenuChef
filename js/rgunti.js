/**
 * Returns a glyphicon span with a checkmark if the given parameter is true
 * @param is_true bool
 * @returns {*}
 */
function getHtmlCheckbox(is_true) {
    if (is_true) {
        return '<span class="glyphicon glyphicon-ok"></span>';
    } else {
        return '';
    }
}
