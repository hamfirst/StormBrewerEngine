cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameClient 
            GameClientController.refl.cpp
            GameServerEventResponder.cpp
            GameModeLoadingGlobal.cpp
            GameModeConnecting.cpp
            GameModeMainMenu.cpp
            GameContainer.cpp
            GameShaders.cpp
            GameClientInputManager.cpp
            GameModeOnlineGameplay.cpp
            GameModeNameSelect.cpp
            GameModeLocalMultiplayer.cpp
            GameClientInstanceResources.cpp
            GameClientUIManager.cpp
            GameClientSave.cpp
            GameClientEntitySync.cpp
            GameModeSinglePlayerBots.cpp
            GameClientSystems.cpp
            GameClientInstanceContainer.cpp
            GameModeLogo.cpp
            GameNetworkClient.cpp
  GameModeEndGame.cpp
            GameCamera.cpp
            GameMode.cpp
            GameModeOfflineStaging.cpp
            GameModeJoinPrivateGame.cpp
            GameModeOnlineStaging.cpp
            GameClientCommon.cpp
            GameClientLevelLoader.cpp
            GameModeTutorial.cpp
            Components/PlayerComponent.refl.cpp
            Components/PlayerComponent.refl.reg.cpp
            Components/Reusable/AttachVfxComponent.refl.reg.cpp
            Components/Reusable/PlayAnimationComponent.refl.cpp
            Components/Reusable/PlayAnimationComponent.refl.reg.cpp
            Components/Reusable/AttachVfxComponent.refl.cpp
            Components/Reusable/SyncServerObjectComponent.refl.reg.cpp
            Components/Reusable/SyncServerObjectComponent.refl.cpp
            EffectLayers/CollisionDrawer.refl.cpp
            EffectLayers/CollisionDrawer.refl.reg.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameClient 
            GameClientEntitySync.h
            GameModeLogo.h
            GameContainer.h
            GameModeTutorial.h
            GameClientInputManager.h
            GameModeSinglePlayerBots.h
            GameModeConnecting.h
            GameClientSave.h
            GameClientInstanceResources.h
            GameClientSaveFileData.refl.h
            GameShaders.h
            GameClientCommon.h
            GameModeLocalMultiplayer.h
            GameModeNameSelect.h
            GameModeEndGame.h
            GameModeOnlineGameplay.h
            GameModeLoadingGlobal.h
            GameClientUIManager.h
            GameMode.h
            GameModeOfflineStaging.h
            GameClientSystems.h
            GameModeOnlineStaging.h
            GameClientInstanceContainer.h
  GameClientLevelLoader.h
            GameClientController.refl.meta.h
            GameNetworkClient.h
            GameClientController.refl.h
            GameClientSaveFileData.refl.meta.h
            GameModeMainMenu.h
            GameModeJoinPrivateGame.h
            GameClientEventSender.h
            GameCamera.h
            GameServerEventResponder.h
            Components/PlayerComponent.refl.meta.h
            Components/PlayerComponent.refl.h
            Components/Reusable/SyncServerObjectComponent.refl.h
            Components/Reusable/PlayAnimationComponent.refl.h
            Components/Reusable/SyncServerObjectComponent.refl.meta.h
            Components/Reusable/AttachVfxComponent.refl.meta.h
            Components/Reusable/AttachVfxComponent.refl.h
            Components/Reusable/PlayAnimationComponent.refl.meta.h
            EffectLayers/CollisionDrawer.refl.meta.h
            EffectLayers/CollisionDrawer.refl.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameClient 
            GameClientSaveFileData.refl.h
            GameClientController.refl.h
            Components/PlayerComponent.refl.h
            Components/Reusable/SyncServerObjectComponent.refl.h
            Components/Reusable/PlayAnimationComponent.refl.h
            Components/Reusable/AttachVfxComponent.refl.h
            EffectLayers/CollisionDrawer.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()


foreach(REFL_FILE ${GENERIC_REFL_GameClient})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(GameClient STATIC ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})
