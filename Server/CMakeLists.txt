cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Server 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Server 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Server 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Server 
            )
endif()

set(GENERIC_SRC_Server 
            ./ServerCommon.cpp
            ./ServerObject/ServerObject.cpp
            ./ServerObject/ServerObjectHandle.cpp
            ./ServerObject/ServerObjectInitData.refl.cpp
            ./ServerObject/ServerObjectManager.cpp
            ./ServerObject/ServerObjectSerialize.cpp
            ./ServerObject/ServerObjectSystem.cpp
            ./ServerObject/ServerObjectUpdate.cpp
            )
add_library(Server ${GENERIC_SRC_Server} ${PLATFORM_SRC_Server} )