
var music_elems = [];
var playback_elems = [];

function LoadMusic(data_ptr, length, music_id) {
    while(music_elems.length <= music_id) {
        music_elems.push(null);
    }

    music_elems[music_id] = [null, null];

    var data = HEAPU8.slice(data_ptr, data_ptr + length);
    console.log("Decoding music of length " + length)

    var buffer = SDL2.audioContext.decodeAudioData(data.buffer).then(function(decoded_data) {        
        music_elems[music_id] = decoded_data;
        console.log("Music decode succeeded");
        Module.ccall('HandleMusicLoaded', 'null', ['number'], [music_id]);
    }, function(reason) {
        console.log("Music decode failed");
        Module.ccall('HandleMusicLoadFailed', 'null', ['number'], [music_id]);
    });

    music_elems[music_id] = buffer;
}

function UnloadMusic(music_id) {
    music_elems[music_id] = null;
}

function PlayMusic(music_id, playback_id, looping, volume, pan) {
    while(playback_elems.length <= playback_id) {
        playback_elems.push(null);
    }

    var source = SDL2.audioContext.createBufferSource();
    var gain_node = SDL2.audioContext.createGain();
    var pan_node = SDL2.audioContext.createStereoPanner();

    source.buffer = music_elems[music_id];
    source.loop = looping;
    source.connect(gain_node);
    gain_node.connect(pan_node);
    gain_node.gain.value = volume;
    pan_node.connect(SDL2.audioContext.destination);
    pan_node.pan.value = pan;

    if(looping == false) {
        source.onended = function(event) {
            Module.ccall('HandleMusicFinished', 'null', ['number'], [playback_id]);
        }
    }

    source.start();

    playback_elems[playback_id] = [source, gain_node, pan_node];
}

function StopMusic(playback_id) {
    playback_elems[playback_id][0].stop();
    playback_elems[playback_id] = null;
}

function SetMusicVolume(playback_id, volume) {
    playback_elems[playback_id][1].gain.value = volume;
}

function SetMusicPan(playback_id, pan) {
    playback_elems[playback_id][2].pan.value = pan;
}
