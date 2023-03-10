cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormBootstrap 
            StormBootstrap.cpp
  StormBootstrapPlatform.cpp)

set(GENERIC_HEADER_StormBootstrap 
            StormBootstrap.h
            )

add_library(StormBootstrap STATIC ${GENERIC_SRC_StormBootstrap} ${GENERIC_HEADER_StormBootstrap})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_StormBootstrap} ${GENERIC_HEADER_StormBootstrap})

