cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../../../. ../../../../.././External)
set(CMAKE_CXX_STANDARD 17)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../../../.././External/Web)
  set(PLATFORM_SRC_SDL-WinPhone80 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../../../.././External/Windows)
  set(PLATFORM_SRC_SDL-WinPhone80 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_SDL-WinPhone80 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../../../../.././External/Android)
  set(PLATFORM_SRC_SDL-WinPhone80 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(../../../../.././External/IOS)
  set(PLATFORM_SRC_SDL-WinPhone80 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_SDL-WinPhone80 
            )
endif()

set(GENERIC_SRC_SDL-WinPhone80 
            )
add_library(SDL-WinPhone80 ${GENERIC_SRC_SDL-WinPhone80} ${PLATFORM_SRC_SDL-WinPhone80} )