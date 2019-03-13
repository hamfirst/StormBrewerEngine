cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_Foundation 
            Common.cpp
            Document/DocumentCompiler.cpp
            Document/Document.cpp
            Lerp/LerpVar.cpp
            Lerp/LerpFuncs.cpp
            TypeDatabase/TypeDatabase.cpp
            Time/FPSClock.cpp
            Time/StopWatch.cpp
            Time/FrameClock.cpp
            Time/Time.cpp
            Json/JsonArray.cpp
            Json/JsonDictionary.cpp
            Json/Json.cpp
            BasicTypes/BasicTypes.refl.cpp
            Bitset/Bitset.cpp
            Script/ScriptFuncPtr.cpp
            Script/ScriptFuncs.cpp
            Script/ScriptState.cpp
            Script/ScriptClassRef.cpp
            Script/ScriptClassInstance.cpp
            Script/ScriptObject.cpp
            Script/ScriptInterface.cpp
            Script/ScriptValue.cpp
            Script/ScriptClass.cpp
            FileSystem/Directory.cpp
            FileSystem/FileSystemWatcher.cpp
            FileSystem/File.cpp
            FileSystem/Path.cpp
            FileSystem/FileMapping.cpp
            Random/RandomGenerator.cpp
            Random/Random.cpp
            Any/Any.cpp
            Sequencer/Sequencer.cpp
            Thread/Semaphore.cpp
            Assert/Assert.cpp
            Network/Network.cpp
            Network/WebSocket.cpp
            Profiling/Profiling.cpp
            Blit/Blit.cpp
            Blit/PixelBuffer.cpp
            PropertyMeta/PropertyFieldDatabase.cpp
            Blackboard/Blackboard.cpp
            SpatialDatabase/SpatialDatabase.cpp
            Math/Util.cpp
            Allocator/IdAllocator.cpp
            Allocator/Allocator2D.cpp
            Buffer/BufferUtil.cpp
            Buffer/Buffer.cpp
            #CPP_PLACEHOLDER
  Encoding/Base64.cpp Encoding/Base64.h Encoding/Url.cpp Encoding/Url.h)

set(GENERIC_HEADER_Foundation 
            Common.h
            Document/DocumentCompiler.h
            Document/DocumentTypes.refl.h
            Document/DocumentTypes.refl.meta.h
            Document/DocumentLoader.h
            Document/Document.h
            Lerp/LerpFuncs.h
            Lerp/LerpVar.h
            TypeDatabase/TypeDatabase.h
            Time/Time.h
            Time/FPSClock.h
            Time/StopWatch.h
            Time/FrameClock.h
            SparseList/SparseList.h
            Variant/Variant.h
            Json/Json.h
            Json/JsonArray.h
            Json/JsonDictionary.h
            Json/JsonType.h
            BasicTypes/BasicTypeHash.h
            BasicTypes/BasicTypeFuncs.h
            BasicTypes/BasicTypes.refl.meta.h
            BasicTypes/BasicTypes.refl.h
            Bitset/Bitset.h
            Script/ScriptClass.h
            Script/ScriptFuncPtr.h
            Script/ScriptFuncs.h
            Script/ScriptRegister.h
            Script/ScriptInternal.h
            Script/ScriptClassDelegate.h
            Script/ScriptState.h
            Script/ScriptObject.h
            Script/ScriptInterface.h
            Script/ScriptValue.h
            Script/ScriptClassRef.h
            Script/ScriptClassInstance.h
            Waveform/Waveform.h
            Handle/Handle.h
            Handle/HandleList.h
            SkipField/SkipFieldIterator.h
            SkipField/SkipField.h
            CallList/CallList.h
            FileSystem/File.h
            FileSystem/FileSystemWatcher.h
            FileSystem/Path.h
            FileSystem/Directory.h
            FileSystem/FileMapping.h
            Random/Random.h
            Random/RandomGenerator.h
            Optional/Optional.h
            Optional/NullOpt.h
            Any/Any.h
            Sequencer/Sequencer.h
            Thread/MessageQueue.h
            Thread/Semaphore.h
            Frame/Frame.h
            Assert/Assert.h
            Network/Network.h
            Network/WebSocket.h
            Profiling/Profiling.h
            HistoryList/HistoryList.h
            Castable/Castable.h
            Blit/PixelBuffer.h
            Blit/Blit.h
            PropertyMeta/PropertyFieldMetaData.h
            PropertyMeta/PropertyFieldDatabase.h
            PropertyMeta/PropertyFieldMetaFuncs.h
            Delegate/DelegateList.h
            Delegate/DelegateLink.h
            Delegate/Delegate.h
            Blackboard/Blackboard.h
            SpatialDatabase/SpatialDatabase.h
            Preprocessor/Preprocessor.h
            Math/Intersection.h
            Math/Math.h
            Math/Util.h
            Math/LineDrawing.h
            Allocator/Allocator2D.h
            Allocator/IdAllocator.h
            Allocator/PoolAllocator.h
            Buffer/Buffer.h
            Buffer/BufferUtil.h
            Pathfinding/Pathfinding.h
            Pathfinding/GraphPathfinding.h
            Pathfinding/GridPathfinding.h
            Pathfinding/PathfindingPathCache.h
            Pathfinding/PathfindingPath.h
            Pathfinding/PlatformerPathfinding.h
            Update/UpdateBucketList.h
            Update/UpdateRegistrationTemplates.h
            CircularBuffer/CircularBuffer.h
            CircularBuffer/CircularQueue.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Foundation 
            Document/DocumentTypes.refl.h
            BasicTypes/BasicTypes.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Foundation})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(Foundation STATIC ${GENERIC_SRC_Foundation} ${GENERIC_HEADER_Foundation})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Foundation} ${GENERIC_HEADER_Foundation})


if(MSVC)
  target_sources(Foundation INTERFACE $<INSTALL_INTERFACE:Foundation.natvis> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Foundation.natvis>)
endif()

set_target_properties(Foundation PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT Common.h)

if(GENERATE_PCH)
  cotire(Foundation)
endif()
