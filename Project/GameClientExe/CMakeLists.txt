cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameClientExe 
            Main.cpp
            )

set(GENERIC_HEADER_GameClientExe 
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_GameClientExe 
            )

set(PLATFORM_HEADER_GameClientExe 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_GameClientExe 
            )

set(PLATFORM_HEADER_GameClientExe 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_GameClientExe 
            )

set(PLATFORM_HEADER_GameClientExe 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClientExe 
            )

set(PLATFORM_HEADER_GameClientExe 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_GameClientExe 
            )

set(PLATFORM_HEADER_GameClientExe 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClientExe 
            )

set(PLATFORM_HEADER_GameClientExe 
            )
endif()


add_library(GameClientExe STATIC ${GENERIC_SRC_GameClientExe} ${PLATFORM_SRC_GameClientExe}
            ${GENERIC_HEADER_GameClientExe} ${PLATFORM_HEADER_GameClientExe})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameClientExe} ${PLATFORM_SRC_GameClientExe}
            ${GENERIC_HEADER_GameClientExe} ${PLATFORM_HEADER_GameClientExe})

