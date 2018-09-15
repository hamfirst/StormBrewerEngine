cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameClient 
            ./GameClientController.refl.cpp
            ./GameServerEventResponder.cpp
            ./GameModeLoadingGlobal.cpp
            ./GameModeConnecting.cpp
            ./GameModeMainMenu.cpp
            ./GameContainer.cpp
            ./GameShaders.cpp
            ./GameClientInputManager.cpp
            ./GameModeOnlineGameplay.cpp
            ./GameModeNameSelect.cpp
            ./GameModeLocalMultiplayer.cpp
            ./GameClientInstanceResources.cpp
            ./GameClientUIManager.cpp
            ./GameClientSave.cpp
            ./GameClientEntitySync.cpp
            ./GameModeSinglePlayerBots.cpp
            ./GameClientSystems.cpp
            ./GameClientInstanceContainer.cpp
            ./GameModeLogo.cpp
            ./GameNetworkClient.cpp
            ./GameClientGlobalResources.cpp
            ./GameModeEndGame.cpp
            ./GameCamera.cpp
            ./GameMode.cpp
            ./GameModeOfflineStaging.cpp
            ./GameClientCommon.cpp
            ./GameClientLevelLoader.cpp
            ./GameModeTutorial.cpp
            ./Components/PlayerComponent.refl.cpp
            ./Components/PlayerComponent.refl.reg.cpp
            ./EffectLayers/CollisionDrawer.refl.cpp
            ./EffectLayers/CollisionDrawer.refl.reg.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_GameClient 
            ./GameClientEntitySync.h
            ./GameModeLogo.h
            ./GameContainer.h
            ./GameModeTutorial.h
            ./GameClientInputManager.h
            ./GameModeSinglePlayerBots.h
            ./GameModeConnecting.h
            ./GameClientSave.h
            ./GameClientInstanceResources.h
            ./GameClientSaveFileData.refl.h
            ./GameShaders.h
            ./GameClientCommon.h
            ./GameModeLocalMultiplayer.h
            ./GameModeNameSelect.h
            ./GameModeEndGame.h
            ./GameModeOnlineGameplay.h
            ./GameModeLoadingGlobal.h
            ./GameClientUIManager.h
            ./GameMode.h
            ./GameModeOfflineStaging.h
            ./GameClientSystems.h
            ./GameClientInstanceContainer.h
            ./GameClientGlobalResources.h
            ./GameClientLevelLoader.h
            ./GameClientController.refl.meta.h
            ./GameNetworkClient.h
            ./GameClientController.refl.h
            ./GameClientSaveFileData.refl.meta.h
            ./GameModeMainMenu.h
            ./GameClientEventSender.h
            ./GameCamera.h
            ./GameServerEventResponder.h
            ./Components/PlayerComponent.refl.meta.h
            ./Components/PlayerComponent.refl.h
            ./EffectLayers/CollisionDrawer.refl.meta.h
            ./EffectLayers/CollisionDrawer.refl.h
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