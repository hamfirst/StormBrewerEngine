cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_GameClient 
            ./GameCamera.cpp
            ./GameClientCommon.cpp
            ./GameClientController.refl.cpp
            ./GameClientEntitySync.cpp
            ./GameClientGlobalResources.cpp
            ./GameClientInputManager.cpp
            ./GameClientInstanceContainer.cpp
            ./GameClientInstanceResources.cpp
            ./GameClientLevelLoader.cpp
            ./GameClientSave.cpp
            ./GameClientSystems.cpp
            ./GameClientUIManager.cpp
            ./GameContainer.cpp
            ./GameMode.cpp
            ./GameModeConnecting.cpp
            ./GameModeEndGame.cpp
            ./GameModeLoadingGlobal.cpp
            ./GameModeLocalMultiplayer.cpp
            ./GameModeLogo.cpp
            ./GameModeMainMenu.cpp
            ./GameModeNameSelect.cpp
            ./GameModeOfflineStaging.cpp
            ./GameModeOnlineGameplay.cpp
            ./GameModeSinglePlayerBots.cpp
            ./GameModeTutorial.cpp
            ./GameNetworkClient.cpp
            ./GameServerEventResponder.cpp
            ./GameShaders.cpp
            ./Components/PlayerComponent.refl.cpp
            ./Components/PlayerComponent.refl.reg.cpp
            ./EffectLayers/CollisionDrawer.refl.cpp
            ./EffectLayers/CollisionDrawer.refl.reg.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_GameClient 
            ./GameCamera.h
            ./GameClientCommon.h
            ./GameClientController.refl.h
            ./GameClientController.refl.meta.h
            ./GameClientEntitySync.h
            ./GameClientEventSender.h
            ./GameClientGlobalResources.h
            ./GameClientInputManager.h
            ./GameClientInstanceContainer.h
            ./GameClientInstanceResources.h
            ./GameClientLevelLoader.h
            ./GameClientSave.h
            ./GameClientSaveFileData.refl.h
            ./GameClientSaveFileData.refl.meta.h
            ./GameClientSystems.h
            ./GameClientUIManager.h
            ./GameContainer.h
            ./GameMode.h
            ./GameModeConnecting.h
            ./GameModeEndGame.h
            ./GameModeLoadingGlobal.h
            ./GameModeLocalMultiplayer.h
            ./GameModeLogo.h
            ./GameModeMainMenu.h
            ./GameModeNameSelect.h
            ./GameModeOfflineStaging.h
            ./GameModeOnlineGameplay.h
            ./GameModeSinglePlayerBots.h
            ./GameModeTutorial.h
            ./GameNetworkClient.h
            ./GameServerEventResponder.h
            ./GameShaders.h
            ./Components/PlayerComponent.refl.h
            ./Components/PlayerComponent.refl.meta.h
            ./EffectLayers/CollisionDrawer.refl.h
            ./EffectLayers/CollisionDrawer.refl.meta.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_GameClient 
            ./GameClientController.refl.h
            ./GameClientSaveFileData.refl.h
            ./Components/PlayerComponent.refl.h
            ./EffectLayers/CollisionDrawer.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_GameClient 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_GameClient 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_GameClient 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_GameClient 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE GameClient ${GENERIC_REFL_GameClient} ${PLATFORM_REFL_GameClient})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(GameClient ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            GameClient ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})