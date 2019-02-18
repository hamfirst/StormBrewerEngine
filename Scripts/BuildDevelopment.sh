#!/bin/bash

CMD_LINE="-DBUILD_TOOLS=ON -DSDL_SHARED=OFF -DSDL_STATIC=ON -DCMAKE_PREFIX_PATH=$QT_DIR -DCLANG_HEADER_PATH=$CLANG_HEADER_PATH $EXTRA_CMAKE_OPTIONS"

for arg in "$@"
do
  if [ $arg == "--cmd-line" ]
  then
    echo $CMD_LINE
    exit
  fi
done

if [ $# != 1 ]
then
  echo "Invalid number of args"
fi

cd $PROJECT_DIR
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug $CMD_LINE $PROJECT_DIR
make
cd $PROJECT_DIR

