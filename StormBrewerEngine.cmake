cmake_minimum_required(VERSION 3.0)

include(CMakeDependentOption)

option(WEB "Emscripten Webassembly Build" OFF)
option(BUILD_CLIENT "Build Client" ON)
CMAKE_DEPENDENT_OPTION(BUILD_SERVER "Build Server" ON "NOT WEB AND NOT ANDROID" OFF)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_DEBUG_POSTFIX "")

if(WEB)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${PROJECT_SOURCE_DIR}/FinalAssets@/")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/WebRTC.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Websocket.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Audio.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s EXPORTED_FUNCTIONS=\"['_main','_HandleStormWebrtcConnect','_HandleStormWebrtcMessage','_HandleStormWebrtcDisconnect','_HandleWebsocketConnect','_HandleWebsocketMessage','_HandleWebsocketClose','_HandleMusicLoaded','_HandleMusicLoadFailed','_HandleMusicFinished','_SetAccountName']\"")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s TOTAL_MEMORY=134217728 -s LINKABLE=1")
  
elseif(MSVC)
  add_definitions(-DUNICODE -D_UNICODE)
endif()

add_subdirectory(External)
add_subdirectory(External/binpack)
add_subdirectory(External/lua)

if(BUILD_CLIENT)
  add_subdirectory(External/gl3w)
  add_subdirectory(External/ogg)
  add_subdirectory(External/lodepng)
  add_subdirectory(External/vorbis)
  add_subdirectory(External/resample)
  add_subdirectory(Engine)
  
  if (MSVC)
    add_subdirectory(External/Windows/SDL2)
    add_subdirectory(External/Windows/freetype2)
  endif()
  
  if(ANDROID)
    add_subdirectory(External/Android/SDL_build)
    add_subdirectory(External/Android/freetype2)
  endif()
endif()

if(WEB)
  add_subdirectory(External/Web/freetype2)
  add_subdirectory(StormWebrtcClientAPI)
  
else()
  add_subdirectory(External/enet)
  add_subdirectory(External/usrsctplib)
  add_subdirectory(External/mbedtls)

  add_subdirectory(External/asio)
  
  add_subdirectory(EngineStubs)
  add_subdirectory(StormSockets)  
  add_subdirectory(StormWebrtc)
  add_subdirectory(StormWebrtcServerAPI)
  add_subdirectory(StormWebrtcClientAPI)
endif()

add_subdirectory(Runtime)
add_subdirectory(Foundation)
add_subdirectory(StormData)
add_subdirectory(StormNet)
add_subdirectory(StormNetCustomBindings)
add_subdirectory(StormExpr)


