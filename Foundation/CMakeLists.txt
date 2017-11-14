cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Foundation 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Foundation 
            )
elseif (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Foundation 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            )
elseif (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Foundation 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            )
endif()

set(GENERIC_SRC_Foundation 
            ./Common.cpp
            ./Allocator/Allocator2D.cpp
            ./Allocator/IdAllocator.cpp
            ./Any/Any.cpp
            ./Assert/Assert.cpp
            ./BasicTypes/BasicTypes.refl.cpp
            ./Bitset/Bitset.cpp
            ./Blit/Blit.cpp
            ./Blit/PixelBuffer.cpp
            ./Buffer/Buffer.cpp
            ./Buffer/BufferUtil.cpp
            ./Document/Document.cpp
            ./Document/DocumentCompiler.cpp
            ./FileSystem/Directory.cpp
            ./FileSystem/File.cpp
            ./FileSystem/Path.cpp
            ./Json/Json.cpp
            ./Json/JsonArray.cpp
            ./Json/JsonDictionary.cpp
            ./Lerp/LerpFuncs.cpp
            ./Lerp/LerpVar.cpp
            ./Math/Util.cpp
            ./Network/Network.cpp
            ./Network/WebSocket.cpp
            ./Profiling/Profiling.cpp
            ./PropertyMeta/PropertyFieldDatabase.cpp
            ./Random/Random.cpp
            ./Random/RandomGenerator.cpp
            ./Sequencer/Sequencer.cpp
            ./SpatialDatabase/SpatialDatabase.cpp
            ./Thread/Semaphore.cpp
            ./Time/FPSClock.cpp
            ./Time/FrameClock.cpp
            ./Time/StopWatch.cpp
            ./Time/Time.cpp
            )
add_library(Foundation ${GENERIC_SRC_Foundation} ${PLATFORM_SRC_Foundation} )