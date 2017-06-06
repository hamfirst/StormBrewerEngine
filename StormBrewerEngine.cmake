cmake_minimum_required(VERSION 3.0)

option(WEB "Emscripten Webassembly Build")

SET(CMAKE_CXX_STANDARD 14)

if(WEB)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s WASM=1")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${PROJECT_SOURCE_DIR}/Test/Assets@/")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Websocket.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s EXPORTED_FUNCTIONS=\"['_main','_HandleWebsocketConnect','_HandleWebsocketMessage','_HandleWebsocketClose']\"")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s TOTAL_MEMORY=134217728")
elseif(MSVC)
  add_definitions(-DUNICODE -D_UNICODE)
endif()

add_subdirectory(External)
add_subdirectory(External/binpack)
add_subdirectory(External/lua)
add_subdirectory(External/gl3w)
add_subdirectory(External/ogg)
add_subdirectory(External/upng)
add_subdirectory(External/vorbis)

if(WEB)
    add_subdirectory(External/Web/freetype2)
else()
  add_subdirectory(External/enet)
  
  if (MSVC)
    add_subdirectory(External/Windows/SDL2)
    add_subdirectory(External/Windows/freetype2)
  endif()

  add_subdirectory(External/asio)
  
  add_subdirectory(EngineStubs)
  add_subdirectory(StormSockets)
endif()

add_subdirectory(Engine)
add_subdirectory(Runtime)
add_subdirectory(Shared)
add_subdirectory(Foundation)
add_subdirectory(StormData)
add_subdirectory(StormNet)


