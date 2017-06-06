cmake_minimum_required(VERSION 3.0)

include(StormBrewerEngine.cmake)

add_subdirectory(Game)
add_subdirectory(GameClient)
add_subdirectory(GameClientExe)

add_executable(ClientExe Dummy.cpp)
target_link_libraries(ClientExe GameClientExe)
target_link_libraries(ClientExe GameClient)
target_link_libraries(ClientExe Game)
target_link_libraries(ClientExe Shared)
target_link_libraries(ClientExe Runtime)
target_link_libraries(ClientExe Engine)
target_link_libraries(ClientExe Foundation)
target_link_libraries(ClientExe binpack)
target_link_libraries(ClientExe lua)
target_link_libraries(ClientExe gl3w)
target_link_libraries(ClientExe upng)
target_link_libraries(ClientExe vorbis)
target_link_libraries(ClientExe ogg)
target_link_libraries(ClientExe freetype)
target_link_libraries(ClientExe StormNet)
target_link_libraries(ClientExe StormData)
target_link_libraries(ClientExe External)

if(WEB)

  target_link_libraries(ClientExe Runtime)
  target_link_libraries(ClientExe Engine)

else()
  
  target_link_libraries(ClientExe asio)
  target_link_libraries(ClientExe ENet)
  target_link_libraries(ClientExe SDL)
  
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
  endif()

endif()
