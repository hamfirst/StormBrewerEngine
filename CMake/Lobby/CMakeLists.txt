cmake_minimum_required(VERSION 3.0)

project(StormBrewerEngineLobby)

include(CMake/cotire.cmake)

include_directories(${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/StormTech
  ${PROJECT_SOURCE_DIR}/External
  ${PROJECT_SOURCE_DIR}/Lobby)


SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_DEBUG_POSTFIX "")

if (MSVC)
  add_definitions(-D_WINDOWS)
endif()

if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
endif()

if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/External/asio")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/mbedtls")

add_subdirectory("${PROJECT_SOURCE_DIR}/External/yajl")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/libbson")
add_subdirectory("${PROJECT_SOURCE_DIR}/External/mongoc")

add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/HurricaneDDS")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormBootstrap")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormSockets")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormData")

add_subdirectory("${PROJECT_SOURCE_DIR}/Lobby/Lobby")

set_target_properties(Lobby PROPERTIES FOLDER Lobby)

add_executable(LobbyExe Lobby/LobbyMain/MainCombined.cpp)

target_link_libraries(LobbyExe Lobby)
target_link_libraries(LobbyExe HurricaneDDS)
target_link_libraries(LobbyExe StormBootstrap)
target_link_libraries(LobbyExe StormSocketCPP)
target_link_libraries(LobbyExe StormData)
target_link_libraries(LobbyExe asio)
target_link_libraries(LobbyExe mbedtls)
target_link_libraries(LobbyExe mongoc)
target_link_libraries(LobbyExe libbson)
target_link_libraries(LobbyExe yajl)

if(UNIX)
  target_link_libraries(LobbyExe ssl crypto)
  target_link_libraries(LobbyExe stdc++fs)
  target_link_libraries(LobbyExe -Wl,--whole-archive pthread -Wl,--no-whole-archive)
  target_link_libraries(LobbyExe rt m c dl)
endif()
