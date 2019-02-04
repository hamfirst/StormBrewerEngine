#!/bin/bash

cd $PROJECT_DIR/Distribute
rm -rf Build
mkdir Build

cd $PROJECT_DIR
mkdir build-dist
cd build-dist
mkdir tools

source $PROJECT_DIR/ProjectEnv.txt

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TOOLS=ON -DSDL_SHARED=OFF -DSDL_STATIC=ON -DCMAKE_PREFIX_HEADER=$QT_DIR -DCLANG_HEADER_PATH=$CLANG_HEADER_PATH $PROJECT_DIR
make -j4
if [[ $? -eq 0 ]]; then
  exit 1
fi

cd $PROJECT_DIR/Distribute
DistUpload Build

