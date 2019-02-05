#!/bin/bash

cd $PROJECT_DIR/Distribute
rm -rf Build
mkdir Build

cd $PROJECT_DIR
mkdir -p build-dist
cd build-dist
mkdir -p tools
cd tools

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TOOLS=ON -DEXPORT_DIST=ON -DEXPORT_TEST=OFF -DSDL_SHARED=OFF -DSDL_STATIC=ON -DCMAKE_PREFIX_HEADER=$QT_DIR -DCLANG_HEADER_PATH=$CLANG_HEADER_PATH $PROJECT_DIR
make -j4
if [[ $? -ne 0 ]]; then
  exit 1
fi

cd $PROJECT_DIR/Distribute
./DistUpload Build

