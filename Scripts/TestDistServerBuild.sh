#!/bin/bash

cd $PROJECT_DIR
rm -rf DistServer
Scripts/PackageDistServer.sh

cd DistServer
cmake . -DCMAKE_BUILD_TYPE=Debug
make

cd $PROJECT_DIR/DistServer
./DistServer

