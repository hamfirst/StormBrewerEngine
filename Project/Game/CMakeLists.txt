cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_Game 
            AI/PlayerAI.cpp
            Configs/GameConfig.refl.reg.cpp
            Configs/PlayerConfig.refl.reg.cpp
            Configs/ProjectileConfig.refl.reg.cpp
            Data/DealDamageAnimationEvent.refl.reg.cpp
            Data/KillVolume.refl.reg.cpp
            Data/PlayerSpawn.refl.reg.cpp
            GameCommon.cpp
            GameController.refl.cpp
            GameMessages.refl.cpp
            GameNetworkEvents.refl.cpp
            GameNetworkExternals.refl.cpp
            GameServerEventSender.cpp
            GameServerTypes.cpp
            GameStage.cpp
            ServerObjects/Bot/BotServerObject.refl.cpp
            ServerObjects/Bot/BotServerObject.refl.reg.cpp
            ServerObjects/Bot/TestBot/TestBot.refl.cpp
            ServerObjects/Bot/TestBot/TestBot.refl.reg.cpp
            ServerObjects/CharacterFacing.refl.cpp
            ServerObjects/GameServerObjectBase.refl.cpp
            ServerObjects/GameServerObjectBase.refl.reg.cpp
            ServerObjects/Player/PlayerServerObject.refl.cpp
            ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ServerObjects/Player/States/PlayerStateBase.refl.cpp
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.cpp
            ServerObjects/Player/States/PlayerStateIdle.refl.cpp
            ServerObjects/Player/States/PlayerStateJump.refl.cpp
            ServerObjects/Player/States/PlayerStateMoving.refl.cpp
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.cpp
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.cpp
            ServerObjects/Projectile/ProjectileServerObject.refl.cpp
            ServerObjects/Projectile/ProjectileServerObject.refl.reg.cpp
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Game 
            AI/PlayerAI.h
            Configs/GameConfig.refl.h
            Configs/GameConfig.refl.meta.h
            Configs/PlayerConfig.refl.h
            Configs/PlayerConfig.refl.meta.h
            Configs/ProjectileConfig.refl.h
            Configs/ProjectileConfig.refl.meta.h
            Data/DealDamageAnimationEvent.refl.h
            Data/DealDamageAnimationEvent.refl.meta.h
            Data/KillVolume.refl.h
            Data/KillVolume.refl.meta.h
            Data/PlayerSpawn.refl.h
            Data/PlayerSpawn.refl.meta.h
            GameCollision.refl.h
            GameCollision.refl.meta.h
            GameCommon.h
            GameController.refl.h
            GameController.refl.meta.h
            GameFullState.refl.h
            GameFullState.refl.meta.h
            GameMessages.refl.h
            GameMessages.refl.meta.h
            GameNetworkData.refl.h
            GameNetworkData.refl.meta.h
            GameNetworkEvents.refl.h
            GameNetworkEvents.refl.meta.h
            GameNetworkExternals.refl.h
            GameNetworkExternals.refl.meta.h
            GameNetworkSettings.h
            GameServerEventSender.h
            GameServerTypes.h
            GameSimulationEventCallbacks.h
            GameSimulationStats.refl.h
            GameSimulationStats.refl.meta.h
            GameStage.h
            GameplayEvents/DamageEvent.h
            GameplayEvents/DamageType.refl.h
            GameplayEvents/DamageType.refl.meta.h
            GameplayEvents/PlaceholderEvent.h
            ServerObjects/Bot/BotBehaviorTree.h
            ServerObjects/Bot/BotServerObject.refl.h
            ServerObjects/Bot/BotServerObject.refl.meta.h
            ServerObjects/Bot/TestBot/TestBot.refl.h
            ServerObjects/Bot/TestBot/TestBot.refl.meta.h
            ServerObjects/CharacterFacing.refl.h
            ServerObjects/CharacterFacing.refl.meta.h
            ServerObjects/GameServerObjectBase.refl.h
            ServerObjects/GameServerObjectBase.refl.meta.h
            ServerObjects/Player/PlayerServerObject.refl.h
            ServerObjects/Player/PlayerServerObject.refl.meta.h
            ServerObjects/Player/States/PlayerStateBase.refl.h
            ServerObjects/Player/States/PlayerStateBase.refl.meta.h
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.h
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.meta.h
            ServerObjects/Player/States/PlayerStateIdle.refl.h
            ServerObjects/Player/States/PlayerStateIdle.refl.meta.h
            ServerObjects/Player/States/PlayerStateJump.refl.h
            ServerObjects/Player/States/PlayerStateJump.refl.meta.h
            ServerObjects/Player/States/PlayerStateMoving.refl.h
            ServerObjects/Player/States/PlayerStateMoving.refl.meta.h
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.meta.h
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.meta.h
            ServerObjects/Projectile/ProjectileServerObject.refl.h
            ServerObjects/Projectile/ProjectileServerObject.refl.meta.h
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.h
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.meta.h
            Systems/GameDeliberateSyncSystemList.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Game 
            Configs/GameConfig.refl.h
            Configs/PlayerConfig.refl.h
            Configs/ProjectileConfig.refl.h
            Data/DealDamageAnimationEvent.refl.h
            Data/KillVolume.refl.h
            Data/PlayerSpawn.refl.h
            GameCollision.refl.h
            GameController.refl.h
            GameFullState.refl.h
            GameMessages.refl.h
            GameNetworkData.refl.h
            GameNetworkEvents.refl.h
            GameNetworkExternals.refl.h
            GameSimulationStats.refl.h
            GameplayEvents/DamageType.refl.h
            ServerObjects/Bot/BotServerObject.refl.h
            ServerObjects/Bot/TestBot/TestBot.refl.h
            ServerObjects/CharacterFacing.refl.h
            ServerObjects/GameServerObjectBase.refl.h
            ServerObjects/Player/PlayerServerObject.refl.h
            ServerObjects/Player/States/PlayerStateBase.refl.h
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.h
            ServerObjects/Player/States/PlayerStateIdle.refl.h
            ServerObjects/Player/States/PlayerStateJump.refl.h
            ServerObjects/Player/States/PlayerStateMoving.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.h
            ServerObjects/Projectile/ProjectileServerObject.refl.h
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Game})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(Game STATIC ${GENERIC_SRC_Game} ${GENERIC_HEADER_Game})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Game} ${GENERIC_HEADER_Game})

set_target_properties(Game PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT GameCommon.h)

if(GENERATE_PCH)
  cotire(Game)
endif()
