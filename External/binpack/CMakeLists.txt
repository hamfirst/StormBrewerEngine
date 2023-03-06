cmake_minimum_required(VERSION 3.20.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

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
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_binpack} ${GENERIC_HEADER_binpack})

