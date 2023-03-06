
if(BUILD_TOOLS)
    set(LLVM_DIR ${LLVM_BUILD_PATH}/lib/cmake/llvm/)
    set(Clang_DIR ${LLVM_BUILD_PATH}/lib/cmake/clang/)

    find_package(LLVM  REQUIRED CONFIG)
    find_package(Clang REQUIRED CONFIG)

    add_executable(stormrefl StormTech/StormRefl/main.cpp StormTech/StormRefl/StormReflOutput.cpp)
    llvm_config(stormrefl)
    set_target_properties(stormrefl PROPERTIES FOLDER StormTech)

    target_include_directories(stormrefl PRIVATE ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
    target_link_directories(stormrefl PRIVATE ${LLVM_LIBRARY_DIRS} ${CLANG_LIBRARY_DIRS})

    target_link_libraries(stormrefl PRIVATE
            clangFrontend
            clangSerialization
            clangDriver
            clangParse
            clangSema
            clangAnalysis
            clangAST
            clangASTMatchers
            clangBasic
            clangEdit
            clangLex
            clangTooling
            clang
            )

    if(MSVC)
        target_compile_options(stormrefl PRIVATE "/MD" "/O2")
        target_link_libraries(stormrefl PRIVATE Mincore.lib)
        STRING (REGEX REPLACE "[/|-]RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    else()
        target_compile_options(stormrefl PUBLIC "-fno-rtti" "-O3")
        target_link_libraries(stormrefl PRIVATE -Wl,--whole-archive pthread -Wl,--no-whole-archive)
        target_link_libraries(stormrefl PRIVATE ncurses stdc++fs z rt m c dl)
    endif()

endif()

if(NOT WEB)
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/HurricaneDDS")
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormSockets")
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormBootstrap")
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtc")
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtcServerAPI")
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtcClientAPI")

    set_target_properties(HurricaneDDS PROPERTIES FOLDER StormTech)
    set_target_properties(StormSocketCPP PROPERTIES FOLDER StormTech)
    set_target_properties(StormBootstrap PROPERTIES FOLDER StormTech)
    set_target_properties(StormWebrtc PROPERTIES FOLDER StormTech)
    set_target_properties(StormWebrtcServerAPI PROPERTIES FOLDER StormTech)
    set_target_properties(StormWebrtcClientAPI PROPERTIES FOLDER StormTech)

    add_dependencies(HurricaneDDS StormData)
endif()

if(WEB)
    add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormWebrtcClientAPI")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormData")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormNet")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormNetCustomBindings")
add_subdirectory("${PROJECT_SOURCE_DIR}/StormTech/StormExpr")

set_target_properties(StormData PROPERTIES FOLDER StormTech)
set_target_properties(StormNet PROPERTIES FOLDER StormTech)
set_target_properties(StormNetCustomBindings PROPERTIES FOLDER StormTech)
set_target_properties(StormNetBindingsEnet PROPERTIES FOLDER StormTech)
set_target_properties(StormExpr PROPERTIES FOLDER StormTech)

if(BUILD_TOOLS)
    add_dependencies(StormData stormrefl)
endif()


