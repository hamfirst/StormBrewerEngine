cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_Foundation 
            Common.cpp
            Document/Document.cpp
            Document/DocumentCompiler.cpp
            Thread/Semaphore.cpp
            Lerp/LerpVar.cpp
            Lerp/LerpFuncs.cpp
            FileSystem/Directory.cpp
            FileSystem/Path.cpp
            FileSystem/File.cpp
            Allocator/Allocator2D.cpp
            Allocator/IdAllocator.cpp
            Blit/Blit.cpp
            Blit/PixelBuffer.cpp
            Any/Any.cpp
            Sequencer/Sequencer.cpp
            PropertyMeta/PropertyFieldDatabase.cpp
            Time/FPSClock.cpp
            Time/FrameClock.cpp
            Time/Time.cpp
            Time/StopWatch.cpp
            Assert/Assert.cpp
            BasicTypes/BasicTypes.refl.cpp
            SpatialDatabase/SpatialDatabase.cpp
            Buffer/Buffer.cpp
            Buffer/BufferUtil.cpp
            Bitset/Bitset.cpp
            Random/Random.cpp
            Random/RandomGenerator.cpp
            Network/Network.cpp
            Network/WebSocket.cpp
            Json/JsonDictionary.cpp
            Json/Json.cpp
            Json/JsonArray.cpp
            Profiling/Profiling.cpp
            Math/Util.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Foundation 
            Common.h
            SkipField/SkipField.h
            SkipField/SkipFieldIterator.h
            Document/DocumentCompiler.h
            Document/Document.h
            Document/DocumentTypes.refl.meta.h
            Document/DocumentTypes.refl.h
            Document/DocumentLoader.h
            Thread/Semaphore.h
            Thread/MessageQueue.h
            Delegate/Delegate.h
            Delegate/DelegateList.h
            Delegate/DelegateLink.h
            CallList/CallList.h
            Lerp/LerpVar.h
            Lerp/LerpFuncs.h
            FileSystem/File.h
            FileSystem/Directory.h
            FileSystem/Path.h
            Allocator/Allocator2D.h
            Allocator/IdAllocator.h
            Blit/PixelBuffer.h
            Blit/Blit.h
            Any/Any.h
            Sequencer/Sequencer.h
            PropertyMeta/PropertyFieldMetaData.h
            PropertyMeta/PropertyFieldDatabase.h
            PropertyMeta/PropertyFieldMetaFuncs.h
            SparseList/SparseList.h
            Pathfinding/Pathfinding.h
            Pathfinding/GraphPathfinding.h
            Pathfinding/PathfindingPathCache.h
            Pathfinding/PathfindingPath.h
            Pathfinding/PlatformerPathfinding.h
            Pathfinding/GridPathfinding.h
            Time/Time.h
            Time/StopWatch.h
            Time/FrameClock.h
            Time/FPSClock.h
            Frame/Frame.h
            Assert/Assert.h
            BasicTypes/BasicTypeHash.h
            BasicTypes/BasicTypes.refl.h
            BasicTypes/BasicTypes.refl.meta.h
            BasicTypes/BasicTypeFuncs.h
            Optional/Optional.h
            Optional/NullOpt.h
            Variant/Variant.h
            SpatialDatabase/SpatialDatabase.h
            CircularBuffer/CircularBuffer.h
            CircularBuffer/CircularQueue.h
            Handle/Handle.h
            Handle/HandleList.h
            Buffer/Buffer.h
            Buffer/BufferUtil.h
            Bitset/Bitset.h
            Waveform/Waveform.h
            Random/Random.h
            Random/RandomGenerator.h
            HistoryList/HistoryList.h
            Network/Network.h
            Network/WebSocket.h
            Json/JsonArray.h
            Json/JsonType.h
            Json/Json.h
            Json/JsonDictionary.h
            Update/UpdateBucketList.h
            Update/UpdateRegistrationTemplates.h
            Profiling/Profiling.h
            Math/Util.h
            Math/Math.h
            Math/LineDrawing.h
            Math/Intersection.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Foundation 
            Document/DocumentTypes.refl.h
            BasicTypes/BasicTypes.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_Foundation})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Foundation ${GENERIC_SRC_Foundation} ${PLATFORM_SRC_Foundation}
            ${GENERIC_HEADER_Foundation} ${PLATFORM_HEADER_Foundation})