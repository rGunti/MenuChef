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

/**
 * Source:
 * @param text string
 * @returns {XML|void|string}
 */
function escapeHtml(text) {
    var map = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#039;'
    };

    return text.replace(/[&<>"']/g, function(m) { return map[m]; });
}

/**
 * Displays the Unhandled Error Modal Box along with some given information about the error reported
 * @param errorText string
 */
function showUnhandledError(errorText) {
    $('#unhandledErrorInfo').html(errorText);
    $('#unhandledErrorDialog').modal('show');
}


function limitString(s,max,trim) {
    if (s.length > max) {
        return s.substring(0, max) + trim;
    } else {
        return s;
    }
}
