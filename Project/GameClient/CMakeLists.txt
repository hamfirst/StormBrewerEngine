cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameClient 
            Components/PlayerComponent.refl.cpp
            Components/PlayerComponent.refl.reg.cpp
            Components/Reusable/AttachVfxComponent.refl.cpp
            Components/Reusable/AttachVfxComponent.refl.reg.cpp
            Components/Reusable/PlayAnimationComponent.refl.cpp
            Components/Reusable/PlayAnimationComponent.refl.reg.cpp
            Components/Reusable/SyncServerObjectComponent.refl.cpp
            Components/Reusable/SyncServerObjectComponent.refl.reg.cpp
            EffectLayers/CollisionDrawer.refl.cpp
            EffectLayers/CollisionDrawer.refl.reg.cpp
            GameCamera.cpp
            GameClientCommon.cpp
            GameClientController.refl.cpp
            GameClientEntitySync.cpp
            GameClientInputManager.cpp
            GameClientInstanceContainer.cpp
            GameClientInstanceResources.cpp
            GameClientLatencyChecker.cpp
            GameClientLevelLoader.cpp
            GameClientSave.cpp
            GameClientSystems.cpp
            GameClientUIManager.cpp
            GameContainer.cpp
            GameNetworkClient.cpp
            GameServerEventResponder.cpp
            GameShaders.cpp
            Modes/GameMode.cpp
            Modes/GameModeConnectingGame.cpp
            Modes/GameModeConnectingLobby.cpp
            Modes/GameModeEndGame.cpp
            Modes/GameModeFindingMatch.cpp
            Modes/GameModeJoinPrivateGame.cpp
            Modes/GameModeLoadingGlobal.cpp
            Modes/GameModeLocalMultiplayer.cpp
            Modes/GameModeLogo.cpp
            Modes/GameModeMainMenu.cpp
            Modes/GameModeMapSettings.cpp
            Modes/GameModeNameSelect.cpp
            Modes/GameModeOfflineStaging.cpp
            Modes/GameModeOnlineBase.cpp
            Modes/GameModeOnlineGameplay.cpp
            Modes/GameModeOnlineStaging.cpp
            Modes/GameModePlayOnline.cpp
            Modes/GameModePlaylistMenu.cpp
            Modes/GameModeSinglePlayerBots.cpp
            Modes/GameModeStagingBase.cpp
            Modes/GameModeTutorial.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameClient 
            Components/PlayerComponent.refl.h
            Components/PlayerComponent.refl.meta.h
            Components/Reusable/AttachVfxComponent.refl.h
            Components/Reusable/AttachVfxComponent.refl.meta.h
            Components/Reusable/PlayAnimationComponent.refl.h
            Components/Reusable/PlayAnimationComponent.refl.meta.h
            Components/Reusable/SyncServerObjectComponent.refl.h
            Components/Reusable/SyncServerObjectComponent.refl.meta.h
            EffectLayers/CollisionDrawer.refl.h
            EffectLayers/CollisionDrawer.refl.meta.h
            GameCamera.h
            GameClientCommon.h
            GameClientController.refl.h
            GameClientController.refl.meta.h
            GameClientEntitySync.h
            GameClientEventSender.h
            GameClientInputManager.h
            GameClientInstanceContainer.h
            GameClientInstanceResources.h
            GameClientLatencyChecker.h
            GameClientLevelLoader.h
            GameClientSave.h
            GameClientSaveFileData.refl.h
            GameClientSaveFileData.refl.meta.h
            GameClientSystems.h
            GameClientUIData.refl.h
            GameClientUIData.refl.meta.h
            GameClientUIManager.h
            GameContainer.h
            GameNetworkClient.h
            GameServerEventResponder.h
            GameShaders.h
            Modes/GameMode.h
            Modes/GameModeConnectingGame.h
            Modes/GameModeConnectingLobby.h
            Modes/GameModeEndGame.h
            Modes/GameModeFindingMatch.h
            Modes/GameModeJoinPrivateGame.h
            Modes/GameModeLoadingGlobal.h
            Modes/GameModeLocalMultiplayer.h
            Modes/GameModeLogo.h
            Modes/GameModeMainMenu.h
            Modes/GameModeMapSettings.h
            Modes/GameModeNameSelect.h
            Modes/GameModeOfflineStaging.h
            Modes/GameModeOnlineBase.h
            Modes/GameModeOnlineGameplay.h
            Modes/GameModeOnlineStaging.h
            Modes/GameModePlayOnline.h
            Modes/GameModePlaylistMenu.h
            Modes/GameModeSinglePlayerBots.h
            Modes/GameModeStagingBase.h
            Modes/GameModeTutorial.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameClient 
            Components/PlayerComponent.refl.h
            Components/Reusable/AttachVfxComponent.refl.h
            Components/Reusable/PlayAnimationComponent.refl.h
            Components/Reusable/SyncServerObjectComponent.refl.h
            EffectLayers/CollisionDrawer.refl.h
            GameClientController.refl.h
            GameClientSaveFileData.refl.h
            GameClientUIData.refl.h
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


if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_GameClient})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(GameClient STATIC ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})

