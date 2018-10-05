cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_GameClientExe 
            Main.cpp
            )

set(GENERIC_HEADER_GameClientExe 
            )

add_library(GameClientExe STATIC ${GENERIC_SRC_GameClientExe} ${GENERIC_HEADER_GameClientExe})
