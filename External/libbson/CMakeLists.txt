cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DBSON_COMPILATION)

set(GENERIC_SRC_libbson 
            bson-keys.c
            bson-iso8601.c
            bson-writer.c
            bson-utf8.c
            bson-context.c
            bson-atomic.c
            bson-oid.c
            bcon.c
            bson-error.c
            bson-reader.c
            bson-iter.c
            bson-md5.c
            bson-string.c
            bson-timegm.c
            bson-clock.c
            bson-version-functions.c
            bson-memory.c
            bson-json.c
            bson.c
            bson-value.c
            )

set(GENERIC_HEADER_libbson
            bson-private.h
            bson-error.h
            bson-string.h
            bson-stdint.h
            bson-macros.h
            bson-context-private.h
            bson-memory.h
            bson-oid.h
            bson.h
            bcon.h
            bson-version.h
            bson-timegm-private.h
            bson-atomic.h
            bson-context.h
            bson-md5.h
            bson-keys.h
            bson-iso8601-private.h
            bson-compat.h
            bson-endian.h
            bson-types.h
            bson-utf8.h
            b64_ntop.h
            bson-version-functions.h
            bson-iter.h
            bson-value.h
            bson-thread-private.h
            bson-config.h
            bson-writer.h
            bson-reader.h
            bson-stdint-win32.h
            bson-clock.h
            bson-json.h
            b64_pton.h
            )

add_library(libbson STATIC ${GENERIC_SRC_libbson} ${GENERIC_HEADER_libbson})

