cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../. ../../.././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../.././External/Web)
  set(PLATFORM_SRC_ClangAttrPCHRead 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../.././External/Windows)
  set(PLATFORM_SRC_ClangAttrPCHRead 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(../../.././External/IOS)
  set(PLATFORM_SRC_ClangAttrPCHRead 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ClangAttrPCHRead 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../../.././External/Android)
  set(PLATFORM_SRC_ClangAttrPCHRead 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ClangAttrPCHRead 
            )
endif()

set(GENERIC_SRC_ClangAttrPCHRead 
            )
add_library(ClangAttrPCHRead ${GENERIC_SRC_ClangAttrPCHRead} ${PLATFORM_SRC_ClangAttrPCHRead} )