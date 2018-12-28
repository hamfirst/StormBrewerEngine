cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_GameShared 
            GameLogicContainer.cpp
            GameLevelList.cpp
            GameStageManager.cpp
            GameSharedCommon.cpp
            GameWebrtc.cpp
            GameEventReconciler.cpp
            GameValidation.cpp
            Systems/GameServerObjectOverlapSystem.cpp
            Systems/GameLogicSystems.cpp
            Systems/CVCPushSystem.cpp
            BehaviorTree/BehaviorTreeTypeDatabase.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.reg.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameShared 
            GameProtocol.h
            GameValidation.h
            GameSharedCommon.h
            GameEventReconciler.h
            GameLogicContainer.h
            GameLevelListAsset.refl.h
            GameLevelListAsset.refl.meta.h
            GameLevelList.h
            GameStageManager.h
            Systems/GameLogicSystems.h
            Systems/GameServerObjectOverlapRegistrationMacros.h
            Systems/GameServerObjectOverlapSystem.h
            Systems/CVCPushSystem.h
            BehaviorTree/BehaviorTreeSerialize.h
            BehaviorTree/BehaviorTreeTypeDatabase.h
            BehaviorTree/BehaviorTree.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.meta.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameShared 
            GameLevelListAsset.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            #REFL_PLACEHOLDER
            )

foreach(REFL_FILE ${GENERIC_REFL_GameShared})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(GameShared STATIC ${GENERIC_SRC_GameShared} ${GENERIC_HEADER_GameShared})

set_target_properties(GameShared PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT GameSharedCommon.h)
cotire(GameShared)
