cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameServerExe 
            Main.cpp
            )

set(GENERIC_HEADER_GameServerExe 
            )

add_library(GameServerExe STATIC ${GENERIC_SRC_GameServerExe} ${GENERIC_HEADER_GameServerExe})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameServerExe} ${GENERIC_HEADER_GameServerExe})

