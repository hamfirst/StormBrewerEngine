cmake_minimum_required(VERSION 2.8.9)
if (NOT DEFINED ENV{INCLUDEOS_PREFIX})
  set(ENV{INCLUDEOS_PREFIX} /usr/local)
endif()
include($ENV{INCLUDEOS_PREFIX}/includeos/pre.service.cmake)
project (StormBrewersIncludeOS)

set(INCLUDEOS ON)

option(GENERATE_REFL OFF)
option(GENERATE_PCH OFF)

# Human-readable name of your service
set(SERVICE_NAME "StormBrewerEngine Server")

# Name of your service binary
set(BINARY       "seed")

# Source files to be linked with OS library parts to form bootable image
set(SOURCES
  Project/GameServerExe/Main.cpp
  )

# To add your own include paths:
set(LOCAL_INCLUDES "." "./External" "./StormTech" "./Shared" "./Project")

# DRIVERS / PLUGINS:
set(DRIVERS
  virtionet     # Virtio networking
  vmxnet3
  boot_logger   # Display boot information
  #boot_logger   # Enable lots of logging from boot stage

  # Use "boot --drivers ." to see other drivers
  )

set(PLUGINS
  # syslogd    # Syslog over UDP

  # Use "boot --plugins ." to see other plugins
  )


# STATIC LIBRARIES:
set(LIBRARIES
  GameServerExe
  GameServer
  Game
  GameShared
  Runtime
  EngineStubs
  Foundation
  StormNetCustomBindings
  StormNet
  StormData
  StormSocketCPP
  binpack
  lua
  glm
  mbedtls
  )

# DEPENDENCIES:
set(DEPENDENCIES
  Project/GameServerExe/GameServerExe
  Project/GameServer/GameServer
  Project/Game/Game
  Project/GameShared/GameShared
  Shared/Runtime/Runtime
  Shared/EngineStubs/EngineStubs
  Shared/Foundation/Foundation
  StormTech/StormNetCustomBindings/StormNetCustomBindings
  StormTech/StormNet/StormNet
  StormTech/StormData/StormData
  StormTech/StormSockets/StormSocketCPP
  External/binpack/binpack
  External/lua/lua
  External/glm/glm
  External/mbedtls/mbedtls
  )

add_definitions(-D_INCLUDEOS)
add_definitions(-D_LINUX)

# include service build script
include($ENV{INCLUDEOS_PREFIX}/includeos/post.service.cmake)
#include($ENV{INCLUDEOS_PREFIX}/includeos/linux.service.cmake)


# Create in-memory filesystem from folder
diskbuilder(${CMAKE_SOURCE_DIR}/Assets)

message("-- IncludeOS root is " ${INSTALL_LOC})
message("-- Arch is " ${ARCH})

foreach(LIB ${LIBRARIES})
  target_include_directories(${LIB} SYSTEM PRIVATE ${INSTALL_LOC}/${ARCH}/include/libcxx)
  target_include_directories(${LIB} SYSTEM PRIVATE ${INSTALL_LOC}/${ARCH}/include/musl)
  target_include_directories(${LIB} SYSTEM PRIVATE ${INSTALL_LOC}/${ARCH}/include/libunwind)
  target_include_directories(${LIB} SYSTEM PRIVATE ${INSTALL_LOC}/${ARCH}/include)
  target_include_directories(${LIB} SYSTEM PRIVATE ${INSTALL_LOC}/api)
  target_include_directories(${LIB} SYSTEM PRIVATE ${INSTALL_LOC}/include)
endforeach()

