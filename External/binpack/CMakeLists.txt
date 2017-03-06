

project(BinPack)
 
include_directories(${PROJECT_SOURCE_DIR})
 
add_library(BinPack STATIC
        GuillotineBinPack.cpp
        MaxRectsBinPack.cpp
        Rect.cpp
        ShelfBinPack.cpp
        ShelfNextFitBinPack.cpp
        SkylineBinPack.cpp
    )

