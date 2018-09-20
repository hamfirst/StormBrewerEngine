cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameServer 
            GameClientConnection.cpp
            GameInstance.cpp
            GameInstanceManager.cpp
            GameInstanceStateData.cpp
            GameInstanceStateGameplay.cpp
            GameInstanceStateLoading.cpp
            GameInstanceStateStaging.cpp
            GameServer.cpp
            GameServerGlobalResources.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_GameServer 
            GameClientConnection.h
            GameInstance.h
            GameInstanceManager.h
            GameInstanceStateBase.h
            GameInstanceStateData.h
            GameInstanceStateGameplay.h
            GameInstanceStateLoading.h
            GameInstanceStateStaging.h
            GameServer.h
            GameServerGlobalResources.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_GameServer 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_GameServer 
            )

set(PLATFORM_HEADER_GameServer 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_GameServer 
            )

set(PLATFORM_HEADER_GameServer 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_GameServer 
            )

set(PLATFORM_HEADER_GameServer 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameServer 
            )

set(PLATFORM_HEADER_GameServer 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_GameServer 
            )

set(PLATFORM_HEADER_GameServer 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameServer 
            )

set(PLATFORM_HEADER_GameServer 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_GameServer})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(GameServer STATIC ${GENERIC_SRC_GameServer} ${PLATFORM_SRC_GameServer}
            ${GENERIC_HEADER_GameServer} ${PLATFORM_HEADER_GameServer})