cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_Runtime 
            Runtime.cpp
            RuntimeCommon.cpp
            SpriteBase/SpriteBaseDef.refl.cpp
            SpriteBase/SpriteAnimationEventTypeDatabase.cpp
            SpriteBase/SpriteAnimationEventDef.refl.cpp
            Path/PathTypeDatabase.cpp
            Path/PathDef.refl.cpp
            Sprite/SpriteResource.cpp
            Sprite/SpriteDef.refl.cpp
            VisualEffect/VisualEffectDef.refl.cpp
            VisualEffect/VisualEffectResource.cpp
            Mover/Mover.cpp
            Anchor/AnchorDef.refl.cpp
            Anchor/AnchorTypeDatabase.cpp
            ServerObject/ServerObjectInitDataTypeDatabase.cpp
            ServerObject/ServerObjectOverlapSystem.cpp
            ServerObject/ServerObjectHandle.cpp
            ServerObject/ServerObjectResource.cpp
            ServerObject/ServerObjectSerialize.cpp
            ServerObject/ServerObjectUpdate.cpp
            ServerObject/ServerObjectDef.refl.cpp
            ServerObject/ServerObject.cpp
            ServerObject/ServerObjectInitData.refl.cpp
            ServerObject/ServerObjectEventSystem.cpp
            ServerObject/ServerObjectSystem.cpp
            ServerObject/ServerObjectManager.cpp
            ServerObject/ServerObjectEventDispatch.cpp
            Config/ConfigManager.cpp
            TileSheet/TileSheetDef.refl.cpp
            TileSheet/TileSheetResource.cpp
            Volume/VolumeDef.refl.cpp
            Volume/VolumeTypeDatabase.cpp
            Asset/Asset.cpp
            Map/MapDef.refl.cpp
            Map/MapCollision.cpp
            Map/MapEffectLayerTypeDatabase.cpp
            Map/MapEffectLayerDef.refl.cpp
            Map/MapPropertiesTypeDatabase.cpp
            Map/MapPropertiesDef.refl.cpp
            Map/MapResource.cpp
            DocumentResource/DocumentResourceReference.cpp
            DocumentResource/DocumentResourceBase.cpp
            DocumentResource/DocumentResourceReferenceBase.cpp
            DocumentResource/DocumentResourceManager.cpp
            FrameData/FrameData.refl.cpp
            FrameData/FrameDataExtract.cpp
            Collision/CollisionDatabase.cpp
            Collision/StaticCollisionDatabase.cpp
            Collision/DynamicCollisionDatabase.cpp
            UI/UIResource.cpp
            UI/UIDef.refl.cpp
            UI/UIElementTypeDatabase.cpp
            Component/ComponentInitData.refl.cpp
            Component/ComponentInitDataTypeDatabase.cpp
            Entity/EntityResource.cpp
            Entity/EntityDef.refl.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Runtime 
            Runtime.h
            RuntimeCommon.h
            SpriteBase/SpriteAnimationEventDef.refl.h
            SpriteBase/SpriteBaseDef.refl.meta.h
            SpriteBase/SpriteAnimationEventTypeDatabase.h
            SpriteBase/SpriteBaseDef.refl.h
            SpriteBase/SpriteAnimationEventDef.refl.meta.h
            SpriteBase/SpriteAnimationEventRegister.h
            Path/PathTypeRegister.h
            Path/PathDef.refl.meta.h
            Path/PathDef.refl.h
            Path/PathTypeDatabase.h
            Sprite/SpriteDef.refl.h
            Sprite/SpriteDef.refl.meta.h
            Sprite/SpriteResource.h
            VisualEffect/VisualEffectResource.h
            VisualEffect/VisualEffectDef.refl.h
            VisualEffect/VisualEffectDef.refl.meta.h
            GenericResource/GenericResource.h
            Mover/Mover.h
            Anchor/AnchorDef.refl.meta.h
            Anchor/AnchorTypeDatabase.h
            Anchor/AnchorDef.refl.h
            Anchor/AnchorTypeRegister.h
            ServerObject/ServerObjectInitData.refl.h
            ServerObject/ServerObject.h
            ServerObject/ServerObjectEventSystem.h
            ServerObject/ServerObjectEventRegister.h
            ServerObject/ServerObjectSystem.h
            ServerObject/ServerTypesNet.h
            ServerObject/ServerObjectEventDispatch.h
            ServerObject/ServerObjectSerialize.h
            ServerObject/ServerObjectInitDataTypeDatabase.h
            ServerObject/ServerObjectHandle.h
            ServerObject/ServerObjectRegistrationMacros.h
            ServerObject/ServerObjectOverlapSystem.h
            ServerObject/ServerObjectResource.h
            ServerObject/ServerObjectManager.h
            ServerObject/ServerObjectMetaFuncs.h
            ServerObject/ServerObjectUpdate.h
            ServerObject/ServerObjectInitData.refl.meta.h
            ServerObject/ServerObjectOverlapRegistrationMacros.h
            ServerObject/ServerObjectDef.refl.h
            ServerObject/ServerTypesJson.h
            ServerObject/ServerObjectDef.refl.meta.h
            Config/ConfigList.h
            Config/ConfigRegistrationMacros.h
            Config/ConfigManager.h
            Config/ConfigResource.h
            TileSheet/TileSheetDef.refl.h
            TileSheet/TileSheetResource.h
            TileSheet/TileSheetDef.refl.meta.h
            Volume/VolumeDef.refl.meta.h
            Volume/VolumeTypeDatabase.h
            Volume/VolumeTypeRegister.h
            Volume/VolumeDef.refl.h
            Asset/Asset.h
            Map/MapPropertiesTypeRegister.h
            Map/MapEffectLayerDef.refl.meta.h
            Map/MapTileJson.h
            Map/MapPropertiesDef.refl.meta.h
            Map/MapEffectLayerDef.refl.h
            Map/MapPropertiesTypeDatabase.h
            Map/MapEffectLayerTypeRegister.h
            Map/MapCollision.h
            Map/MapDef.refl.meta.h
            Map/MapEffectLayerTypeDatabase.h
            Map/MapMetaExtractor.h
            Map/MapTile.h
            Map/MapResource.h
            Map/MapDef.refl.h
            Map/MapPropertiesDef.refl.h
            DocumentResource/DocumentResourcePtr.h
            DocumentResource/DocumentResourceReferenceBase.h
            DocumentResource/DocumentResourceBase.h
            DocumentResource/DocumentResourceMacros.h
            DocumentResource/DocumentResourceReference.h
            DocumentResource/DocumentResourceManager.h
            DocumentResource/DocumentResourceLoader.h
            FrameData/FrameDataExtract.h
            FrameData/FrameData.refl.meta.h
            FrameData/FrameData.refl.h
            Collision/DynamicCollisionDatabase.h
            Collision/CollisionDatabaseResult.h
            Collision/IntersectionDatabase.h
            Collision/CollisionDatabase.h
            Collision/StaticCollisionDatabase.h
            Event/EventSystem.h
            Event/EventDispatcher.h
            Event/Event.h
            Event/EventHandler.h
            UI/UITypes.refl.h
            UI/UIElementTypeDatabase.h
            UI/UIDef.refl.meta.h
            UI/UIResource.h
            UI/UITypes.refl.meta.h
            UI/UIElementTypeRegister.h
            UI/UIDef.refl.h
            Component/ComponentInitData.refl.h
            Component/ComponentInitDataTypeDatabase.h
            Component/ComponentInitDataTypeDatabaseRegister.h
            Component/ComponentInitData.refl.meta.h
            Entity/EntityResource.h
            Entity/EntityDef.refl.h
            Entity/EntityDef.refl.meta.h
            Animation/AnimationState.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Runtime 
            SpriteBase/SpriteAnimationEventDef.refl.h
            SpriteBase/SpriteBaseDef.refl.h
            Path/PathDef.refl.h
            Sprite/SpriteDef.refl.h
            VisualEffect/VisualEffectDef.refl.h
            Anchor/AnchorDef.refl.h
            ServerObject/ServerObjectInitData.refl.h
            ServerObject/ServerObjectDef.refl.h
            TileSheet/TileSheetDef.refl.h
            Volume/VolumeDef.refl.h
            Map/MapEffectLayerDef.refl.h
            Map/MapDef.refl.h
            Map/MapPropertiesDef.refl.h
            FrameData/FrameData.refl.h
            UI/UITypes.refl.h
            UI/UIDef.refl.h
            Component/ComponentInitData.refl.h
            Entity/EntityDef.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Runtime 
            )

set(PLATFORM_HEADER_Runtime 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_Runtime})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Runtime ${GENERIC_SRC_Runtime} ${PLATFORM_SRC_Runtime}
            ${GENERIC_HEADER_Runtime} ${PLATFORM_HEADER_Runtime})