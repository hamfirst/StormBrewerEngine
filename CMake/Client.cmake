
if(BUILD_CLIENT OR BUILD_TOOLS)
    add_subdirectory(Project/GameClient)
    add_subdirectory(Project/GameClientExe)

    set_target_properties(GameClient PROPERTIES FOLDER Project)
    set_target_properties(GameClientExe PROPERTIES FOLDER Project)

    add_dependencies(GameClient Game GameShared)
    add_dependencies(GameClientExe GameShared)
    add_dependencies(GameClientExe Lobby)

    add_subdirectory(Lobby/LobbyClientConnection)
    set_target_properties(LobbyClientConnection PROPERTIES FOLDER Project)

    add_dependencies(LobbyClientConnection Game)
    add_dependencies(LobbyClientConnection Lobby)

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

        set_target_properties(ClientExe PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:GameClientExe.lib /WHOLEARCHIVE:GameClient.lib /WHOLEARCHIVE:Game.lib /WHOLEARCHIVE:GameShared.lib /WHOLEARCHIVE:Runtime.lib /WHOLEARCHIVE:Engine.lib")
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
    target_link_libraries(ClientExe LobbyShared)
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
                target_link_libraries(ClientExe SDL2::SDL2)
            endif()

            target_link_libraries(ClientExe stdc++fs)
            target_link_libraries(ClientExe dl pthread)
        endif()
    endif()

    set_target_properties(ClientExe PROPERTIES FOLDER Executable)
    set(OUTPUTS ${OUTPUTS} ClientExe)
endif()
