cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_Game 
            ./GameCommon.cpp
            ./GameController.refl.cpp
            ./GameEventReconciler.cpp
            ./GameLevelList.cpp
            ./GameLogicContainer.cpp
            ./GameMessages.refl.cpp
            ./GameNetworkEvents.refl.cpp
            ./GameNetworkExternals.refl.cpp
            ./GameServerEventSender.cpp
            ./GameServerTypes.cpp
            ./GameSharedGlobalResources.cpp
            ./GameSharedInstanceResources.cpp
            ./GameStage.cpp
            ./GameStageManager.cpp
            ./GameValidation.cpp
            ./GameWebrtc.cpp
            ./AI/PlayerAI.cpp
            ./Configs/GameConfig.refl.reg.cpp
            ./Configs/PlayerConfig.refl.reg.cpp
            ./Data/PlayerSpawn.refl.reg.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ./ServerObjects/Player/States/PlayerStateBase.refl.cpp
            ./ServerObjects/Player/States/PlayerStateIdle.refl.cpp
            ./ServerObjects/Player/States/PlayerStateJump.refl.cpp
            ./ServerObjects/Player/States/PlayerStateMoving.refl.cpp
            ./Systems/GameLogicSystems.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Game 
            ./GameCommon.h
            ./GameController.refl.h
            ./GameController.refl.meta.h
            ./GameEventReconciler.h
            ./GameFullState.refl.h
            ./GameFullState.refl.meta.h
            ./GameLevelList.h
            ./GameLevelListAsset.refl.h
            ./GameLevelListAsset.refl.meta.h
            ./GameLogicContainer.h
            ./GameMessages.refl.h
            ./GameMessages.refl.meta.h
            ./GameNetworkData.refl.h
            ./GameNetworkData.refl.meta.h
            ./GameNetworkEvents.refl.h
            ./GameNetworkEvents.refl.meta.h
            ./GameNetworkExternals.refl.h
            ./GameNetworkExternals.refl.meta.h
            ./GameNetworkSettings.h
            ./GameProtocol.h
            ./GameServerEventSender.h
            ./GameServerTypes.h
            ./GameSettings.h
            ./GameSharedGlobalResources.h
            ./GameSharedInstanceResources.h
            ./GameSimulationEventCallbacks.h
            ./GameStage.h
            ./GameStageManager.h
            ./GameValidation.h
            ./AI/PlayerAI.h
            ./Configs/GameConfig.refl.h
            ./Configs/GameConfig.refl.meta.h
            ./Configs/PlayerConfig.refl.h
            ./Configs/PlayerConfig.refl.meta.h
            ./Data/PlayerSpawn.refl.h
            ./Data/PlayerSpawn.refl.meta.h
            ./GameplayEvents/PlaceholderEvent.h
            ./ServerObjects/Player/PlayerServerObject.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.meta.h
            ./Systems/GameDeliberateSyncSystemList.h
            ./Systems/GameLogicSystems.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Game 
            ./GameController.refl.h
            ./GameFullState.refl.h
            ./GameLevelListAsset.refl.h
            ./GameMessages.refl.h
            ./GameNetworkData.refl.h
            ./GameNetworkEvents.refl.h
            ./GameNetworkExternals.refl.h
            ./Configs/GameConfig.refl.h
            ./Configs/PlayerConfig.refl.h
            ./Data/PlayerSpawn.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Game 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Game 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Game 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Game 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE Game ${GENERIC_REFL_Game} ${PLATFORM_REFL_Game})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(Game ${GENERIC_SRC_Game} ${PLATFORM_SRC_Game}
            Game ${GENERIC_HEADER_Game} ${PLATFORM_HEADER_Game})