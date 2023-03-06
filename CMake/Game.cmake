
add_subdirectory(Project/Game)
add_subdirectory(Project/GameShared)

set_target_properties(Game PROPERTIES FOLDER Project)
set_target_properties(GameShared PROPERTIES FOLDER Project)

add_dependencies(Game Runtime)
add_dependencies(GameShared Game)
