
include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/StormTech
        ${PROJECT_SOURCE_DIR}/External
        ${PROJECT_SOURCE_DIR}/Tools
        ${PROJECT_SOURCE_DIR}/Shared
        ${PROJECT_SOURCE_DIR}/Project
        ${PROJECT_SOURCE_DIR}/Lobby)

include(CMake/Platform.cmake)
include(CMake/External.cmake)
include(CMake/StormTech.cmake)
include(CMake/Shared.cmake)
