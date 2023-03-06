cmake_minimum_required(VERSION 3.20.0)

file(READ ProjectSettings/ProjectName.txt PROJECT_NAME)
string(REGEX REPLACE "\n$" "" PROJECT_NAME "${PROJECT_NAME}")

file(WRITE ProjectSettings/ProjectName.h "#pragma once\n\nstatic const char * kProjectName = \"" ${PROJECT_NAME} "\";\n\n")

file(STRINGS ProjectSettings/ProjectEnv.txt CONFIG REGEX "^[ ]*[A-Za-z0-9_]+[ ]*=")
list(TRANSFORM CONFIG STRIP)
list(TRANSFORM CONFIG REPLACE "([^=]+)=[ ]*(.*)" "set(\\1 \"\\2\")\n")
cmake_language(EVAL CODE ${CONFIG})

project(${PROJECT_NAME})

message("-- Project Name: " ${PROJECT_NAME})

if(MSVC)
    set(CLANG_HEADER_PATH "${LLVM_ROOT_PATH}\\clang\\lib\\Headers")
else()
    set(CLANG_HEADER_PATH "${LLVM_ROOT_PATH}/clang/lib/Headers")
endif()

message("Building StormBrewerEngine")

set(CLIENT_LINK)
set(OUTPUTS)

option(EXPORT_TEST "Export Test Exes" ON)
option(EXPORT_DIST "Export Dist Exes" OFF)
option(ENABLE_PERFORCE "Build Editor With Perforce SCM" OFF)
option(GENERATE_REFL "Generate reflection data" ON)
option(GENERATE_PCH "Generate precompiled headers" ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CMakeDependentOption)

option(WEB "Emscripten Webassembly Build" OFF)
option(BUILD_CLIENT "Build Client" ON)
CMAKE_DEPENDENT_OPTION(BUILD_TOOLS "Build Client" ON "NOT WEB AND NOT ANDROID AND NOT IOS" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_SERVER "Build Server" ON "NOT WEB AND NOT ANDROID AND NOT IOS" OFF)
CMAKE_DEPENDENT_OPTION(DEVELOPMENT_BUILD "Development Build" ON "BUILD_TOOLS" OFF)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_DEBUG_POSTFIX "")

include(CMake/cotire.cmake)
include(CMake/StormBrewerEngine.cmake)

include(CMake/Tools.cmake)

include(CMake/Game.cmake)
include(CMake/LobbyServer.cmake)
include(CMake/Client.cmake)
include(CMake/Server.cmake)
include(CMake/Editor.cmake)

if(CMAKE_BUILD_TYPE EQUAL "RELWITHDEBUGINFO")
  if(MSVC)
    set_target_properties(GameClient PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(GameServer PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(Game PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(GameShared PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(LobbyShared PROPERTIES COMPILE_FLAGS "/Od")
  else()
    set_target_properties(GameClient PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(GameServer PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(Game PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(GameShared PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(LobbyShared PROPERTIES COMPILE_FLAGS "-O0")
  endif()
endif()

if(EXPORT_TEST)
  foreach(OUTPUT ${OUTPUTS})

    add_custom_target(Test${OUTPUT} ALL
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${OUTPUT}> ${CMAKE_CURRENT_SOURCE_DIR}/Test/
      DEPENDS ${OUTPUT}
      COMMENT "Copying to Test Directory"
    )

    set_target_properties(Test${OUTPUT} PROPERTIES FOLDER Executable)
    set_property(TARGET ${OUTPUT} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/Test")
    set_property(TARGET Test${OUTPUT} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/Test")

  endforeach()
endif()

if(EXPORT_DIST)
  foreach(OUTPUT ${OUTPUTS})

    add_custom_target(Dist${OUTPUT} ALL
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${OUTPUT}> ${CMAKE_CURRENT_SOURCE_DIR}/Distribute/Build/
      DEPENDS ${OUTPUT}
      COMMENT "Copying to Dist Directory"
    )
    
    set_target_properties(Dist${OUTPUT} PROPERTIES FOLDER Executable)

  endforeach()
endif()


