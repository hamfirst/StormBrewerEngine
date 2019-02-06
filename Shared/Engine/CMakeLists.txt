cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_Engine 
            Engine.cpp
            EngineCommon.cpp
            EngineCommonPCH.cpp
            EngineState.cpp
            Asset/Asset.cpp
            Asset/AssetBundle.cpp
            Asset/AssetLoad.cpp
            Asset/AssetLoader.cpp
            Asset/AssetReferenceBase.cpp
            Asset/AudioAsset.cpp
            Asset/BinaryAsset.cpp
            Asset/BinaryAssetLoader.cpp
            Asset/ClientAssetLoader.cpp
            Asset/DocumentAsset.cpp
            Asset/DocumentAssetLoader.cpp
            Asset/FontAsset.cpp
            Asset/MusicAsset.cpp
            Asset/TextureAsset.cpp
            Atlas/AtlasEngineData.cpp
            Audio/AudioManager.cpp
            Audio/MusicManager.cpp
            Audio/MusicSpec.cpp
            Camera/Camera.cpp
            Component/Component.cpp
            Component/ComponentHandle.cpp
            Component/ComponentSystem.cpp
            Component/ComponentUpdateBucketList.cpp
            DrawList/DrawList.cpp
            Entity/Entity.cpp
            Entity/EntityHandle.cpp
            Entity/EntitySystem.cpp
            Input/BinaryControlBinding.cpp
            Input/ControlBindingHandleList.cpp
            Input/ControlBindingSet.cpp
            Input/ControlHandle.cpp
            Input/ControlId.cpp
            Input/GamepadState.cpp
            Input/InputState.cpp
            Input/KeyboardState.cpp
            Input/MouseState.cpp
            Input/PointerControlBinding.cpp
            Input/ScalarControlBinding.cpp
            Input/TextInputContext.cpp
            Input/VectorControlBinding.cpp
            Map/MapEffectLayerInstance.cpp
            Map/MapEffectLayerRenderer.cpp
            Map/MapInstance.cpp
            Map/MapManualTileLayerInstance.cpp
            Map/MapParalaxLayerInstance.cpp
            Map/MapSystem.cpp
            Profiler/Profiler.cpp
            Rendering/GeometryVertexBufferBuilder.cpp
            Rendering/RenderException.cpp
            Rendering/RenderState.cpp
            Rendering/RenderTarget.cpp
            Rendering/RenderUtil.cpp
            Rendering/Shader.cpp
            Rendering/ShaderProgram.cpp
            Rendering/Texture.cpp
            Rendering/VertexArray.cpp
            Rendering/VertexAttrib.cpp
            Rendering/VertexBuffer.cpp
            Rendering/VertexBufferBuilder.cpp
            Rendering/VertexList.cpp
            SaveFile/SaveFile.cpp
            Settings/EngineSettings.refl.cpp
            Shader/ShaderManager.cpp
            Sprite/SpriteEngineData.cpp
            Text/TextBackupFont.cpp
            Text/TextBufferBuilder.cpp
            Text/TextManager.cpp
            Text/TextRenderer.cpp
            UI/UIClickable.refl.cpp
            UI/UIManager.cpp
            UI/UIScriptInterface.cpp
            UI/UIScriptLoader.cpp
            UI/UITextInput.refl.cpp
            UI/UITextureBinding.cpp
            VisualEffect/VisualEffect.cpp
            VisualEffect/VisualEffectFuncs.cpp
            VisualEffect/VisualEffectHandle.cpp
            VisualEffect/VisualEffectInstance.cpp
            VisualEffect/VisualEffectManager.cpp
            Window/FakeWindow.cpp
            Window/Window.cpp
            Window/WindowManager.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Engine 
            Engine.h
            EngineCommon.h
            EngineState.h
            EngineStateFuncs.h
            Asset/Asset.h
            Asset/AssetBundle.h
            Asset/AssetLoad.h
            Asset/AssetLoader.h
            Asset/AssetManager.h
            Asset/AssetReference.h
            Asset/AssetReferenceBase.h
            Asset/AssetReloadCallback.h
            Asset/AssetSync.h
            Asset/AssetTypeMacros.h
            Asset/AudioAsset.h
            Asset/BinaryAsset.h
            Asset/BinaryAssetLoader.h
            Asset/ClientAssetLoader.h
            Asset/DocumentAsset.h
            Asset/DocumentAssetLoader.h
            Asset/FontAsset.h
            Asset/MusicAsset.h
            Asset/TextureAsset.h
            Atlas/AtlasEngineData.h
            Audio/AudioFormat.h
            Audio/AudioHandle.h
            Audio/AudioManager.h
            Audio/AudioSpec.h
            Audio/MusicManager.h
            Audio/MusicSpec.h
            Audio/VolumeCategory.h
            Camera/Camera.h
            Component/Component.h
            Component/ComponentHandle.h
            Component/ComponentIterator.h
            Component/ComponentList.h
            Component/ComponentRegistrationMacros.h
            Component/ComponentSystem.h
            Component/ComponentUpdateBucketList.h
            Component/ComponentUpdateRegistrationTemplates.h
            DrawList/DrawList.h
            Entity/Entity.h
            Entity/EntityHandle.h
            Entity/EntitySystem.h
            Input/BinaryControlBinding.h
            Input/ControlBinding.h
            Input/ControlBindingHandleList.h
            Input/ControlBindingList.h
            Input/ControlBindingSet.h
            Input/ControlHandle.h
            Input/ControlId.h
            Input/GamepadState.h
            Input/InputState.h
            Input/KeyboardState.h
            Input/MouseState.h
            Input/PointerControlBinding.h
            Input/ScalarControlBinding.h
            Input/TextInputContext.h
            Input/VectorControlBinding.h
            Map/MapEffectLayerInstance.h
            Map/MapEffectLayerRenderer.h
            Map/MapInstance.h
            Map/MapManualTileLayerInstance.h
            Map/MapParalaxLayerInstance.h
            Map/MapSystem.h
            Profiler/Profiler.h
            Rendering/GeometryVertexBufferBuilder.h
            Rendering/RenderErrorMacros.h
            Rendering/RenderException.h
            Rendering/Rendering.h
            Rendering/RenderSettings.h
            Rendering/RenderState.h
            Rendering/RenderTarget.h
            Rendering/RenderUtil.h
            Rendering/Shader.h
            Rendering/ShaderLiteral.h
            Rendering/ShaderProgram.h
            Rendering/Texture.h
            Rendering/VertexArray.h
            Rendering/VertexAttrib.h
            Rendering/VertexBuffer.h
            Rendering/VertexBufferBuilder.h
            Rendering/VertexDefinition.h
            Rendering/VertexList.h
            SaveFile/SaveFile.h
            SaveFile/SaveFileMetaFuncs.h
            Settings/EngineSettings.refl.h
            Settings/EngineSettings.refl.meta.h
            Shader/DefaultShader.h
            Shader/ShaderManager.h
            Sprite/SpriteEngineData.h
            Text/TextBackupFont.h
            Text/TextBufferBuilder.h
            Text/TextManager.h
            Text/TextRenderer.h
            Text/TextRenderMode.refl.h
            Text/TextRenderMode.refl.meta.h
            Text/TextWrap.h
            UI/UIClickable.refl.h
            UI/UIClickable.refl.meta.h
            UI/UIManager.h
            UI/UIScriptInterface.h
            UI/UIScriptLoader.h
            UI/UITextInput.refl.h
            UI/UITextInput.refl.meta.h
            UI/UITextureBinding.h
            VisualEffect/VisualEffect.h
            VisualEffect/VisualEffectFuncs.h
            VisualEffect/VisualEffectHandle.h
            VisualEffect/VisualEffectInstance.h
            VisualEffect/VisualEffectManager.h
            VisualEffect/VisualEffectTypes.refl.h
            VisualEffect/VisualEffectTypes.refl.meta.h
            Window/FakeWindow.h
            Window/Window.h
            Window/WindowManager.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Engine 
            Settings/EngineSettings.refl.h
            Text/TextRenderMode.refl.h
            UI/UIClickable.refl.h
            UI/UITextInput.refl.h
            VisualEffect/VisualEffectTypes.refl.h
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
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Engine} ${PLATFORM_SRC_Engine}
            ${GENERIC_HEADER_Engine} ${PLATFORM_HEADER_Engine})

set_target_properties(Engine PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT EngineCommon.h)
cotire(Engine)
