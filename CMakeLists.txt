cmake_minimum_required(VERSION 3.0)

file(READ ProjectSettings/ProjectName.txt PROJECT_NAME)
file(WRITE ProjectSettings/ProjectName.h "#pragma once\n\nstatic const char * kProjectName = \"" ${PROJECT_NAME} "\";\n\n")

project(${PROJECT_NAME})

message("-- Project Name: " ${PROJECT_NAME})

include(CMake/StormBrewerEngine.cmake)
include(CMake/cotire.cmake)

include_directories(${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

add_subdirectory(Project/Game)
add_subdirectory(Project/GameShared)

set_target_properties(Game PROPERTIES FOLDER Project)
set_target_properties(GameShared PROPERTIES FOLDER Project)

set(CLIENT_LINK)
set(OUTPUTS)

option(EXPORT_TEST ON)
option(EXPORT_DIST OFF)
option(ENABLE_PERFORCE OFF)
option(GENERATE_REFL ON)
option(GENERATE_PCH ON)



if(${ENABLE_PERFORCE})
  message("-- Enabling perforce")
endif()

if(MSVC)
  add_definitions(-D_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING)
endif()

if(BUILD_CLIENT OR BUILD_TOOLS)
  add_subdirectory(Project/GameClient)
  add_subdirectory(Project/GameClientExe)
  
  set_target_properties(GameClient PROPERTIES FOLDER Project)
  set_target_properties(GameClientExe PROPERTIES FOLDER Project)

  add_subdirectory(Lobby/LobbyClientConnection)
  set_target_properties(LobbyClientConnection PROPERTIES FOLDER Lobby)
  
  if(ANDROID)
    add_library(ClientExe SHARED Dummy.cpp)
  elseif(IOS)

    file(GLOB_RECURSE IOSAssets "${PROJECT_SOURCE_DIR}/Test/Assets/*")

    foreach(FullFile ${IOSAssets})

      file(RELATIVE_PATH ResFile "${PROJECT_SOURCE_DIR}/Test/Assets/" "${FullFile}")
      get_filename_component(Dir ${ResFile} DIRECTORY)
      #message(STATUS "Adding asset file: ${ResFile}")

      set_source_files_properties(
        "${FullFile}" PROPERTIES MACOSX_PACKAGE_LOCATION "${Dir}")

      message(STATUS "Source map ${FullFile} ${Dir}")
    endforeach(FullFile)

    add_executable(ClientExe MACOSX_BUNDLE Dummy.cpp "${IOSAssets}")

  elseif(WEB)
    add_definitions(-D_WEB)
    include_directories(External/Web)

    file(GLOB_RECURSE ClientSrc
      ${PROJECT_SOURCE_DIR}/Project/GameClientExe/*.cpp
      ${PROJECT_SOURCE_DIR}/Project/GameClient/*.cpp
      ${PROJECT_SOURCE_DIR}/Project/Game/*.cpp
      ${PROJECT_SOURCE_DIR}/Shared/Runtime/*.cpp
      ${PROJECT_SOURCE_DIR}/Shared/Engine/*.cpp)

    add_executable(ClientExe ${ClientSrc})
  else()
    add_executable(ClientExe Dummy.cpp)
  endif()

  if(MSVC)
    target_link_libraries(ClientExe GameClientExe)
    target_link_libraries(ClientExe GameClient)
    target_link_libraries(ClientExe Game)
    target_link_libraries(ClientExe GameShared)
    target_link_libraries(ClientExe Runtime)
    target_link_libraries(ClientExe Engine)
    target_link_libraries(ClientExe SDL2main)

    set_target_properties(ClientExe PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:GameClientExe.lib /WHOLEARCHIVE:GameClient.lib /WHOLEARCHIVE:Game.lib /WHOLEARCHIVE:Runtime.lib /WHOLEARCHIVE:Engine.lib")
  elseif(IOS)
    target_link_libraries(ClientExe -Wl,-all_load GameClientExe -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load GameClient -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load Game -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load GameShared -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load Runtime -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load Engine -Wl,-noall_load)
  elseif(NOT WEB)
    target_link_libraries(ClientExe -Wl,--whole-archive GameClientExe -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive GameClient -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive Game -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive GameShared -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive Runtime -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive Engine -Wl,--no-whole-archive)
  endif()

  if(NOT WEB)
    target_link_libraries(ClientExe Runtime)
    target_link_libraries(ClientExe Engine)
  endif()

  target_link_libraries(ClientExe Foundation)
  target_link_libraries(ClientExe LobbyClientConnection)
  target_link_libraries(ClientExe StormNetCustomBindings)
  target_link_libraries(ClientExe StormWebrtcClientAPI)
  target_link_libraries(ClientExe StormWebrtcServerAPI)
  target_link_libraries(ClientExe StormSocketCPP)
  target_link_libraries(ClientExe StormExpr)
  target_link_libraries(ClientExe StormNet)
  target_link_libraries(ClientExe StormData)
  target_link_libraries(ClientExe binpack)
  target_link_libraries(ClientExe lua)
  target_link_libraries(ClientExe glm)
  target_link_libraries(ClientExe gl3w)
  target_link_libraries(ClientExe lodepng)
  target_link_libraries(ClientExe resample)
  target_link_libraries(ClientExe vorbis)
  target_link_libraries(ClientExe ogg)
  target_link_libraries(ClientExe freetype)

  if(WEB)
    add_custom_command(TARGET ClientExe PRE_LINK COMMAND ${PROJECT_SOURCE_DIR}/BuildFinalAssets.exe WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  else()

    target_link_libraries(ClientExe StormNetBindingsEnet)
    target_link_libraries(ClientExe StormNet)
    target_link_libraries(ClientExe StormWebrtc)
    target_link_libraries(ClientExe asio)
    target_link_libraries(ClientExe ENet)
    target_link_libraries(ClientExe usrsctp-static)
    target_link_libraries(ClientExe mbedtls)

    if(MSVC)
      if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
        target_link_libraries(ClientExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\x64\\libEGL.lib)
        target_link_libraries(ClientExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\x64\\libGLESv2.lib)
      else()
        target_link_libraries(ClientExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\libEGL.lib)
        target_link_libraries(ClientExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\libGLESv2.lib)
      endif()

      target_link_libraries(ClientExe Winmm.lib)
      target_link_libraries(ClientExe Version.lib)
      target_link_libraries(ClientExe Imm32.lib)
      target_link_libraries(ClientExe SDL2-static)
    elseif(ANDROID)
      target_link_libraries(ClientExe dl)
      target_link_libraries(ClientExe SDL2)
    elseif(IOS)
      target_link_libraries(ClientExe
        "-framework AVFoundation"
        "-framework Foundation"
        "-framework OpenGLES"
        "-framework UIKit"
        "-framework AVKit"
        "-framework QuartzCore"
        "-framework CoreGraphics"
        "-framework GameController"
        "-framework MediaPlayer"
        "-framework CoreMotion"
        )

      add_definitions(-D_IOS)

      set_target_properties(ClientExe PROPERTIES
        BUNDLE YES
        BUNDLE_EXTENSION "app"
        MACOSX_BUNDLE YES
        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2" # iPhone/iPad
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ""
        XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
        XCODE_ATTRIBUTE_WRAPPER_EXTENSION "app"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "10.0"
        MACOSX_BUNDLE_GUI_IDENTIFIER "StormBrewerEngineTest"
        MACOSX_BUNDLE_BUNDLE_NAME "StormBrewerEngineTest"
        RESOURCE "${IOSAssets}"
      )

      target_link_libraries(ClientExe SDL2-static)
      target_link_libraries(ClientExe dl pthread)

    else()
      if(UNIX AND NOT APPLE)
        target_link_libraries(ClientExe SDL2-static)
      endif()

      target_link_libraries(ClientExe stdc++fs)
      target_link_libraries(ClientExe dl pthread)
    endif()
  endif()

  set_target_properties(ClientExe PROPERTIES FOLDER Executable)
  set(OUTPUTS ${OUTPUTS} ClientExe)
endif()

if(BUILD_SERVER OR BUILD_TOOLS)
  add_subdirectory(Project/GameServer)
  add_subdirectory(Project/GameServerExe)
  
  set_target_properties(GameServer PROPERTIES FOLDER Project)
  set_target_properties(GameServerExe PROPERTIES FOLDER Project)

  add_subdirectory(Lobby/LobbyServerConnection)
  set_target_properties(LobbyServerConnection PROPERTIES FOLDER Lobby)

  add_executable(ServerExe Dummy.cpp)

  if(MSVC)
    target_link_libraries(ServerExe GameServerExe)
    target_link_libraries(ServerExe GameServer)
    target_link_libraries(ServerExe Game)
    target_link_libraries(ServerExe GameShared)
    target_link_libraries(ServerExe Runtime)

    set_target_properties(ServerExe PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:GameServerExe.lib /WHOLEARCHIVE:GameServer.lib /WHOLEARCHIVE:Game.lib /WHOLEARCHIVE:Runtime.lib")

  else()
    target_link_libraries(ServerExe -Wl,--whole-archive GameServerExe -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive GameServer -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive Game -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive GameShared -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive Runtime -Wl,--no-whole-archive)
  endif()

  target_link_libraries(ServerExe LobbyServerConnection)
  target_link_libraries(ServerExe EngineStubs)
  target_link_libraries(ServerExe Foundation)
  target_link_libraries(ServerExe binpack)
  target_link_libraries(ServerExe lua)
  target_link_libraries(ServerExe StormNetCustomBindings)
  target_link_libraries(ServerExe StormNetBindingsEnet)
  target_link_libraries(ServerExe StormNet)
  target_link_libraries(ServerExe StormData)
  target_link_libraries(ServerExe StormWebrtc)
  target_link_libraries(ServerExe StormWebrtcServerAPI)
  target_link_libraries(ServerExe StormWebrtcClientAPI)
  target_link_libraries(ServerExe StormBootstrap)
  target_link_libraries(ServerExe StormSocketCPP)
  target_link_libraries(ServerExe glm)
  target_link_libraries(ServerExe asio)
  target_link_libraries(ServerExe ENet)
  target_link_libraries(ServerExe usrsctp-static)
  target_link_libraries(ServerExe mbedtls)

  if(UNIX)
    target_link_libraries(ServerExe stdc++fs)
    target_link_libraries(ServerExe -Wl,--whole-archive pthread -Wl,--no-whole-archive)
    target_link_libraries(ServerExe rt m c dl)

    #set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
    #set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")

    #set_target_properties(ServerExe PROPERTIES LINK_SEARCH_START_STATIC 1)
    #set_target_properties(ServerExe PROPERTIES LINK_SEARCH_END_STATIC 1)
  endif()

  set_target_properties(ServerExe PROPERTIES FOLDER Executable)
  set(OUTPUTS ${OUTPUTS} ServerExe)

  add_subdirectory(Lobby/Lobby)
  set_target_properties(Lobby PROPERTIES FOLDER Lobby)

  add_executable(LobbyExe Lobby/LobbyMain/MainCombined.cpp)

  target_link_libraries(LobbyExe Lobby)
  target_link_libraries(LobbyExe HurricaneDDS)
  target_link_libraries(LobbyExe StormBootstrap)
  target_link_libraries(LobbyExe StormSocketCPP)
  target_link_libraries(LobbyExe StormData)
  target_link_libraries(LobbyExe asio)
  target_link_libraries(LobbyExe mbedtls)
  target_link_libraries(LobbyExe mongoc)
  target_link_libraries(LobbyExe libbson)
  target_link_libraries(LobbyExe yajl)

  if(UNIX)
    target_link_libraries(LobbyExe ssl crypto)
    target_link_libraries(LobbyExe stdc++fs)
    target_link_libraries(LobbyExe -Wl,--whole-archive pthread -Wl,--no-whole-archive)
    target_link_libraries(LobbyExe rt m c dl)
  endif()

  set_target_properties(LobbyExe PROPERTIES FOLDER Executable)
  set(OUTPUTS ${OUTPUTS} LobbyExe)
endif()

if(BUILD_TOOLS)
  add_executable(generatecmake Tools/GenerateCMake/Main.cpp)
  set_target_properties(generatecmake PROPERTIES FOLDER Tools)

  if(NOT MSVC)
	  target_link_libraries(generatecmake stdc++fs)
  endif()

  add_custom_command(TARGET generatecmake POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:generatecmake> ${CMAKE_CURRENT_SOURCE_DIR}
  )

  add_executable(addcode Dummy.cpp ProjectSettings/ProjectNetworkSettings.h)
  target_link_libraries(addcode addcodelib TemplateLib git2)
  set_target_properties(addcodelib PROPERTIES FOLDER Tools)
  set_target_properties(addcode PROPERTIES FOLDER Executable)

  if(NOT MSVC)
	  target_link_libraries(addcode stdc++fs)
  endif()

  set_target_properties(addcode PROPERTIES CXX_STANDARD 17)

  if(MSVC)
	  link_directories("C:\\Dev\\llvm-build\\RelWithDebInfo\\lib")
  else()
    link_directories("/usr/local/lib")
  endif()

  add_executable(DistFetch Dummy.cpp)
  target_link_libraries(DistFetch DistFetchLib DistFetcher StormSocketCPP mbedtls asio)
  set_target_properties(DistFetch PROPERTIES FOLDER Executable)

  if(NOT MSVC)
    target_link_libraries(DistFetch stdc++fs pthread)
  endif()

  add_executable(DistUpload Dummy.cpp)
  target_link_libraries(DistUpload DistUploadLib StormSocketCPP mbedtls asio)
  set_target_properties(DistUpload PROPERTIES FOLDER Executable)

  if(NOT MSVC)
    target_link_libraries(DistUpload stdc++fs pthread)
  endif()

  add_executable(stormrefl StormTech/StormRefl/main.cpp StormTech/StormRefl/StormReflOutput.cpp)
  set_target_properties(stormrefl PROPERTIES FOLDER Tools)

  target_link_libraries(stormrefl
    clangFrontend
    clangSerialization
    clangDriver
    clangParse
    clangSema
    clangAnalysis
    clangAST
    clangBasic
    clangEdit
    clangLex
    clangTooling
  )

  if(MSVC)
    target_link_libraries(stormrefl libclang)
  else()
    target_link_libraries(stormrefl clang)
  endif()

	target_link_libraries(stormrefl
	  LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
	  LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
	  LLVMX86AsmPrinter # MC, Support, X86Utils
	  LLVMX86Info # MC, Support, Target
	  LLVMX86Utils # Core, Support
	  LLVMipo
	  LLVMScalarOpts
	  LLVMInstCombine
	  LLVMTransformUtils
	  LLVMAnalysis
	  LLVMTarget
	  LLVMOption # Support
	  LLVMMCParser # MC, Support
	  LLVMMC # Object, Support
	  LLVMObject # BitReader, Core, Support
	  LLVMBitReader # Core, Support
	  LLVMCore # Support
	  LLVMSupport
	  #LLVMDebugInfoDWARF
	  LLVMBinaryFormat
	  LLVMProfileData
	)

  if(MSVC)
    target_include_directories(stormrefl PUBLIC C:\\Dev\\llvm\\tools\\clang\\include C:\\Dev\\llvm-build\\tools\\clang\\include C:\\Dev\\llvm\\include C:\\Dev\\llvm-build\\include)
    target_compile_options(stormrefl PRIVATE "/MD" "/O2")
    target_link_libraries(stormrefl Mincore.lib)
    STRING (REGEX REPLACE "[/|-]RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  else()
    target_compile_options(stormrefl PUBLIC "-fno-rtti" "-O3")
    target_link_libraries(stormrefl -Wl,--whole-archive pthread -Wl,--no-whole-archive)
    target_link_libraries(stormrefl ncurses stdc++fs z rt m c dl)
  endif()

  add_executable(documentserver Dummy.cpp)
  set_target_properties(documentserver PROPERTIES FOLDER Executable)

  target_link_libraries(documentserver DocumentServer Foundation StormSocketCPP StormData git2 asio mbedtls binpack)

  if(NOT MSVC)
    target_link_libraries(documentserver -Wl,--whole-archive pthread -Wl,--no-whole-archive)
    target_link_libraries(documentserver GL GLU stdc++fs z rt m c dl)
  endif()

  if(ENABLE_PERFORCE)
    target_compile_definitions(DocumentServer PRIVATE -DENABLE_PERFORCE)

    if(MSVC)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/windows/libclient.lib)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/windows/librpc.lib)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/windows/libsupp.lib)
    elseif(APPLE)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/mac/libclient.a)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/mac/librpc.a)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/mac/libsupp.a)
    else()
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/linux/libclient.a)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/linux/librpc.a)
      target_link_libraries(documentserver ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/linux/libsupp.a)

      find_package(OpenSSL 1.0.2 REQUIRED)
      target_link_libraries(documentserver ${OPENSSL_LIBRARIES})
    endif()
  endif()

  find_package(Qt5Widgets CONFIG REQUIRED)
  find_package(Qt5OpenGL CONFIG REQUIRED)

  add_executable(editor Dummy.cpp)
  set_target_properties(editor PROPERTIES FOLDER Executable)

  add_dependencies(Foundation stormrefl)
  add_dependencies(Engine stormrefl)
  add_dependencies(Runtime stormrefl)
  add_dependencies(Game stormrefl)
  add_dependencies(GameServer stormrefl)
  add_dependencies(GameClient stormrefl)
  add_dependencies(Editor stormrefl)

  if(MSVC)
    target_link_libraries(editor Editor)
    target_link_libraries(editor GameClient)
    target_link_libraries(editor GameServer)
    target_link_libraries(editor Game)
    target_link_libraries(editor GameShared)
    target_link_libraries(editor Runtime)
    target_link_libraries(editor Engine)

    set_target_properties(editor PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:Editor.lib /WHOLEARCHIVE:GameClient.lib /WHOLEARCHIVE:GameServer.lib /WHOLEARCHIVE:Game.lib /WHOLEARCHIVE:Runtime.lib /WHOLEARCHIVE:Engine.lib")
  elseif(NOT WEB)
    target_link_libraries(editor -Wl,--whole-archive Editor -Wl,--no-whole-archive)
    target_link_libraries(editor -Wl,--whole-archive GameClient -Wl,--no-whole-archive)
    target_link_libraries(editor -Wl,--whole-archive GameServer -Wl,--no-whole-archive)
    target_link_libraries(editor -Wl,--whole-archive Game -Wl,--no-whole-archive)
    target_link_libraries(editor -Wl,--whole-archive GameShared -Wl,--no-whole-archive)
    target_link_libraries(editor -Wl,--whole-archive Runtime -Wl,--no-whole-archive)
    target_link_libraries(editor -Wl,--whole-archive Engine -Wl,--no-whole-archive)
  endif()

  target_link_libraries(editor LobbyServerConnection)
  target_link_libraries(editor Foundation)
  target_link_libraries(editor StormNetCustomBindings)
  target_link_libraries(editor StormNetBindingsEnet)
  target_link_libraries(editor StormNet)
  target_link_libraries(editor StormExpr)
  target_link_libraries(editor StormData)
  target_link_libraries(editor DistFetcher)
  target_link_libraries(editor StormSocketCPP)

  target_link_libraries(editor StormWebrtcServerAPI)
  target_link_libraries(editor StormWebrtcClientAPI)
  target_link_libraries(editor StormWebrtc)
  target_link_libraries(editor asio)
  target_link_libraries(editor ENet)
  target_link_libraries(editor usrsctp-static)
  target_link_libraries(editor mbedtls)

  target_link_libraries(editor binpack)
  target_link_libraries(editor lua)
  target_link_libraries(editor gl3w)
  target_link_libraries(editor glm)
  target_link_libraries(editor lodepng)
  target_link_libraries(editor resample)
  target_link_libraries(editor vorbis)
  target_link_libraries(editor ogg)
  target_link_libraries(editor freetype)

  target_link_libraries(editor QTUtil)
  target_link_libraries(editor Qt5::Widgets Qt5::OpenGL)

  if(MSVC)
    if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
      target_link_libraries(editor ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\x64\\libEGL.lib)
      target_link_libraries(editor ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\x64\\libGLESv2.lib)
    else()
      target_link_libraries(editor ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\libEGL.lib)
      target_link_libraries(editor ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\libGLESv2.lib)
    endif()

    target_link_libraries(editor Winmm.lib)
    target_link_libraries(editor Version.lib)
    target_link_libraries(editor Imm32.lib)
    target_link_libraries(editor SDL2-static)
  endif()

  if(UNIX AND NOT APPLE)
    target_link_libraries(editor SDL2-static)
  endif()

  if(NOT MSVC)
    target_link_libraries(editor stdc++fs)
    target_link_libraries(editor dl pthread)
  endif()

  add_custom_target(TargetAddCode ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:addcode> ${CMAKE_CURRENT_SOURCE_DIR}/
    DEPENDS addcode
    COMMENT "Copying to Base Directory"
  )
  
  add_custom_target(TargetDistFetch ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DistFetch> ${CMAKE_CURRENT_SOURCE_DIR}/Test/
    DEPENDS DistFetch
    COMMENT "Copying to Test Directory"
  )

  add_custom_target(TargetDistUpload ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DistUpload> ${CMAKE_CURRENT_SOURCE_DIR}/Distribute/
    DEPENDS DistUpload
    COMMENT "Copying to Distribute Directory"
  )
  
  set_target_properties(TargetAddCode PROPERTIES FOLDER Executable)
  set_target_properties(TargetDistFetch PROPERTIES FOLDER Executable)
  set_target_properties(TargetDistUpload PROPERTIES FOLDER Executable)

  set(OUTPUTS ${OUTPUTS} documentserver editor)
endif()

add_dependencies(StormData stormrefl)

add_dependencies(Game Runtime)
add_dependencies(GameShared Game)
add_dependencies(Runtime Foundation)


if(BUILD_CLIENT OR BUILD_TOOLS)
  add_dependencies(Engine Runtime)
  add_dependencies(GameClient Game GameShared)
  add_dependencies(GameClientExe GameShared)
  add_dependencies(LobbyClientConnection Game)
  add_dependencies(LobbyClientConnection Lobby)
endif()

if(BUILD_SERVER OR BUILD_TOOLS)
  add_dependencies(HurricaneDDS StormData)
  add_dependencies(GameServer Game)
  add_dependencies(GameServerExe Game)
  add_dependencies(LobbyServerConnection Game)
  add_dependencies(LobbyServerConnection Lobby)
endif()

if(BUILD_TOOLS)
  add_dependencies(Editor documentserver)
  add_dependencies(Editor Game)
endif()

if(CMAKE_BUILD_TYPE EQUAL "RELWITHDEBUGINFO")
  if(MSVC)
    set_target_properties(GameClient PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(GameServer PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(Game PROPERTIES COMPILE_FLAGS "/Od")
    set_target_properties(GameShared PROPERTIES COMPILE_FLAGS "/Od")
  else()
    set_target_properties(GameClient PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(GameServer PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(Game PROPERTIES COMPILE_FLAGS "-O0")
    set_target_properties(GameShared PROPERTIES COMPILE_FLAGS "-O0")
  endif()
endif()

if(EXPORT_TEST)
  foreach(OUTPUT ${OUTPUTS})

    add_custom_target(Test${OUTPUT} ALL
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${OUTPUT}> ${CMAKE_CURRENT_SOURCE_DIR}/Test/
      DEPENDS ${OUTPUT}
      COMMENT "Copying to Test Directory"
    )
    
    set_target_properties(Test${OUTPUT} PROPERTIES FOLDER Executable)

  endforeach()
endif()

if(EXPORT_DIST)
  foreach(OUTPUT ${OUTPUTS})

    add_custom_target(Dist${OUTPUT} ALL
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${OUTPUT}> ${CMAKE_CURRENT_SOURCE_DIR}/Distribute/Build/
      DEPENDS ${OUTPUT}
      COMMENT "Copying to Dist Directory"
    )
    
    set_target_properties(Dist${OUTPUT} PROPERTIES FOLDER Executable)

  endforeach()
endif()


