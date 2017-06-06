cmake_minimum_required(VERSION 3.0)

include_directories(. ../../. ../.././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../.././External/Web)
  set(PLATFORM_SRC_ENet 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../.././External/Windows)
  set(PLATFORM_SRC_ENet 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ENet 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ENet 
            )
endif()

set(GENERIC_SRC_ENet 
            ./callbacks.c
            ./compress.c
            ./host.c
            ./list.c
            ./packet.c
            ./peer.c
            ./protocol.c
            ./unix.c
            ./win32.c
            )
add_library(ENet ${GENERIC_SRC_ENet} ${PLATFORM_SRC_ENet} )