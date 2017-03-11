
cmake_minimum_required(VERSION 3.5)

include_directories(.. ../External /usr/include/freetype2)
add_definitions(-D_LINUX)

set(CMAKE_CXX_STANDARD 14)


add_library(Engine STATIC
            Asset/Asset.cpp
            Asset/AssetLoader.cpp
            Asset/AssetReferenceBase.cpp
            Asset/AudioAsset.cpp
            Asset/FontAsset.cpp
            Asset/MusicAsset.cpp
            Asset/TextureAsset.cpp
            Audio/AudioManager.cpp
            Audio/MusicSpec.cpp
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
            Rendering/GeometryVertexBufferBuilder.cpp
            Rendering/RenderException.cpp
            Rendering/RenderState.cpp
            Rendering/RenderTarget.cpp
            Rendering/RenderUtil.cpp
            Rendering/Shader.cpp
            Rendering/ShaderProgram.cpp
            Rendering/Texture.cpp
            Rendering/VertexArray.cpp
            Rendering/VertexBuffer.cpp
            Rendering/VertexBufferBuilder.cpp
            Rendering/VertexList.cpp
            Settings/EngineSettings.refl.cpp
            Text/TextBackupFont.cpp
            Text/TextBufferBuilder.cpp
            Text/TextManager.cpp
            Text/TextRenderer.cpp
            Window/FakeWindow.cpp
            Window/Window.cpp
            Window/WindowManager.cpp
            Engine.cpp)
                        
            
            
