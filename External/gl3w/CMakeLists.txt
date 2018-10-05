cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_gl3w 
            gl3w.c
            )

set(GENERIC_HEADER_gl3w 
            gl3w.h
            glcorearb.h
            )

add_library(gl3w STATIC ${GENERIC_SRC_gl3w} ${GENERIC_HEADER_gl3w})
