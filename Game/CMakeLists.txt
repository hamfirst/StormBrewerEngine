cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Game 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Game 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            )
endif()

set(GENERIC_SRC_Game 
            ./GameMessages.refl.cpp
            ./GameSimulation.refl.cpp
            ./GameStage.cpp
            ./GameStageManager.cpp
            ./GameState.cpp
            )
add_library(Game ${GENERIC_SRC_Game} ${PLATFORM_SRC_Game} )