cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../../. ../../../.././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../../.././External/Web)
  set(PLATFORM_SRC_ClangSACheckers 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../../.././External/Windows)
  set(PLATFORM_SRC_ClangSACheckers 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ClangSACheckers 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ClangSACheckers 
            )
endif()

set(GENERIC_SRC_ClangSACheckers 
            )
add_library(ClangSACheckers ${GENERIC_SRC_ClangSACheckers} ${PLATFORM_SRC_ClangSACheckers} )