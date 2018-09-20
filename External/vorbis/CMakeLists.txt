cmake_minimum_required(VERSION 3.0)

include_directories(. ../../. ../.././External)
set(CMAKE_CXX_STANDARD 17)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../.././External/Web)
  set(PLATFORM_SRC_vorbis 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../.././External/Windows)
  set(PLATFORM_SRC_vorbis 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_vorbis 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_vorbis 
            )
endif()

set(GENERIC_SRC_vorbis 
            ./analysis.c
            ./bitrate.c
            ./block.c
            ./codebook.c
            ./envelope.c
            ./floor0.c
            ./floor1.c
            ./info.c
            ./lookup.c
            ./lpc.c
            ./lsp.c
            ./mapping0.c
            ./mdct.c
            ./psy.c
            ./registry.c
            ./res0.c
            ./sharedbook.c
            ./smallft.c
            ./synthesis.c
            ./vorbisenc.c
            ./vorbisfile.c
            ./window.c
            )
add_library(vorbis STATIC ${GENERIC_SRC_vorbis} ${PLATFORM_SRC_vorbis} )