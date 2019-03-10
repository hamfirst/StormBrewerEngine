cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_Lobby 
            BuiltInChannel.refl.cpp
            ServerManager.refl.cpp
            NodeState.cpp
            SteamOpenIdValidatorPage.cpp
            BanList.refl.cpp
            LoadBalancer.cpp
            SharedTypes.refl.cpp
            Bot.refl.cpp
            Channel.refl.cpp
            GameData.refl.cpp
            CommandParse.cpp
            BotEndpoint.cpp
            ServerList.refl.cpp
            UserEndpoint.cpp
            BotConnection.refl.cpp
            GameServerEndpoint.cpp
            WelcomeInfo.refl.cpp
            Squad.refl.cpp
            Rewards.refl.cpp
            GameServerConnection.refl.cpp
            UserConnection.refl.cpp
            User.refl.cpp
            CoordinatorState.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Lobby 
            ServerManager.refl.meta.h
            SharedTypes.refl.h
            BotConnection.refl.h
            GameData.refl.meta.h
            User.refl.h
            CoordinatorState.h
            NodeState.h
            Rewards.refl.meta.h
            BuiltInChannel.refl.meta.h
            WelcomeInfo.refl.meta.h
            UserEndpoint.h
            Bot.refl.h
            GameServerMessages.refl.meta.h
            BanList.refl.h
            GameServerEndpoint.h
            CommandParse.h
            DataTypes.h
            GameServerConnection.refl.meta.h
            Squad.refl.h
            Rewards.refl.h
            BotMessages.refl.meta.h
            SteamServerMessages.refl.h
            BotConnection.refl.meta.h
            GameData.refl.h
            BanList.refl.meta.h
            UserConnection.refl.meta.h
            UserConnection.refl.h
            User.refl.meta.h
            Bot.refl.meta.h
            SharedTypes.refl.meta.h
            Channel.refl.meta.h
            UserConnectionMessages.refl.meta.h
            ServerList.refl.meta.h
            SteamServerMessages.refl.meta.h
            Squad.refl.meta.h
            UserConnectionMessages.refl.h
            WelcomeInfo.refl.h
            LobbyConfig.h
            GameServerMessages.refl.h
            BotMessages.refl.h
            SteamOpenIdValidatorPage.h
            GameServerConnection.refl.h
            LoadBalancer.h
            Channel.refl.h
            BuiltInChannel.refl.h
            ServerManager.refl.h
            ServerList.refl.h
            BotEndpoint.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Lobby 
            SharedTypes.refl.h
            BotConnection.refl.h
            User.refl.h
            Bot.refl.h
            BanList.refl.h
            Squad.refl.h
            Rewards.refl.h
            SteamServerMessages.refl.h
            GameData.refl.h
            UserConnection.refl.h
            UserConnectionMessages.refl.h
            WelcomeInfo.refl.h
            GameServerMessages.refl.h
            BotMessages.refl.h
            GameServerConnection.refl.h
            Channel.refl.h
            BuiltInChannel.refl.h
            ServerManager.refl.h
            ServerList.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Lobby})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(Lobby STATIC ${GENERIC_SRC_Lobby} ${GENERIC_HEADER_Lobby})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Lobby} ${GENERIC_HEADER_Lobby})

