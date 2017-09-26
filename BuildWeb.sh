#!/bin/bash
cmake -DCMAKE_TOOLCHAIN_FILE=$1\EmscriptenBuild.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DWEB=ON $1
