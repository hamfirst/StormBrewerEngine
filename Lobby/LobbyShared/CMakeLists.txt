cmake_minimum_required(VERSION 3.20.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_LobbyShared 
            LobbyGameFuncs.cpp
            LobbyValidation.cpp
            SharedTypes.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_LobbyShared 
            LobbyGameFuncs.h
            LobbyValidation.h
            SharedTypes.refl.h
            SharedTypes.refl.meta.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_LobbyShared 
            SharedTypes.refl.h
            #REFL_PLACEHOLDER
            )

add_library(LobbyShared STATIC ${GENERIC_SRC_LobbyShared} ${GENERIC_HEADER_LobbyShared})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_LobbyShared} ${GENERIC_HEADER_LobbyShared})

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_LobbyShared})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -I${CLANG_HEADER_PATH} "-I$<JOIN:$<TARGET_PROPERTY:LobbyShared,INCLUDE_DIRECTORIES>,;-I>" -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       COMMAND_EXPAND_LISTS
                       VERBATIM
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

