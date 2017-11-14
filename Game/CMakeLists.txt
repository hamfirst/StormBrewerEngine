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
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Game 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Game 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Game 
            )
endif()

set(GENERIC_SRC_Game 
            ./GameCommon.cpp
            ./GameController.refl.cpp
            ./GameEventReconciler.cpp
            ./GameLevelList.cpp
            ./GameLogicContainer.cpp
            ./GameMessages.refl.cpp
            ./GameNetworkEvents.refl.cpp
            ./GameNetworkExternals.refl.cpp
            ./GameServerTypes.cpp
            ./GameSharedGlobalResources.cpp
            ./GameSharedInstanceResources.cpp
            ./GameStage.cpp
            ./GameStageManager.cpp
            ./GameValidation.cpp
            ./GameWebrtc.cpp
            ./AI/PlayerAI.cpp
            ./Data/PlayerSpawn.refl.reg.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.cpp
            ./ServerObjects/Player/PlayerServerObject.refl.reg.cpp
            ./ServerObjects/Player/States/PlayerStateDefault.refl.cpp
            )
add_library(Game ${GENERIC_SRC_Game} ${PLATFORM_SRC_Game} )