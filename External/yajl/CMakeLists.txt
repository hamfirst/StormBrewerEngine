cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DBSON_COMPILATION)

set(GENERIC_SRC_yajl 
            yajl_encode.c
            yajl_buf.c
            yajl_tree.c
            yajl.c
            yajl_lex.c
            yajl_alloc.c
            yajl_parser.c
            yajl_version.c
            yajl_gen.c
            )

set(GENERIC_HEADER_yajl 
            yajl_tree.h
            yajl_alloc.h
            yajl_encode.h
            yajl_buf.h
            yajl_parser.h
            yajl_version.h
            yajl_common.h
            yajl_bytestack.h
            yajl_parse.h
            yajl_lex.h
            yajl_gen.h
            )

add_library(yajl STATIC ${GENERIC_SRC_yajl} ${GENERIC_HEADER_yajl})

