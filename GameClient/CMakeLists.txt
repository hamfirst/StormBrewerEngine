cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_GameClient 
            ./GameClientSystems.cpp
            ./GameClientInstanceContainer.cpp
            ./GameModeLocalMultiplayer.cpp
            ./GameModeLogo.cpp
            ./GameNetworkClient.cpp
            ./GameContainer.cpp
            ./GameModeNameSelect.cpp
            ./GameServerEventResponder.cpp
            ./GameModeLoadingGlobal.cpp
            ./GameModeConnecting.cpp
            ./GameClientUIManager.cpp
            ./GameModeOnlineGameplay.cpp
            ./GameModeMainMenu.cpp
            ./GameModeOfflineStaging.cpp
            ./GameClientController.refl.cpp
            ./GameClientInstanceResources.cpp
            ./GameMode.cpp
            ./GameModeTutorial.cpp
            ./GameClientLevelLoader.cpp
            ./GameClientInputManager.cpp
            ./GameModeSinglePlayerBots.cpp
            ./GameClientEntitySync.cpp
            ./GameClientGlobalResources.cpp
            ./GameShaders.cpp
            ./GameCamera.cpp
            ./GameModeEndGame.cpp
            ./GameClientSave.cpp
            ./GameClientCommon.cpp
            ./Components/PlayerComponent.refl.reg.cpp
            ./Components/PlayerComponent.refl.cpp
            ./EffectLayers/CollisionDrawer.refl.reg.cpp
            ./EffectLayers/CollisionDrawer.refl.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_GameClient 
            ./GameClientGlobalResources.h
            ./GameClientInputManager.h
            ./GameClientEntitySync.h
            ./GameClientInstanceResources.h
            ./GameModeTutorial.h
            ./GameClientEventSender.h
            ./GameClientSystems.h
            ./GameModeEndGame.h
            ./GameClientCommon.h
            ./GameContainer.h
            ./GameModeOfflineStaging.h
            ./GameNetworkClient.h
            ./GameModeNameSelect.h
            ./GameClientSaveFileData.refl.h
            ./GameShaders.h
            ./GameModeOnlineGameplay.h
            ./GameClientController.refl.meta.h
            ./GameClientSave.h
            ./GameCamera.h
            ./GameModeConnecting.h
            ./GameModeLogo.h
            ./GameModeLocalMultiplayer.h
            ./GameClientInstanceContainer.h
            ./GameMode.h
            ./GameClientController.refl.h
            ./GameServerEventResponder.h
            ./GameClientSaveFileData.refl.meta.h
            ./GameClientUIManager.h
            ./GameModeLoadingGlobal.h
            ./GameModeMainMenu.h
            ./GameClientLevelLoader.h
            ./GameModeSinglePlayerBots.h
            ./Components/PlayerComponent.refl.meta.h
            ./Components/PlayerComponent.refl.h
            ./EffectLayers/CollisionDrawer.refl.h
            ./EffectLayers/CollisionDrawer.refl.meta.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_GameClient 
            ./GameClientSaveFileData.refl.h
            ./GameClientController.refl.h
            ./Components/PlayerComponent.refl.h
            ./EffectLayers/CollisionDrawer.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_GameClient})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(GameClient ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})