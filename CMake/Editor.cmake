
if(BUILD_TOOLS)
    add_executable(DocumentServerExe Dummy.cpp)
    set_target_properties(DocumentServerExe PROPERTIES FOLDER Executable)

    target_link_libraries(DocumentServerExe DocumentServer Foundation StormSocketCPP StormData git2 asio mbedtls binpack)

    if(NOT MSVC)
        target_link_libraries(DocumentServerExe -Wl,--whole-archive pthread -Wl,--no-whole-archive)
        target_link_libraries(DocumentServerExe GL GLU stdc++fs z rt m c dl)
    endif()

    if(ENABLE_PERFORCE)
        target_compile_definitions(DocumentServer PRIVATE -DENABLE_PERFORCE)

        if(MSVC)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/windows/libclient.lib)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/windows/librpc.lib)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/windows/libsupp.lib)
        elseif(APPLE)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/mac/libclient.a)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/mac/librpc.a)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/mac/libsupp.a)
        else()
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/linux/libclient.a)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/linux/librpc.a)
            target_link_libraries(DocumentServerExe ${CMAKE_CURRENT_SOURCE_DIR}/External/p4/lib/linux/libsupp.a)

            find_package(OpenSSL 1.0.2 REQUIRED)
            target_link_libraries(DocumentServerExe ${OPENSSL_LIBRARIES})
        endif()
    endif()


    add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/Editor")

    set_target_properties(Editor PROPERTIES FOLDER Editor)

    add_dependencies(Editor DocumentServerExe)
    add_dependencies(Editor Game)

    add_executable(EditorExe Dummy.cpp)

    find_package(Qt5Widgets CONFIG REQUIRED)
    find_package(Qt5OpenGL CONFIG REQUIRED)

    set_target_properties(EditorExe PROPERTIES FOLDER Executable)

    if(MSVC)
        target_link_libraries(EditorExe Editor)
        target_link_libraries(EditorExe GameClient)
        target_link_libraries(EditorExe GameServer)
        target_link_libraries(EditorExe Game)
        target_link_libraries(EditorExe GameShared)
        target_link_libraries(EditorExe LobbyShared)
        target_link_libraries(EditorExe Runtime)
        target_link_libraries(EditorExe Engine)

        set_target_properties(EditorExe PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:Editor.lib /WHOLEARCHIVE:GameClient.lib /WHOLEARCHIVE:GameServer.lib /WHOLEARCHIVE:Game.lib /WHOLEARCHIVE:Runtime.lib /WHOLEARCHIVE:Engine.lib")
    elseif(NOT WEB)
        target_link_libraries(EditorExe -Wl,--whole-archive Editor -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive GameClient -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive GameServer -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive Game -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive GameShared -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive LobbyShared -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive Runtime -Wl,--no-whole-archive)
        target_link_libraries(EditorExe -Wl,--whole-archive Engine -Wl,--no-whole-archive)
    endif()

    target_link_libraries(EditorExe LobbyServerConnection)
    target_link_libraries(EditorExe LobbyClientConnection)
    target_link_libraries(EditorExe Foundation)
    target_link_libraries(EditorExe StormNetCustomBindings)
    target_link_libraries(EditorExe StormNetBindingsEnet)
    target_link_libraries(EditorExe StormNet)
    target_link_libraries(EditorExe StormExpr)
    target_link_libraries(EditorExe StormData)
    target_link_libraries(EditorExe DistFetcher)
    target_link_libraries(EditorExe StormSocketCPP)

    target_link_libraries(EditorExe StormWebrtcServerAPI)
    target_link_libraries(EditorExe StormWebrtcClientAPI)
    target_link_libraries(EditorExe StormWebrtc)
    target_link_libraries(EditorExe asio)
    target_link_libraries(EditorExe ENet)
    target_link_libraries(EditorExe usrsctp-static)
    target_link_libraries(EditorExe mbedtls)

    target_link_libraries(EditorExe binpack)
    target_link_libraries(EditorExe lua)
    target_link_libraries(EditorExe gl3w)
    target_link_libraries(EditorExe glm)
    target_link_libraries(EditorExe lodepng)
    target_link_libraries(EditorExe resample)
    target_link_libraries(EditorExe vorbis)
    target_link_libraries(EditorExe ogg)
    target_link_libraries(EditorExe freetype)

    target_link_libraries(EditorExe QTUtil)
    target_link_libraries(EditorExe Qt5::Widgets Qt5::OpenGL)

    if(MSVC)
        if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
            target_link_libraries(EditorExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\x64\\libEGL.lib)
            target_link_libraries(EditorExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\x64\\libGLESv2.lib)
        else()
            target_link_libraries(EditorExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\libEGL.lib)
            target_link_libraries(EditorExe ${PROJECT_SOURCE_DIR}\\External\\Windows\\angle\\libGLESv2.lib)
        endif()

        target_link_libraries(EditorExe Winmm.lib)
        target_link_libraries(EditorExe Version.lib)
        target_link_libraries(EditorExe Imm32.lib)
        target_link_libraries(EditorExe SDL2-static)
    endif()

    if(UNIX AND NOT APPLE)
        target_link_libraries(EditorExe SDL2::SDL2)
    endif()

    if(NOT MSVC)
        target_link_libraries(EditorExe stdc++fs)
        target_link_libraries(EditorExe dl pthread)
    endif()

    set(OUTPUTS ${OUTPUTS} DocumentServerExe EditorExe)
endif()

