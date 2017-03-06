cmake_minimum_required(VERSION 2.6)

project(vorbis)
 
include_directories(${PROJECT_SOURCE_DIR}/..)
 
add_library(vorbis STATIC
    analysis.c
    bitrate.c
    block.c
    codebook.c
    envelope.c
    floor0.c
    floor1.c
    info.c
    lookup.c
    lpc.c
    lsp.c
    mapping0.c
    mdct.c
    registry.c
    res0.c
    sharedbook.c
    smallft.c
    sythesis.c
    vorbisenc.c
    vorbisfile.c
    window.c
    )
