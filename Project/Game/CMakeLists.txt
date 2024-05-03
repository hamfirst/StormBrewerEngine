cmake_minimum_required(VERSION 3.20.0)

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
            AnimationEvents/DealDamageAnimationEvent.refl.reg.cpp
            GameCommon.cpp
            GameController/Config/GameConfig.refl.reg.cpp
            GameController/GameController.refl.cpp
            GameTypes.cpp
            Markup/KillVolume.refl.reg.cpp
            Markup/PlayerSpawn.refl.reg.cpp
            NetworkEvents/GameMessages.refl.cpp
            NetworkEvents/GameNetworkEvents.refl.cpp
            NetworkEvents/GameNetworkExternals.refl.cpp
            NetworkEvents/GameServerEventSender.cpp
            ServerObjects/Bot/BotServerObject.refl.cpp
            ServerObjects/Bot/BotServerObject.refl.reg.cpp
            ServerObjects/Bot/TestBot/TestBot.refl.cpp
            ServerObjects/Bot/TestBot/TestBot.refl.reg.cpp
            ServerObjects/CharacterFacing.refl.cpp
            ServerObjects/GameServerObjectBase.refl.cpp
            ServerObjects/GameServerObjectBase.refl.reg.cpp
            ServerObjects/Player/Config/PlayerConfig.refl.reg.cpp
            ServerObjects/Player/PlayerServerObject.refl.cpp
            ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ServerObjects/Player/States/PlayerStateBase.refl.cpp
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.cpp
            ServerObjects/Player/States/PlayerStateIdle.refl.cpp
            ServerObjects/Player/States/PlayerStateJump.refl.cpp
            ServerObjects/Player/States/PlayerStateMoving.refl.cpp
            ServerObjects/Projectile/Config/ProjectileConfig.refl.reg.cpp
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.cpp
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.cpp
            ServerObjects/Projectile/ProjectileServerObject.refl.cpp
            ServerObjects/Projectile/ProjectileServerObject.refl.reg.cpp
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.cpp
            Stage/GameStage.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Game 
            AI/PlayerAI.h
            AnimationEvents/DealDamageAnimationEvent.refl.h
            AnimationEvents/DealDamageAnimationEvent.refl.meta.h
            GameCommon.h
            GameController/Config/GameConfig.refl.h
            GameController/Config/GameConfig.refl.meta.h
            GameController/GameController.refl.h
            GameController/GameController.refl.meta.h
            GameTypes.h
            GameplayEvents/DamageEvent.h
            GameplayEvents/DamageType.refl.h
            GameplayEvents/DamageType.refl.meta.h
            GameplayEvents/PlaceholderEvent.h
            Markup/KillVolume.refl.h
            Markup/KillVolume.refl.meta.h
            Markup/PlayerSpawn.refl.h
            Markup/PlayerSpawn.refl.meta.h
            NetworkEvents/GameMessages.refl.h
            NetworkEvents/GameMessages.refl.meta.h
            NetworkEvents/GameNetworkData.refl.h
            NetworkEvents/GameNetworkData.refl.meta.h
            NetworkEvents/GameNetworkEvents.refl.h
            NetworkEvents/GameNetworkEvents.refl.meta.h
            NetworkEvents/GameNetworkExternals.refl.h
            NetworkEvents/GameNetworkExternals.refl.meta.h
            NetworkEvents/GameServerEventSender.h
            ServerObjects/Bot/BotBehaviorTree.h
            ServerObjects/Bot/BotServerObject.refl.h
            ServerObjects/Bot/BotServerObject.refl.meta.h
            ServerObjects/Bot/TestBot/TestBot.refl.h
            ServerObjects/Bot/TestBot/TestBot.refl.meta.h
            ServerObjects/CharacterFacing.refl.h
            ServerObjects/CharacterFacing.refl.meta.h
            ServerObjects/GameServerObjectBase.refl.h
            ServerObjects/GameServerObjectBase.refl.meta.h
            ServerObjects/Player/Config/PlayerConfig.refl.h
            ServerObjects/Player/Config/PlayerConfig.refl.meta.h
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
            ServerObjects/Projectile/Config/ProjectileConfig.refl.h
            ServerObjects/Projectile/Config/ProjectileConfig.refl.meta.h
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.meta.h
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.meta.h
            ServerObjects/Projectile/ProjectileServerObject.refl.h
            ServerObjects/Projectile/ProjectileServerObject.refl.meta.h
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.h
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.meta.h
            SimulationEvents/GameSimulationEventCallbacks.h
            SimulationEvents/GameSimulationStats.refl.h
            SimulationEvents/GameSimulationStats.refl.meta.h
            Stage/GameCollision.refl.h
            Stage/GameCollision.refl.meta.h
            Stage/GameStage.h
            State/GameFullState.refl.h
            State/GameFullState.refl.meta.h
            Systems/GameDeliberateSyncSystemList.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Game 
            AnimationEvents/DealDamageAnimationEvent.refl.h
            GameController/Config/GameConfig.refl.h
            GameController/GameController.refl.h
            GameplayEvents/DamageType.refl.h
            Markup/KillVolume.refl.h
            Markup/PlayerSpawn.refl.h
            NetworkEvents/GameMessages.refl.h
            NetworkEvents/GameNetworkData.refl.h
            NetworkEvents/GameNetworkEvents.refl.h
            NetworkEvents/GameNetworkExternals.refl.h
            ServerObjects/Bot/BotServerObject.refl.h
            ServerObjects/Bot/TestBot/TestBot.refl.h
            ServerObjects/CharacterFacing.refl.h
            ServerObjects/GameServerObjectBase.refl.h
            ServerObjects/Player/Config/PlayerConfig.refl.h
            ServerObjects/Player/PlayerServerObject.refl.h
            ServerObjects/Player/States/PlayerStateBase.refl.h
            ServerObjects/Player/States/PlayerStateBasicAttack.refl.h
            ServerObjects/Player/States/PlayerStateIdle.refl.h
            ServerObjects/Player/States/PlayerStateJump.refl.h
            ServerObjects/Player/States/PlayerStateMoving.refl.h
            ServerObjects/Projectile/Config/ProjectileConfig.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h
            ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.h
            ServerObjects/Projectile/ProjectileServerObject.refl.h
            ServerObjects/Projectile/Response/ProjectileResponseBase.refl.h
            SimulationEvents/GameSimulationStats.refl.h
            Stage/GameCollision.refl.h
            State/GameFullState.refl.h
            #REFL_PLACEHOLDER
            )

add_library(Game STATIC ${GENERIC_SRC_Game} ${GENERIC_HEADER_Game})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Game} ${GENERIC_HEADER_Game})

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Game})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -I${CLANG_HEADER_PATH} "-I$<JOIN:$<TARGET_PROPERTY:Game,INCLUDE_DIRECTORIES>,;-I>" -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       COMMAND_EXPAND_LISTS
                       VERBATIM
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

target_precompile_headers(Game PRIVATE GameCommon.h)

