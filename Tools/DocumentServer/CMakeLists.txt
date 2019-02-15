cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_DocumentServer 
            DocumentServer.cpp
            FileNameDatabase.cpp
            Main.cpp
            #CPP_PLACEHOLDER
        DocumentServerVCSGit.cpp DocumentServerVCSGit.h)

set(GENERIC_HEADER_DocumentServer 
            DocumentServer.h
            DocumentServerMessages.refl.h
            DocumentServerMessages.refl.meta.h
            FileNameDatabase.h
            #HEADER_PLACEHOLDER
        DocumentServerVCS.h)

set(GENERIC_REFL_DocumentServer 
            DocumentServerMessages.refl.h
            #REFL_PLACEHOLDER
            )

foreach(REFL_FILE ${GENERIC_REFL_DocumentServer})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(DocumentServer STATIC ${GENERIC_SRC_DocumentServer} ${GENERIC_HEADER_DocumentServer})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_DocumentServer} ${GENERIC_HEADER_DocumentServer})

