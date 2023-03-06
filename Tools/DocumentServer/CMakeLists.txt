cmake_minimum_required(VERSION 3.20.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_DocumentServer 
            DocumentServer.cpp
            DocumentServerVCSGit.refl.cpp
            DocumentServerVCSPerforce.refl.cpp
            FileNameDatabase.cpp
            Main.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_DocumentServer 
            DocumentServer.h
            DocumentServerMessages.refl.h
            DocumentServerMessages.refl.meta.h
            DocumentServerVCS.refl.h
            DocumentServerVCS.refl.meta.h
            DocumentServerVCSGit.refl.h
            DocumentServerVCSGit.refl.meta.h
            DocumentServerVCSPerforce.refl.h
            DocumentServerVCSPerforce.refl.meta.h
            FileNameDatabase.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_DocumentServer 
            DocumentServerMessages.refl.h
            DocumentServerVCS.refl.h
            DocumentServerVCSGit.refl.h
            DocumentServerVCSPerforce.refl.h
            #REFL_PLACEHOLDER
            )

add_library(DocumentServer STATIC ${GENERIC_SRC_DocumentServer} ${GENERIC_HEADER_DocumentServer})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_DocumentServer} ${GENERIC_HEADER_DocumentServer})

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_DocumentServer})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -I${CLANG_HEADER_PATH} "-I$<JOIN:$<TARGET_PROPERTY:DocumentServer,INCLUDE_DIRECTORIES>,;-I>" -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       COMMAND_EXPAND_LISTS
                       VERBATIM
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

