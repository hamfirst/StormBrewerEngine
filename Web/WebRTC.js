
var _webrtc_array = [];

var _webrtc_sdp_part1 = 
"v=0\n" +
"o=- 0 2 IN IP4 0.0.0.0\n" +
"s=-\n" +
"t=0 0\n";

var _webrtc_sdp_part2 = 
"a=ice-options:trickle\n" +
"a=msid-semantic: WMS *\n" +
"m=application 9 DTLS/SCTP 5000\n" +
"c=IN IP4 0.0.0.0\n" +
"a=sendrecv\n" +
"a=ice-ufrag:7GEO\n" +
"a=ice-pwd:3S0OeHDz16aoWRK4tnALIsebH4nk9olF\n" +
"a=sctpmap:5000 webrtc-datachannel 256\n" +
"a=setup:passive\n";

function StormWebrtcOpen(index) {
    Module.ccall('HandleStormWebrtcConnect', 'null', ['number'], [index]);
}

function StormWebrtcData(sender_channel, index, stream_index, msg) {
    if(typeof(msg) == 'string') {
        var l = Module.lengthBytesUTF8(msg.data);
        var ptr = Module._malloc(l);
        Module.stringToUTF8(msg.data, ptr, l);
        Module.ccall('HandleStormWebrtcMessage', 'null', ['number', 'number', 'number', 'number', 'number'], [index, stream_index, sender_channel, ptr, l]);
    } else {
        var len = msg.byteLength;
        var ptr = Module._malloc(len);
        var buffer = new Uint8Array(msg);

        //Module.print("JS MSG - " + msg + " " + index + " " + stream_index + " " + sender_channel + " " + ptr + " " + len);

        Module.writeArrayToMemory(buffer, ptr);
        Module.ccall('HandleStormWebrtcMessage', 'null', ['number', 'number', 'number', 'number', 'number'], [index, stream_index, sender_channel, ptr, len]);
    }
}

function StormWebrtcSendBinaryMessage(index, stream, sender_channel, ptr, length) {
    var packet = HEAPU8.slice(ptr, ptr + length);

    if(sender_channel == 0) {
        _webrtc_array[index].out_channels[stream].send(packet);
    } else {
        _webrtc_array[index].inc_channels[stream].send(packet);
    }
}

function StormWebrtcCheckConnected(index) {
    if(_webrtc_array[index].connected) {
        return;
    }

    for(var stream = 0; stream < _webrtc_array[index].inc_seqs.length; stream++) {
        if(_webrtc_array[index].inc_seqs[stream] == -1) {
            return;
        }
    }

    for(var stream = 0; stream < _webrtc_array[index].out_seqs.length; stream++) {
        if(_webrtc_array[index].out_seqs[stream] == -1) {
            return;
        }
    } 

    _webrtc_array[index].connected = true;
    
    Module.ccall('HandleStormWebrtcConnect', 'null', ['number'], [index]);
}

function StormWebrtcCheckDisconnect(index) {
    if(_webrtc_array[index].connected && _webrtc_array[index].dead == false) {
        Module.ccall('HandleStormWebrtcDisconnect', 'null', ['number'], [index]);
        _webrtc_array[index].connected = false;
    }    
}

function StormWebrtcHandleConnectionError(webrtc_index, reason) {
    Module.print("Connection failure (" + webrtc_index + "): " + reason + "\n");
}

