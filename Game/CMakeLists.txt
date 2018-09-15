cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_Game 
            ./GameLogicContainer.cpp
            ./GameLevelList.cpp
            ./GameStageManager.cpp
            ./GameSharedGlobalResources.cpp
            ./GameServerTypes.cpp
            ./GameServerEventSender.cpp
            ./GameController.refl.cpp
            ./GameWebrtc.cpp
            ./GameStage.cpp
            ./GameMessages.refl.cpp
            ./GameEventReconciler.cpp
            ./GameSharedInstanceResources.cpp
            ./GameCommon.cpp
            ./GameNetworkEvents.refl.cpp
            ./GameNetworkExternals.refl.cpp
            ./GameValidation.cpp
            ./Configs/PlayerConfig.refl.reg.cpp
            ./Configs/GameConfig.refl.reg.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ./ServerObjects/Player/States/PlayerStateJump.refl.cpp
            ./ServerObjects/Player/States/PlayerStateBase.refl.cpp
            ./ServerObjects/Player/States/PlayerStateIdle.refl.cpp
            ./ServerObjects/Player/States/PlayerStateMoving.refl.cpp
            ./Systems/GameLogicSystems.cpp
            ./AI/PlayerAI.cpp
            ./Data/PlayerSpawn.refl.reg.cpp
            ./ServerObjects/Bot/BotServerObject.refl.cpp
            ./ServerObjects/Bot/BotServerObject.refl.reg.cpp
            ./ServerObjects/Bot/BehaviorTree/BehaviorTreeTypeDatabase.cpp
            ./ServerObjects/Bot/BehaviorTree/States/PlayAnimationBotState.refl.cpp
            ./ServerObjects/Bot/BehaviorTree/States/PlayAnimationBotState.refl.reg.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Game 
            ./GameProtocol.h
            ./GameValidation.h
            ./GameNetworkSettings.h
            ./GameController.refl.meta.h
            ./GameFullState.refl.h
            ./GameNetworkEvents.refl.h
            ./GameNetworkData.refl.meta.h
            ./GameMessages.refl.h
            ./GameSharedInstanceResources.h
            ./GameNetworkExternals.refl.h
            ./GameController.refl.h
            ./GameServerTypes.h
            ./GameSimulationEventCallbacks.h
            ./GameSettings.h
            ./GameNetworkEvents.refl.meta.h
            ./GameEventReconciler.h
            ./GameLogicContainer.h
            ./GameLevelListAsset.refl.h
            ./GameMessages.refl.meta.h
            ./GameLevelListAsset.refl.meta.h
            ./GameNetworkExternals.refl.meta.h
            ./GameSharedGlobalResources.h
            ./GameLevelList.h
            ./GameNetworkData.refl.h
            ./GameStage.h
            ./GameCommon.h
            ./GameStageManager.h
            ./GameFullState.refl.meta.h
            ./GameServerEventSender.h
            ./Configs/GameConfig.refl.meta.h
            ./Configs/GameConfig.refl.h
            ./Configs/PlayerConfig.refl.meta.h
            ./Configs/PlayerConfig.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.meta.h
            ./ServerObjects/Player/PlayerServerObject.refl.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.meta.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.h
            ./Systems/GameLogicSystems.h
            ./Systems/GameDeliberateSyncSystemList.h
            ./AI/PlayerAI.h
            ./GameplayEvents/PlaceholderEvent.h
            ./Data/PlayerSpawn.refl.meta.h
            ./Data/PlayerSpawn.refl.h
            ./ServerObjects/Bot/BotServerObject.refl.h
            ./ServerObjects/Bot/BotServerObject.refl.meta.h
            ./ServerObjects/CharacterFacing.refl.h
            ./ServerObjects/CharacterFacing.refl.meta.h
            ./ServerObjects/Bot/BehaviorTree/BehaviorTreeTypeDatabase.h
            ./ServerObjects/Bot/BehaviorTree/States/PlayAnimationBotState.refl.h
            ./ServerObjects/Bot/BehaviorTree/States/PlayAnimationBotState.refl.meta.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Game 
            ./GameFullState.refl.h
            ./GameNetworkEvents.refl.h
            ./GameMessages.refl.h
            ./GameNetworkExternals.refl.h
            ./GameController.refl.h
            ./GameLevelListAsset.refl.h
            ./GameNetworkData.refl.h
            ./Configs/GameConfig.refl.h
            ./Configs/PlayerConfig.refl.h
            ./ServerObjects/Player/PlayerServerObject.refl.h
            ./ServerObjects/Player/States/PlayerStateBase.refl.h
            ./ServerObjects/Player/States/PlayerStateMoving.refl.h
            ./ServerObjects/Player/States/PlayerStateIdle.refl.h
            ./ServerObjects/Player/States/PlayerStateJump.refl.h
            ./Data/PlayerSpawn.refl.h
            ./ServerObjects/Bot/BotServerObject.refl.h
            ./ServerObjects/CharacterFacing.refl.h
            ./ServerObjects/Bot/BehaviorTree/States/PlayAnimationBotState.refl.h
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
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- --std=c++1z -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Game ${GENERIC_SRC_Game} ${PLATFORM_SRC_Game}
            ${GENERIC_HEADER_Game} ${PLATFORM_HEADER_Game})