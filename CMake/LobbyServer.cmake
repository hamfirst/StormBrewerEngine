
if(BUILD_SERVER OR BUILD_TOOLS)

    add_subdirectory(Lobby/Lobby)
    set_target_properties(Lobby PROPERTIES FOLDER Lobby)

    add_dependencies(Lobby Game)

    add_executable(LobbyExe Lobby/LobbyMain/MainCombined.cpp)

    target_link_libraries(LobbyExe Lobby)
    target_link_libraries(LobbyExe HurricaneDDS)
    target_link_libraries(LobbyExe StormBootstrap)
    target_link_libraries(LobbyExe StormSocketCPP)
    target_link_libraries(LobbyExe StormData)
    target_link_libraries(LobbyExe LobbyShared)
    target_link_libraries(LobbyExe Runtime)
    target_link_libraries(LobbyExe Foundation)
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
