cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_binpack 
            GuillotineBinPack.cpp
            SkylineBinPack.cpp
            ShelfNextFitBinPack.cpp
            ShelfBinPack.cpp
            MaxRectsBinPack.cpp
            Rect.cpp
            )

set(GENERIC_HEADER_binpack 
            GuillotineBinPack.h
            ShelfNextFitBinPack.h
            Rect.h
            MaxRectsBinPack.h
            SkylineBinPack.h
            ShelfBinPack.h
            )

add_library(binpack STATIC ${GENERIC_SRC_binpack} ${GENERIC_HEADER_binpack})

