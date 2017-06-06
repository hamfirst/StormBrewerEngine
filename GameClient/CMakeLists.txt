cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_GameClient 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_GameClient 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )
endif()

set(GENERIC_SRC_GameClient 
            ./GameContainer.cpp
            ./GameMode.cpp
            ./GameModeTestSprite.cpp
            ./GameRender.cpp
            )
add_library(GameClient ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient} )