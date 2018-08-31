cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_StormWebrtc 
            ./StormWebrtc.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_StormWebrtc 
            ./StormWebrtcDataChannel.h
            ./StormWebrtcConnection.h
            ./StormWebrtc.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_StormWebrtc 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_StormWebrtc 
            )

set(PLATFORM_HEADER_StormWebrtc 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_StormWebrtc 
            )

set(PLATFORM_HEADER_StormWebrtc 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_StormWebrtc 
            )

set(PLATFORM_HEADER_StormWebrtc 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormWebrtc 
            )

set(PLATFORM_HEADER_StormWebrtc 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_StormWebrtc 
            )

set(PLATFORM_HEADER_StormWebrtc 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormWebrtc 
            )

set(PLATFORM_HEADER_StormWebrtc 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_StormWebrtc})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(StormWebrtc ${GENERIC_SRC_StormWebrtc} ${PLATFORM_SRC_StormWebrtc}
            ${GENERIC_HEADER_StormWebrtc} ${PLATFORM_HEADER_StormWebrtc})