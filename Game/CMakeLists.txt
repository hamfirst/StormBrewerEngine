cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_Game 
            ./GameCommon.cpp
            ./GameValidation.cpp
            ./GameServerTypes.cpp
            ./GameWebrtc.cpp
            ./GameNetworkEvents.refl.cpp
            ./GameStageManager.cpp
            ./GameEventReconciler.cpp
            ./GameServerEventSender.cpp
            ./GameSharedInstanceResources.cpp
            ./GameController.refl.cpp
            ./GameLogicContainer.cpp
            ./GameLevelList.cpp
            ./GameNetworkExternals.refl.cpp
            ./GameSharedGlobalResources.cpp
            ./GameStage.cpp
            ./GameMessages.refl.cpp
            ./AI/PlayerAI.cpp
            ./Configs/PlayerConfig.refl.reg.cpp
            ./Configs/GameConfig.refl.reg.cpp
            ./Systems/GameLogicSystems.cpp
            ./Data/PlayerSpawn.refl.reg.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ./ServerObjects/Player/States/PlayerStateIdle.refl.cpp
            ./ServerObjects/Player/States/PlayerStateBase.refl.cpp
            ./ServerObjects/Player/States/PlayerStateJump.refl.cpp
            ./ServerObjects/Player/States/PlayerStateMoving.refl.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Game 
            ./GameMessages.refl.meta.h
            ./GameNetworkEvents.refl.meta.h
            ./GameNetworkEvents.refl.h
            ./GameStageManager.h
            ./GameCommon.h
            ./GameStage.h
            ./GameNetworkExternals.refl.meta.h
            ./GameNetworkSettings.h
            ./GameFullState.refl.meta.h
            ./GameController.refl.meta.h
            ./GameNetworkExternals.refl.h
            ./GameSettings.h
            ./GameLevelList.h
            ./GameSimulationEventCallbacks.h
            ./GameFullState.refl.h
            ./GameProtocol.h
            ./GameEventReconciler.h
            ./GameController.refl.h
            ./GameLevelListAsset.refl.h
            ./GameServerTypes.h
            ./GameNetworkData.refl.h
            ./GameServerEventSender.h
            ./GameLogicContainer.h
            ./GameSharedGlobalResources.h
            ./GameSharedInstanceResources.h
            ./GameValidation.h
            ./GameNetworkData.refl.meta.h
            ./GameMessages.refl.h
            ./GameLevelListAsset.refl.meta.h
            ./GameplayEvents/PlaceholderEvent.h
            ./AI/PlayerAI.h
            ./Configs/PlayerConfig.refl.meta.h
            ./Configs/GameConfig.refl.h
            ./Configs/GameConfig.refl.meta.h
            ./Configs/PlayerConfig.refl.h
            ./Systems/GameLogicSystems.h
            ./Systems/GameDeliberateSyncSystemList.h
            ./Data/PlayerSpawn.refl.meta.h
            ./Data/PlayerSpawn.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Game 
            ./GameNetworkEvents.refl.h
            ./GameNetworkExternals.refl.h
            ./GameFullState.refl.h
            ./GameController.refl.h
            ./GameLevelListAsset.refl.h
            ./GameNetworkData.refl.h
            ./GameMessages.refl.h
            ./Configs/GameConfig.refl.h
            ./Configs/PlayerConfig.refl.h
            ./Data/PlayerSpawn.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Game 
            )

set(PLATFORM_HEADER_Game 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Game 
            )

set(PLATFORM_HEADER_Game 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Game 
            )

set(PLATFORM_HEADER_Game 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            )

set(PLATFORM_HEADER_Game 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Game 
            )

set(PLATFORM_HEADER_Game 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            )

set(PLATFORM_HEADER_Game 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_Game})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Game ${GENERIC_SRC_Game} ${PLATFORM_SRC_Game}
            ${GENERIC_HEADER_Game} ${PLATFORM_HEADER_Game})