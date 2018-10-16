cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_Game 
            GameLogicContainer.cpp
            GameLevelList.cpp
            GameStageManager.cpp
            GameSharedGlobalResources.cpp
            GameServerTypes.cpp
            GameServerEventSender.cpp
            GameController.refl.cpp
            GameWebrtc.cpp
            GameStage.cpp
            GameMessages.refl.cpp
            GameEventReconciler.cpp
            GameSharedInstanceResources.cpp
            GameCommon.cpp
            GameNetworkEvents.refl.cpp
            GameNetworkExternals.refl.cpp
            GameValidation.cpp
            Configs/ProjectileConfig.refl.reg.cpp
            Configs/PlayerConfig.refl.reg.cpp
            Configs/GameConfig.refl.reg.cpp
            ServerObjects/GameServerObjectBase.refl.cpp
            ServerObjects/CharacterFacing.refl.cpp
            ServerObjects/GameServerObjectBase.refl.reg.cpp
            ServerObjects/Player/PlayerServerObject.refl.cpp
            ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ServerObjects/Player/States/PlayerStateJump.refl.cpp
            ServerObjects/Player/States/PlayerStateBase.refl.cpp
            ServerObjects/Player/States/PlayerStateIdle.refl.cpp
            ServerObjects/Player/States/PlayerStateMoving.refl.cpp
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.cpp
            ServerObjects/Projectile/ProjectileServerObject.refl.reg.cpp
            ServerObjects/Projectile/ProjectileServerObject.refl.cpp
            ServerObjects/Bot/BotServerObject.refl.reg.cpp
            ServerObjects/Bot/BotServerObject.refl.cpp
            ServerObjects/Bot/TestBot/TestBot.refl.cpp
            ServerObjects/Bot/TestBot/TestBot.refl.reg.cpp
            Systems/GameServerObjectOverlapSystem.cpp
            Systems/GameLogicSystems.cpp
            Systems/CVCPushSystem.cpp
            BehaviorTree/BehaviorTreeTypeDatabase.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.reg.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.cpp
            AI/PlayerAI.cpp
            Data/KillVolume.refl.reg.cpp
            Data/PlayerSpawn.refl.reg.cpp
            Data/DealDamageAnimationEvent.refl.reg.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Game 
            GameProtocol.h
            GameValidation.h
            GameNetworkSettings.h
            GameFullState.refl.h
            GameCollision.refl.h
            GameNetworkEvents.refl.h
            GameMessages.refl.h
            GameSharedInstanceResources.h
            GameNetworkExternals.refl.h
            GameController.refl.h
            GameServerTypes.h
            GameSimulationEventCallbacks.h
            GameEventReconciler.h
            GameLogicContainer.h
            GameLevelListAsset.refl.h
            GameSharedGlobalResources.h
            GameLevelList.h
            GameNetworkData.refl.h
            GameStage.h
            GameCommon.h
            GameStageManager.h
            GameServerEventSender.h
            Configs/ProjectileConfig.refl.h
            Configs/GameConfig.refl.h
            Configs/PlayerConfig.refl.h
            ServerObjects/CharacterFacing.refl.h
            ServerObjects/GameServerObjectBase.refl.h
            ServerObjects/Player/PlayerServerObject.refl.h
            ServerObjects/Player/States/PlayerStateBase.refl.h
            ServerObjects/Player/States/PlayerStateMoving.refl.h
            ServerObjects/Player/States/PlayerStateIdle.refl.h
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.h
            ServerObjects/Player/States/PlayerStateJump.refl.h
            ServerObjects/Projectile/ProjectileServerObject.refl.h
            ServerObjects/Bot/BotBehaviorTree.h
            ServerObjects/Bot/BotServerObject.refl.h
            ServerObjects/Bot/TestBot/TestBot.refl.h
            Systems/GameLogicSystems.h
            Systems/GameDeliberateSyncSystemList.h
            Systems/GameServerObjectOverlapRegistrationMacros.h
            Systems/GameServerObjectOverlapSystem.h
            Systems/CVCPushSystem.h
            BehaviorTree/BehaviorTreeSerialize.h
            BehaviorTree/BehaviorTreeTypeDatabase.h
            BehaviorTree/BehaviorTree.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            AI/PlayerAI.h
            GameplayEvents/DamageType.refl.h
            GameplayEvents/PlaceholderEvent.h
            GameplayEvents/DamageEvent.h
            Data/DealDamageAnimationEvent.refl.h
            Data/PlayerSpawn.refl.h
            Data/KillVolume.refl.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Game 
            GameFullState.refl.h
            GameCollision.refl.h
            GameNetworkEvents.refl.h
            GameMessages.refl.h
            GameNetworkExternals.refl.h
            GameController.refl.h
            GameLevelListAsset.refl.h
            GameNetworkData.refl.h
            Configs/ProjectileConfig.refl.h
            Configs/GameConfig.refl.h
            Configs/PlayerConfig.refl.h
            ServerObjects/CharacterFacing.refl.h
            ServerObjects/GameServerObjectBase.refl.h
            ServerObjects/Player/PlayerServerObject.refl.h
            ServerObjects/Player/States/PlayerStateBase.refl.h
            ServerObjects/Player/States/PlayerStateMoving.refl.h
            ServerObjects/Player/States/PlayerStateIdle.refl.h
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.h
            ServerObjects/Player/States/PlayerStateJump.refl.h
            ServerObjects/Projectile/ProjectileServerObject.refl.h
            ServerObjects/Bot/BotServerObject.refl.h
            ServerObjects/Bot/TestBot/TestBot.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            GameplayEvents/DamageType.refl.h
            Data/DealDamageAnimationEvent.refl.h
            Data/PlayerSpawn.refl.h
            Data/KillVolume.refl.h
            #REFL_PLACEHOLDER
            )


foreach(REFL_FILE ${GENERIC_REFL_Game})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Game STATIC ${GENERIC_SRC_Game} ${GENERIC_HEADER_Game})

set_target_properties(Game PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT GameCommon.h)
cotire(Game)
