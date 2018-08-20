cmake_minimum_required(VERSION 3.0)

include_directories(. ../. .././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_GameClientExe 
            ./Main.cpp
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_GameClientExe 
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_GameClientExe 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(.././External/Windows)
  set(PLATFORM_SRC_GameClientExe 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(.././External/Web)
  set(PLATFORM_SRC_GameClientExe 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(.././External/IOS)
  set(PLATFORM_SRC_GameClientExe 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClientExe 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(.././External/Android)
  set(PLATFORM_SRC_GameClientExe 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClientExe 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE GameClientExe ${GENERIC_REFL_GameClientExe} ${PLATFORM_REFL_GameClientExe})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../. -I.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(GameClientExe ${GENERIC_SRC_GameClientExe} ${PLATFORM_SRC_GameClientExe}
            GameClientExe ${GENERIC_HEADER_GameClientExe} ${PLATFORM_HEADER_GameClientExe})