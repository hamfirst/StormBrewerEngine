#!/bin/bash

cd $PROJECT_DIR
rm -rf DistServer

echo "Creating dist server directory"
CreateDistServerBuild.sh

cd $PROJECT_DIR
if [ -d DistServer ]; then
  cd $PROJECT_DIR/DistServer
  cmake . -DCMAKE_BUILD_TYPE=Debug
  make

  if [ $? -eq 0 ]; then
    ./DistServer
  fi
else
  echo "CreateDistServerBuild failed"
fi
