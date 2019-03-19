
_http_request_array = [];

function FoundationHandleHttpRequestOpen(index) {
    Module.ccall('HandleHttpRequestConnect', 'null', ['number'], [index]);
}

function FoundationHandleHttpRequestData(index, status_code, body, headers) {

    var body_len = body.data.byteLength;
    var body_ptr = Module._malloc(body_len);
    var body_buffer = new Uint8Array(body.data);
    Module.writeArrayToMemory(body_buffer, body_ptr);
    var header_len = Module.lengthBytesUTF8(headers) + 1;
    var header_ptr = Module._malloc(header_len);
    Module.stringToUTF8(headers, header_ptr, header_len);
    Module.ccall('HandleHttpRequestMessage', 'null', ['number', 'number', 'number', 'number', 'number', 'number'], [index, status_code, body_ptr, body_len, header_ptr, header_len]);
    Module._free(body_ptr);
    Module._free(header_ptr);
}

function FoundationHandleHttpRequestClose(index) {
    Module.ccall('HandleHttpRequestClose', 'null', ['number'], [index]);
}

function FoundationCreateHttpRequest(index, url_ptr, headers_ptr, body_ptr) {

    var url = Module.UTF8ToString(url_ptr);
    var headers = Module.UTF8ToString(headers_ptr);
    var body = Module.UTF8ToString(body_ptr);

    var method = "GET";

    if(body.length > 0) {
        method = "POST";
    }

    while(_http_request_array.length <= index) {
        _http_request_array.push(null);
    }

    _http_request_array[index] = new XMLHttpRequest();
    _http_request_array[index].open(method, url);
    _http_request_array[index].responseType = "arraybuffer";

    var headers_array = headers.split("\n");
    for(var i = 0; i < headers_array.length; i++) {
        var parts = headers_array[i].split(":", 2);
        if(parts.length == 2) {
            _http_request_array[index].setRequestHeader(parts[0], parts[1]);
        }
    }

    _http_request_array[index].onreadystatechange = function(request_index) {

        if(this.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
            FoundationHandleHttpRequestOpen(request_index);
        }

        if(this.readyState === XMLHttpRequest.DONE) {
            var status_code = this.status;
            var headers = this.getAllResponseHeaders();
            var body = this.response;

            FoundationHandleHttpRequestData(request_index, status_code, body, headers);
        }

    }.bind(null, index);

    _http_request_array[index].onerror = function(request_index) {
        FoundationHandleHttpRequestClose(request_index);
    }.bind(null, index);

    _http_request_array[index].send(body);
}

function FoundationDestroyHttpRequest(index) {
    _http_request_array[index].onreadystatechange = null;
    _http_request_array[index].onerror = null;
}
