cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_Runtime 
            ./RuntimeCommon.cpp
            ./Runtime.cpp
            ./Entity/EntityResource.cpp
            ./Entity/EntityDef.refl.cpp
            ./Map/MapCollision.cpp
            ./Map/MapPropertiesTypeDatabase.cpp
            ./Map/MapDef.refl.cpp
            ./Map/MapEffectLayerTypeDatabase.cpp
            ./Map/MapEffectLayerDef.refl.cpp
            ./Map/MapPropertiesDef.refl.cpp
            ./Map/MapResource.cpp
            ./Volume/VolumeTypeDatabase.cpp
            ./Volume/VolumeDef.refl.cpp
            ./Sprite/SpriteResource.cpp
            ./Sprite/SpriteDef.refl.cpp
            ./FrameData/FrameDataExtract.cpp
            ./FrameData/FrameData.refl.cpp
            ./Component/ComponentInitDataTypeDatabase.cpp
            ./Component/ComponentInitData.refl.cpp
            ./Collision/StaticCollisionDatabase.cpp
            ./Collision/DynamicCollisionDatabase.cpp
            ./Collision/CollisionDatabase.cpp
            ./UI/UIDef.refl.cpp
            ./UI/UIResource.cpp
            ./UI/UIElementTypeDatabase.cpp
            ./Config/ConfigManager.cpp
            ./Mover/Mover.cpp
            ./Path/PathTypeDatabase.cpp
            ./Path/PathDef.refl.cpp
            ./TileSheet/TileSheetDef.refl.cpp
            ./TileSheet/TileSheetResource.cpp
            ./VisualEffect/VisualEffectDef.refl.cpp
            ./VisualEffect/VisualEffectResource.cpp
            ./Asset/Asset.cpp
            ./ServerObject/ServerObjectInitData.refl.cpp
            ./ServerObject/ServerObjectHandle.cpp
            ./ServerObject/ServerObjectDef.refl.cpp
            ./ServerObject/ServerObjectUpdate.cpp
            ./ServerObject/ServerObjectInitDataTypeDatabase.cpp
            ./ServerObject/ServerObjectManager.cpp
            ./ServerObject/ServerObjectSerialize.cpp
            ./ServerObject/ServerObjectSystem.cpp
            ./ServerObject/ServerObject.cpp
            ./ServerObject/ServerObjectEventSystem.cpp
            ./ServerObject/ServerObjectOverlapSystem.cpp
            ./ServerObject/ServerObjectResource.cpp
            ./ServerObject/ServerObjectEventDispatch.cpp
            ./DocumentResource/DocumentResourceReference.cpp
            ./DocumentResource/DocumentResourceReferenceBase.cpp
            ./DocumentResource/DocumentResourceBase.cpp
            ./DocumentResource/DocumentResourceManager.cpp
            ./SpriteBase/SpriteAnimationEventTypeDatabase.cpp
            ./SpriteBase/SpriteBaseDef.refl.cpp
            ./SpriteBase/SpriteAnimationEventDef.refl.cpp
            ./Anchor/AnchorDef.refl.cpp
            ./Anchor/AnchorTypeDatabase.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Runtime 
            ./Runtime.h
            ./RuntimeCommon.h
            ./Entity/EntityDef.refl.meta.h
            ./Entity/EntityResource.h
            ./Entity/EntityDef.refl.h
            ./GenericResource/GenericResource.h
            ./Map/MapPropertiesTypeRegister.h
            ./Map/MapEffectLayerTypeRegister.h
            ./Map/MapEffectLayerTypeDatabase.h
            ./Map/MapEffectLayerDef.refl.meta.h
            ./Map/MapResource.h
            ./Map/MapDef.refl.h
            ./Map/MapCollision.h
            ./Map/MapMetaExtractor.h
            ./Map/MapTileJson.h
            ./Map/MapDef.refl.meta.h
            ./Map/MapPropertiesDef.refl.h
            ./Map/MapPropertiesDef.refl.meta.h
            ./Map/MapEffectLayerDef.refl.h
            ./Map/MapTile.h
            ./Map/MapPropertiesTypeDatabase.h
            ./Volume/VolumeTypeDatabase.h
            ./Volume/VolumeTypeRegister.h
            ./Volume/VolumeDef.refl.h
            ./Volume/VolumeDef.refl.meta.h
            ./Sprite/SpriteDef.refl.h
            ./Sprite/SpriteDef.refl.meta.h
            ./Sprite/SpriteResource.h
            ./FrameData/FrameData.refl.h
            ./FrameData/FrameData.refl.meta.h
            ./FrameData/FrameDataExtract.h
            ./Component/ComponentInitDataTypeDatabaseRegister.h
            ./Component/ComponentInitData.refl.h
            ./Component/ComponentInitDataTypeDatabase.h
            ./Component/ComponentInitData.refl.meta.h
            ./Collision/CollisionDatabase.h
            ./Collision/StaticCollisionDatabase.h
            ./Collision/DynamicCollisionDatabase.h
            ./Collision/IntersectionDatabase.h
            ./Collision/CollisionDatabaseResult.h
            ./UI/UIElementTypeRegister.h
            ./UI/UITypes.refl.h
            ./UI/UIResource.h
            ./UI/UITypes.refl.meta.h
            ./UI/UIDef.refl.meta.h
            ./UI/UIElementTypeDatabase.h
            ./UI/UIDef.refl.h
            ./Animation/AnimationState.h
            ./Config/ConfigManager.h
            ./Config/ConfigResource.h
            ./Config/ConfigRegistrationMacros.h
            ./Config/ConfigList.h
            ./Mover/Mover.h
            ./Path/PathTypeDatabase.h
            ./Path/PathDef.refl.meta.h
            ./Path/PathTypeRegister.h
            ./Path/PathDef.refl.h
            ./Event/EventDispatcher.h
            ./Event/EventHandler.h
            ./Event/EventSystem.h
            ./Event/Event.h
            ./TileSheet/TileSheetDef.refl.meta.h
            ./TileSheet/TileSheetResource.h
            ./TileSheet/TileSheetDef.refl.h
            ./VisualEffect/VisualEffectResource.h
            ./VisualEffect/VisualEffectDef.refl.meta.h
            ./VisualEffect/VisualEffectDef.refl.h
            ./Asset/Asset.h
            ./ServerObject/ServerObjectManager.h
            ./ServerObject/ServerObjectSerialize.h
            ./ServerObject/ServerObjectDef.refl.h
            ./ServerObject/ServerObjectOverlapSystem.h
            ./ServerObject/ServerObjectEventRegister.h
            ./ServerObject/ServerObjectInitDataTypeDatabase.h
            ./ServerObject/ServerObjectSystem.h
            ./ServerObject/ServerObjectDef.refl.meta.h
            ./ServerObject/ServerObjectInitData.refl.h
            ./ServerObject/ServerTypesNet.h
            ./ServerObject/ServerObjectUpdate.h
            ./ServerObject/ServerObjectHandle.h
            ./ServerObject/ServerObjectInitData.refl.meta.h
            ./ServerObject/ServerObjectOverlapRegistrationMacros.h
            ./ServerObject/ServerObjectEventDispatch.h
            ./ServerObject/ServerTypesJson.h
            ./ServerObject/ServerObjectRegistrationMacros.h
            ./ServerObject/ServerObjectResource.h
            ./ServerObject/ServerObjectEventSystem.h
            ./ServerObject/ServerObject.h
            ./ServerObject/ServerObjectMetaFuncs.h
            ./DocumentResource/DocumentResourceReference.h
            ./DocumentResource/DocumentResourceLoader.h
            ./DocumentResource/DocumentResourceMacros.h
            ./DocumentResource/DocumentResourcePtr.h
            ./DocumentResource/DocumentResourceBase.h
            ./DocumentResource/DocumentResourceReferenceBase.h
            ./DocumentResource/DocumentResourceManager.h
            ./SpriteBase/SpriteAnimationEventRegister.h
            ./SpriteBase/SpriteAnimationEventTypeDatabase.h
            ./SpriteBase/SpriteAnimationEventDef.refl.meta.h
            ./SpriteBase/SpriteBaseDef.refl.meta.h
            ./SpriteBase/SpriteAnimationEventDef.refl.h
            ./SpriteBase/SpriteBaseDef.refl.h
            ./Anchor/AnchorTypeDatabase.h
            ./Anchor/AnchorDef.refl.meta.h
            ./Anchor/AnchorTypeRegister.h
            ./Anchor/AnchorDef.refl.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Runtime 
            ./Entity/EntityDef.refl.h
            ./Map/MapDef.refl.h
            ./Map/MapPropertiesDef.refl.h
            ./Map/MapEffectLayerDef.refl.h
            ./Volume/VolumeDef.refl.h
            ./Sprite/SpriteDef.refl.h
            ./FrameData/FrameData.refl.h
            ./Component/ComponentInitData.refl.h
            ./UI/UITypes.refl.h
            ./UI/UIDef.refl.h
            ./Path/PathDef.refl.h
            ./TileSheet/TileSheetDef.refl.h
            ./VisualEffect/VisualEffectDef.refl.h
            ./ServerObject/ServerObjectDef.refl.h
            ./ServerObject/ServerObjectInitData.refl.h
            ./SpriteBase/SpriteAnimationEventDef.refl.h
            ./SpriteBase/SpriteBaseDef.refl.h
            ./Anchor/AnchorDef.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_Runtime})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Runtime ${GENERIC_SRC_Runtime} ${PLATFORM_SRC_Runtime}
            ${GENERIC_HEADER_Runtime} ${PLATFORM_HEADER_Runtime})