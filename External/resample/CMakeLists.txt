cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_resample 
            filtering.c
            multi_stage.c
            polyfilt.c
            remez_lp.c
            smarc.c
            stage_impl.c
            )

set(GENERIC_HEADER_resample 
            filtering.h
            multi_stage.h
            polyfilt.h
            remez_lp.h
            smarc.h
            stage_impl.h
            )

add_library(resample STATIC ${GENERIC_SRC_resample} ${GENERIC_HEADER_resample})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_resample} ${GENERIC_HEADER_resample})

