
if (MSVC)
    add_definitions(-D_WINDOWS)
endif()

if (WEB)
    add_definitions(-D_WEB)
endif()

if (IOS)
    add_definitions(-D_IOS)
endif()

if (APPLE AND NOT IOS)
    add_definitions(-D_MACOS)
endif()

if (ANDROID)
    add_definitions(-D_ANDROID)
endif()

if (UNIX AND NOT APPLE)
    add_definitions(-D_LINUX)
endif()

if (DEVELOPMENT_BUILD)
    add_definitions(-D_DEV_BUILD)
endif()

if(WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${PROJECT_SOURCE_DIR}/FinalAssets@/")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Web/WebRTC.js")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Web/Websocket.js")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Web/Audio.js")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s EXPORTED_FUNCTIONS=\"['_main','_HandleStormWebrtcConnect','_HandleStormWebrtcMessage','_HandleStormWebrtcDisconnect','_HandleHttpRequestConnect','_HandleHttpRequestMessage','_HandleHttpRequestClose','_HandleWebsocketConnect','_HandleWebsocketMessage','_HandleWebsocketClose','_HandleMusicLoaded','_HandleMusicLoadFailed','_HandleMusicFinished','_SetLoginToken']\"")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s TOTAL_MEMORY=134217728 -s LINKABLE=1")

elseif(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
    add_definitions(-D_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING)
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pragma-once-outside-header")
endif()
