
cmake_minimum_required(VERSION 3.5)

include_directories(.. ../External)
add_definitions(-D_LINUX)

set(CMAKE_CXX_STANDARD 14)


add_library(Foundation STATIC
            Common.cpp
            Allocator/Allocator2D.cpp
            Assert/Assert.cpp
            Blit/Blit.cpp
            Blit/PixelBuffer.cpp
            Buffer/Buffer.cpp
            Buffer/BufferUtil.cpp
            Document/Document.cpp
            Document/DocumentCompiler.cpp
            FileSystem/File.cpp
            Json/Json.cpp
            Json/JsonSchema.cpp
            Json/JsonSchemaSerialize.cpp
            Network/Network.cpp
            Network/WebSocket.cpp
            Thread/Semaphore.cpp
            Time/FrameClock.cpp
            Time/StopWatch.cpp
            Time/Time.cpp)
            
