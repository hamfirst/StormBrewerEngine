cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Runtime 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Runtime 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Runtime 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Runtime 
            )
endif()

set(GENERIC_SRC_Runtime 
            ./Runtime.cpp
            ./RuntimeCommon.cpp
            ./Anchor/AnchorDef.refl.cpp
            ./Anchor/AnchorTypeDatabase.cpp
            ./Collision/CollisionSystem.cpp
            ./Component/ComponentInitData.refl.cpp
            ./Component/ComponentInitDataTypeDatabase.cpp
            ./Config/ConfigManager.cpp
            ./DocumentResource/DocumentResourceBase.cpp
            ./DocumentResource/DocumentResourceManager.cpp
            ./DocumentResource/DocumentResourceReference.cpp
            ./DocumentResource/DocumentResourceReferenceBase.cpp
            ./Entity/EntityDef.refl.cpp
            ./Entity/EntityResource.cpp
            ./FrameData/FrameData.refl.cpp
            ./Map/MapDef.refl.cpp
            ./Map/MapEffectLayerDef.refl.cpp
            ./Map/MapEffectLayerTypeDatabase.cpp
            ./Map/MapResource.cpp
            ./Mover/Mover.cpp
            ./Path/PathDef.refl.cpp
            ./Path/PathTypeDatabase.cpp
            ./Sprite/SpriteDef.refl.cpp
            ./Sprite/SpriteResource.cpp
            ./SpriteBase/SpriteBaseDef.refl.cpp
            ./TileSheet/TileSheetDef.refl.cpp
            ./TileSheet/TileSheetResource.cpp
            ./UI/UIDef.refl.cpp
            ./UI/UIElementTypeDatabase.cpp
            ./UI/UIResource.cpp
            ./VisualEffect/VisualEffectDef.refl.cpp
            ./VisualEffect/VisualEffectResource.cpp
            ./Volume/VolumeDef.refl.cpp
            ./Volume/VolumeTypeDatabase.cpp
            )
add_library(Runtime ${GENERIC_SRC_Runtime} ${PLATFORM_SRC_Runtime} )