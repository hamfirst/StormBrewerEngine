cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

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
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_Foundation 
            ./Common.h
            ./Allocator/Allocator2D.h
            ./Allocator/IdAllocator.h
            ./Any/Any.h
            ./Assert/Assert.h
            ./BasicTypes/BasicTypeFuncs.h
            ./BasicTypes/BasicTypeHash.h
            ./BasicTypes/BasicTypes.refl.h
            ./BasicTypes/BasicTypes.refl.meta.h
            ./Bitset/Bitset.h
            ./Blit/Blit.h
            ./Blit/PixelBuffer.h
            ./Buffer/Buffer.h
            ./Buffer/BufferUtil.h
            ./CallList/CallList.h
            ./CircularBuffer/CircularBuffer.h
            ./CircularBuffer/CircularQueue.h
            ./Delegate/Delegate.h
            ./Delegate/DelegateLink.h
            ./Delegate/DelegateList.h
            ./Document/Document.h
            ./Document/DocumentCompiler.h
            ./Document/DocumentLoader.h
            ./Document/DocumentTypes.refl.h
            ./Document/DocumentTypes.refl.meta.h
            ./FileSystem/Directory.h
            ./FileSystem/File.h
            ./FileSystem/Path.h
            ./Frame/Frame.h
            ./Handle/Handle.h
            ./Handle/HandleList.h
            ./HistoryList/HistoryList.h
            ./Json/Json.h
            ./Json/JsonArray.h
            ./Json/JsonDictionary.h
            ./Json/JsonType.h
            ./Lerp/LerpFuncs.h
            ./Lerp/LerpVar.h
            ./Math/Intersection.h
            ./Math/LineDrawing.h
            ./Math/Math.h
            ./Math/Util.h
            ./Network/Network.h
            ./Network/WebSocket.h
            ./Optional/NullOpt.h
            ./Optional/Optional.h
            ./Pathfinding/GraphPathfinding.h
            ./Pathfinding/GridPathfinding.h
            ./Pathfinding/Pathfinding.h
            ./Pathfinding/PathfindingPath.h
            ./Pathfinding/PathfindingPathCache.h
            ./Pathfinding/PlatformerPathfinding.h
            ./Profiling/Profiling.h
            ./PropertyMeta/PropertyFieldDatabase.h
            ./PropertyMeta/PropertyFieldMetaData.h
            ./PropertyMeta/PropertyFieldMetaFuncs.h
            ./Random/Random.h
            ./Random/RandomGenerator.h
            ./Sequencer/Sequencer.h
            ./SkipField/SkipField.h
            ./SkipField/SkipFieldIterator.h
            ./SparseList/SparseList.h
            ./SpatialDatabase/SpatialDatabase.h
            ./Thread/MessageQueue.h
            ./Thread/Semaphore.h
            ./Time/FPSClock.h
            ./Time/FrameClock.h
            ./Time/StopWatch.h
            ./Time/Time.h
            ./Update/UpdateBucketList.h
            ./Update/UpdateRegistrationTemplates.h
            ./Variant/Variant.h
            ./Waveform/Waveform.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_Foundation 
            ./BasicTypes/BasicTypes.refl.h
            ./Document/DocumentTypes.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_Foundation 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_Foundation 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_Foundation 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_Foundation 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_Foundation 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE Foundation ${GENERIC_REFL_Foundation} ${PLATFORM_REFL_Foundation})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(Foundation ${GENERIC_SRC_Foundation} ${PLATFORM_SRC_Foundation}
            Foundation ${GENERIC_HEADER_Foundation} ${PLATFORM_HEADER_Foundation})