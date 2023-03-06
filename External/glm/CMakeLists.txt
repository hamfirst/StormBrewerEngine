cmake_minimum_required(VERSION 3.20.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_glm 
            detail/glm.cpp
            )

set(GENERIC_HEADER_glm 
            simd/common.h
            simd/exponential.h
            simd/geometric.h
            simd/integer.h
            simd/matrix.h
            simd/packing.h
            simd/platform.h
            simd/trigonometric.h
            simd/vector_relational.h
            )

add_library(glm STATIC ${GENERIC_SRC_glm} ${GENERIC_HEADER_glm})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_glm} ${GENERIC_HEADER_glm})

