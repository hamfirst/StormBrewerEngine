cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_GameServer 
            ./GameClient.cpp
            ./GameClientConnection.cpp
            ./GameInstance.cpp
            ./GameInstanceManager.cpp
            ./GameInstanceStateData.cpp
            ./GameInstanceStateGameplay.cpp
            ./GameInstanceStateLoading.cpp
            ./GameInstanceStateStaging.cpp
            ./GameServer.cpp
            ./GameServerGlobalResources.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_GameServer 
            ./GameClientConnection.h
            ./GameInstance.h
            ./GameInstanceManager.h
            ./GameInstanceStateBase.h
            ./GameInstanceStateData.h
            ./GameInstanceStateGameplay.h
            ./GameInstanceStateLoading.h
            ./GameInstanceStateStaging.h
            ./GameServer.h
            ./GameServerGlobalResources.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_GameServer 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_GameServer 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_GameServer 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_GameServer 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameServer 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_GameServer 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameServer 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE GameServer ${GENERIC_REFL_GameServer} ${PLATFORM_REFL_GameServer})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(GameServer ${GENERIC_SRC_GameServer} ${PLATFORM_SRC_GameServer}
            GameServer ${GENERIC_HEADER_GameServer} ${PLATFORM_HEADER_GameServer})