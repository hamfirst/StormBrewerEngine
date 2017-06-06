cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../. ../../.././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../.././External/Web)
  set(PLATFORM_SRC_ClangAttrClasses 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../.././External/Windows)
  set(PLATFORM_SRC_ClangAttrClasses 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ClangAttrClasses 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ClangAttrClasses 
            )
endif()

set(GENERIC_SRC_ClangAttrClasses 
            )
add_library(ClangAttrClasses ${GENERIC_SRC_ClangAttrClasses} ${PLATFORM_SRC_ClangAttrClasses} )