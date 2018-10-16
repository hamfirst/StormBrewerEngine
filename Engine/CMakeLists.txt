cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_Engine 
            EngineCommon.cpp
            Engine.cpp
            EngineState.cpp
            EngineCommonPCH.cpp
            Entity/Entity.cpp
            Entity/EntityHandle.cpp
            Entity/EntitySystem.cpp
            Text/TextBackupFont.cpp
            Text/TextManager.cpp
            Text/TextBufferBuilder.cpp
            Text/TextRenderer.cpp
            Map/MapEffectLayerInstance.cpp
            Map/MapParalaxLayerInstance.cpp
            Map/MapEffectLayerRenderer.cpp
            Map/MapSystem.cpp
            Map/MapInstance.cpp
            Map/MapManualTileLayerInstance.cpp
            Camera/Camera.cpp
            Input/PointerControlBinding.cpp
            Input/VectorControlBinding.cpp
            Input/MouseState.cpp
            Input/BinaryControlBinding.cpp
            Input/ControlId.cpp
            Input/ControlHandle.cpp
            Input/InputState.cpp
            Input/GamepadState.cpp
            Input/ControlBindingSet.cpp
            Input/ControlBindingHandleList.cpp
            Input/KeyboardState.cpp
            Input/TextInputContext.cpp
            Input/ScalarControlBinding.cpp
            Sprite/SpriteEngineData.cpp
            DrawList/DrawList.cpp
            Component/ComponentSystem.cpp
            Component/ComponentHandle.cpp
            Component/ComponentUpdateBucketList.cpp
            Component/Component.cpp
            UI/UIManager.cpp
            UI/UIElementTextInput.refl.cpp
            UI/UIElementText.refl.cpp
            UI/UIElementTextureSlice.refl.cpp
            UI/UIClickable.cpp
            UI/UIElementFullTexture.refl.cpp
            UI/UIClickablePtr.cpp
            UI/UIElementContainer.refl.cpp
            UI/UIElementHandle.cpp
            UI/UIElementExprBinding.cpp
            UI/UIElement.cpp
            UI/UIElementGradient.refl.cpp
            UI/UIElementExprFuncs.cpp
            UI/UIElementSpriteFrame.refl.cpp
            UI/UIElementShape.refl.cpp
            UI/Prototype/UIPrototypeSlider.cpp
            UI/Prototype/UIPrototypeTutorialPopup.cpp
            UI/Prototype/UIPrototypeButton.cpp
            UI/Prototype/UIPrototypeFullscreenButton.cpp
            UI/Prototype/UIPrototypeMuteButton.cpp
            UI/Prototype/UIPrototypeConfirmPopup.cpp
            UI/Prototype/UIPrototypeTextInput.cpp
            Rendering/RenderTarget.cpp
            Rendering/VertexBufferBuilder.cpp
            Rendering/Shader.cpp
            Rendering/ShaderProgram.cpp
            Rendering/VertexBuffer.cpp
            Rendering/RenderUtil.cpp
            Rendering/VertexArray.cpp
            Rendering/VertexList.cpp
            Rendering/VertexAttrib.cpp
            Rendering/RenderState.cpp
            Rendering/GeometryVertexBufferBuilder.cpp
            Rendering/Texture.cpp
            Rendering/RenderException.cpp
            VisualEffect/VisualEffectHandle.cpp
            VisualEffect/VisualEffectFuncs.cpp
            VisualEffect/VisualEffectManager.cpp
            VisualEffect/VisualEffectInstance.cpp
            VisualEffect/VisualEffect.cpp
            Asset/AssetReferenceBase.cpp
            Asset/ClientAssetLoader.cpp
            Asset/DocumentAssetLoader.cpp
            Asset/FontAsset.cpp
            Asset/AssetLoader.cpp
            Asset/AudioAsset.cpp
            Asset/AssetBundle.cpp
            Asset/AssetLoad.cpp
            Asset/MusicAsset.cpp
            Asset/DocumentAsset.cpp
            Asset/Asset.cpp
            Asset/TextureAsset.cpp
            Profiler/Profiler.cpp
            SaveFile/SaveFile.cpp
            Window/WindowManager.cpp
            Window/FakeWindow.cpp
            Window/Window.cpp
            Audio/AudioManager.cpp
            Audio/MusicSpec.cpp
            Audio/MusicManager.cpp
            Shader/ShaderManager.cpp
            Settings/EngineSettings.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Engine 
            Engine.h
            EngineState.h
            EngineStateFuncs.h
            EngineCommon.h
            Entity/EntitySystem.h
            Entity/Entity.h
            Entity/EntityHandle.h
            Text/TextManager.h
            Text/TextBufferBuilder.h
            Text/TextBackupFont.h
            Text/TextShaders.h
            Text/TextWrap.h
            Text/TextRenderer.h
            Map/MapSystem.h
            Map/MapManualTileLayerInstance.h
            Map/MapInstance.h
            Map/MapParalaxLayerInstance.h
            Map/MapEffectLayerRenderer.h
            Map/MapEffectLayerInstance.h
            Camera/Camera.h
            Input/BinaryControlBinding.h
            Input/ControlBindingSet.h
            Input/MouseState.h
            Input/VectorControlBinding.h
            Input/ControlHandle.h
            Input/ControlId.h
            Input/InputState.h
            Input/ControlBinding.h
            Input/PointerControlBinding.h
            Input/ControlBindingList.h
            Input/KeyboardState.h
            Input/TextInputContext.h
            Input/ScalarControlBinding.h
            Input/GamepadState.h
            Input/ControlBindingHandleList.h
            Sprite/SpriteEngineData.h
            DrawList/DrawList.h
            Component/ComponentIterator.h
            Component/ComponentUpdateBucketList.h
            Component/ComponentRegistrationMacros.h
            Component/ComponentSystem.h
            Component/ComponentList.h
            Component/Component.h
            Component/ComponentUpdateRegistrationTemplates.h
            Component/ComponentHandle.h
            UI/UIElement.h
            UI/UIElementText.refl.h
            UI/UIElementFullTexture.refl.h
            UI/UIElementSpriteFrame.refl.h
            UI/UIElementHandle.h
            UI/UIElementExprFuncs.h
            UI/UIElementShape.refl.h
            UI/UIElementContainer.refl.h
            UI/UIElementExprBinding.h
            UI/UIElementTextureSlice.refl.h
            UI/UIClickable.h
            UI/UIClickablePtr.h
            UI/UIElementTextInput.refl.h
            UI/UIElementExprTypes.refl.h
            UI/UICustomPropertyData.refl.h
            UI/UIManager.h
            UI/UIElementPtr.h
            UI/UIElementGradient.refl.h
            UI/Prototype/UIPrototypeTextInput.h
            UI/Prototype/UIPrototypeTutorialPopup.h
            UI/Prototype/UIPrototypeButton.h
            UI/Prototype/UIPrototypeSlider.h
            UI/Prototype/UISoundPrototypeEffects.h
            UI/Prototype/UIPrototypeConfirmPopup.h
            UI/Prototype/UIPrototypeMuteButton.h
            UI/Prototype/UIPrototypeFullscreenButton.h
            Rendering/Shader.h
            Rendering/VertexBufferBuilder.h
            Rendering/VertexDefinition.h
            Rendering/RenderException.h
            Rendering/RenderTarget.h
            Rendering/RenderState.h
            Rendering/ShaderProgram.h
            Rendering/ShaderLiteral.h
            Rendering/Texture.h
            Rendering/VertexAttrib.h
            Rendering/RenderSettings.h
            Rendering/VertexBuffer.h
            Rendering/VertexArray.h
            Rendering/RenderErrorMacros.h
            Rendering/RenderUtil.h
            Rendering/Rendering.h
            Rendering/VertexList.h
            Rendering/GeometryVertexBufferBuilder.h
            VisualEffect/VisualEffectInstance.h
            VisualEffect/VisualEffectFuncs.h
            VisualEffect/VisualEffectTypes.refl.h
            VisualEffect/VisualEffectManager.h
            VisualEffect/VisualEffectHandle.h
            VisualEffect/VisualEffect.h
            Asset/AssetLoad.h
            Asset/AudioAsset.h
            Asset/AssetReferenceBase.h
            Asset/AssetSync.h
            Asset/AssetBundle.h
            Asset/TextureAsset.h
            Asset/AssetManager.h
            Asset/AssetReloadCallback.h
            Asset/AssetLoader.h
            Asset/MusicAsset.h
            Asset/DocumentAssetLoader.h
            Asset/Asset.h
            Asset/FontAsset.h
            Asset/ClientAssetLoader.h
            Asset/DocumentAsset.h
            Asset/AssetReference.h
            Asset/AssetTypeMacros.h
            Profiler/Profiler.h
            SaveFile/SaveFileMetaFuncs.h
            SaveFile/SaveFile.h
            Window/FakeWindow.h
            Window/Window.h
            Window/WindowManager.h
            Audio/MusicManager.h
            Audio/AudioFormat.h
            Audio/AudioManager.h
            Audio/AudioHandle.h
            Audio/VolumeCategory.h
            Audio/MusicSpec.h
            Audio/AudioSpec.h
            Shader/ShaderManager.h
            Shader/DefaultShader.h
            Settings/EngineSettings.refl.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Engine 
            UI/UIElementText.refl.h
            UI/UIElementFullTexture.refl.h
            UI/UIElementSpriteFrame.refl.h
            UI/UIElementShape.refl.h
            UI/UIElementContainer.refl.h
            UI/UIElementTextureSlice.refl.h
            UI/UIElementTextInput.refl.h
            UI/UIElementExprTypes.refl.h
            UI/UICustomPropertyData.refl.h
            UI/UIElementGradient.refl.h
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
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Engine STATIC ${GENERIC_SRC_Engine} ${PLATFORM_SRC_Engine}
            ${GENERIC_HEADER_Engine} ${PLATFORM_HEADER_Engine})
set_target_properties(Engine PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT EngineCommon.h)
cotire(Engine)
