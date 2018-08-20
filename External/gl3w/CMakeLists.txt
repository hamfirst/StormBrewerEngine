cmake_minimum_required(VERSION 3.0)

include_directories(. ../../. ../.././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_gl3w 
            ./gl3w.c
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_gl3w 
            ./gl3w.h
            ./glcorearb.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_gl3w 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../.././External/Windows)
  set(PLATFORM_SRC_gl3w 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(../.././External/Web)
  set(PLATFORM_SRC_gl3w 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(../.././External/IOS)
  set(PLATFORM_SRC_gl3w 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(../.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_gl3w 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../.././External/Android)
  set(PLATFORM_SRC_gl3w 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(../.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_gl3w 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE gl3w ${GENERIC_REFL_gl3w} ${PLATFORM_REFL_gl3w})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../../. -I../.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(gl3w ${GENERIC_SRC_gl3w} ${PLATFORM_SRC_gl3w}
            gl3w ${GENERIC_HEADER_gl3w} ${PLATFORM_HEADER_gl3w})