cmake_minimum_required(VERSION 2.8.9)
if (NOT DEFINED ENV{INCLUDEOS_PREFIX})
  set(ENV{INCLUDEOS_PREFIX} /usr/local)
endif()
include($ENV{INCLUDEOS_PREFIX}/includeos/pre.service.cmake)
project (service)

# Human-readable name of your service
set(SERVICE_NAME "StormBrewerEngine Server")

# Name of your service binary
set(BINARY       "seed")

# Source files to be linked with OS library parts to form bootable image
set(SOURCES
  Dummy.cpp # ...add more here
  )

# To add your own include paths:
set(LOCAL_INCLUDES "." "./External" "./StormTech" "./Shared" "./Project")

# DRIVERS / PLUGINS:
set(DRIVERS
  # virtionet   # Virtio networking driver
  # virtioblk   # Virtio block device driver
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
  External/binpack/binpack
  External/lua/lua
  External/glm/glm
  External/mbedtls/mbedtls
  )


# include service build script
include($ENV{INCLUDEOS_PREFIX}/includeos/post.service.cmake)

# Create in-memory filesystem from folder
#diskbuilder(my_folder)