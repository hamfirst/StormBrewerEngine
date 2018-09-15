cmake_minimum_required(VERSION 3.0)

include_directories(. ../../../. ../../.././External)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DFT2_BUILD_LIBRARY)

if (WEB)
  add_definitions(-D_WEB)
  include_directories(../../.././External/Web)
  set(PLATFORM_SRC_freetype 
            )
elseif (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../../.././External/Windows)
  set(PLATFORM_SRC_freetype 
            )
elseif (APPLE)
  add_definitions(-D_MACOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_freetype 
            )
elseif (UNIX)
  add_definitions(-D_LINUX)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_freetype 
            )
endif()

set(GENERIC_SRC_freetype 
            ./ftdebug.c
            ./autofit/autofit.c
            ./base/ftbase.c
            ./base/ftbbox.c
            ./base/ftbitmap.c
            ./base/ftfntfmt.c
            ./base/ftfstype.c
            ./base/ftgasp.c
            ./base/ftglyph.c
            ./base/ftgxval.c
            ./base/ftinit.c
            ./base/ftlcdfil.c
            ./base/ftmm.c
            ./base/ftotval.c
            ./base/ftpatent.c
            ./base/ftpfr.c
            ./base/ftstroke.c
            ./base/ftsynth.c
            ./base/ftsystem.c
            ./base/fttype1.c
            ./base/ftwinfnt.c
            ./bdf/bdf.c
            ./cache/ftcache.c
            ./cff/cff.c
            ./cid/type1cid.c
            ./gzip/ftgzip.c
            ./lzw/ftlzw.c
            ./pcf/pcf.c
            ./pfr/pfr.c
            ./psaux/psaux.c
            ./pshinter/pshinter.c
            ./psnames/psmodule.c
            ./raster/raster.c
            ./sfnt/sfnt.c
            ./smooth/smooth.c
            ./truetype/truetype.c
            ./type1/type1.c
            ./type42/type42.c
            ./winfonts/winfnt.c
            )
add_library(freetype ${GENERIC_SRC_freetype} ${PLATFORM_SRC_freetype} )