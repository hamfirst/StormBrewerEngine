cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/.. ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormWebrtcClientAPI
            StormWebrtcClientNative.cpp
            StormWebrtcClient.cpp
            StormWebrtcClientWeb.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_StormWebrtcClientAPI
            StormWebrtcClientTypes.h
            StormWebrtcClientNative.h
            StormWebrtcClientWeb.h
            StormWebrtcClient.h
            #HEADER_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_StormWebrtcClientAPI
            )

set(PLATFORM_HEADER_StormWebrtcClientAPI
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_StormWebrtcClientAPI
            )

set(PLATFORM_HEADER_StormWebrtcClientAPI
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_StormWebrtcClientAPI
            )

set(PLATFORM_HEADER_StormWebrtcClientAPI
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormWebrtcClientAPI
            )

set(PLATFORM_HEADER_StormWebrtcClientAPI
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_StormWebrtcClientAPI
            )

set(PLATFORM_HEADER_StormWebrtcClientAPI
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_StormWebrtcClientAPI
            )

set(PLATFORM_HEADER_StormWebrtcClientAPI
            )
endif()

add_library(StormWebrtcClientAPI STATIC ${GENERIC_SRC_StormWebrtcClientAPI} ${PLATFORM_SRC_StormWebrtcClientAPI}
            ${GENERIC_HEADER_StormWebrtcClientAPI} ${PLATFORM_HEADER_StormWebrtcClientAPI})
