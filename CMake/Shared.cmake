
add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/Foundation")
add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/Runtime")

set_target_properties(Foundation PROPERTIES FOLDER Shared)
set_target_properties(Runtime PROPERTIES FOLDER Shared)

if(BUILD_CLIENT OR BUILD_TOOLS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/Engine")
    set_target_properties(Engine PROPERTIES FOLDER Shared)

    add_dependencies(Runtime Foundation)
    add_dependencies(Engine Runtime)
endif()

if(NOT WEB)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Shared/EngineStubs")
    set_target_properties(EngineStubs PROPERTIES FOLDER Shared)
endif()

add_subdirectory(Lobby/LobbyShared)
set_target_properties(LobbyShared PROPERTIES FOLDER Shared)

