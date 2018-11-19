cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/.. ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormWebrtc
            StormWebrtc.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_StormWebrtc
            StormWebrtc.h
            StormWebrtcDataChannel.h
            StormWebrtcConnection.h
            #HEADER_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_StormWebrtc
            )

set(PLATFORM_HEADER_StormWebrtc
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_StormWebrtc
            )

set(PLATFORM_HEADER_StormWebrtc
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_StormWebrtc
            )

set(PLATFORM_HEADER_StormWebrtc
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormWebrtc
            )

set(PLATFORM_HEADER_StormWebrtc
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_StormWebrtc
            )

set(PLATFORM_HEADER_StormWebrtc
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormWebrtc
            )

set(PLATFORM_HEADER_StormWebrtc
            )
endif()

add_library(StormWebrtc STATIC ${GENERIC_SRC_StormWebrtc} ${PLATFORM_SRC_StormWebrtc}
            ${GENERIC_HEADER_StormWebrtc} ${PLATFORM_HEADER_StormWebrtc})
