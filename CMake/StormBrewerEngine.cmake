cmake_minimum_required(VERSION 3.0)

include(CMakeDependentOption)

option(WEB "Emscripten Webassembly Build" OFF)
option(BUILD_CLIENT "Build Client" ON)
CMAKE_DEPENDENT_OPTION(BUILD_TOOLS "Build Client" ON "NOT WEB AND NOT ANDROID AND NOT IOS" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_SERVER "Build Server" ON "NOT WEB AND NOT ANDROID AND NOT IOS" OFF)

include_directories("${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/Tools")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_DEBUG_POSTFIX "")

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

if(WEB)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${PROJECT_SOURCE_DIR}/FinalAssets@/")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Web/WebRTC.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Web/Websocket.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --post-js ${PROJECT_SOURCE_DIR}/Web/Audio.js")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s EXPORTED_FUNCTIONS=\"['_main','_HandleStormWebrtcConnect','_HandleStormWebrtcMessage','_HandleStormWebrtcDisconnect','_HandleWebsocketConnect','_HandleWebsocketMessage','_HandleWebsocketClose','_HandleMusicLoaded','_HandleMusicLoadFailed','_HandleMusicFinished','_SetAccountName']\"")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s TOTAL_MEMORY=134217728 -s LINKABLE=1")
  
elseif(MSVC)
  add_definitions(-DUNICODE -D_UNICODE)

elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pragma-once-outside-header")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/External")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/binpack")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/lua")


if(BUILD_CLIENT OR BUILD_TOOLS)
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/gl3w")
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/ogg")
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/lodepng")
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/vorbis")
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/resample")
  add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/Engine")
  
  if (MSVC)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/Windows/SDL_build")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/Windows/freetype2")
  endif()
  
  if(ANDROID)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/Android/SDL_build")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/Android/freetype2")
  endif()

  if(IOS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/IOS/SDL_build")
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/IOS/freetype2")
  endif()

  if(UNIX AND NOT APPLE)
    add_subdirectory("${PROJECT_SOURCE_DIR}/External/Linux/SDL_build")
  endif()
endif()

if(WEB)
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/Web/freetype2")
  add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtcClientAPI")
  
else()
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/enet")
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/usrsctplib")
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/mbedtls")

  add_subdirectory("${PROJECT_SOURCE_DIR}/External/asio")
  
  add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/EngineStubs")
  add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/HurricanDDS")  
  add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormSockets")  
  add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtc")
  add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtcServerAPI")
  add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtcClientAPI")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/Foundation")
add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/Runtime")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormData")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormNet")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormNetCustomBindings")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormExpr")

if(BUILD_TOOLS)
  add_subdirectory("${PROJECT_SOURCE_DIR}/External/libgit2")
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/Wizards/TemplateLib")
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/Wizards/addcode")
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/DocumentServer")
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/QTUtil")
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/Editor")
endif()

