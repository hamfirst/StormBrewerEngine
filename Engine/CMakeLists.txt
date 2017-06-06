cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Engine 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Engine 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Engine 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Engine 
            )
endif()

set(GENERIC_SRC_Engine 
            ./Engine.cpp
            ./EngineCommon.cpp
            ./EngineCommonPCH.cpp
            ./Asset/Asset.cpp
            ./Asset/AssetLoad.cpp
            ./Asset/AssetLoader.cpp
            ./Asset/AssetReferenceBase.cpp
            ./Asset/AudioAsset.cpp
            ./Asset/DocumentAsset.cpp
            ./Asset/DocumentAssetLoader.cpp
            ./Asset/FontAsset.cpp
            ./Asset/MusicAsset.cpp
            ./Asset/TextureAsset.cpp
            ./Audio/AudioManager.cpp
            ./Audio/MusicSpec.cpp
            ./Camera/Camera.cpp
            ./DrawList/DrawList.cpp
            ./Entity/EntityRender.cpp
            ./Input/BinaryControlBinding.cpp
            ./Input/ControlBindingHandleList.cpp
            ./Input/ControlBindingSet.cpp
            ./Input/ControlHandle.cpp
            ./Input/ControlId.cpp
            ./Input/GamepadState.cpp
            ./Input/InputState.cpp
            ./Input/KeyboardState.cpp
            ./Input/MouseState.cpp
            ./Input/PointerControlBinding.cpp
            ./Input/ScalarControlBinding.cpp
            ./Input/TextInputContext.cpp
            ./Input/VectorControlBinding.cpp
            ./Map/MapEngineInstance.cpp
            ./Map/MapManualTileLayerInstance.cpp
            ./Map/MapRender.cpp
            ./Rendering/GeometryVertexBufferBuilder.cpp
            ./Rendering/RenderException.cpp
            ./Rendering/RenderState.cpp
            ./Rendering/RenderTarget.cpp
            ./Rendering/RenderUtil.cpp
            ./Rendering/Shader.cpp
            ./Rendering/ShaderProgram.cpp
            ./Rendering/Texture.cpp
            ./Rendering/VertexArray.cpp
            ./Rendering/VertexBuffer.cpp
            ./Rendering/VertexBufferBuilder.cpp
            ./Rendering/VertexList.cpp
            ./Settings/EngineSettings.refl.cpp
            ./Shader/ShaderManager.cpp
            ./Sprite/SpriteEngineData.cpp
            ./Text/TextBackupFont.cpp
            ./Text/TextBufferBuilder.cpp
            ./Text/TextManager.cpp
            ./Text/TextRenderer.cpp
            ./Window/FakeWindow.cpp
            ./Window/Window.cpp
            ./Window/WindowManager.cpp
            )
add_library(Engine ${GENERIC_SRC_Engine} ${PLATFORM_SRC_Engine} )