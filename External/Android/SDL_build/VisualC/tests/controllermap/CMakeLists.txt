cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../../../../. ../../../../../.././External)
set(CMAKE_CXX_STANDARD 17)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../../../../.././External/Web)
  set(PLATFORM_SRC_controllermap 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../../../../.././External/Windows)
  set(PLATFORM_SRC_controllermap 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_controllermap 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../../../../../.././External/Android)
  set(PLATFORM_SRC_controllermap 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(../../../../../.././External/IOS)
  set(PLATFORM_SRC_controllermap 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_controllermap 
            )
endif()

set(GENERIC_SRC_controllermap 
            )
add_library(controllermap ${GENERIC_SRC_controllermap} ${PLATFORM_SRC_controllermap} )