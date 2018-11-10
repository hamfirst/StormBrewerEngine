cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_binpack 
            GuillotineBinPack.cpp
            MaxRectsBinPack.cpp
            Rect.cpp
            ShelfBinPack.cpp
            ShelfNextFitBinPack.cpp
            SkylineBinPack.cpp
            )

set(GENERIC_HEADER_binpack 
            GuillotineBinPack.h
            MaxRectsBinPack.h
            Rect.h
            ShelfBinPack.h
            ShelfNextFitBinPack.h
            SkylineBinPack.h
            )

add_library(binpack STATIC ${GENERIC_SRC_binpack} ${GENERIC_HEADER_binpack})

