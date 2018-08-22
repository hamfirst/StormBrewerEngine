cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../../../. ../../../../.././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../../../.././External/Web)
  set(PLATFORM_SRC_SDL-UWP 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../../../.././External/Windows)
  set(PLATFORM_SRC_SDL-UWP 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_SDL-UWP 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../../../../.././External/Android)
  set(PLATFORM_SRC_SDL-UWP 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(../../../../.././External/IOS)
  set(PLATFORM_SRC_SDL-UWP 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_SDL-UWP 
            )
endif()

set(GENERIC_SRC_SDL-UWP 
            )
add_library(SDL-UWP ${GENERIC_SRC_SDL-UWP} ${PLATFORM_SRC_SDL-UWP} )