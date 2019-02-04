#!/bin/bash

cd $PROJECT_DIR/Distribute
rm -rf Build
mkdir Build

cd $PROJECT_DIR
mkdir build-dist
cd build-dist
mkdir tools

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TOOLS=ON -DSDL_SHARED=OFF -DSDL_STATIC=ON -DCLANG_HEADER_PATH=. -build $PROJECT_DIR
make -j4
if [[ $? -eq 0 ]]; then
  exit 1
fi

cd $PROJECT_DIR/Distribute
DistUpload Build

