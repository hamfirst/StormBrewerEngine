cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../../../../. ../../../../../.././External)
set(CMAKE_CXX_STANDARD 17)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../../../../.././External/Web)
  set(PLATFORM_SRC_testatomic 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../../../../.././External/Windows)
  set(PLATFORM_SRC_testatomic 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_testatomic 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../../../../../.././External/Android)
  set(PLATFORM_SRC_testatomic 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(../../../../../.././External/IOS)
  set(PLATFORM_SRC_testatomic 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_testatomic 
            )
endif()

set(GENERIC_SRC_testatomic 
            )
add_library(testatomic ${GENERIC_SRC_testatomic} ${PLATFORM_SRC_testatomic} )