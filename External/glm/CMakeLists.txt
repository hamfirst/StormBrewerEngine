cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_glm 
            detail/glm.cpp
            )

set(GENERIC_HEADER_glm 
            simd/common.h
            simd/exponential.h
            simd/packing.h
            simd/integer.h
            simd/vector_relational.h
            simd/platform.h
            simd/matrix.h
            simd/trigonometric.h
            simd/geometric.h
            )

add_library(glm STATIC ${GENERIC_SRC_glm} ${GENERIC_HEADER_glm})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_glm} ${GENERIC_HEADER_glm})

