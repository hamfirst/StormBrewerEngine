cmake_minimum_required(VERSION 3.5)

include_directories(. External)

if(LINUX)
  add_definitions(-D_LINUX)
endif()

SET(CMAKE_CXX_STANDARD 14)

project(UniballClient)

link_directories(/usr/local/lib)

add_subdirectory(External/binpack)
add_subdirectory(External/enet)
add_subdirectory(External/gl3w)
add_subdirectory(External/ogg)
add_subdirectory(External/upng)
add_subdirectory(External/vorbis)
add_subdirectory(Engine)
add_subdirectory(Foundation)
add_subdirectory(StormData)
add_subdirectory(StormNet)
add_subdirectory(StormSockets)


