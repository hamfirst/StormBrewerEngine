cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_resample 
            stage_impl.c
            smarc.c
            remez_lp.c
            filtering.c
            polyfilt.c
            multi_stage.c
            )

set(GENERIC_HEADER_resample 
            polyfilt.h
            multi_stage.h
            smarc.h
            remez_lp.h
            filtering.h
            stage_impl.h
            )

add_library(resample STATIC ${GENERIC_SRC_resample} ${GENERIC_HEADER_resample})

