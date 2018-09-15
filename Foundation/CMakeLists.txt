cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_Foundation 
            ./Common.cpp
            ./Document/DocumentCompiler.cpp
            ./Document/Document.cpp
            ./Lerp/LerpVar.cpp
            ./Lerp/LerpFuncs.cpp
            ./Time/FPSClock.cpp
            ./Time/StopWatch.cpp
            ./Time/FrameClock.cpp
            ./Time/Time.cpp
            ./Json/JsonArray.cpp
            ./Json/JsonDictionary.cpp
            ./Json/Json.cpp
            ./BasicTypes/BasicTypes.refl.cpp
            ./Bitset/Bitset.cpp
            ./FileSystem/Directory.cpp
            ./FileSystem/File.cpp
            ./FileSystem/Path.cpp
            ./Random/RandomGenerator.cpp
            ./Random/Random.cpp
            ./Any/Any.cpp
            ./Sequencer/Sequencer.cpp
            ./Thread/Semaphore.cpp
            ./Assert/Assert.cpp
            ./Network/Network.cpp
            ./Network/WebSocket.cpp
            ./Profiling/Profiling.cpp
            ./Blit/Blit.cpp
            ./Blit/PixelBuffer.cpp
            ./PropertyMeta/PropertyFieldDatabase.cpp
            ./SpatialDatabase/SpatialDatabase.cpp
            ./Math/Util.cpp
            ./Allocator/IdAllocator.cpp
            ./Allocator/Allocator2D.cpp
            ./Buffer/BufferUtil.cpp
            ./Buffer/Buffer.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Foundation 
            ./Common.h
            ./Document/DocumentCompiler.h
            ./Document/DocumentTypes.refl.h
            ./Document/DocumentTypes.refl.meta.h
            ./Document/DocumentLoader.h
            ./Document/Document.h
            ./Lerp/LerpFuncs.h
            ./Lerp/LerpVar.h
            ./Time/Time.h
            ./Time/FPSClock.h
            ./Time/StopWatch.h
            ./Time/FrameClock.h
            ./SparseList/SparseList.h
            ./Variant/Variant.h
            ./Json/Json.h
            ./Json/JsonArray.h
            ./Json/JsonDictionary.h
            ./Json/JsonType.h
            ./BasicTypes/BasicTypeHash.h
            ./BasicTypes/BasicTypeFuncs.h
            ./BasicTypes/BasicTypes.refl.meta.h
            ./BasicTypes/BasicTypes.refl.h
            ./Bitset/Bitset.h
            ./Waveform/Waveform.h
            ./Handle/Handle.h
            ./Handle/HandleList.h
            ./SkipField/SkipFieldIterator.h
            ./SkipField/SkipField.h
            ./CallList/CallList.h
            ./FileSystem/File.h
            ./FileSystem/Path.h
            ./FileSystem/Directory.h
            ./Random/Random.h
            ./Random/RandomGenerator.h
            ./Optional/Optional.h
            ./Optional/NullOpt.h
            ./Any/Any.h
            ./Sequencer/Sequencer.h
            ./Thread/MessageQueue.h
            ./Thread/Semaphore.h
            ./Frame/Frame.h
            ./Assert/Assert.h
            ./Network/Network.h
            ./Network/WebSocket.h
            ./Profiling/Profiling.h
            ./HistoryList/HistoryList.h
            ./Blit/PixelBuffer.h
            ./Blit/Blit.h
            ./PropertyMeta/PropertyFieldMetaData.h
            ./PropertyMeta/PropertyFieldDatabase.h
            ./PropertyMeta/PropertyFieldMetaFuncs.h
            ./Delegate/DelegateList.h
            ./Delegate/DelegateLink.h
            ./Delegate/Delegate.h
            ./SpatialDatabase/SpatialDatabase.h
            ./Math/Intersection.h
            ./Math/Math.h
            ./Math/Util.h
            ./Math/LineDrawing.h
            ./Allocator/Allocator2D.h
            ./Allocator/IdAllocator.h
            ./Buffer/Buffer.h
            ./Buffer/BufferUtil.h
            ./Pathfinding/Pathfinding.h
            ./Pathfinding/GraphPathfinding.h
            ./Pathfinding/GridPathfinding.h
            ./Pathfinding/PathfindingPathCache.h
            ./Pathfinding/PathfindingPath.h
            ./Pathfinding/PlatformerPathfinding.h
            ./Update/UpdateBucketList.h
            ./Update/UpdateRegistrationTemplates.h
            ./CircularBuffer/CircularBuffer.h
            ./CircularBuffer/CircularQueue.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Foundation 
            ./Document/DocumentTypes.refl.h
            ./BasicTypes/BasicTypes.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            )

set(PLATFORM_HEADER_Foundation 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_Foundation})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../. -I${CMAKE_CURRENT_SOURCE_DIR}/.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(Foundation ${GENERIC_SRC_Foundation} ${PLATFORM_SRC_Foundation}
            ${GENERIC_HEADER_Foundation} ${PLATFORM_HEADER_Foundation})