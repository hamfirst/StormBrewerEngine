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
            ./GameCamera.cpp
            ./GameClientController.refl.cpp
            ./GameClientEntitySync.cpp
            ./GameClientGlobalResources.cpp
            ./GameClientInputManager.cpp
            ./GameClientInstanceContainer.cpp
            ./GameClientInstanceData.cpp
            ./GameClientInstanceResources.cpp
            ./GameClientLevelLoader.cpp
            ./GameClientSave.cpp
            ./GameClientSystems.cpp
            ./GameClientUIManager.cpp
            ./GameContainer.cpp
            ./GameMode.cpp
            ./GameModeConnecting.cpp
            ./GameModeEndGame.cpp
            ./GameModeLoadingGlobal.cpp
            ./GameModeLocalMultiplayer.cpp
            ./GameModeLogo.cpp
            ./GameModeMainMenu.cpp
            ./GameModeNameSelect.cpp
            ./GameModeOfflineStaging.cpp
            ./GameModeOnlineGameplay.cpp
            ./GameModeSinglePlayerBots.cpp
            ./GameModeTutorial.cpp
            ./GameNetworkClient.cpp
            ./GameServerEventResponder.cpp
            ./Components/BallComponent.refl.cpp
            ./Components/BallComponent.refl.reg.cpp
            ./Components/FireComponent.refl.cpp
            ./Components/FireComponent.refl.reg.cpp
            ./Components/PlayerComponent.refl.cpp
            ./Components/PlayerComponent.refl.reg.cpp
            ./Components/PlayerExplodeComponent.refl.cpp
            ./Components/PlayerExplodeComponent.refl.reg.cpp
            ./Components/SwipeComponent.refl.cpp
            ./Components/SwipeComponent.refl.reg.cpp
            ./EffectLayers/CollisionDrawer.refl.cpp
            ./EffectLayers/CollisionDrawer.refl.reg.cpp
            ./UI/QuitGamePopup.cpp
            )
add_library(GameClient ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient} )