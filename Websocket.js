
_websocket_array = [];

function FoundationHandleWebsocketOpen(index) {
    Module.ccall('HandleWebsocketConnect', 'null', ['number'], [index]);
}

function FoundationHandleWebsocketData(index, msg) {
    if(typeof(msg) == 'string') {
        var l = Module.lengthBytesUTF8(msg.data);
        var ptr = Module._malloc(l);
        Module.stringToUTF8(msg.data, ptr, l);
        Module.ccall('HandleWebsocketMessage', 'null', ['number', 'number', 'number', 'number'], [index, ptr, l, 0]);
        Module._free(ptr);
    } else {
        var l = msg.data.byteLength;
        var ptr = Module._malloc(l);
        var buffer = new Uint8Array(msg.data);
        Module.writeArrayToMemory(buffer, ptr);
        Module.ccall('HandleWebsocketMessage', 'null', ['number', 'number', 'number', 'number'], [index, ptr, l, 1]);
        Module._free(ptr);
    }
}

function FoundationHandleWebsocketClose(index) {
    Module.ccall('HandleWebsocketClose', 'null', ['number'], [index]);
}

function FoundationHandleWebsocketSendTextMessage(index, ptr) {
    var str = Module.UTF8ToString(ptr);
    _websocket_array[index].send(str);
}

function FoundationHandleWebsocketSendBinaryMessage(index, ptr, length) {
    var packet = HEAPU8.slice(ptr, ptr + length);
    _websocket_array[index].send(packet);
}

function FoundationCreateWebsocket(index, host_ptr, port, uri_ptr) {

    var host = Module.UTF8ToString(host_ptr);
    var uri = Module.UTF8ToString(uri_ptr);
    var full_url = "ws://" + host + ":" + port + uri;

    while(_websocket_array.length <= index) {
        _websocket_array.push(null);
    }

    _websocket_array[index] = new WebSocket(full_url);
    _websocket_array[index].binaryType = "arraybuffer";
    _websocket_array[index].onopen = function(websocket_index) { FoundationHandleWebsocketOpen(websocket_index); }.bind(null, index);
    _websocket_array[index].onmessage = function(websocket_index, msg) { FoundationHandleWebsocketData(websocket_index, msg); }.bind(null, index);
    _websocket_array[index].onclose = function(websocket_index) { FoundationHandleWebsocketClose(websocket_index); }.bind(null, index);
}

function FoundationDestroyWebsocket(index) {
    _websocket_array[index].onopen = null;
    _websocket_array[index].onmessage = null;
    _websocket_array[index].onclose = null;
    _websocket_array[index].close();
    _websocket_array[index] = null;
}
