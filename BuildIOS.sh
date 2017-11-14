#!/bin/bash
cmake -DCMAKE_TOOLCHAIN_FILE=$1\IOSBuild.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DIOS=ON $1
