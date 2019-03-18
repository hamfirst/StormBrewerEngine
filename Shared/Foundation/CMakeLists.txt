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
            Allocator/Allocator2D.cpp
            Allocator/IdAllocator.cpp
            Any/Any.cpp
            Assert/Assert.cpp
            BasicTypes/BasicTypes.refl.cpp
            Bitset/Bitset.cpp
            Blackboard/Blackboard.cpp
            Blit/Blit.cpp
            Blit/PixelBuffer.cpp
            Buffer/Buffer.cpp
            Buffer/BufferUtil.cpp
            Common.cpp
            Document/Document.cpp
            Document/DocumentCompiler.cpp
            FileSystem/Directory.cpp
            FileSystem/File.cpp
            FileSystem/FileMapping.cpp
            FileSystem/FileSystemWatcher.cpp
            FileSystem/Path.cpp
            Json/Json.cpp
            Json/JsonArray.cpp
            Json/JsonDictionary.cpp
            Lerp/LerpFuncs.cpp
            Lerp/LerpVar.cpp
            Math/Util.cpp
            Network/Network.cpp
            Network/WebSocket.cpp
            Network/WebSocketWeb.cpp
            Profiling/Profiling.cpp
            PropertyMeta/PropertyFieldDatabase.cpp
            Random/Random.cpp
            Random/RandomGenerator.cpp
            Script/ScriptClass.cpp
            Script/ScriptClassInstance.cpp
            Script/ScriptClassRef.cpp
            Script/ScriptFuncPtr.cpp
            Script/ScriptFuncs.cpp
            Script/ScriptInterface.cpp
            Script/ScriptObject.cpp
            Script/ScriptState.cpp
            Script/ScriptValue.cpp
            Sequencer/Sequencer.cpp
            SpatialDatabase/SpatialDatabase.cpp
            Thread/Semaphore.cpp
            Time/FPSClock.cpp
            Time/FrameClock.cpp
            Time/StopWatch.cpp
            Time/Time.cpp
            TypeDatabase/TypeDatabase.cpp
            #CPP_PLACEHOLDER
  Network/HttpRequest.cpp Network/HttpRequest.h)

set(GENERIC_HEADER_Foundation 
            Allocator/Allocator2D.h
            Allocator/IdAllocator.h
            Allocator/PoolAllocator.h
            Any/Any.h
            Assert/Assert.h
            BasicTypes/BasicTypeFuncs.h
            BasicTypes/BasicTypeHash.h
            BasicTypes/BasicTypes.refl.h
            BasicTypes/BasicTypes.refl.meta.h
            Bitset/Bitset.h
            Blackboard/Blackboard.h
            Blit/Blit.h
            Blit/PixelBuffer.h
            Buffer/Buffer.h
            Buffer/BufferUtil.h
            CallList/CallList.h
            Castable/Castable.h
            CircularBuffer/CircularBuffer.h
            CircularBuffer/CircularQueue.h
            Common.h
            Delegate/Delegate.h
            Delegate/DelegateLink.h
            Delegate/DelegateList.h
            Document/Document.h
            Document/DocumentCompiler.h
            Document/DocumentLoader.h
            Document/DocumentTypes.refl.h
            Document/DocumentTypes.refl.meta.h
            FileSystem/Directory.h
            FileSystem/File.h
            FileSystem/FileMapping.h
            FileSystem/FileSystemWatcher.h
            FileSystem/Path.h
            Frame/Frame.h
            Handle/Handle.h
            Handle/HandleList.h
            HistoryList/HistoryList.h
            Json/Json.h
            Json/JsonArray.h
            Json/JsonDictionary.h
            Json/JsonType.h
            Lerp/LerpFuncs.h
            Lerp/LerpVar.h
            Math/Intersection.h
            Math/LineDrawing.h
            Math/Math.h
            Math/Util.h
            Network/Network.h
            Network/NetworkInternal.h
            Network/WebSocket.h
            Optional/NullOpt.h
            Optional/Optional.h
            Pathfinding/GraphPathfinding.h
            Pathfinding/GridPathfinding.h
            Pathfinding/Pathfinding.h
            Pathfinding/PathfindingPath.h
            Pathfinding/PathfindingPathCache.h
            Pathfinding/PlatformerPathfinding.h
            Preprocessor/Preprocessor.h
            Profiling/Profiling.h
            PropertyMeta/PropertyFieldDatabase.h
            PropertyMeta/PropertyFieldMetaData.h
            PropertyMeta/PropertyFieldMetaFuncs.h
            Random/Random.h
            Random/RandomGenerator.h
            Script/ScriptClass.h
            Script/ScriptClassDelegate.h
            Script/ScriptClassInstance.h
            Script/ScriptClassRef.h
            Script/ScriptFuncPtr.h
            Script/ScriptFuncs.h
            Script/ScriptInterface.h
            Script/ScriptInternal.h
            Script/ScriptObject.h
            Script/ScriptRegister.h
            Script/ScriptState.h
            Script/ScriptValue.h
            Sequencer/Sequencer.h
            SkipField/SkipField.h
            SkipField/SkipFieldIterator.h
            SparseList/SparseList.h
            SpatialDatabase/SpatialDatabase.h
            Thread/MessageQueue.h
            Thread/Semaphore.h
            Time/FPSClock.h
            Time/FrameClock.h
            Time/StopWatch.h
            Time/Time.h
            TypeDatabase/TypeDatabase.h
            Update/UpdateBucketList.h
            Update/UpdateRegistrationTemplates.h
            Variant/Variant.h
            Waveform/Waveform.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Foundation 
            BasicTypes/BasicTypes.refl.h
            Document/DocumentTypes.refl.h
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
