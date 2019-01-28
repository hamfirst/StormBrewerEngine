#!/bin/bash

cd $PROJECT_DIR
mkdir DistServer
mkdir DistServer/External
mkdir DistServer/StormTech

cp -r Tools/DistTools DistServer/DistTools
cp -r StormTech/StormSockets DistServer/StormTech
cp -r StormTech/StormRefl DistServer/StormRefl
cp -r External/asio DistServer/External/asio
cp -r External/miniz-cpp DistServer/External/miniz-cpp
cp -r External/gsl DistServer/External/gsl
cp -r External/hash DistServer/External/hash
cp -r External/mbedtls DistServer/External/mbedtls
cp -r External/optional DistServer/External/optional
cp -r External/sb DistServer/External/sb

cp ProjectSettings/ProjectCredentials.txt DistServer/ProjectCredentials.txt

mv DistServer/DistTools/BuildServerCMake.txt DistServer/CMakeLists.txt