function StormWebrtcCreateConnection(index, ipaddr_ptr, fingerprint_ptr, port, inc_types_ptr, inc_types_len, out_types_ptr, out_types_len) {

    var ipaddr = Module.UTF8ToString(ipaddr_ptr);
    var fingerprint = Module.UTF8ToString(fingerprint_ptr);

    Module.print("Connecting to server " + ipaddr + ":" + port + "\n");
    Module.print("Fingerprint " + fingerprint + "\n");

    while(_webrtc_array.length <= index) {
        _webrtc_array.push(null);
    }

    _webrtc_array[index] = {};
    _webrtc_array[index].connection = new RTCPeerConnection();
    _webrtc_array[index].connected = false;
    _webrtc_array[index].dead = false;
    _webrtc_array[index].inc_types = HEAPU8.slice(inc_types_ptr, inc_types_ptr + inc_types_len);
    _webrtc_array[index].out_types = HEAPU8.slice(out_types_ptr, out_types_ptr + out_types_len);

    _webrtc_array[index].inc_seqs = [];
    _webrtc_array[index].inc_channels = [];
    for(var stream = 0; stream < inc_types_len; stream++) {
        _webrtc_array[index].inc_seqs.push(-1);
        _webrtc_array[index].inc_channels.push(null);
    }

    _webrtc_array[index].out_seqs = [];
    _webrtc_array[index].out_channels = [];
    for(var stream = 0; stream < out_types_len; stream++) {
        _webrtc_array[index].out_seqs.push(-1);

        var channel_options = {};
        channel_options.id = stream * 2;

        if(_webrtc_array[index].out_types[stream] == 0) {
            channel_options.ordered = true;
        } else {
            channel_options.ordered = false;            
        }

        var out_channel = _webrtc_array[index].connection.createDataChannel(stream, channel_options);
        out_channel.onopen = function(webrtc_index, stream_index, event) {
            _webrtc_array[webrtc_index].out_seqs[stream_index] = 0;
            StormWebrtcCheckConnected(webrtc_index);
        }.bind(null, index, stream);

        out_channel.onclose = function(webrtc_index, event) {
            StormWebrtcCheckDisconnect(webrtc_index);
        }.bind(null, index);

        out_channel.onmessage = function(webrtc_index, stream_index, event) {
            StormWebrtcData(1, webrtc_index, stream_index, event.data);
        }.bind(null, index, stream);

        out_channel.binaryType = "arraybuffer";

        _webrtc_array[index].out_channels.push(out_channel);
    }

    _webrtc_array[index].connection.ondatachannel = function(webrtc_index, event) {
        var channel = event.channel;
        channel.binaryType = "arraybuffer";

        var stream_index = Math.floor(channel.id / 2);
        _webrtc_array[webrtc_index].inc_channels[stream_index] = channel;
        _webrtc_array[webrtc_index].inc_channels[stream_index].onopen = function(webrtc_index, stream_index) {
            _webrtc_array[webrtc_index].inc_seqs[stream_index] = 0;

            _webrtc_array[webrtc_index].inc_channels[stream_index].onmessage = function(event) {
                StormWebrtcData(0, webrtc_index, stream_index, event.data);
            }

            StormWebrtcCheckConnected(webrtc_index);
        }.bind(null, webrtc_index, stream_index); 
    }.bind(null, index); 

    _webrtc_array[index].connection.onconnectionstatechange = function(webrtc_index, event) {
        if(_webrtc_array[webrtc_index].connectionState == "disconnected") {
            if(_webrtc_array[webrtc_index].dead == false)
            {
                Module.ccall('HandleStormWebrtcDisconnect', 'null', ['number'], [index]);
                _webrtc_array[webrtc_index].connected = false;
            }
        }
    }.bind(null, index); 
 
    _webrtc_array[index].connection.createOffer().then(function(webrtc_index, offer) { 
        var lines = offer.sdp.split('\n');
        for(var index = 0; index < lines.length; index++) {
            if(lines[index].substr(0, 10) == "a=ice-pwd:") {
                lines[index] = "a=ice-pwd:3S0OeHDz16aoWRK4tnALIsebH4nk9olF";
            }
        }

        offer.sdp = lines.join("\n");
        Module.print("Setting local offer:\n"+ offer.sdp + "\n");

        _webrtc_array[webrtc_index].connection.setLocalDescription(offer).then(function(webrtc_index) {

            var sdp = _webrtc_sdp_part1 + "a=fingerprint:sha-256 " + fingerprint + "\n";

            var lines = offer.sdp.split('\n');
            var sdpmid = "data";
            var sdpgroup = "a=group:BUNDLE ";

            for(var index = 0; index < lines.length; index++) {
                if(lines[index].substr(0, 6) == "a=mid:") {
                    sdpmid = lines[index].substr(6).trim();
                }
            }

            sdp += sdpgroup + sdpmid + "\n";
            sdp += _webrtc_sdp_part2;
            sdp += "a=mid:" + sdpmid + "\n";

            var desc = {'sdp': sdp, 'type': 'answer'};

            Module.print("Setting remote offer:\n"+ sdp + "\n");
            _webrtc_array[webrtc_index].connection.setRemoteDescription(desc).then(function(webrtc_index, sdpmid) {
                var ice_candidate = {
                    'candidate': "a=candidate:0 1 UDP 1 "+ipaddr+" "+port+" typ host",
                    'sdpMid': sdpmid,
                    'sdpMLineIndex': 0
                };

                Module.print("Adding ice candidate:\n"+ JSON.stringify(ice_candidate) + "\n");

                _webrtc_array[webrtc_index].connection.addIceCandidate(new RTCIceCandidate(ice_candidate)).then(function() {
                    Module.print("Ice candidate successfully added\n");
                }, StormWebrtcHandleConnectionError.bind(webrtc_index));
            }.bind(null, webrtc_index, sdpmid), StormWebrtcHandleConnectionError.bind(webrtc_index));
        }.bind(null, webrtc_index), StormWebrtcHandleConnectionError.bind(webrtc_index));
    }.bind(null, index), StormWebrtcHandleConnectionError.bind(index));
}

function StormWebrtcDestroyConnection(index) {
    _webrtc_array[index].dead = true;
    _webrtc_array[index].connection.ondatachannel = null;
    _webrtc_array[index].connection.onconnectionstatechange = null;
    _webrtc_array[index].connection.close();

    for(var i = 0; i < _webrtc_array[index].inc_channels.length; ++i) {
        if(_webrtc_array[index].inc_channels[i] != null) {
            _webrtc_array[index].inc_channels[i].onopen = null;
            _webrtc_array[index].inc_channels[i].onmessage = null;
            _webrtc_array[index].inc_channels[i].onclose = null;
        }
    }

    for(var i = 0; i < _webrtc_array[index].out_channels.length; ++i) {
        if(_webrtc_array[index].out_channels[i] != null) {
            _webrtc_array[index].out_channels[i].onopen = null;
            _webrtc_array[index].out_channels[i].onmessage = null;
            _webrtc_array[index].out_channels[i].onclose = null;
        }
    }

    _webrtc_array[index] = null;
}
