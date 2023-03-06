
if(BUILD_TOOLS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/Wizards/TemplateLib")
    add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/DistTools")
    add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/Wizards/addcode")
    add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/DocumentServer")
    add_subdirectory("${PROJECT_SOURCE_DIR}/Tools/QTUtil")

    set_target_properties(TemplateLib PROPERTIES FOLDER Tools)
    set_target_properties(DistFetchLib PROPERTIES FOLDER Tools)
    set_target_properties(DistServerLib PROPERTIES FOLDER Tools)
    set_target_properties(DistUploadLib PROPERTIES FOLDER Tools)
    set_target_properties(DistFetcher PROPERTIES FOLDER Tools)
    set_target_properties(DocumentServer PROPERTIES FOLDER Tools)
    set_target_properties(QTUtil PROPERTIES FOLDER Tools)

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

endif()
