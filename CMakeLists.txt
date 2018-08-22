cmake_minimum_required(VERSION 3.0)

include(StormBrewerEngine.cmake)

add_subdirectory(Game)

if(BUILD_CLIENT OR BUILD_TOOLS)  
  add_subdirectory(GameClient)
  add_subdirectory(GameClientExe)

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
    include_directories(${PROJECT_SOURCE_DIR} External External/Web)
  
    file(GLOB_RECURSE ClientSrc 
      ${PROJECT_SOURCE_DIR}/GameClientExe/*.cpp
      ${PROJECT_SOURCE_DIR}/GameClient/*.cpp
      ${PROJECT_SOURCE_DIR}/Game/*.cpp
      ${PROJECT_SOURCE_DIR}/Runtime/*.cpp
      ${PROJECT_SOURCE_DIR}/Engine/*.cpp)
     
    add_executable(ClientExe ${ClientSrc})
  else()
    add_executable(ClientExe Dummy.cpp)
  endif()

  if(MSVC)
    target_link_libraries(ClientExe GameClientExe)
    target_link_libraries(ClientExe GameClient)
    target_link_libraries(ClientExe Game)
    target_link_libraries(ClientExe Runtime)
    target_link_libraries(ClientExe Engine)
  elseif(IOS)
    target_link_libraries(ClientExe -Wl,-all_load GameClientExe -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load GameClient -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load Game -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load Runtime -Wl,-noall_load)
    target_link_libraries(ClientExe -Wl,-all_load Engine -Wl,-noall_load)
  elseif(NOT WEB)
    target_link_libraries(ClientExe -Wl,--whole-archive GameClientExe -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive GameClient -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive Game -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive Runtime -Wl,--no-whole-archive)
    target_link_libraries(ClientExe -Wl,--whole-archive Engine -Wl,--no-whole-archive)
  endif()
  
  if(NOT WEB)
    target_link_libraries(ClientExe Runtime)
    target_link_libraries(ClientExe Engine)
  endif()
  
  target_link_libraries(ClientExe Foundation)
  target_link_libraries(ClientExe External)
  target_link_libraries(ClientExe StormNetCustomBindings)
  target_link_libraries(ClientExe StormWebrtcClientAPI)
  target_link_libraries(ClientExe StormExpr)
  target_link_libraries(ClientExe StormNet)
  target_link_libraries(ClientExe StormData)
  target_link_libraries(ClientExe binpack)
  target_link_libraries(ClientExe lua)
  target_link_libraries(ClientExe gl3w)
  target_link_libraries(ClientExe LodePNG)
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
      target_link_libraries(ClientExe SDL2)
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
        target_link_libraries(ClientExe SDL)
      endif()

      target_link_libraries(ClientExe stdc++fs)
      target_link_libraries(ClientExe dl pthread)
    endif()
  endif()
endif()

if(BUILD_SERVER)
  add_subdirectory(GameServer)
  add_subdirectory(GameServerExe)

  add_executable(ServerExe Dummy.cpp)
  
  if(MSVC)
    target_link_libraries(ServerExe GameServerExe)
    target_link_libraries(ServerExe GameServer)
    target_link_libraries(ServerExe Game)
    target_link_libraries(ServerExe Runtime)
    target_link_libraries(ServerExe Server)  
  else()
    target_link_libraries(ServerExe -Wl,--whole-archive GameServerExe -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive GameServer -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive Game -Wl,--no-whole-archive)
    target_link_libraries(ServerExe -Wl,--whole-archive Runtime -Wl,--no-whole-archive)
  endif()

  target_link_libraries(ServerExe EngineStubs)
  target_link_libraries(ServerExe Foundation)
  target_link_libraries(ServerExe binpack)
  target_link_libraries(ServerExe lua)
  target_link_libraries(ServerExe StormNetCustomBindings)
  target_link_libraries(ServerExe StormNetBindingsEnet)
  target_link_libraries(ServerExe StormNet)
  target_link_libraries(ServerExe StormData)
  target_link_libraries(ServerExe External)
  target_link_libraries(ServerExe StormWebrtc)
  target_link_libraries(ServerExe StormWebrtcServerAPI)
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
endif()

if(BUILD_TOOLS)
  add_executable(generatecmake GenerateCMake/Main.cpp)  
  target_link_libraries(generatecmake stdc++fs)

  add_executable(stormrefl StormRefl/main.cpp  StormRefl/StaticLibs.cpp StormRefl/StormReflOutput.cpp)  
  target_include_directories(stormrefl PUBLIC . External)
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
    clang
  )

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
    LLVMDebugInfoDWARF
    LLVMBinaryFormat
    LLVMProfileData
  )

  target_compile_options(stormrefl PUBLIC -fno-rtti)
  target_link_libraries(stormrefl -Wl,--whole-archive pthread -Wl,--no-whole-archive)
  target_link_libraries(stormrefl stdc++fs z rt m c dl)

  install(TARGETS generatecmake stormrefl DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

  add_executable(documentserver Dummy.cpp)
  target_link_libraries(documentserver DocumentServer Foundation StormSocketCPP StormData asio mbedtls) 
  target_link_libraries(documentserver -Wl,--whole-archive pthread -Wl,--no-whole-archive)
  target_link_libraries(documentserver GL GLU stdc++fs z rt m c dl)

  find_package(Qt5Widgets CONFIG REQUIRED)
  find_package(Qt5OpenGL CONFIG REQUIRED)

  add_executable(editor Dummy.cpp)
  target_link_libraries(editor Editor GameClient GameServer Game Engine Runtime Foundation StormSocketCPP StormData QTUtil SDL2 asio mbedtls) 
  target_link_libraries(editor -Wl,--whole-archive pthread -Wl,--no-whole-archive)
  target_link_libraries(editor Qt5::Widgets Qt5::OpenGL)
  target_link_libraries(editor stdc++fs z rt m c dl)

  install(TARGETS documentserver editor DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Test)

endif()

