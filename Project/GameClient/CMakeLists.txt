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
            GameClientLevelLoader.cpp
            GameClientSave.cpp
            GameClientSystems.cpp
            GameClientUIManager.cpp
            GameContainer.cpp
            GameMode.cpp
            GameModeConnecting.cpp
            GameModeEndGame.cpp
            GameModeJoinPrivateGame.cpp
            GameModeLoadingGlobal.cpp
            GameModeLocalMultiplayer.cpp
            GameModeLogo.cpp
            GameModeMainMenu.cpp
            GameModeMapSettings.cpp
            GameModeNameSelect.cpp
            GameModeOfflineStaging.cpp
            GameModeOnlineGameplay.cpp
            GameModeOnlineStaging.cpp
            GameModeSinglePlayerBots.cpp
            GameModeStagingBase.cpp
            GameModeTutorial.cpp
            GameNetworkClient.cpp
            GameServerEventResponder.cpp
            GameShaders.cpp
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
            GameClientLevelLoader.h
            GameClientSave.h
            GameClientSaveFileData.refl.h
            GameClientSaveFileData.refl.meta.h
            GameClientSystems.h
            GameClientUIManager.h
            GameContainer.h
            GameMode.h
            GameModeConnecting.h
            GameModeEndGame.h
            GameModeJoinPrivateGame.h
            GameModeLoadingGlobal.h
            GameModeLocalMultiplayer.h
            GameModeLogo.h
            GameModeMainMenu.h
            GameModeMapSettings.h
            GameModeNameSelect.h
            GameModeOfflineStaging.h
            GameModeOnlineGameplay.h
            GameModeOnlineStaging.h
            GameModeSinglePlayerBots.h
            GameModeStagingBase.h
            GameModeTutorial.h
            GameNetworkClient.h
            GameServerEventResponder.h
            GameShaders.h
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
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(GameClient STATIC ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})

