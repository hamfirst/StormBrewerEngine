cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_Engine 
            EngineState.cpp
            EngineCommon.cpp
            Engine.cpp
            EngineCommonPCH.cpp
            Atlas/AtlasEngineData.cpp
            Rendering/VertexAttrib.cpp
            Rendering/RenderUtil.cpp
            Rendering/VertexBuffer.cpp
            Rendering/ShaderProgram.cpp
            Rendering/VertexBufferBuilder.cpp
            Rendering/Shader.cpp
            Rendering/RenderState.cpp
            Rendering/VertexList.cpp
            Rendering/GeometryVertexBufferBuilder.cpp
            Rendering/RenderTarget.cpp
            Rendering/Texture.cpp
            Rendering/RenderException.cpp
            Rendering/VertexArray.cpp
            Sprite/SpriteEngineData.cpp
            VisualEffect/VisualEffectFuncs.cpp
            VisualEffect/VisualEffect.cpp
            VisualEffect/VisualEffectInstance.cpp
            VisualEffect/VisualEffectManager.cpp
            VisualEffect/VisualEffectHandle.cpp
            Audio/MusicManager.cpp
            Audio/AudioManager.cpp
            Audio/MusicSpec.cpp
            Shader/ShaderManager.cpp
            Window/Window.cpp
            Window/WindowManager.cpp
            Window/FakeWindow.cpp
            Profiler/Profiler.cpp
            DrawList/DrawList.cpp
            Asset/Asset.cpp
            Asset/TextureAsset.cpp
            Asset/AssetLoader.cpp
            Asset/AssetBundle.cpp
            Asset/MusicAsset.cpp
            Asset/AudioAsset.cpp
            Asset/AssetLoad.cpp
            Asset/DocumentAsset.cpp
            Asset/FontAsset.cpp
            Asset/ClientAssetLoader.cpp
            Asset/AssetReferenceBase.cpp
            Asset/DocumentAssetLoader.cpp
            Map/MapSystem.cpp
            Map/MapParalaxLayerInstance.cpp
            Map/MapInstance.cpp
            Map/MapEffectLayerRenderer.cpp
            Map/MapManualTileLayerInstance.cpp
            Map/MapEffectLayerInstance.cpp
            Settings/EngineSettings.refl.cpp
            Camera/Camera.cpp
            UI/UIClickablePtr.cpp
            UI/UIClickable.cpp
            UI/UIManager.cpp
            Component/Component.cpp
            Component/ComponentSystem.cpp
            Component/ComponentHandle.cpp
            Component/ComponentUpdateBucketList.cpp
            Text/TextManager.cpp
            Text/TextRenderer.cpp
            Text/TextBackupFont.cpp
            Text/TextBufferBuilder.cpp
            Input/ScalarControlBinding.cpp
            Input/ControlBindingSet.cpp
            Input/VectorControlBinding.cpp
            Input/ControlHandle.cpp
            Input/PointerControlBinding.cpp
            Input/InputState.cpp
            Input/BinaryControlBinding.cpp
            Input/ControlId.cpp
            Input/TextInputContext.cpp
            Input/ControlBindingHandleList.cpp
            Input/GamepadState.cpp
            Input/MouseState.cpp
            Input/KeyboardState.cpp
            Entity/EntitySystem.cpp
            Entity/EntityHandle.cpp
            Entity/Entity.cpp
            SaveFile/SaveFile.cpp
            Asset/BinaryAssetLoader.cpp
            Asset/BinaryAsset.cpp
            Asset/BinaryAsset.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Engine 
            EngineStateFuncs.h
            EngineCommon.h
            Engine.h
            EngineState.h
            Atlas/AtlasEngineData.h
            Rendering/ShaderProgram.h
            Rendering/RenderErrorMacros.h
            Rendering/VertexDefinition.h
            Rendering/RenderException.h
            Rendering/RenderUtil.h
            Rendering/Shader.h
            Rendering/VertexList.h
            Rendering/Rendering.h
            Rendering/RenderTarget.h
            Rendering/Texture.h
            Rendering/GeometryVertexBufferBuilder.h
            Rendering/VertexBufferBuilder.h
            Rendering/VertexBuffer.h
            Rendering/VertexArray.h
            Rendering/VertexAttrib.h
            Rendering/ShaderLiteral.h
            Rendering/RenderSettings.h
            Rendering/RenderState.h
            Sprite/SpriteEngineData.h
            VisualEffect/VisualEffect.h
            VisualEffect/VisualEffectFuncs.h
            VisualEffect/VisualEffectTypes.refl.meta.h
            VisualEffect/VisualEffectInstance.h
            VisualEffect/VisualEffectManager.h
            VisualEffect/VisualEffectHandle.h
            VisualEffect/VisualEffectTypes.refl.h
            Audio/MusicManager.h
            Audio/AudioHandle.h
            Audio/AudioFormat.h
            Audio/AudioSpec.h
            Audio/MusicSpec.h
            Audio/AudioManager.h
            Audio/VolumeCategory.h
            Shader/ShaderManager.h
            Shader/DefaultShader.h
            Window/Window.h
            Window/FakeWindow.h
            Window/WindowManager.h
            Profiler/Profiler.h
            DrawList/DrawList.h
            Asset/AssetLoad.h
            Asset/ClientAssetLoader.h
            Asset/FontAsset.h
            Asset/AssetReference.h
            Asset/AudioAsset.h
            Asset/AssetBundle.h
            Asset/AssetLoader.h
            Asset/DocumentAssetLoader.h
            Asset/AssetReloadCallback.h
            Asset/AssetReferenceBase.h
            Asset/DocumentAsset.h
            Asset/Asset.h
            Asset/AssetManager.h
            Asset/TextureAsset.h
            Asset/MusicAsset.h
            Asset/AssetSync.h
            Asset/AssetTypeMacros.h
            Map/MapManualTileLayerInstance.h
            Map/MapInstance.h
            Map/MapParalaxLayerInstance.h
            Map/MapSystem.h
            Map/MapEffectLayerRenderer.h
            Map/MapEffectLayerInstance.h
            Settings/EngineSettings.refl.h
            Settings/EngineSettings.refl.meta.h
            Camera/Camera.h
            UI/UIManager.h
            UI/UIClickable.h
            UI/UIClickablePtr.h
            Component/ComponentIterator.h
            Component/ComponentHandle.h
            Component/ComponentList.h
            Component/ComponentUpdateBucketList.h
            Component/ComponentRegistrationMacros.h
            Component/ComponentSystem.h
            Component/Component.h
            Component/ComponentUpdateRegistrationTemplates.h
            Text/TextManager.h
            Text/TextShaders.h
            Text/TextBackupFont.h
            Text/TextBufferBuilder.h
            Text/TextWrap.h
            Text/TextRenderer.h
            Input/TextInputContext.h
            Input/ControlBinding.h
            Input/MouseState.h
            Input/InputState.h
            Input/ControlId.h
            Input/GamepadState.h
            Input/PointerControlBinding.h
            Input/ScalarControlBinding.h
            Input/VectorControlBinding.h
            Input/ControlBindingList.h
            Input/ControlBindingSet.h
            Input/KeyboardState.h
            Input/ControlHandle.h
            Input/ControlBindingHandleList.h
            Input/BinaryControlBinding.h
            Entity/EntitySystem.h
            Entity/EntityHandle.h
            Entity/Entity.h
            SaveFile/SaveFileMetaFuncs.h
            SaveFile/SaveFile.h
            Asset/BinaryAssetLoader.h
            Asset/BinaryAsset.h
            Asset/BinaryAsset.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Engine 
            VisualEffect/VisualEffectTypes.refl.h
            Settings/EngineSettings.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_Engine 
            )

set(PLATFORM_HEADER_Engine 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_Engine 
            )

set(PLATFORM_HEADER_Engine 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_Engine 
            )

set(PLATFORM_HEADER_Engine 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Engine 
            )

set(PLATFORM_HEADER_Engine 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_Engine 
            )

set(PLATFORM_HEADER_Engine 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Engine 
            )

set(PLATFORM_HEADER_Engine 
            )
endif()


foreach(REFL_FILE ${GENERIC_REFL_Engine})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Engine STATIC ${GENERIC_SRC_Engine} ${PLATFORM_SRC_Engine}
            ${GENERIC_HEADER_Engine} ${PLATFORM_HEADER_Engine})
set_target_properties(Engine PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT EngineCommon.h)
cotire(Engine)
