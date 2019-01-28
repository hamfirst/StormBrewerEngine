#!/bin/bash

cd $PROJECT_DIR
rm -rf DistServer
Scripts/PackageDistServer.sh

cd DistServer
cmake .
make

cd $PROJECT_DIR

