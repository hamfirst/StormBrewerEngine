cmake_minimum_required(VERSION 3.20.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_gl3w 
            gl3w.c
            )

set(GENERIC_HEADER_gl3w 
            gl3w.h
            glcorearb.h
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_gl3w 
            )

set(PLATFORM_HEADER_gl3w 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_gl3w 
            )

set(PLATFORM_HEADER_gl3w 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_gl3w 
            )

set(PLATFORM_HEADER_gl3w 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_gl3w 
            )

set(PLATFORM_HEADER_gl3w 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_gl3w 
            )

set(PLATFORM_HEADER_gl3w 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_gl3w 
            )

set(PLATFORM_HEADER_gl3w 
            )
endif()


add_library(gl3w STATIC ${GENERIC_SRC_gl3w} ${PLATFORM_SRC_gl3w}
            ${GENERIC_HEADER_gl3w} ${PLATFORM_HEADER_gl3w})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_gl3w} ${PLATFORM_SRC_gl3w}
            ${GENERIC_HEADER_gl3w} ${PLATFORM_HEADER_gl3w})

