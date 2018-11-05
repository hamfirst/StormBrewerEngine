cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_EngineStubs 
            EngineStubs.cpp
            )

set(GENERIC_HEADER_EngineStubs 
            )

add_library(EngineStubs STATIC ${GENERIC_SRC_EngineStubs} ${GENERIC_HEADER_EngineStubs})

