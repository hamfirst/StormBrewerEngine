cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameServerExe 
            Main.cpp
            )

set(GENERIC_HEADER_GameServerExe 
            )

add_library(GameServerExe STATIC ${GENERIC_SRC_GameServerExe} ${GENERIC_HEADER_GameServerExe})

