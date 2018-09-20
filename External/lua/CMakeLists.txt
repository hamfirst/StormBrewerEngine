cmake_minimum_required(VERSION 3.0)

include_directories(. ../../. ../.././External)
set(CMAKE_CXX_STANDARD 17)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../.././External/Web)
  set(PLATFORM_SRC_lua 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../.././External/Windows)
  set(PLATFORM_SRC_lua 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_lua 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_lua 
            )
endif()

set(GENERIC_SRC_lua 
            ./lapi.c
            ./lauxlib.c
            ./lbaselib.c
            ./lbitlib.c
            ./lcode.c
            ./lcorolib.c
            ./lctype.c
            ./ldblib.c
            ./ldebug.c
            ./ldo.c
            ./ldump.c
            ./lfunc.c
            ./lgc.c
            ./linit.c
            ./liolib.c
            ./llex.c
            ./lmathlib.c
            ./lmem.c
            ./loadlib.c
            ./lobject.c
            ./lopcodes.c
            ./lparser.c
            ./lstate.c
            ./lstring.c
            ./lstrlib.c
            ./ltable.c
            ./ltablib.c
            ./ltm.c
            ./lundump.c
            ./lutf8lib.c
            ./lvm.c
            ./lzio.c
            )
add_library(lua STATIC ${GENERIC_SRC_lua} ${PLATFORM_SRC_lua} )