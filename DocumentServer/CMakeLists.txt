cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_DocumentServer 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_DocumentServer 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_DocumentServer 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_DocumentServer 
            )
endif()

set(GENERIC_SRC_DocumentServer 
            ./DocumentServer.cpp
            ./FileNameDatabase.cpp
            ./FileSystemWatcher.cpp
            ./Main.cpp
            )
add_library(DocumentServer ${GENERIC_SRC_DocumentServer} ${PLATFORM_SRC_DocumentServer} )