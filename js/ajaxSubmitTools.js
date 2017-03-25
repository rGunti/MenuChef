
function onAjaxError(jqXHR, textStatus, errorThrown) {
    console.log(this, jqXHR, textStatus, errorThrown);

    var errorText = '';
    if (jqXHR.status == 404) {
        errorText += 'Error 404: The requested resource could not be found.\n';
        errorText += 'Resource Requested: ' + this.url;
    } else {
        errorText += 'HTTP Error:         ' + jqXHR.status + ' ' + errorThrown + '\n';
        errorText += 'Resource Requested: ' + this.url + '\n';
        errorText += 'Method Requested:   ' + this.method + '\n';
        errorText += 'Data Transmitted:   ' + this.data + '\n';
        errorText += '\n';
        if (jqXHR.responseJSON) {
            errorText += 'Sever provided information:\n';
            if (typeof jqXHR.responseJSON.ErrorInfo == 'string') {
                errorText += jqXHR.responseJSON.ErrorInfo;
            } else {
                errorText += JSON.stringify(jqXHR.responseJSON.ErrorInfo, '   ');
            }
        } else {
            errorText += 'No additional information is available.\nThis is the first part of the response:\n\n';
            errorText += 'Total Size of response: ~ ' + jqXHR.responseText.length + ' bytes';
            errorText += '\n --- START OF RESPONSE --- \n';
            errorText += escapeHtml(limitString(jqXHR.responseText, 512, '\n -[ trimmed after 512 bytes ]-'));
            errorText += '\n --- END OF RESPONSE --- ';
        }
    }

    showUnhandledError(errorText);
}

function submitSimplePostRequest(_url,_data,onBeforeSend,onSuccess,onError,onComplete) {
    $.ajax({
        url: _url + '?lang=' + Cookies.get('ForcedLanguage'),
        method: 'post',
        data: _data,
        beforeSend: onBeforeSend,
        success: onSuccess,
        error: (onError == null) ? onAjaxError : onError,
        complete: onComplete
    });
}
